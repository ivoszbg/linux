// SPDX-License-Identifier: GPL-2.0-or-later
/*
 * Samsung S2MU005 PMIC Integrated Fuel Gauge Driver
 *
 * Copyright (C) 2015 Samsung Electronics
 * Copyright (C) 2023 Yassine Oudjana <y.oudjana@protonmail.com>
 *
 */

#include <linux/i2c.h>
#include <linux/irq.h>
#include <linux/power_supply.h>
#include <linux/regmap.h>

#define S2MU005_REG_STATUS		0x00
#define S2MU005_REG_IRQ			0x02
#define S2MU005_REG_RVBAT		0x04
#define S2MU005_REG_RCUR_CC		0x06
#define S2MU005_REG_RSOC		0x08
#define S2MU005_REG_MONOUT		0x0a
#define S2MU005_REG_MONOUT_SEL		0x0c
#define S2MU005_REG_RBATCAP		0x0e
#define S2MU005_REG_RZADJ		0x12
#define S2MU005_REG_RBATZ0		0x16
#define S2MU005_REG_RBATZ1		0x18
#define S2MU005_REG_IRQ_LVL		0x1a
#define S2MU005_REG_START		0x1e
#define S2MU005_REG_COFFSET		0x5a

#define S2MU005_MONOUT_TEMP		0x10
#define S2MU005_MONOUT_AVGCUR		0x26

#define S2MU005_REG_IRQ_LVL_ALERT_SOC	BIT(4)

struct s2mu005_fg {
	struct device *dev;
	struct regmap *regmap;
	struct power_supply *psy;
};

static const struct regmap_config s2mu005_fg_regmap_config = {
	.reg_bits = 8,
	.reg_stride = 2,
	.val_bits = 16,
};

static irqreturn_t s2mu005_handle_irq(int irq, void *data)
{
	struct s2mu005_fg *fg = data;

	power_supply_changed(fg->psy);
	
	dev_info(fg->dev, "irq\n");

	return IRQ_HANDLED;
}

static int s2mu005_fg_get_voltage(struct s2mu005_fg *fg, int *value)
{
	u16 reg;
	int ret;

	ret = regmap_raw_read(fg->regmap, S2MU005_REG_RVBAT, &reg, sizeof(reg));
	if (ret)
		return ret;

	*value = ((unsigned long)reg * 1000000) >> 13;

	return 0;
}

static int s2mu005_fg_get_current(struct s2mu005_fg *fg, int *value)
{
	s16 reg;
	int ret;

	ret = regmap_raw_read(fg->regmap, S2MU005_REG_RCUR_CC, &reg, sizeof(reg));
	if (ret)
		return ret;

	*value = ((long)reg * 1000000) >> 12;

	return 0;
}

static int s2mu005_fg_get_capacity(struct s2mu005_fg *fg, int *value)
{
	s16 reg;
	int ret;

	ret = regmap_raw_read(fg->regmap, S2MU005_REG_RSOC, &reg, sizeof(reg));
	if (ret)
		return ret;

	*value = (reg * 100) >> 14;

	return 0;
}

static int s2mu005_fg_get_temperature(struct s2mu005_fg *fg, int *value)
{
	s16 reg;
	int ret;

	ret = regmap_raw_read(fg->regmap, S2MU005_REG_MONOUT, &reg, sizeof(reg));
	if (ret)
		return ret;

	*value = (reg * 10) >> 8;

	return 0;
}

static const enum power_supply_property s2mu005_fg_properties[] = {
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_TEMP,
};

static int s2mu005_fg_get_property(struct power_supply *psy,
				   enum power_supply_property psp,
				   union power_supply_propval *val)
{
	struct s2mu005_fg *fg = power_supply_get_drvdata(psy);
	int ret = 0;

	switch(psp) {
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = s2mu005_fg_get_voltage(fg, &val->intval);
		break;
	case POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = s2mu005_fg_get_current(fg, &val->intval);
		break;
	case POWER_SUPPLY_PROP_CAPACITY:
		ret = s2mu005_fg_get_capacity(fg, &val->intval);
		break;
	case POWER_SUPPLY_PROP_TEMP:
		ret = s2mu005_fg_get_temperature(fg, &val->intval);
		break;
	default:
		return -EINVAL;
	}

	return ret;
}

static const struct power_supply_desc s2mu005_fg_desc = {
	.name = "s2mu005-fg",
	.type = POWER_SUPPLY_TYPE_BATTERY,
	.properties = s2mu005_fg_properties,
	.num_properties = ARRAY_SIZE(s2mu005_fg_properties),
	.get_property = s2mu005_fg_get_property,
};

static int s2mu005_fg_i2c_probe(struct i2c_client *client)
{
	struct s2mu005_fg *fg;
	struct power_supply_config psy_cfg = {};

	fg = devm_kzalloc(&client->dev, sizeof(*fg), GFP_KERNEL);
	if (!fg)
		return -ENOMEM;

	fg->regmap = devm_regmap_init_i2c(client, &s2mu005_fg_regmap_config);
	if (IS_ERR(fg->regmap))
		return PTR_ERR(fg->regmap);

	fg->dev = &client->dev;

	psy_cfg.drv_data = fg;
	psy_cfg.of_node = fg->dev->of_node;

	i2c_set_clientdata(client, fg);

	fg->psy = devm_power_supply_register(fg->dev, &s2mu005_fg_desc, &psy_cfg);
	if (IS_ERR(fg->psy))
		return PTR_ERR(fg->psy);

	return devm_request_threaded_irq(fg->dev, client->irq, NULL,
					s2mu005_handle_irq, IRQF_ONESHOT,
					s2mu005_fg_desc.name, fg);

	return 0;
}

static const struct of_device_id s2mu005_fg_i2c_of_match_table[] = {
	{ .compatible = "samsung,s2mu005-fg" },
	{ },
};
MODULE_DEVICE_TABLE(of, s2mu005_fg_i2c_of_match_table);

static struct i2c_driver s2mu005_fg_i2c_driver = {
	.driver = {
		.name = "s2mu005-fg",
		.of_match_table = of_match_ptr(s2mu005_fg_i2c_of_match_table),
	},
	.probe = s2mu005_fg_i2c_probe,
};
module_i2c_driver(s2mu005_fg_i2c_driver);

MODULE_AUTHOR("Yassine Oudjana <y.oudjana@protonmail.com>");
MODULE_DESCRIPTION("Samsung S2MU005 PMIC fuel gauge driver");
MODULE_LICENSE("GPL");

