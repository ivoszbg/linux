/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Samsung Exynos DTS pinctrl constants
 *
 * Copyright (c) 2016 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 * Copyright (c) 2022 Linaro Ltd
 * Author: Krzysztof Kozlowski <krzk@kernel.org>
 */

#ifndef __DTS_ARM_SAMSUNG_EXYNOS_PINCTRL_H__
#define __DTS_ARM_SAMSUNG_EXYNOS_PINCTRL_H__

#define EXYNOS_PIN_PULL_NONE		0
#define EXYNOS_PIN_PULL_DOWN		1
#define EXYNOS_PIN_PULL_UP		3

/* Pin function in power down mode */
#define EXYNOS_PIN_PDN_OUT0		0
#define EXYNOS_PIN_PDN_OUT1		1
#define EXYNOS_PIN_PDN_INPUT		2
#define EXYNOS_PIN_PDN_PREV		3

/* Drive strengths for Exynos3250, Exynos4 (all) and Exynos5250 */
#define EXYNOS4_PIN_DRV_LV1		0
#define EXYNOS4_PIN_DRV_LV2		2
#define EXYNOS4_PIN_DRV_LV3		1
#define EXYNOS4_PIN_DRV_LV4		3

/* Drive strengths for Exynos5260 */
#define EXYNOS5260_PIN_DRV_LV1		0
#define EXYNOS5260_PIN_DRV_LV2		1
#define EXYNOS5260_PIN_DRV_LV4		2
#define EXYNOS5260_PIN_DRV_LV6		3

/*
 * Drive strengths for Exynos5410, Exynos542x, Exynos5800 and Exynos850 (except
 * GPIO_HSI block)
 */
#define EXYNOS5420_PIN_DRV_LV1		0
#define EXYNOS5420_PIN_DRV_LV2		1
#define EXYNOS5420_PIN_DRV_LV3		2
#define EXYNOS5420_PIN_DRV_LV4		3

/* Drive strengths for Exynos3475 */
#define EXYNOS3475_PIN_DRV_FAST_SR1	0
#define EXYNOS3475_PIN_DRV_FAST_SR2	1
#define EXYNOS3475_PIN_DRV_FAST_SR3	2
#define EXYNOS3475_PIN_DRV_FAST_SR4	3
#define EXYNOS3475_PIN_DRV_FAST_SR5	4
#define EXYNOS3475_PIN_DRV_FAST_SR6	5
#define EXYNOS3475_PIN_DRV_SLOW_SR1	8
#define EXYNOS3475_PIN_DRV_SLOW_SR2	9
#define EXYNOS3475_PIN_DRV_SLOW_SR3	0xa
#define EXYNOS3475_PIN_DRV_SLOW_SR4	0xb
#define EXYNOS3475_PIN_DRV_SLOW_SR5	0xc
#define EXYNOS3475_PIN_DRV_SLOW_SR6	0xf

/* Drive strengths for Exynos850 GPIO_HSI block */
#define EXYNOS850_HSI_PIN_DRV_LV1	0	/* 1x   */
#define EXYNOS850_HSI_PIN_DRV_LV1_5	1	/* 1.5x */
#define EXYNOS850_HSI_PIN_DRV_LV2	2	/* 2x   */
#define EXYNOS850_HSI_PIN_DRV_LV2_5	3	/* 2.5x */
#define EXYNOS850_HSI_PIN_DRV_LV3	4	/* 3x   */
#define EXYNOS850_HSI_PIN_DRV_LV4	5	/* 4x   */

#define EXYNOS_PIN_FUNC_INPUT		0
#define EXYNOS_PIN_FUNC_OUTPUT		1
#define EXYNOS_PIN_FUNC_2		2
#define EXYNOS_PIN_FUNC_3		3
#define EXYNOS_PIN_FUNC_4		4
#define EXYNOS_PIN_FUNC_5		5
#define EXYNOS_PIN_FUNC_6		6
#define EXYNOS_PIN_FUNC_EINT		0xf
#define EXYNOS_PIN_FUNC_F		EXYNOS_PIN_FUNC_EINT

#endif /* __DTS_ARM_SAMSUNG_EXYNOS_PINCTRL_H__ */
