// SPDX-License-Identifier: GPL-2.0-only
/*
 * Copyright (C) 2022 Ivaylo Ivanov <ivo.ivanov.ivanov1@gmail.com>
 * Author: Ivaylo Ivanov <ivo.ivanov.ivanov1@gmail.com>
 *
 * Common Clock Framework support for Exynos3475 SoC.
 */

#include <linux/clk-provider.h>
#include <linux/of.h>

#include "clk.h"
#include <dt-bindings/clock/exynos3475.h>

/* Register Offset definitions for CMU_BUS0 (0x11800000) */
#define CLK_CON_MUX_ACLK_BUS0_333_USER			0x0200
#define CLK_CON_DIV_PCLK_BUS0_83			0x0400

static const unsigned long bus0_clk_regs[] __initconst = {
	CLK_CON_MUX_ACLK_BUS0_333_USER,
	CLK_CON_DIV_PCLK_BUS0_83,
};

static const struct samsung_div_clock bus0_div_clks[] __initconst = {
	DIV(0, "dout_pclk_bus0_83", "mout_aclk_bus0_333_user", CLK_CON_DIV_PCLK_BUS0_83, 0, 3),
};

static const struct samsung_gate_clock bus0_gate_clks[] __initconst = {
	GATE(0, "mout_aclk_bus0_333_user", "aclk_bus0_333", CLK_CON_MUX_ACLK_BUS0_333_USER, 26, CLK_IGNORE_UNUSED, 0),
};

static const struct samsung_cmu_info bus0_cmu_info __initconst = {
	.div_clks		= bus0_div_clks,
	.nr_div_clks		= ARRAY_SIZE(bus0_div_clks),
	.gate_clks		= bus0_gate_clks,
	.nr_gate_clks		= ARRAY_SIZE(bus0_gate_clks),
	.nr_clk_ids		= BUS0_NR_CLK,
	.clk_regs		= bus0_clk_regs,
	.nr_clk_regs		= ARRAY_SIZE(bus0_clk_regs),
};

static void __init exynos3475_cmu_bus0_init(struct device_node *np)
{
	samsung_cmu_register_one(np, &bus0_cmu_info);
}
CLK_OF_DECLARE(exynos3475_cmu_bus0, "samsung,exynos3475-cmu-bus0",
		exynos3475_cmu_bus0_init);

/* Register Offset definitions for CMU_BUS2 (0x11800000) */
#define CLK_CON_MUX_ACLK_BUS2_333_USER			0x0200
#define CLK_CON_DIV_PCLK_BUS2_83			0x0400

static const unsigned long bus2_clk_regs[] __initconst = {
	CLK_CON_MUX_ACLK_BUS2_333_USER,
	CLK_CON_DIV_PCLK_BUS2_83,
};

static const struct samsung_div_clock bus2_div_clks[] __initconst = {
	DIV(0, "dout_pclk_bus2_83", "mout_aclk_bus2_333_user", CLK_CON_DIV_PCLK_BUS2_83, 0, 3),
};

static const struct samsung_gate_clock bus2_gate_clks[] __initconst = {
	GATE(0, "mout_aclk_bus2_333_user", "aclk_bus2_333", CLK_CON_MUX_ACLK_BUS2_333_USER, 26, CLK_IGNORE_UNUSED, 0),
};

static const struct samsung_cmu_info bus2_cmu_info __initconst = {
	.div_clks		= bus2_div_clks,
	.nr_div_clks		= ARRAY_SIZE(bus2_div_clks),
	.gate_clks		= bus2_gate_clks,
	.nr_gate_clks		= ARRAY_SIZE(bus2_gate_clks),
	.nr_clk_ids		= BUS2_NR_CLK,
	.clk_regs		= bus2_clk_regs,
	.nr_clk_regs		= ARRAY_SIZE(bus2_clk_regs),
};

static void __init exynos3475_cmu_bus2_init(struct device_node *np)
{
	samsung_cmu_register_one(np, &bus2_cmu_info);
}
CLK_OF_DECLARE(exynos3475_cmu_bus2, "samsung,exynos3475-cmu-bus2",
		exynos3475_cmu_bus2_init);

/* Register Offset definitions for CMU_CPU (0x10900000) */
#define CPU_PLL_LOCK					0x0000
#define CPU_PLL_CON0					0x0100

#define CLK_CON_MUX_CPU_PLL				0x0200
#define CLK_CON_MUX_SCLK_BUS_PLL_USER			0x0204
#define CLK_CON_MUX_CPU				0x0208

#define CLK_CON_DIV_CPU_1				0x0400
#define CLK_CON_DIV_CPU_2				0x0404
#define CLK_CON_DIV_ATCLK_CPU				0x0408
#define CLK_CON_DIV_PCLK_DBG				0x040C
#define CLK_CON_DIV_ACLK_CPU				0x0410
#define CLK_CON_DIV_PCLK_CPU				0x0414
#define CLK_CON_DIV_SCLK_HPM_CPU			0x0418
#define CLK_CON_DIV_CPU_PLL				0x041C
#define CLK_CON_DIV_CPU_RUN_MONITOR			0x0420

PNAME(mout_cpu_p) = {"cpu_pll", "mout_sclk_bus_pll_user"};

static const unsigned long cpu_clk_regs[] __initconst = {
	CPU_PLL_LOCK,
	CPU_PLL_CON0,
	CLK_CON_MUX_CPU_PLL,
	CLK_CON_MUX_SCLK_BUS_PLL_USER,
	CLK_CON_MUX_CPU,
	CLK_CON_DIV_CPU_1,
	CLK_CON_DIV_CPU_2,
	CLK_CON_DIV_ATCLK_CPU,
	CLK_CON_DIV_PCLK_DBG,
	CLK_CON_DIV_ACLK_CPU,
	CLK_CON_DIV_PCLK_CPU,
	CLK_CON_DIV_SCLK_HPM_CPU,
	CLK_CON_DIV_CPU_PLL,
	CLK_CON_DIV_CPU_RUN_MONITOR,
};

static const struct samsung_mux_clock cpu_mux_clks[] __initconst = {
	MUX(CLK_MOUT_CPU, "mout_cpu", mout_cpu_p, CLK_CON_MUX_CPU, 12, 1),
};

static const struct samsung_div_clock cpu_div_clks[] __initconst = {
	DIV(0, "dout_cpu_1", "mout_cpu", CLK_CON_DIV_CPU_1, 0, 3),
	DIV(0, "dout_cpu_2", "dout_cpu_1", CLK_CON_DIV_CPU_2, 0, 3),
	DIV(0, "dout_atclk_cpu", "dout_cpu_2", CLK_CON_DIV_ATCLK_CPU, 0, 3),
	DIV(0, "dout_pclk_dbg", "dout_cpu_2", CLK_CON_DIV_PCLK_DBG, 0, 3),
	DIV(0, "dout_aclk_cpu", "dout_cpu_2", CLK_CON_DIV_ACLK_CPU, 0, 3),
	DIV(0, "dout_pclk_cpu", "dout_cpu_2", CLK_CON_DIV_PCLK_CPU, 0, 3),
	DIV(0, "dout_sclk_hpm_cpu", "mout_cpu", CLK_CON_DIV_SCLK_HPM_CPU, 0, 3),
	DIV(0, "dout_cpu_pll", "mout_cpu", CLK_CON_DIV_CPU_PLL, 0, 3),
	DIV(0, "dout_cpu_run_monitor", "dout_cpu_2", CLK_CON_DIV_CPU_RUN_MONITOR, 0, 3),
};

static const struct samsung_gate_clock cpu_gate_clks[] __initconst = {
	GATE(0, "mout_sclk_bus_pll_user", "aclk_cpu_800", CLK_CON_MUX_SCLK_BUS_PLL_USER, 26, CLK_IGNORE_UNUSED, 0),
};

struct samsung_pll_rate_table table_cpu[] = {
	{ 2000000000U,	13,	1000,	0,	0 }, /* L0 */
	{ 1898000000U,	 4,	292,	0,	0 }, /* L1 */
	{ 1794000000U,	 4,	276,	0,	0 }, /* L2 */
	{ 1703000000U,	 4,	262,	0,	0 }, /* L3 */
	{ 1599000000U,	 4,	246,	0,	0 }, /* L4 */
	{ 1495000000U,	 4,	230,	0,	0 }, /* L5 */
	{ 1404000000U,	 4,	216,	0,	0 }, /* L6 */
	{ 1300000000U,	 4,	200,	0,	0 }, /* L7 */
	{ 1196000000U,	 4,	368,	1,	0 }, /* L8 */
	{ 1105000000U,	 4,	340,	1,	0 }, /* L9 */
	{ 1001000000U,	 4,	308,	1,	0 }, /* L10 */
	{  897000000U,	 4,	276,	1,	0 }, /* L11 */
	{  806000000U,	 4,	248,	1,	0 }, /* L12 */
	{  702000000U,	 4,	216,	1,	0 }, /* L13 */
	{  598000000U,	 4,	368,	2,	0 }, /* L14 */
	{  507000000U,	 4,	312,	2,	0 }, /* L15 */
	{  403000000U,	 4,	248,	2,	0 }, /* L16 */
	{  299000000U,	 4,	368,	3,	0 }, /* L17 */
	{  195000000U,	 4,	240,	3,	0 }, /* L18 */
};

static const struct samsung_pll_clock cpu_pll_clks[] __initconst = {
	PLL(pll_2555x, CLK_CPU_PLL, "cpu_pll", "oscclk", CPU_PLL_LOCK, CPU_PLL_CON0, table_cpu),
};

static const struct samsung_cmu_info cpu_cmu_info __initconst = {
	.pll_clks		= cpu_pll_clks,
	.nr_pll_clks		= ARRAY_SIZE(cpu_pll_clks),
	.mux_clks		= cpu_mux_clks,
	.nr_mux_clks		= ARRAY_SIZE(cpu_mux_clks),
	.div_clks		= cpu_div_clks,
	.nr_div_clks		= ARRAY_SIZE(cpu_div_clks),
	.gate_clks		= cpu_gate_clks,
	.nr_gate_clks		= ARRAY_SIZE(cpu_gate_clks),
	.nr_clk_ids		= CPU_NR_CLK,
	.clk_regs		= cpu_clk_regs,
	.nr_clk_regs		= ARRAY_SIZE(cpu_clk_regs),
};

static void __init exynos3475_cmu_cpu_init(struct device_node *np)
{
	samsung_cmu_register_one(np, &cpu_cmu_info);
}
CLK_OF_DECLARE(exynos3475_cmu_cpu, "samsung,exynos3475-cmu-cpu",
		exynos3475_cmu_cpu_init);

/* Register Offset definitions for CMU_FSYS (0x13730000) */
#define USB_PLL_LOCK					0x0000
#define USB_PLL_CON0					0x0100

#define CLK_ENABLE_ACLK_FSYS_200			0x0800
#define CLK_ENABLE_SCLK_FSYS_MMC0_SDCLKIN		0x0804
#define CLK_ENABLE_SCLK_FSYS_MMC1_SDCLKIN		0x0808
#define CLK_ENABLE_SCLK_FSYS_MMC2_SDCLKIN		0x080C
#define CLK_ENABLE_SCLK_USB20_PHY_CLKCORE		0x0810
#define CLK_ENABLE_PHYCLK_USBHOST20_USB20_FREECLK	0x0814
#define CLK_ENABLE_PHYCLK_USBHOST20_USB20_PHYCLOCK	0x0818
#define CLK_ENABLE_PHYCLK_USBHOST20_USB20_CLK48MOHCI	0x081C
#define CLK_ENABLE_PHYCLK_USBHOTG_OTG20_PHYCLOCK	0x0820

#define CLK_CON_MUX_ACLK_FSYS_200_USER			0x0204
#define CLK_CON_MUX_SCLK_FSYS_MMC0_SDCLKIN_USER	0x0208
#define CLK_CON_MUX_SCLK_FSYS_MMC1_SDCLKIN_USER	0x020C
#define CLK_CON_MUX_SCLK_FSYS_MMC2_SDCLKIN_USER	0x0210
#define CLK_CON_MUX_PHYCLK_USBHOST20_USB20_FREECLK_USER 0x0214
#define CLK_CON_MUX_PHYCLK_USBHOST20_USB20_PHYCLOCK_USER 0x0218
#define CLK_CON_MUX_PHYCLK_USBHOST20_USB20_CLK48MOHCI_USER 0x021C
#define CLK_CON_MUX_PHYCLK_USBOTG_OTG20_PHYCLOCK_USER	0x0220

static const struct samsung_fixed_rate_clock fsys_fixed_rate_clks[] __initconst = {
	FRATE(0, "phyclk_usbhost20_phy_usb20_freeclk", NULL, 0, 60000000),
	FRATE(0, "phyclk_usbhost20_phy_usb20_phyclock", NULL, 0, 60000000),
	FRATE(0, "phyclk_usbhost20_phy_usb20_clk48mohci", NULL, 0, 48000000),
	FRATE(0, "phyclk_usbotg_phy_otg20_phyclock", NULL, 0, 60000000),
};

static const unsigned long fsys_clk_regs[] __initconst = {
	USB_PLL_LOCK,
	USB_PLL_CON0,
	CLK_ENABLE_ACLK_FSYS_200,
	CLK_ENABLE_SCLK_FSYS_MMC0_SDCLKIN,
	CLK_ENABLE_SCLK_FSYS_MMC1_SDCLKIN,
	CLK_ENABLE_SCLK_FSYS_MMC2_SDCLKIN,
	CLK_ENABLE_SCLK_USB20_PHY_CLKCORE,
	CLK_ENABLE_PHYCLK_USBHOST20_USB20_FREECLK,
	CLK_ENABLE_PHYCLK_USBHOST20_USB20_PHYCLOCK,
	CLK_ENABLE_PHYCLK_USBHOST20_USB20_CLK48MOHCI,
	CLK_ENABLE_PHYCLK_USBHOTG_OTG20_PHYCLOCK,
	CLK_CON_MUX_ACLK_FSYS_200_USER,
	CLK_CON_MUX_SCLK_FSYS_MMC0_SDCLKIN_USER,
	CLK_CON_MUX_SCLK_FSYS_MMC1_SDCLKIN_USER,
	CLK_CON_MUX_SCLK_FSYS_MMC2_SDCLKIN_USER,
	CLK_CON_MUX_PHYCLK_USBHOST20_USB20_FREECLK_USER,
	CLK_CON_MUX_PHYCLK_USBHOST20_USB20_PHYCLOCK_USER,
	CLK_CON_MUX_PHYCLK_USBHOST20_USB20_CLK48MOHCI_USER,
	CLK_CON_MUX_PHYCLK_USBOTG_OTG20_PHYCLOCK_USER,
};

static const struct samsung_gate_clock fsys_gate_clks[] __initconst = {
	GATE(0, "aclk_fsys_200_pclk_ppmu_fsys_pclk", "mout_aclk_fsys_200_user", CLK_ENABLE_ACLK_FSYS_200, 27, 0, 0),
	GATE(0, "aclk_fsys_200_pclk_sysreg_fsys_pclk", "mout_aclk_fsys_200_user", CLK_ENABLE_ACLK_FSYS_200, 25, CLK_IGNORE_UNUSED, 0),
	GATE(0, "aclk_fsys_200_pclk_pmu_fsys_pclk", "mout_aclk_fsys_200_user", CLK_ENABLE_ACLK_FSYS_200, 24, CLK_IGNORE_UNUSED, 0),
	GATE(0, "aclk_fsys_200_aclk_ppmu_fsys_aclk", "mout_aclk_fsys_200_user", CLK_ENABLE_ACLK_FSYS_200, 23, 0, 0),
	GATE(CLK_ACLK_FSYS_200_ACLK_UPSIZER_AHB_USBHS_ACLK, "aclk_fsys_200_aclk_upsizer_ahb_usbhs_aclk", "mout_aclk_fsys_200_user", CLK_ENABLE_ACLK_FSYS_200, 22, 0, 0),
	GATE(0, "aclk_fsys_200_aclk_upsizer_dma_fsys1_aclk", "mout_aclk_fsys_200_user", CLK_ENABLE_ACLK_FSYS_200, 21, 0, 0),
	GATE(0, "aclk_fsys_200_aclk_upsizer_dma_fsys0_aclk", "mout_aclk_fsys_200_user", CLK_ENABLE_ACLK_FSYS_200, 20, 0, 0),
	GATE(CLK_ACLK_FSYS_200_ACLK_UPSIZER_FSYS1_TO_FSYS0_ACLK, "aclk_fsys_200_aclk_upsizer_fsys1_to_fsys0_aclk", "mout_aclk_fsys_200_user", CLK_ENABLE_ACLK_FSYS_200, 19, CLK_IGNORE_UNUSED, 0),
	GATE(0, "aclk_fsys_200_aclk_bus_d_fsys_aclk_fsysnd", "mout_aclk_fsys_200_user", CLK_ENABLE_ACLK_FSYS_200, 18, CLK_IGNORE_UNUSED, 0),
	GATE(0, "aclk_fsys_200_aclk_ahb2apb_fsys1_hclk", "mout_aclk_fsys_200_user", CLK_ENABLE_ACLK_FSYS_200, 16, CLK_IGNORE_UNUSED, 0),
	GATE(CLK_ACLK_FSYS_200_ACLK_AHB2AXI_USBHS_HCLK, "aclk_fsys_200_aclk_ahb2axi_usbhs_hclk", "mout_aclk_fsys_200_user", CLK_ENABLE_ACLK_FSYS_200, 15, CLK_IGNORE_UNUSED, 0),
	GATE(CLK_ACLK_FSYS_200_ACLK_AHB_USBHS_HCLK, "aclk_fsys_200_aclk_ahb_usbhs_hclk", "mout_aclk_fsys_200_user", CLK_ENABLE_ACLK_FSYS_200, 14, CLK_IGNORE_UNUSED, 0),
	GATE(0, "aclk_fsys_200_aclk_ahb_fsys0_hclk", "mout_aclk_fsys_200_user", CLK_ENABLE_ACLK_FSYS_200, 13, CLK_IGNORE_UNUSED, 0),
	GATE(CLK_ACLK_FSYS_200_ACLK_XIU_D_FSYS1_ACLK, "aclk_fsys_200_aclk_xiu_d_fsys1_aclk", "mout_aclk_fsys_200_user", CLK_ENABLE_ACLK_FSYS_200, 11, CLK_IGNORE_UNUSED, 0),
	GATE(0, "aclk_fsys_200_aclk_xiu_d_fsys0_aclk", "mout_aclk_fsys_200_user", CLK_ENABLE_ACLK_FSYS_200, 10, CLK_IGNORE_UNUSED, 0),
	GATE(CLK_ACLK_FSYS_200_ACLK_UPSIZER_USBOTG_ACLK, "aclk_fsys_200_aclk_upsizer_usbotg_aclk", "mout_aclk_fsys_200_user", CLK_ENABLE_ACLK_FSYS_200, 9, 0, 0),
	GATE(CLK_ACLK_FSYS_200_ACLK_AHB2AXI_USBOTG_HCLK, "aclk_fsys_200_aclk_ahb2axi_usbotg_hclk", "mout_aclk_fsys_200_user", CLK_ENABLE_ACLK_FSYS_200, 8, 0, 0),
	GATE(CLK_ACLK_FSYS_200_ACLK_USBOTG20_ACLK, "aclk_fsys_200_aclk_usbotg20_aclk", "mout_aclk_fsys_200_user", CLK_ENABLE_ACLK_FSYS_200, 7, 0, 0),
	GATE(CLK_ACLK_FSYS_200_ACLK_MMC2_I_ACLK, "aclk_fsys_200_aclk_mmc2_i_aclk", "mout_aclk_fsys_200_user", CLK_ENABLE_ACLK_FSYS_200, 6, 0, 0),
	GATE(CLK_ACLK_FSYS_200_ACLK_MMC1_I_ACLK, "aclk_fsys_200_aclk_mmc1_i_aclk", "mout_aclk_fsys_200_user", CLK_ENABLE_ACLK_FSYS_200, 5, 0, 0),
	GATE(CLK_ACLK_FSYS_200_ACLK_MMC0_I_ACLK, "aclk_fsys_200_aclk_mmc0_i_aclk", "mout_aclk_fsys_200_user", CLK_ENABLE_ACLK_FSYS_200, 4, 0, 0),
	GATE(0, "aclk_fsys_200_aclk_sromc_hclk", "mout_aclk_fsys_200_user", CLK_ENABLE_ACLK_FSYS_200, 3, 0, 0),
	GATE(CLK_ACLK_FSYS_200_ACLK_USBHOST20_ACLK, "aclk_fsys_200_aclk_usbhost20_aclk", "mout_aclk_fsys_200_user", CLK_ENABLE_ACLK_FSYS_200, 2, 0, 0),
	GATE(CLK_ACLK_FSYS_200_ACLK_DMA_FSYS1_ACLK, "aclk_fsys_200_aclk_dma_fsys1_aclk", "aclk_fsys_200_aclk_upsizer_dma_fsys1_aclk", CLK_ENABLE_ACLK_FSYS_200, 1, 0, 0),
	GATE(CLK_ACLK_FSYS_200_ACLK_DMA_FSYS0_ACLK, "aclk_fsys_200_aclk_dma_fsys0_aclk", "aclk_fsys_200_aclk_upsizer_dma_fsys0_aclk", CLK_ENABLE_ACLK_FSYS_200, 0, 0, 0),
	GATE(CLK_SCLK_FSYS_MMC0_SDCLKIN_SCLK_MMC0_SDCLKIN, "sclk_fsys_mmc0_sdclkin_sclk_mmc0_sdclkin", "mout_sclk_fsys_mmc0_sdclkin_user", CLK_ENABLE_SCLK_FSYS_MMC0_SDCLKIN, 0,	CLK_IGNORE_UNUSED, 0),
	GATE(CLK_SCLK_FSYS_MMC1_SDCLKIN_SCLK_MMC1_SDCLKIN, "sclk_fsys_mmc1_sdclkin_sclk_mmc1_sdclkin", "mout_sclk_fsys_mmc1_sdclkin_user", CLK_ENABLE_SCLK_FSYS_MMC1_SDCLKIN, 0,	CLK_IGNORE_UNUSED, 0),
	GATE(CLK_SCLK_FSYS_MMC2_SDCLKIN_SCLK_MMC2_SDCLKIN, "sclk_fsys_mmc2_sdclkin_sclk_mmc2_sdclkin", "mout_sclk_fsys_mmc2_sdclkin_user", CLK_ENABLE_SCLK_FSYS_MMC2_SDCLKIN, 0, CLK_IGNORE_UNUSED, 0),
	GATE(CLK_USB_PLL, "sclk_usb20_phy_clkcore", "usb_pll", CLK_ENABLE_SCLK_USB20_PHY_CLKCORE, 0, CLK_IGNORE_UNUSED, 0),
	GATE(CLK_PHYCLK_USBHOST20_USB20_FREECLK, "phyclk_usbhost20_usb20_freeclk", "mout_phyclk_usbhost20_usb20_freeclk_user", CLK_ENABLE_PHYCLK_USBHOST20_USB20_FREECLK, 0, 0, 0),
	GATE(CLK_PHYCLK_USBHOST20_USB20_PHYCLOCK, "phyclk_usbhost20_usb20_phyclock", "mout_phyclk_usbhost20_usb20_phyclock_user", CLK_ENABLE_PHYCLK_USBHOST20_USB20_PHYCLOCK, 0, 0, 0),
	GATE(CLK_PHYCLK_USBHOST20_USB20_CLK48MOHCI, "phyclk_usbhost20_usb20_clk48mohci", "mout_phyclk_usbhost20_usb20_clk48mohci_user", CLK_ENABLE_PHYCLK_USBHOST20_USB20_CLK48MOHCI, 0, 0, 0),
	GATE(0, "phyclk_usbhotg_otg20_phyclock_phyclk_usbotg_otg20_phyclock", "mout_phyclk_usbotg_otg20_phyclock_user", CLK_ENABLE_PHYCLK_USBHOTG_OTG20_PHYCLOCK, 0, CLK_IGNORE_UNUSED, 0),
	GATE(0, "mout_aclk_fsys_200_user", "aclk_fsys_200", CLK_CON_MUX_ACLK_FSYS_200_USER, 26, 0, 0),
	GATE(CLK_MOUT_SCLK_FSYS_MMC0_SDCLKIN_USER, "mout_sclk_fsys_mmc0_sdclkin_user", "sclk_fsys_mmc0_sdclkin", CLK_CON_MUX_SCLK_FSYS_MMC0_SDCLKIN_USER, 26, CLK_IGNORE_UNUSED, 0),
	GATE(CLK_MOUT_SCLK_FSYS_MMC1_SDCLKIN_USER, "mout_sclk_fsys_mmc1_sdclkin_user", "sclk_fsys_mmc1_sdclkin", CLK_CON_MUX_SCLK_FSYS_MMC1_SDCLKIN_USER, 26, CLK_IGNORE_UNUSED, 0),
	GATE(CLK_MOUT_SCLK_FSYS_MMC2_SDCLKIN_USER, "mout_sclk_fsys_mmc2_sdclkin_user", "sclk_fsys_mmc2_sdclkin", CLK_CON_MUX_SCLK_FSYS_MMC2_SDCLKIN_USER, 26, CLK_IGNORE_UNUSED, 0),
	GATE(0, "mout_phyclk_usbhost20_usb20_freeclk_user", "phyclk_usbhost20_phy_usb20_freeclk", CLK_CON_MUX_PHYCLK_USBHOST20_USB20_FREECLK_USER, 26, 0, 0),
	GATE(0, "mout_phyclk_usbhost20_usb20_phyclock_user", "phyclk_usbhost20_phy_usb20_phyclock", CLK_CON_MUX_PHYCLK_USBHOST20_USB20_PHYCLOCK_USER, 26, 0, 0),
	GATE(0, "mout_phyclk_usbhost20_usb20_clk48mohci_user", "phyclk_usbhost20_phy_usb20_clk48mohci", CLK_CON_MUX_PHYCLK_USBHOST20_USB20_CLK48MOHCI_USER, 26, 0, 0),
	GATE(CLK_MOUT_PHYCLK_USBOTG_OTG20_PHYCLOCK_USER, "mout_phyclk_usbotg_otg20_phyclock_user", "phyclk_usbotg_phy_otg20_phyclock", CLK_CON_MUX_PHYCLK_USBOTG_OTG20_PHYCLOCK_USER, 26, 0, 0),
};

struct samsung_pll_rate_table table_usb[] = {
	{50000000U,	13,	400,	4,	0},
	{24000000U,	13,	384,	5,	0},
	{0,		0,	0,	0,	0},
};

static const struct samsung_pll_clock fsys_pll_clks[] __initconst = {
	PLL(pll_2551x, 0, "usb_pll", "oscclk", USB_PLL_LOCK, USB_PLL_CON0, table_usb),
};

static const struct samsung_cmu_info fsys_cmu_info __initconst = {
	.fixed_clks		= fsys_fixed_rate_clks,
	.nr_fixed_clks		= ARRAY_SIZE(fsys_fixed_rate_clks),
	.pll_clks		= fsys_pll_clks,
	.nr_pll_clks		= ARRAY_SIZE(fsys_pll_clks),
	.gate_clks		= fsys_gate_clks,
	.nr_gate_clks		= ARRAY_SIZE(fsys_gate_clks),
	.nr_clk_ids		= FSYS_NR_CLK,
	.clk_regs		= fsys_clk_regs,
	.nr_clk_regs		= ARRAY_SIZE(fsys_clk_regs),
};

static void __init exynos3475_cmu_fsys_init(struct device_node *np)
{
	samsung_cmu_register_one(np, &fsys_cmu_info);
}
CLK_OF_DECLARE(exynos3475_cmu_fsys, "samsung,exynos3475-cmu-fsys",
		exynos3475_cmu_fsys_init);

/* Register Offset definitions for CMU_G3D (0x10464060) */
#define G3D_PLL_LOCK					0x0000
#define G3D_PLL_CON0					0x0100

#define CLK_CON_MUX_ACLK_G3D_667			0x0208

#define CLK_CON_DIV_ACLK_G3D_667			0x0400
#define CLK_CON_DIV_PCLK_G3D_167			0x0404

#define CLK_ENABLE_ACLK_G3D_667			0x0800
#define CLK_ENABLE_ACLK_G3D_667_SECURE_CFW		0x0804
#define CLK_ENABLE_PCLK_G3D_167			0x0808
#define CLK_ENABLE_PCLK_G3D_167_SECURE_CFW		0x080C
#define CLK_CON_MUX_ACLK_G3D_400_USER			0x0204

PNAME(mout_aclk_g3d_667_p) = {"g3d_pll", "mout_aclk_g3d_400_user"};

static const unsigned long g3d_clk_regs[] __initconst = {
	G3D_PLL_LOCK,
	G3D_PLL_CON0,
	CLK_CON_MUX_ACLK_G3D_667,
	CLK_CON_DIV_ACLK_G3D_667,
	CLK_CON_DIV_PCLK_G3D_167,
	CLK_ENABLE_ACLK_G3D_667,
	CLK_ENABLE_ACLK_G3D_667_SECURE_CFW,
	CLK_ENABLE_PCLK_G3D_167,
	CLK_ENABLE_PCLK_G3D_167_SECURE_CFW,
	CLK_CON_MUX_ACLK_G3D_400_USER,
};

static const struct samsung_mux_clock g3d_mux_clks[] __initconst = {
	MUX(CLK_MOUT_ACLK_G3D_667, "mout_aclk_g3d_667", mout_aclk_g3d_667_p, CLK_CON_MUX_ACLK_G3D_667, 12, 1),
};

static const struct samsung_div_clock g3d_div_clks[] __initconst = {
	DIV(0, "dout_aclk_g3d_667", "mout_aclk_g3d_667", CLK_CON_DIV_ACLK_G3D_667, 0, 3),
	DIV(0, "dout_pclk_g3d_167", "dout_aclk_g3d_667", CLK_CON_DIV_PCLK_G3D_167, 0, 3),
};

static const struct samsung_gate_clock g3d_gate_clks[] __initconst = {

	GATE(0, "aclk_g3d_667_aclk_ppmu_g3d_aclk", "dout_aclk_g3d_667", CLK_ENABLE_ACLK_G3D_667, 4, CLK_IGNORE_UNUSED, 0),
	GATE(0, "aclk_g3d_667_aclk_qe_g3d_aclk", "dout_aclk_g3d_667", CLK_ENABLE_ACLK_G3D_667, 3, CLK_IGNORE_UNUSED, 0),
	GATE(0, "aclk_g3d_667_aclk_async_ahb2apb_g3d_to_g3d_cclk", "dout_aclk_g3d_667", CLK_ENABLE_ACLK_G3D_667, 2, CLK_IGNORE_UNUSED, 0),
	GATE(0, "aclk_g3d_667_aclk_bus_d_g3d_aclk_g3dnd", "dout_aclk_g3d_667", CLK_ENABLE_ACLK_G3D_667, 1, CLK_IGNORE_UNUSED, 0),
	GATE(CLK_ACLK_G3D_667_ACLK_G3D_CLK, "aclk_g3d_667_aclk_g3d_clk", "dout_aclk_g3d_667", CLK_ENABLE_ACLK_G3D_667, 0, CLK_IGNORE_UNUSED, 0),
	GATE(0, "aclk_g3d_667_secure_cfw_aclk_smmu_g3d_aclk_cfw", "dout_aclk_g3d_667", CLK_ENABLE_ACLK_G3D_667_SECURE_CFW, 0, CLK_IGNORE_UNUSED, 0),
	GATE(0, "pclk_g3d_167_pclk_ppmu_g3d_pclk", "dout_pclk_g3d_167", CLK_ENABLE_PCLK_G3D_167, 6, CLK_IGNORE_UNUSED, 0),
	GATE(0, "pclk_g3d_167_pclk_qe_g3d_pclk", "dout_pclk_g3d_167", CLK_ENABLE_PCLK_G3D_167, 5, CLK_IGNORE_UNUSED, 0),
	GATE(0, "pclk_g3d_167_pclk_sysreg_g3d_pclk", "dout_pclk_g3d_167", CLK_ENABLE_PCLK_G3D_167, 4, CLK_IGNORE_UNUSED, 0),
	GATE(0, "pclk_g3d_167_pclk_pmu_g3d_pclk", "dout_pclk_g3d_167", CLK_ENABLE_PCLK_G3D_167, 3, CLK_IGNORE_UNUSED, 0),
	GATE(0, "pclk_g3d_167_pclk_async_ahb2apb_g3d_to_g3d_pclk", "dout_pclk_g3d_167", CLK_ENABLE_PCLK_G3D_167, 2, CLK_IGNORE_UNUSED, 0),
	GATE(0, "pclk_g3d_167_secure_cfw_pclk_smmu_g3d_pclk_cfw", "dout_pclk_g3d_167", CLK_ENABLE_PCLK_G3D_167_SECURE_CFW, 0, CLK_IGNORE_UNUSED, 0),
	GATE(0, "mout_aclk_g3d_400_user", "aclk_g3d_400", CLK_CON_MUX_ACLK_G3D_400_USER, 26, CLK_IGNORE_UNUSED, 0),
};

struct samsung_pll_rate_table table_g3d[] = {
	{ 667000000U,	12,	308,	0,	0 }, /* L0 */
	{ 600000000U,	13,	300,	0,	0 }, /* L1 */
	{ 533000000U,	14,	287,	0,	0 }, /* L2 */
	{ 480000000U,	13,	480,	1,	0 }, /* L3 */
	{ 440000000U,	13,	440,	1,	0 }, /* L4 */
	{ 420000000U,	13,	420,	1,	0 }, /* L5 */
	{ 370000000U,	13,	370,	1,	0 }, /* L6 */
	{ 350000000U,	13,	350,	1,	0 }, /* L7 */
	{ 266000000U,	13,	266,	1,	0 }, /* L8 */
	{ 160000000U,	13,	320,	2,	0 }, /* L9 */
	{ 100000000U,	13,	400,	3,	0 }, /* L10 */
};

static const struct samsung_pll_clock g3d_pll_clks[] __initconst = {
	PLL(pll_2551x, 0, "g3d_pll", "oscclk", G3D_PLL_LOCK, G3D_PLL_CON0, table_g3d),
};

static const struct samsung_cmu_info g3d_cmu_info __initconst = {
	.pll_clks		= g3d_pll_clks,
	.nr_pll_clks		= ARRAY_SIZE(g3d_pll_clks),
	.mux_clks		= g3d_mux_clks,
	.nr_mux_clks		= ARRAY_SIZE(g3d_mux_clks),
	.div_clks		= g3d_div_clks,
	.nr_div_clks		= ARRAY_SIZE(g3d_div_clks),
	.gate_clks		= g3d_gate_clks,
	.nr_gate_clks		= ARRAY_SIZE(g3d_gate_clks),
	.nr_clk_ids		= G3D_NR_CLK,
	.clk_regs		= g3d_clk_regs,
	.nr_clk_regs		= ARRAY_SIZE(g3d_clk_regs),
};

static void __init exynos3475_cmu_g3d_init(struct device_node *np)
{
	samsung_cmu_register_one(np, &g3d_cmu_info);
}
CLK_OF_DECLARE(exynos3475_cmu_g3d, "samsung,exynos3475-cmu-g3d",
		exynos3475_cmu_g3d_init);

/* Register Offset definitions for CMU_PERI (0x139f0000) */
#define CLK_CON_MUX_ACLK_PERI_66_USER			0x0200
#define CLK_CON_MUX_SCLK_PERI_SPI0_SPI_EXT_CLK_USER	0x0204
#define CLK_CON_MUX_SCLK_PERI_SPI1_SPI_EXT_CLK_USER	0x0208
#define CLK_CON_MUX_SCLK_PERI_SPI2_SPI_EXT_CLK_USER	0x020C
#define CLK_CON_MUX_SCLK_PERI_UART0_EXT_UCLK_USER	0x0210
#define CLK_CON_MUX_SCLK_PERI_UART1_EXT_UCLK_USER	0x0214
#define CLK_CON_MUX_SCLK_PERI_UART2_EXT_UCLK_USER	0x0218

#define CLK_ENABLE_ACLK_PERI_66_1			0x0800
#define CLK_ENABLE_ACLK_PERI_66_SECURE_TZPC		0x0804
#define CLK_ENABLE_ACLK_PERI_66_SECURE_RTC_TOP	0x0808
#define CLK_ENABLE_ACLK_PERI_66_SECURE_CHIPID		0x080C
#define CLK_ENABLE_ACLK_PERI_66_SECURE_SECKEY		0x0810
#define CLK_ENABLE_ACLK_PERI_66_SECURE_ANTIRBK_CNT	0x0814
#define CLK_ENABLE_ACLK_PERI_66_SECURE_MONOTONIC_CNT	0x0818
#define CLK_ENABLE_ACLK_PERI_66_SECURE_RTC		0x081C
#define CLK_ENABLE_ACLK_PERI_66_2			0x0820
#define CLK_ENABLE_SCLK_PERI_SPI0_SPI_EXT_CLK		0x082C
#define CLK_ENABLE_SCLK_PERI_SPI1_SPI_EXT_CLK		0x0830
#define CLK_ENABLE_SCLK_PERI_SPI2_SPI_EXT_CLK		0x0834
#define CLK_ENABLE_SCLK_PERI_UART0_EXT_UCLK		0x0838
#define CLK_ENABLE_SCLK_PERI_UART1_EXT_UCLK		0x083C
#define CLK_ENABLE_SCLK_PERI_UART2_EXT_UCLK		0x0844

static const unsigned long peri_clk_regs[] __initconst = {
	CLK_ENABLE_ACLK_PERI_66_1,
	CLK_ENABLE_ACLK_PERI_66_SECURE_TZPC,
	CLK_ENABLE_ACLK_PERI_66_SECURE_RTC_TOP,
	CLK_ENABLE_ACLK_PERI_66_SECURE_CHIPID,
	CLK_ENABLE_ACLK_PERI_66_SECURE_SECKEY,
	CLK_ENABLE_ACLK_PERI_66_SECURE_ANTIRBK_CNT,
	CLK_ENABLE_ACLK_PERI_66_SECURE_MONOTONIC_CNT,
	CLK_ENABLE_ACLK_PERI_66_SECURE_RTC,
	CLK_ENABLE_ACLK_PERI_66_2,
	CLK_ENABLE_SCLK_PERI_SPI0_SPI_EXT_CLK,
	CLK_ENABLE_SCLK_PERI_SPI1_SPI_EXT_CLK,
	CLK_ENABLE_SCLK_PERI_SPI2_SPI_EXT_CLK,
	CLK_ENABLE_SCLK_PERI_UART0_EXT_UCLK,
	CLK_ENABLE_SCLK_PERI_UART1_EXT_UCLK,
	CLK_ENABLE_SCLK_PERI_UART2_EXT_UCLK,
	CLK_CON_MUX_ACLK_PERI_66_USER,
	CLK_CON_MUX_SCLK_PERI_SPI0_SPI_EXT_CLK_USER,
	CLK_CON_MUX_SCLK_PERI_SPI1_SPI_EXT_CLK_USER,
	CLK_CON_MUX_SCLK_PERI_SPI2_SPI_EXT_CLK_USER,
	CLK_CON_MUX_SCLK_PERI_UART0_EXT_UCLK_USER,
	CLK_CON_MUX_SCLK_PERI_UART1_EXT_UCLK_USER,
	CLK_CON_MUX_SCLK_PERI_UART2_EXT_UCLK_USER,
};

static const struct samsung_gate_clock peri_gate_clks[] __initconst = {
	GATE(CLK_ACLK_PERI_PCLK_HSI2C8_IPCLK, "aclk_peri_66_1_pclk_hsi2c8_ipclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_1, 18, 0, 0),
	GATE(CLK_ACLK_PERI_PCLK_HSI2C7_IPCLK, "aclk_peri_66_1_pclk_hsi2c7_ipclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_1, 17, 0, 0),
	GATE(CLK_ACLK_PERI_PCLK_HSI2C1_IPCLK, "aclk_peri_66_1_pclk_hsi2c1_ipclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_1, 16, 0, 0),
	GATE(CLK_ACLK_PERI_PCLK_HSI2C0_IPCLK, "aclk_peri_66_1_pclk_hsi2c0_ipclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_1, 15, 0, 0),
	GATE(CLK_ACLK_PERI_PCLK_I2C6_PCLK, "aclk_peri_66_1_pclk_i2c6_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_1, 14, 0, 0),
	GATE(CLK_ACLK_PERI_PCLK_I2C5_PCLK, "aclk_peri_66_1_pclk_i2c5_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_1, 13, 0, 0),
	GATE(CLK_ACLK_PERI_PCLK_I2C4_PCLK, "aclk_peri_66_1_pclk_i2c4_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_1, 12, 0, 0),
	GATE(CLK_ACLK_PERI_PCLK_I2C3_PCLK, "aclk_peri_66_1_pclk_i2c3_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_1, 11, 0, 0),
	GATE(0, "aclk_peri_66_1_aclk_ahb2apb_peric0_hclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_1, 9, CLK_IGNORE_UNUSED, 0),
	GATE(0, "aclk_peri_66_1_pclk_efuse_writer_sc_apbif_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_1, 7, 0, 0),
	GATE(0, "aclk_peri_66_1_pclk_cmu_top_apbif_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_1, 6, CLK_IGNORE_UNUSED, 0),
	GATE(CLK_ACLK_PERI_PCLK_WDT_CPU_PCLK, "aclk_peri_66_1_pclk_wdt_cpu_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_1, 5, 0, 0),
	GATE(CLK_ACLK_PERI_PCLK_MCT_PCLK, "aclk_peri_66_1_pclk_mct_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_1, 4, 0, 0),
	GATE(0, "aclk_peri_66_1_aclk_ahb2apb_peris1_hclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_1, 3, CLK_IGNORE_UNUSED, 0),
	GATE(0, "aclk_peri_66_1_aclk_ahb2apb_peris0_hclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_1, 2, CLK_IGNORE_UNUSED, 0),
	GATE(0, "aclk_peri_66_secure_tzpc_pclk_tzpc10_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_SECURE_TZPC, 10, 0, 0),
	GATE(0, "aclk_peri_66_secure_tzpc_pclk_tzpc9_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_SECURE_TZPC, 9, 0, 0),
	GATE(0, "aclk_peri_66_secure_tzpc_pclk_tzpc8_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_SECURE_TZPC, 8, 0, 0),
	GATE(0, "aclk_peri_66_secure_tzpc_pclk_tzpc7_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_SECURE_TZPC, 7, 0, 0),
	GATE(0, "aclk_peri_66_secure_tzpc_pclk_tzpc6_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_SECURE_TZPC, 6, 0, 0),
	GATE(0, "aclk_peri_66_secure_tzpc_pclk_tzpc4_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_SECURE_TZPC, 4, 0, 0),
	GATE(0, "aclk_peri_66_secure_tzpc_pclk_tzpc3_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_SECURE_TZPC, 3, 0, 0),
	GATE(0, "aclk_peri_66_secure_tzpc_pclk_tzpc2_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_SECURE_TZPC, 2, 0, 0),
	GATE(0, "aclk_peri_66_secure_rtc_top_pclk_rtc_top_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_SECURE_RTC_TOP, 0, 0, 0),
	GATE(0, "aclk_peri_66_secure_chipid_pclk_chipid_apbif_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_SECURE_CHIPID, 0, CLK_IGNORE_UNUSED, 0),
	GATE(CLK_ACLK_PERI_SECURE_RTC_PCLK_RTC_APBIF_PCLK, "aclk_peri_66_secure_rtc_pclk_rtc_apbif_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_SECURE_RTC, 0, 0, 0),
	GATE(0, "aclk_peri_66_2_pclk_sysreg_peri_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_2, 17, CLK_IGNORE_UNUSED, 0),
	GATE(0, "aclk_peri_66_2_pclk_pmu_peri_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_2, 16, 0, 0),
	GATE(0, "aclk_peri_66_2_pclk_gpio_alive_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_2, 15, CLK_IGNORE_UNUSED, 0),
	GATE(0, "aclk_peri_66_2_pclk_gpio_ese_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_2, 14, CLK_IGNORE_UNUSED, 0),
	GATE(0, "aclk_peri_66_2_pclk_gpio_touch_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_2, 13, CLK_IGNORE_UNUSED, 0),
	GATE(0, "aclk_peri_66_2_pclk_gpio_nfc_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_2, 12, CLK_IGNORE_UNUSED, 0),
	GATE(0, "aclk_peri_66_2_pclk_gpio_peri_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_2, 11, CLK_IGNORE_UNUSED, 0),
	GATE(0, "aclk_peri_66_2_pclk_tmu0_apbif_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_2, 10, CLK_IGNORE_UNUSED, 0),
	GATE(CLK_ACLK_PERI_PCLK_PWM_PCLK, "aclk_peri_66_2_pclk_pwm_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_2, 9, 0, 0),
	GATE(CLK_ACLK_PERI_PCLK_I2C10_PCLK, "aclk_peri_66_2_pclk_i2c10_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_2, 8, 0, 0),
	GATE(CLK_ACLK_PERI_PCLK_I2C9_PCLK, "aclk_peri_66_2_pclk_i2c9_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_2, 7, 0, 0),
	GATE(CLK_ACLK_PERI_PCLK_SPI2_PCLK, "aclk_peri_66_2_pclk_spi2_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_2, 6, 0, 0),
	GATE(CLK_ACLK_PERI_PCLK_SPI1_PCLK, "aclk_peri_66_2_pclk_spi1_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_2, 5, 0, 0),
	GATE(CLK_ACLK_PERI_PCLK_SPI0_PCLK, "aclk_peri_66_2_pclk_spi0_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_2, 4, 0, 0),
	GATE(CLK_ACLK_PERI_PCLK_ADCIF_PCLK, "aclk_peri_66_2_pclk_adcif_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_2, 3, 0, 0),
	GATE(CLK_ACLK_PERI_PCLK_UART2_PCLK, "aclk_peri_66_2_pclk_uart2_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_2, 2, 0, 0),
	GATE(CLK_ACLK_PERI_PCLK_UART1_PCLK, "aclk_peri_66_2_pclk_uart1_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_2, 1, 0, 0),
	GATE(CLK_ACLK_PERI_PCLK_UART0_PCLK, "aclk_peri_66_2_pclk_uart0_pclk", "mout_aclk_peri_66_user", CLK_ENABLE_ACLK_PERI_66_2, 0, 0, 0),
	GATE(CLK_SCLK_PERI_SPI0_SPI_EXT_CLK_SCLK_SPI0_SPI_EXT_CLK, "sclk_peri_spi0_spi_ext_clk_sclk_spi0_spi_ext_clk", "mout_sclk_peri_spi0_spi_ext_clk_user", CLK_ENABLE_SCLK_PERI_SPI0_SPI_EXT_CLK, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_PERI_SPI1_SPI_EXT_CLK_SCLK_SPI1_SPI_EXT_CLK, "sclk_peri_spi1_spi_ext_clk_sclk_spi1_spi_ext_clk", "mout_sclk_peri_spi1_spi_ext_clk_user", CLK_ENABLE_SCLK_PERI_SPI1_SPI_EXT_CLK, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_PERI_SPI2_SPI_EXT_CLK_SCLK_SPI2_SPI_EXT_CLK, "sclk_peri_spi2_spi_ext_clk_sclk_spi2_spi_ext_clk", "mout_sclk_peri_spi2_spi_ext_clk_user", CLK_ENABLE_SCLK_PERI_SPI2_SPI_EXT_CLK, 0, CLK_SET_RATE_PARENT, 0),
	GATE(CLK_SCLK_PERI_UART0_EXT_UCLK_SCLK_UART0_EXT_UCLK, "sclk_peri_uart0_ext_uclk_sclk_uart0_ext_uclk", "mout_sclk_peri_uart0_ext_uclk_user", CLK_ENABLE_SCLK_PERI_UART0_EXT_UCLK, 0, 0, 0),
	GATE(CLK_SCLK_PERI_UART1_EXT_UCLK_SCLK_UART1_EXT_UCLK, "sclk_peri_uart1_ext_uclk_sclk_uart1_ext_uclk", "mout_sclk_peri_uart1_ext_uclk_user", CLK_ENABLE_SCLK_PERI_UART1_EXT_UCLK, 0, 0, 0),
	GATE(CLK_SCLK_PERI_UART2_EXT_UCLK_SCLK_UART2_EXT_UCLK, "sclk_peri_uart2_ext_uclk_sclk_uart2_ext_uclk", "mout_sclk_peri_uart2_ext_uclk_user", CLK_ENABLE_SCLK_PERI_UART2_EXT_UCLK, 0, 0, 0),
	GATE(0, "mout_aclk_peri_66_user", "aclk_peri_66", CLK_CON_MUX_ACLK_PERI_66_USER, 26, CLK_IGNORE_UNUSED, 0),
	GATE(0, "mout_sclk_peri_spi0_spi_ext_clk_user", "sclk_peri_spi0_spi_ext_clk", CLK_CON_MUX_SCLK_PERI_SPI0_SPI_EXT_CLK_USER, 26, CLK_SET_RATE_PARENT, 0),
	GATE(0, "mout_sclk_peri_spi1_spi_ext_clk_user", "sclk_peri_spi1_spi_ext_clk", CLK_CON_MUX_SCLK_PERI_SPI1_SPI_EXT_CLK_USER, 26, CLK_SET_RATE_PARENT, 0),
	GATE(0, "mout_sclk_peri_spi2_spi_ext_clk_user", "sclk_peri_spi2_spi_ext_clk", CLK_CON_MUX_SCLK_PERI_SPI2_SPI_EXT_CLK_USER, 26, 0, 0),
	GATE(0, "mout_sclk_peri_uart0_ext_uclk_user", "sclk_peri_uart0_ext_uclk", CLK_CON_MUX_SCLK_PERI_UART0_EXT_UCLK_USER, 26, 0, 0),
	GATE(0, "mout_sclk_peri_uart1_ext_uclk_user", "sclk_peri_uart1_ext_uclk", CLK_CON_MUX_SCLK_PERI_UART1_EXT_UCLK_USER, 26, 0, 0),
	GATE(0, "mout_sclk_peri_uart2_ext_uclk_user", "sclk_peri_uart2_ext_uclk", CLK_CON_MUX_SCLK_PERI_UART2_EXT_UCLK_USER, 26, 0, 0),
};

static const struct samsung_cmu_info peri_cmu_info __initconst = {
	.gate_clks		= peri_gate_clks,
	.nr_gate_clks		= ARRAY_SIZE(peri_gate_clks),
	.nr_clk_ids		= PERI_NR_CLK,
	.clk_regs		= peri_clk_regs,
	.nr_clk_regs		= ARRAY_SIZE(peri_clk_regs),
};

static void __init exynos3475_cmu_peri_init(struct device_node *np)
{
	samsung_cmu_register_one(np, &peri_cmu_info);
}
CLK_OF_DECLARE(exynos3475_cmu_peri, "samsung,exynos3475-cmu-peri",
		exynos3475_cmu_peri_init);

/* Register Offset definitions for CMU_MIF (0x10430000) */
#define MEM0_PLL_LOCK					0x0000
#define MEDIA_PLL_LOCK					0x0008
#define BUS_PLL_LOCK					0x000C
#define MEM0_PLL_CON0					0x0100
#define MEDIA_PLL_CON0					0x0110
#define BUS_PLL_CON0					0x0120

#define CLK_CON_MUX_DIV2_MEM0_PLL			0x210
#define CLK_CON_MUX_DIV2_MEDIA_PLL			0x214
#define CLK_CON_MUX_CLKM_PHY_A				0x218
#define CLK_CON_MUX_CLKM_PHY_B				0x21C
#define CLK_CON_MUX_CLK2X_PHY_A			0x220
#define CLK_CON_MUX_CLK2X_PHY_B			0x224
#define CLK_CON_MUX_ACLK_MIF_333			0x228
#define CLK_CON_MUX_ACLK_MIF_83			0x22C
#define CLK_CON_MUX_ACLK_MIF_FIX_50			0x230
#define CLK_CON_MUX_ACLK_DISPAUD_133			0x234
#define CLK_CON_MUX_ACLK_ISP_300			0x238
#define CLK_CON_MUX_SCLK_DISP_DECON_INT_ECLK		0x23C
#define CLK_CON_MUX_SCLK_DISP_DECON_INT_VCLK		0x240

#define CLK_CON_DIV_CLKM_PHY				0x400
#define CLK_CON_DIV_CLK2X_PHY				0x404
#define CLK_CON_DIV_ACLK_MIF_333			0x408
#define CLK_CON_DIV_ACLK_MIF_166			0x40C
#define CLK_CON_DIV_ACLK_MIF_83			0x410
#define CLK_CON_DIV_ACLK_MIF_FIX_50			0x414
#define CLK_CON_DIV_ACLK_DISPAUD_133			0x418
#define CLK_CON_DIV_ACLK_ISP_300			0x41C
#define CLK_CON_DIV_SCLK_DISP_DECON_INT_ECLK		0x420
#define CLK_CON_DIV_SCLK_DISP_DECON_INT_VCLK		0x424
#define CLK_CON_DIV_MIF_NODDR				0x428

#define CLK_ENABLE_ACLK_CPU_800			0x83C
#define CLK_ENABLE_SCLK_BUS_PLL_TOP			0x840
#define CLK_ENABLE_SCLK_MEDIA_PLL_TOP			0x844

PNAME(mout_div2_mem0_pll_p) = {"mem0_pll", "ffac_mem0_pll_div2"};
PNAME(mout_div2_media_pll_p) = {"media_pll", "ffac_media_pll_div2"};
PNAME(mout_clkm_phy_a_p) = {"mout_div2_media_pll", "mout_div2_mem0_pll"};
PNAME(mout_clkm_phy_b_p) = {"mout_clkm_phy_a", "bus_pll"};
PNAME(mout_clk2x_phy_a_p) = {"mout_div2_media_pll", "mout_div2_mem0_pll"};
PNAME(mout_clk2x_phy_b_p) = {"mout_clk2x_phy_a", "bus_pll"};
PNAME(mout_aclk_mif_333_p) = {"dout_mif_noddr", "bus_pll", "mout_div2_mem0_pll"};
PNAME(mout_aclk_mif_83_p) = {"dout_mif_noddr", "bus_pll", "mout_div2_mem0_pll"};
PNAME(mout_aclk_mif_fix_50_p) = {"bus_pll", "dout_mif_noddr"};
PNAME(mout_aclk_dispaud_133_p) = {"bus_pll", "dout_mif_noddr", "aud_pll"};
PNAME(mout_aclk_isp_300_p) = {"aud_pll", "bus_pll", "dout_mif_noddr"};
PNAME(mout_sclk_disp_decon_int_eclk_p) = {"bus_pll", "dout_mif_noddr", "aud_pll"};
PNAME(mout_sclk_disp_decon_int_vclk_p) = {"bus_pll", "dout_mif_noddr", "aud_pll"};

static const unsigned long mif_clk_regs[] __initconst = {
	MEM0_PLL_LOCK,
	MEDIA_PLL_LOCK,
	BUS_PLL_LOCK,
	MEM0_PLL_CON0,
	MEDIA_PLL_CON0,
	BUS_PLL_CON0,
	CLK_CON_MUX_DIV2_MEM0_PLL,
	CLK_CON_MUX_DIV2_MEDIA_PLL,
	CLK_CON_MUX_CLKM_PHY_A,
	CLK_CON_MUX_CLKM_PHY_B,
	CLK_CON_MUX_CLK2X_PHY_A,
	CLK_CON_MUX_CLK2X_PHY_B,
	CLK_CON_MUX_ACLK_MIF_333,
	CLK_CON_MUX_ACLK_MIF_83,
	CLK_CON_MUX_ACLK_MIF_FIX_50,
	CLK_CON_MUX_ACLK_DISPAUD_133,
	CLK_CON_MUX_ACLK_ISP_300,
	CLK_CON_MUX_SCLK_DISP_DECON_INT_ECLK,
	CLK_CON_MUX_SCLK_DISP_DECON_INT_VCLK,
	CLK_CON_DIV_CLKM_PHY,
	CLK_CON_DIV_CLK2X_PHY,
	CLK_CON_DIV_ACLK_MIF_333,
	CLK_CON_DIV_ACLK_MIF_166,
	CLK_CON_DIV_ACLK_MIF_83,
	CLK_CON_DIV_ACLK_MIF_FIX_50,
	CLK_CON_DIV_ACLK_DISPAUD_133,
	CLK_CON_DIV_ACLK_ISP_300,
	CLK_CON_DIV_SCLK_DISP_DECON_INT_ECLK,
	CLK_CON_DIV_SCLK_DISP_DECON_INT_VCLK,
	CLK_CON_DIV_MIF_NODDR,
	CLK_ENABLE_ACLK_CPU_800,
	CLK_ENABLE_SCLK_MEDIA_PLL_TOP,
	CLK_ENABLE_SCLK_BUS_PLL_TOP,
};

static const struct samsung_mux_clock mif_mux_clks[] __initconst = {
	MUX(0, "mout_div2_mem0_pll", mout_div2_mem0_pll_p, CLK_CON_MUX_DIV2_MEM0_PLL, 12, 1),
	MUX(0, "mout_div2_media_pll", mout_div2_media_pll_p, CLK_CON_MUX_DIV2_MEDIA_PLL, 12, 1),
	MUX(0, "mout_clkm_phy_a", mout_clkm_phy_a_p, CLK_CON_MUX_CLKM_PHY_A, 12, 1),
	MUX(0, "mout_clkm_phy_b", mout_clkm_phy_b_p, CLK_CON_MUX_CLKM_PHY_B, 12, 1),
	MUX(0, "mout_clk2x_phy_a", mout_clk2x_phy_a_p, CLK_CON_MUX_CLK2X_PHY_A, 12, 1),
	MUX(0, "mout_clk2x_phy_b", mout_clk2x_phy_b_p, CLK_CON_MUX_CLK2X_PHY_B, 12, 1),
	MUX(CLK_MOUT_ACLK_MIF_333, "mout_aclk_mif_333", mout_aclk_mif_333_p, CLK_CON_MUX_ACLK_MIF_333, 12, 2),
	MUX(CLK_MOUT_ACLK_MIF_83, "mout_aclk_mif_83", mout_aclk_mif_83_p, CLK_CON_MUX_ACLK_MIF_83, 12, 2),
	MUX(CLK_MOUT_ACLK_MIF_FIX_50, "mout_aclk_mif_fix_50", mout_aclk_mif_fix_50_p, CLK_CON_MUX_ACLK_MIF_FIX_50, 12, 1),
	MUX(CLK_MOUT_ACLK_DISPAUD_133, "mout_aclk_dispaud_133", mout_aclk_dispaud_133_p, CLK_CON_MUX_ACLK_DISPAUD_133, 12, 2),
	MUX(CLK_MOUT_ACLK_ISP_300, "mout_aclk_isp_300", mout_aclk_isp_300_p, CLK_CON_MUX_ACLK_ISP_300, 12, 2),
	MUX(CLK_MOUT_SCLK_DISP_DECON_INT_ECLK, "mout_sclk_disp_decon_int_eclk", mout_sclk_disp_decon_int_eclk_p, CLK_CON_MUX_SCLK_DISP_DECON_INT_ECLK, 12, 2),
	MUX(CLK_MOUT_SCLK_DISP_DECON_INT_VCLK, "mout_sclk_disp_decon_int_vclk", mout_sclk_disp_decon_int_vclk_p, CLK_CON_MUX_SCLK_DISP_DECON_INT_VCLK, 12, 2),
};

static const struct samsung_div_clock mif_div_clks[] __initconst = {
	DIV(0, "dout_clkm_phy", "mout_clkm_phy_b", CLK_CON_DIV_CLKM_PHY, 0, 4),
	DIV(0, "dout_clk2x_phy", "mout_clk2x_phy_b", CLK_CON_DIV_CLK2X_PHY, 0, 4),
	DIV(CLK_DOUT_ACLK_MIF_333, "dout_aclk_mif_333", "mout_aclk_mif_333", CLK_CON_DIV_ACLK_MIF_333, 0, 3),
	DIV(CLK_DOUT_ACLK_MIF_166, "dout_aclk_mif_166", "dout_aclk_mif_333", CLK_CON_DIV_ACLK_MIF_166, 0, 2),
	DIV(CLK_DOUT_ACLK_MIF_83, "dout_aclk_mif_83", "mout_aclk_mif_83", CLK_CON_DIV_ACLK_MIF_83, 0, 4),
	DIV(CLK_DOUT_ACLK_MIF_FIX_50, "dout_aclk_mif_fix_50", "mout_aclk_mif_fix_50", CLK_CON_DIV_ACLK_MIF_FIX_50, 0, 4),
	DIV(CLK_DOUT_ACLK_DISPAUD_133, "dout_aclk_dispaud_133", "mout_aclk_dispaud_133", CLK_CON_DIV_ACLK_DISPAUD_133, 0, 4),
	DIV(CLK_DOUT_ACLK_ISP_300, "dout_aclk_isp_300", "mout_aclk_isp_300", CLK_CON_DIV_ACLK_ISP_300, 0, 4),
	DIV(CLK_DOUT_SCLK_DISP_DECON_INT_ECLK, "dout_sclk_disp_decon_int_eclk", "mout_sclk_disp_decon_int_eclk", CLK_CON_DIV_SCLK_DISP_DECON_INT_ECLK, 0, 4),
	DIV(CLK_DOUT_SCLK_DISP_DECON_INT_VCLK, "dout_sclk_disp_decon_int_vclk", "mout_sclk_disp_decon_int_vclk", CLK_CON_DIV_SCLK_DISP_DECON_INT_VCLK, 0, 4),
	DIV(CLK_DOUT_MIF_NODDR, "dout_mif_noddr", "mout_div2_media_pll", CLK_CON_DIV_MIF_NODDR, 0, 4),
};

static const struct samsung_gate_clock mif_gate_clks[] __initconst = {
	GATE(CLK_ACLK_CPU_800, "aclk_cpu_800", "bus_pll", CLK_ENABLE_ACLK_CPU_800, 0, CLK_IGNORE_UNUSED, 0),
	GATE(CLK_SCLK_MEDIA_PLL_TOP, "sclk_media_pll_top", "ffac_media_pll_div2", CLK_ENABLE_SCLK_MEDIA_PLL_TOP, 0, CLK_IGNORE_UNUSED, 0),
	GATE(CLK_SCLK_BUS_PLL_TOP, "sclk_bus_pll_top", "bus_pll", CLK_ENABLE_SCLK_BUS_PLL_TOP, 0, CLK_IGNORE_UNUSED, 0),
};

struct samsung_pll_rate_table table_bus[] = {
	{ 825000000U,	26,	825,	0,	0 },
	{ 800000000U,	13,	400,	0,	0 },
};

struct samsung_pll_rate_table table_media[] = {
	{ 1334000000U,	13,	667,	0,	0 },
	{ 1332000000U,	13,	666,	0,	0 },
};

struct samsung_pll_rate_table table_mem0[] = {
	{ 1650000000U,	13,	825,	0,	0 }, /* L0 */
	{ 1332000000U,	13,	666,	0,	0 }, /* L1 */
	{ 1118000000U,	4,	344,	1,	0 }, /* L2 */
	{  676000000U,	4,	208,	1,	0 }, /* L3 */
	{  546000000U,	4,	336,	2,	0 }, /* L4 */
	{  400000000U,	13,	800,	2,	0 }, /* L5 */
};

static const struct samsung_pll_clock mif_pll_clks[] __initconst = {
	PLL(pll_2555x, CLK_MEM0_PLL, "mem0_pll", "oscclk", MEM0_PLL_LOCK, MEM0_PLL_CON0, table_mem0),
	PLL(pll_2555x, 0, "media_pll", "oscclk", MEDIA_PLL_LOCK, MEDIA_PLL_CON0, table_media),
	PLL(pll_2551x, CLK_BUS_PLL, "bus_pll", "oscclk", BUS_PLL_LOCK, BUS_PLL_CON0, table_bus),
};

static const struct samsung_fixed_factor_clock mif_fixed_factor_clks[] __initconst = {
	FFACTOR(0, "ffac_mem0_pll_div2", "mem0_pll", 1, 2, 0),
	FFACTOR(0, "ffac_media_pll_div2", "media_pll", 1, 2, 0),
	FFACTOR(0, "ffac_media_pll_div4", "ffac_media_pll_div2", 1, 2, 0),
	FFACTOR(0, "ffac_bus_pll_div2", "bus_pll", 1, 2, 0),
};

static const struct samsung_cmu_info mif_cmu_info __initconst = {
	.pll_clks		= mif_pll_clks,
	.nr_pll_clks		= ARRAY_SIZE(mif_pll_clks),
	.mux_clks		= mif_mux_clks,
	.nr_mux_clks		= ARRAY_SIZE(mif_mux_clks),
	.gate_clks		= mif_gate_clks,
	.nr_gate_clks		= ARRAY_SIZE(mif_gate_clks),
	.div_clks		= mif_div_clks,
	.nr_div_clks		= ARRAY_SIZE(mif_div_clks),
	.fixed_factor_clks	= mif_fixed_factor_clks,
	.nr_fixed_factor_clks	= ARRAY_SIZE(mif_fixed_factor_clks),
	.nr_clk_ids		= MIF_NR_CLK,
	.clk_regs		= mif_clk_regs,
	.nr_clk_regs		= ARRAY_SIZE(mif_clk_regs),
};

static void __init exynos3475_cmu_mif_init(struct device_node *np)
{
	samsung_cmu_register_one(np, &mif_cmu_info);
}
CLK_OF_DECLARE(exynos3475_cmu_mif, "samsung,exynos3475-cmu-mif",
		exynos3475_cmu_mif_init);

/* Register Offset definitions for CMU_TOP (0x10010000) */
#define CLK_CON_MUX_BUS_PLL_USER			0x0200
#define CLK_CON_MUX_MEDIA_PLL_USER			0x0204
#define CLK_CON_MUX_ACLK_BUS0_333			0x0208
#define CLK_CON_MUX_ACLK_BUS2_333			0x020C
#define CLK_CON_MUX_ACLK_MFCMSCL_200			0x0210
#define CLK_CON_MUX_ACLK_MFCMSCL_333			0x0214
#define CLK_CON_MUX_SCLK_FSYS_MMC0_SDCLKIN		0x0218
#define CLK_CON_MUX_SCLK_FSYS_MMC1_SDCLKIN		0x021C
#define CLK_CON_MUX_SCLK_FSYS_MMC2_SDCLKIN		0x0220
#define CLK_CON_MUX_SCLK_PERI_SPI0_SPI_EXT_CLK	0x0224
#define CLK_CON_MUX_SCLK_PERI_SPI1_SPI_EXT_CLK	0x0228
#define CLK_CON_MUX_SCLK_PERI_SPI2_SPI_EXT_CLK	0x022C
#define CLK_CON_MUX_SCLK_PERI_UART0_EXT_UCLK		0x0230
#define CLK_CON_MUX_SCLK_PERI_UART1_EXT_UCLK		0x0234
#define CLK_CON_MUX_SCLK_PERI_UART2_EXT_UCLK		0x0238
#define CLK_CON_MUX_SCLK_ISP_SENSOR0			0x023C
#define CLK_CON_MUX_SCLK_ISP_SENSOR1			0x0240

#define CLK_CON_DIV_ACLK_FSYS_200			0x0400
#define CLK_CON_DIV_ACLK_IMEM_266			0x0404
#define CLK_CON_DIV_ACLK_IMEM_200			0x0408
#define CLK_CON_DIV_ACLK_BUS0_333			0x040C
#define CLK_CON_DIV_ACLK_BUS2_333			0x0410
#define CLK_CON_DIV_ACLK_PERI_66			0x0414
#define CLK_CON_DIV_ACLK_G3D_400			0x0418
#define CLK_CON_DIV_ACLK_MFCMSCL_200			0x041C
#define CLK_CON_DIV_ACLK_MFCMSCL_333			0x0420
#define CLK_CON_DIV_SCLK_FSYS_MMC0_SDCLKIN_A		0x0424
#define CLK_CON_DIV_SCLK_FSYS_MMC0_SDCLKIN_B		0x0428
#define CLK_CON_DIV_SCLK_FSYS_MMC1_SDCLKIN_A		0x042C
#define CLK_CON_DIV_SCLK_FSYS_MMC1_SDCLKIN_B		0x0430
#define CLK_CON_DIV_SCLK_FSYS_MMC2_SDCLKIN_A		0x0434
#define CLK_CON_DIV_SCLK_FSYS_MMC2_SDCLKIN_B		0x0438
#define CLK_CON_DIV_SCLK_PERI_SPI0_A			0x043C
#define CLK_CON_DIV_SCLK_PERI_SPI0_B			0x0440
#define CLK_CON_DIV_SCLK_PERI_SPI1_A			0x0444
#define CLK_CON_DIV_SCLK_PERI_SPI1_B			0x0448
#define CLK_CON_DIV_SCLK_PERI_SPI2_A			0x044C
#define CLK_CON_DIV_SCLK_PERI_SPI2_B			0x0450
#define CLK_CON_DIV_SCLK_PERI_UART0			0x0454
#define CLK_CON_DIV_SCLK_PERI_UART1			0x0458
#define CLK_CON_DIV_SCLK_PERI_UART2			0x045C
#define CLK_CON_DIV_SCLK_ISP_SENSOR0_A			0x0460
#define CLK_CON_DIV_SCLK_ISP_SENSOR0_B			0x0464
#define CLK_CON_DIV_SCLK_ISP_SENSOR1_A			0x0468
#define CLK_CON_DIV_SCLK_ISP_SENSOR1_B			0x046C

#define CLK_ENABLE_ACLK_FSYS_200_TOP			0x0800
#define CLK_ENABLE_ACLK_IMEM_266_TOP			0x0804
#define CLK_ENABLE_ACLK_IMEM_200_TOP			0x0808
#define CLK_ENABLE_ACLK_BUS0_333			0x080C
#define CLK_ENABLE_ACLK_BUS2_333			0x0810
#define CLK_ENABLE_ACLK_PERI_66			0x0814
#define CLK_ENABLE_ACLK_G3D_400			0x0818
#define CLK_ENABLE_ACLK_MFCMSCL_200_TOP		0x081C
#define CLK_ENABLE_ACLK_MFCMSCL_333_TOP		0x0820
#define CLK_ENABLE_SCLK_FSYS_MMC0_SDCLKIN_TOP		0x0824
#define CLK_ENABLE_SCLK_FSYS_MMC1_SDCLKIN_TOP		0x0828
#define CLK_ENABLE_SCLK_FSYS_MMC2_SDCLKIN_TOP		0x082C
#define CLK_ENABLE_SCLK_PERI_SPI0_SPI_EXT_CLK_TOP	0x0830
#define CLK_ENABLE_SCLK_PERI_SPI1_SPI_EXT_CLK_TOP	0x0834
#define CLK_ENABLE_SCLK_PERI_SPI2_SPI_EXT_CLK_TOP	0x0838
#define CLK_ENABLE_SCLK_PERI_UART0_EXT_UCLK_TOP	0x083C
#define CLK_ENABLE_SCLK_PERI_UART1_EXT_UCLK_TOP	0x0840
#define CLK_ENABLE_SCLK_PERI_UART2_EXT_UCLK_TOP	0x0844
#define CLK_ENABLE_SCLK_ISP_SENSOR0			0x0848
#define CLK_ENABLE_SCLK_ISP_SENSOR1			0x084C

PNAME(mout_aclk_bus0_333_p) = {"mout_media_pll_user", "mout_bus_pll_user"};
PNAME(mout_aclk_bus2_333_p) = {"mout_media_pll_user", "mout_bus_pll_user"};
PNAME(mout_aclk_mfcmscl_200_p) = {"mout_media_pll_user", "mout_bus_pll_user"};
PNAME(mout_aclk_mfcmscl_333_p) = {"mout_media_pll_user", "mout_bus_pll_user"};
PNAME(mout_sclk_fsys_mmc0_sdclkin_p) = {"mout_bus_pll_user", "mout_media_pll_user"};
PNAME(mout_sclk_fsys_mmc1_sdclkin_p) = {"mout_bus_pll_user", "mout_media_pll_user"};
PNAME(mout_sclk_fsys_mmc2_sdclkin_p) = {"mout_bus_pll_user", "mout_media_pll_user"};
PNAME(mout_sclk_peri_spi0_spi_ext_clk_p) = {"mout_bus_pll_user", "mout_media_pll_user"};
PNAME(mout_sclk_peri_spi1_spi_ext_clk_p) = {"mout_bus_pll_user", "mout_media_pll_user"};
PNAME(mout_sclk_peri_spi2_spi_ext_clk_p) = {"mout_bus_pll_user", "mout_media_pll_user"};
PNAME(mout_sclk_peri_uart0_ext_uclk_p) = {"mout_bus_pll_user", "mout_media_pll_user"};
PNAME(mout_sclk_peri_uart1_ext_uclk_p) = {"mout_bus_pll_user", "mout_media_pll_user"};
PNAME(mout_sclk_peri_uart2_ext_uclk_p) = {"mout_bus_pll_user", "mout_media_pll_user"};
PNAME(mout_sclk_isp_sensor0_p) = {"oscclk", "mout_bus_pll_user"};
PNAME(mout_sclk_isp_sensor1_p) = {"oscclk", "mout_bus_pll_user"};

static const unsigned long top_clk_regs[] __initconst = {
	CLK_CON_MUX_BUS_PLL_USER,
	CLK_CON_MUX_MEDIA_PLL_USER,
	CLK_CON_MUX_ACLK_BUS0_333,
	CLK_CON_MUX_ACLK_BUS2_333,
	CLK_CON_MUX_ACLK_MFCMSCL_200,
	CLK_CON_MUX_ACLK_MFCMSCL_333,
	CLK_CON_MUX_SCLK_FSYS_MMC0_SDCLKIN,
	CLK_CON_MUX_SCLK_FSYS_MMC1_SDCLKIN,
	CLK_CON_MUX_SCLK_FSYS_MMC2_SDCLKIN,
	CLK_CON_MUX_SCLK_PERI_SPI0_SPI_EXT_CLK,
	CLK_CON_MUX_SCLK_PERI_SPI1_SPI_EXT_CLK,
	CLK_CON_MUX_SCLK_PERI_SPI2_SPI_EXT_CLK,
	CLK_CON_MUX_SCLK_PERI_UART0_EXT_UCLK,
	CLK_CON_MUX_SCLK_PERI_UART1_EXT_UCLK,
	CLK_CON_MUX_SCLK_PERI_UART2_EXT_UCLK,
	CLK_CON_MUX_SCLK_ISP_SENSOR0,
	CLK_CON_MUX_SCLK_ISP_SENSOR1,
	CLK_CON_DIV_ACLK_FSYS_200,
	CLK_CON_DIV_ACLK_IMEM_266,
	CLK_CON_DIV_ACLK_IMEM_200,
	CLK_CON_DIV_ACLK_BUS0_333,
	CLK_CON_DIV_ACLK_BUS2_333,
	CLK_CON_DIV_ACLK_PERI_66,
	CLK_CON_DIV_ACLK_G3D_400,
	CLK_CON_DIV_ACLK_MFCMSCL_200,
	CLK_CON_DIV_ACLK_MFCMSCL_333,
	CLK_CON_DIV_SCLK_FSYS_MMC0_SDCLKIN_A,
	CLK_CON_DIV_SCLK_FSYS_MMC0_SDCLKIN_B,
	CLK_CON_DIV_SCLK_FSYS_MMC1_SDCLKIN_A,
	CLK_CON_DIV_SCLK_FSYS_MMC1_SDCLKIN_B,
	CLK_CON_DIV_SCLK_FSYS_MMC2_SDCLKIN_A,
	CLK_CON_DIV_SCLK_FSYS_MMC2_SDCLKIN_B,
	CLK_CON_DIV_SCLK_PERI_SPI0_A,
	CLK_CON_DIV_SCLK_PERI_SPI0_B,
	CLK_CON_DIV_SCLK_PERI_SPI1_A,
	CLK_CON_DIV_SCLK_PERI_SPI1_B,
	CLK_CON_DIV_SCLK_PERI_SPI2_A,
	CLK_CON_DIV_SCLK_PERI_SPI2_B,
	CLK_CON_DIV_SCLK_PERI_UART0,
	CLK_CON_DIV_SCLK_PERI_UART1,
	CLK_CON_DIV_SCLK_PERI_UART2,
	CLK_CON_DIV_SCLK_ISP_SENSOR0_A,
	CLK_CON_DIV_SCLK_ISP_SENSOR0_B,
	CLK_CON_DIV_SCLK_ISP_SENSOR1_A,
	CLK_CON_DIV_SCLK_ISP_SENSOR1_B,
	CLK_ENABLE_ACLK_FSYS_200_TOP,
	CLK_ENABLE_ACLK_IMEM_266_TOP,
	CLK_ENABLE_ACLK_IMEM_200_TOP,
	CLK_ENABLE_ACLK_BUS0_333,
	CLK_ENABLE_ACLK_BUS2_333,
	CLK_ENABLE_ACLK_PERI_66,
	CLK_ENABLE_ACLK_G3D_400,
	CLK_ENABLE_ACLK_MFCMSCL_200_TOP,
	CLK_ENABLE_ACLK_MFCMSCL_333_TOP,
	CLK_ENABLE_SCLK_FSYS_MMC0_SDCLKIN_TOP,
	CLK_ENABLE_SCLK_FSYS_MMC1_SDCLKIN_TOP,
	CLK_ENABLE_SCLK_FSYS_MMC2_SDCLKIN_TOP,
	CLK_ENABLE_SCLK_PERI_SPI0_SPI_EXT_CLK_TOP,
	CLK_ENABLE_SCLK_PERI_SPI1_SPI_EXT_CLK_TOP,
	CLK_ENABLE_SCLK_PERI_SPI2_SPI_EXT_CLK_TOP,
	CLK_ENABLE_SCLK_PERI_UART0_EXT_UCLK_TOP,
	CLK_ENABLE_SCLK_PERI_UART1_EXT_UCLK_TOP,
	CLK_ENABLE_SCLK_PERI_UART2_EXT_UCLK_TOP,
	CLK_ENABLE_SCLK_ISP_SENSOR0,
	CLK_ENABLE_SCLK_ISP_SENSOR1,
};

static const struct samsung_mux_clock top_mux_clks[] __initconst = {
	MUX(CLK_MOUT_ACLK_BUS0_333, "mout_aclk_bus0_333", mout_aclk_bus0_333_p, CLK_CON_MUX_ACLK_BUS0_333, 12, 1),
	MUX(CLK_MOUT_ACLK_BUS2_333, "mout_aclk_bus2_333", mout_aclk_bus2_333_p, CLK_CON_MUX_ACLK_BUS2_333, 12, 1),
	MUX(CLK_MOUT_ACLK_MFCMSCL_200, "mout_aclk_mfcmscl_200", mout_aclk_mfcmscl_200_p, CLK_CON_MUX_ACLK_MFCMSCL_200, 12, 1),
	MUX(CLK_MOUT_ACLK_MFCMSCL_333, "mout_aclk_mfcmscl_333", mout_aclk_mfcmscl_333_p, CLK_CON_MUX_ACLK_MFCMSCL_333, 12, 1),
	MUX(CLK_MOUT_SCLK_FSYS_MMC0_SDCLKIN, "mout_sclk_fsys_mmc0_sdclkin", mout_sclk_fsys_mmc0_sdclkin_p, CLK_CON_MUX_SCLK_FSYS_MMC0_SDCLKIN, 12, 1),
	MUX(CLK_MOUT_SCLK_FSYS_MMC1_SDCLKIN, "mout_sclk_fsys_mmc1_sdclkin", mout_sclk_fsys_mmc1_sdclkin_p, CLK_CON_MUX_SCLK_FSYS_MMC1_SDCLKIN, 12, 1),
	MUX(CLK_MOUT_SCLK_FSYS_MMC2_SDCLKIN, "mout_sclk_fsys_mmc2_sdclkin", mout_sclk_fsys_mmc2_sdclkin_p, CLK_CON_MUX_SCLK_FSYS_MMC2_SDCLKIN, 12, 1),
	MUX(0, "mout_sclk_peri_spi0_spi_ext_clk", mout_sclk_peri_spi0_spi_ext_clk_p, CLK_CON_MUX_SCLK_PERI_SPI0_SPI_EXT_CLK, 12, 1),
	MUX(0, "mout_sclk_peri_spi1_spi_ext_clk", mout_sclk_peri_spi1_spi_ext_clk_p, CLK_CON_MUX_SCLK_PERI_SPI1_SPI_EXT_CLK, 12, 1),
	MUX(0, "mout_sclk_peri_spi2_spi_ext_clk", mout_sclk_peri_spi2_spi_ext_clk_p, CLK_CON_MUX_SCLK_PERI_SPI2_SPI_EXT_CLK, 12, 1),
	MUX(0, "mout_sclk_peri_uart0_ext_uclk", mout_sclk_peri_uart0_ext_uclk_p, CLK_CON_MUX_SCLK_PERI_UART0_EXT_UCLK, 12, 1),
	MUX(0, "mout_sclk_peri_uart1_ext_uclk", mout_sclk_peri_uart1_ext_uclk_p, CLK_CON_MUX_SCLK_PERI_UART1_EXT_UCLK, 12, 1),
	MUX(0, "mout_sclk_peri_uart2_ext_uclk", mout_sclk_peri_uart2_ext_uclk_p, CLK_CON_MUX_SCLK_PERI_UART2_EXT_UCLK, 12, 1),
	MUX(CLK_MOUT_SCLK_ISP_SENSOR0, "mout_sclk_isp_sensor0", mout_sclk_isp_sensor0_p, CLK_CON_MUX_SCLK_ISP_SENSOR0, 12, 1),
	MUX(CLK_MOUT_SCLK_ISP_SENSOR1, "mout_sclk_isp_sensor1", mout_sclk_isp_sensor1_p, CLK_CON_MUX_SCLK_ISP_SENSOR1, 12, 1),
};

static const struct samsung_div_clock top_div_clks[] __initconst = {
	DIV(CLK_DOUT_ACLK_FSYS_200, "dout_aclk_fsys_200", "mout_bus_pll_user", CLK_CON_DIV_ACLK_FSYS_200, 0, 4),
	DIV(CLK_DOUT_ACLK_IMEM_266, "dout_aclk_imem_266", "mout_bus_pll_user", CLK_CON_DIV_ACLK_IMEM_266, 0, 4),
	DIV(CLK_DOUT_ACLK_IMEM_200, "dout_aclk_imem_200", "mout_bus_pll_user", CLK_CON_DIV_ACLK_IMEM_200, 0, 4),
	DIV(CLK_DOUT_ACLK_BUS0_333, "dout_aclk_bus0_333", "mout_aclk_bus0_333", CLK_CON_DIV_ACLK_BUS0_333, 0, 4),
	DIV(CLK_DOUT_ACLK_BUS2_333, "dout_aclk_bus2_333", "mout_aclk_bus2_333", CLK_CON_DIV_ACLK_BUS2_333, 0, 4),
	DIV(CLK_DOUT_ACLK_PERI_66, "dout_aclk_peri_66", "mout_bus_pll_user", CLK_CON_DIV_ACLK_PERI_66, 0, 4),
	DIV(CLK_DOUT_ACLK_G3D_400, "dout_aclk_g3d_400", "mout_bus_pll_user", CLK_CON_DIV_ACLK_G3D_400, 0, 4),
	DIV(CLK_DOUT_ACLK_MFCMSCL_200, "dout_aclk_mfcmscl_200", "mout_aclk_mfcmscl_200", CLK_CON_DIV_ACLK_MFCMSCL_200, 0, 4),
	DIV(CLK_DOUT_ACLK_MFCMSCL_333, "dout_aclk_mfcmscl_333", "mout_aclk_mfcmscl_333", CLK_CON_DIV_ACLK_MFCMSCL_333, 0, 4),
	DIV(CLK_DOUT_SCLK_FSYS_MMC0_SDCLKIN_A, "dout_sclk_fsys_mmc0_sdclkin_a", "mout_sclk_fsys_mmc0_sdclkin", CLK_CON_DIV_SCLK_FSYS_MMC0_SDCLKIN_A, 0, 4),
	DIV(CLK_DOUT_SCLK_FSYS_MMC0_SDCLKIN_B, "dout_sclk_fsys_mmc0_sdclkin_b", "dout_sclk_fsys_mmc0_sdclkin_a", CLK_CON_DIV_SCLK_FSYS_MMC0_SDCLKIN_B, 0, 8),
	DIV(CLK_DOUT_SCLK_FSYS_MMC1_SDCLKIN_A, "dout_sclk_fsys_mmc1_sdclkin_a", "mout_sclk_fsys_mmc1_sdclkin", CLK_CON_DIV_SCLK_FSYS_MMC1_SDCLKIN_A, 0, 4),
	DIV(CLK_DOUT_SCLK_FSYS_MMC1_SDCLKIN_B, "dout_sclk_fsys_mmc1_sdclkin_b", "dout_sclk_fsys_mmc1_sdclkin_a", CLK_CON_DIV_SCLK_FSYS_MMC1_SDCLKIN_B, 0, 8),
	DIV(CLK_DOUT_SCLK_FSYS_MMC2_SDCLKIN_A, "dout_sclk_fsys_mmc2_sdclkin_a", "mout_sclk_fsys_mmc2_sdclkin", CLK_CON_DIV_SCLK_FSYS_MMC2_SDCLKIN_A, 0, 4),
	DIV(CLK_DOUT_SCLK_FSYS_MMC2_SDCLKIN_B, "dout_sclk_fsys_mmc2_sdclkin_b", "dout_sclk_fsys_mmc2_sdclkin_a", CLK_CON_DIV_SCLK_FSYS_MMC2_SDCLKIN_B, 0, 8),
	DIV(0, "dout_sclk_peri_spi0_a", "mout_sclk_peri_spi0_spi_ext_clk", CLK_CON_DIV_SCLK_PERI_SPI0_A, 0, 4),
	DIV(0, "dout_sclk_peri_spi0_b", "dout_sclk_peri_spi0_a", CLK_CON_DIV_SCLK_PERI_SPI0_B, 0, 8),
	DIV(0, "dout_sclk_peri_spi1_a", "mout_sclk_peri_spi1_spi_ext_clk", CLK_CON_DIV_SCLK_PERI_SPI1_A, 0, 4),
	DIV(0, "dout_sclk_peri_spi1_b", "dout_sclk_peri_spi1_a", CLK_CON_DIV_SCLK_PERI_SPI1_B, 0, 8),
	DIV(0, "dout_sclk_peri_spi2_a", "mout_sclk_peri_spi2_spi_ext_clk", CLK_CON_DIV_SCLK_PERI_SPI2_A, 0, 4),
	DIV(0, "dout_sclk_peri_spi2_b", "dout_sclk_peri_spi2_a", CLK_CON_DIV_SCLK_PERI_SPI2_B, 0, 8),
	DIV(CLK_DOUT_SCLK_PERI_UART0, "dout_sclk_peri_uart0", "mout_sclk_peri_uart0_ext_uclk", CLK_CON_DIV_SCLK_PERI_UART0, 0, 4),
	DIV(CLK_DOUT_SCLK_PERI_UART1, "dout_sclk_peri_uart1", "mout_sclk_peri_uart1_ext_uclk", CLK_CON_DIV_SCLK_PERI_UART1, 0, 4),
	DIV(CLK_DOUT_SCLK_PERI_UART2, "dout_sclk_peri_uart2", "mout_sclk_peri_uart2_ext_uclk", CLK_CON_DIV_SCLK_PERI_UART2, 0, 4),
	DIV(CLK_DOUT_SCLK_ISP_SENSOR0_A, "dout_sclk_isp_sensor0_a", "mout_sclk_isp_sensor0", CLK_CON_DIV_SCLK_ISP_SENSOR0_A, 0, 4),
	DIV(CLK_DOUT_SCLK_ISP_SENSOR0_B, "dout_sclk_isp_sensor0_b", "dout_sclk_isp_sensor0_a", CLK_CON_DIV_SCLK_ISP_SENSOR0_B, 0, 4),
	DIV(CLK_DOUT_SCLK_ISP_SENSOR1_A, "dout_sclk_isp_sensor1_a", "mout_sclk_isp_sensor1", CLK_CON_DIV_SCLK_ISP_SENSOR1_A, 0, 4),
	DIV(CLK_DOUT_SCLK_ISP_SENSOR1_B, "dout_sclk_isp_sensor1_b", "dout_sclk_isp_sensor1_a", CLK_CON_DIV_SCLK_ISP_SENSOR1_B, 0, 4),
};

static const struct samsung_gate_clock top_gate_clks[] __initconst = {
	GATE(0, "aclk_fsys_200", "dout_aclk_fsys_200", CLK_ENABLE_ACLK_FSYS_200_TOP, 0, 0, 0),
	GATE(0, "aclk_imem_266", "dout_aclk_imem_266", CLK_ENABLE_ACLK_IMEM_266_TOP, 0, CLK_IGNORE_UNUSED, 0),
	GATE(0, "aclk_imem_200", "dout_aclk_imem_200", CLK_ENABLE_ACLK_IMEM_200_TOP, 0, CLK_IGNORE_UNUSED, 0),
	GATE(CLK_ACLK_BUS0_333, "aclk_bus0_333", "dout_aclk_bus0_333", CLK_ENABLE_ACLK_BUS0_333, 0, CLK_IGNORE_UNUSED, 0),
	GATE(CLK_ACLK_BUS2_333, "aclk_bus2_333", "dout_aclk_bus2_333", CLK_ENABLE_ACLK_BUS2_333, 0, CLK_IGNORE_UNUSED, 0),
	GATE(CLK_ACLK_PERI_66, "aclk_peri_66", "dout_aclk_peri_66", CLK_ENABLE_ACLK_PERI_66, 0, 0, 0),
	GATE(CLK_ACLK_G3D_400, "aclk_g3d_400", "dout_aclk_g3d_400", CLK_ENABLE_ACLK_G3D_400, 0, 0, 0),
	GATE(0, "aclk_mfcmscl_200", "dout_aclk_mfcmscl_200", CLK_ENABLE_ACLK_MFCMSCL_200_TOP, 0, 0, 0),
	GATE(0, "aclk_mfcmscl_333", "dout_aclk_mfcmscl_333", CLK_ENABLE_ACLK_MFCMSCL_333_TOP, 0, CLK_IGNORE_UNUSED, 0),
	GATE(CLK_SCLK_FSYS_MMC0_SDCLKIN, "sclk_fsys_mmc0_sdclkin", "dout_sclk_fsys_mmc0_sdclkin_b", CLK_ENABLE_SCLK_FSYS_MMC0_SDCLKIN_TOP, 0, 0, 0),
	GATE(CLK_SCLK_FSYS_MMC1_SDCLKIN, "sclk_fsys_mmc1_sdclkin", "dout_sclk_fsys_mmc1_sdclkin_b", CLK_ENABLE_SCLK_FSYS_MMC1_SDCLKIN_TOP, 0, 0, 0),
	GATE(CLK_SCLK_FSYS_MMC2_SDCLKIN, "sclk_fsys_mmc2_sdclkin", "dout_sclk_fsys_mmc2_sdclkin_b", CLK_ENABLE_SCLK_FSYS_MMC2_SDCLKIN_TOP, 0, 0, 0),
	GATE(0, "sclk_peri_spi0_spi_ext_clk", "dout_sclk_peri_spi0_b", CLK_ENABLE_SCLK_PERI_SPI0_SPI_EXT_CLK_TOP, 0, CLK_SET_RATE_PARENT, 0),
	GATE(0, "sclk_peri_spi1_spi_ext_clk", "dout_sclk_peri_spi1_b", CLK_ENABLE_SCLK_PERI_SPI1_SPI_EXT_CLK_TOP, 0, CLK_SET_RATE_PARENT, 0),
	GATE(0, "sclk_peri_spi2_spi_ext_clk", "dout_sclk_peri_spi2_b", CLK_ENABLE_SCLK_PERI_SPI2_SPI_EXT_CLK_TOP, 0, CLK_SET_RATE_PARENT, 0),
	GATE(0, "sclk_peri_uart0_ext_uclk", "dout_sclk_peri_uart0", CLK_ENABLE_SCLK_PERI_UART0_EXT_UCLK_TOP, 0, 0, 0),
	GATE(0, "sclk_peri_uart1_ext_uclk", "dout_sclk_peri_uart1", CLK_ENABLE_SCLK_PERI_UART1_EXT_UCLK_TOP, 0, 0, 0),
	GATE(0, "sclk_peri_uart2_ext_uclk", "dout_sclk_peri_uart2", CLK_ENABLE_SCLK_PERI_UART2_EXT_UCLK_TOP, 0, 0, 0),
	GATE(CLK_SCLK_ISP_SENSOR0, "sclk_isp_sensor0", "dout_sclk_isp_sensor0_b", CLK_ENABLE_SCLK_ISP_SENSOR0, 0, 0, 0),
	GATE(CLK_SCLK_ISP_SENSOR1, "sclk_isp_sensor1", "dout_sclk_isp_sensor1_b", CLK_ENABLE_SCLK_ISP_SENSOR1, 0, 0, 0),
	GATE(CLK_MOUT_BUS_PLL_USER, "mout_bus_pll_user", "sclk_bus_pll_top", CLK_CON_MUX_BUS_PLL_USER, 8, CLK_IGNORE_UNUSED, 0),
	GATE(CLK_MOUT_MEDIA_PLL_USER, "mout_media_pll_user", "sclk_media_pll_top", CLK_CON_MUX_MEDIA_PLL_USER, 4, CLK_IGNORE_UNUSED, 0),
};

static const struct samsung_cmu_info top_cmu_info __initconst = {
	.mux_clks		= top_mux_clks,
	.nr_mux_clks		= ARRAY_SIZE(top_mux_clks),
	.gate_clks		= top_gate_clks,
	.nr_gate_clks		= ARRAY_SIZE(top_gate_clks),
	.div_clks		= top_div_clks,
	.nr_div_clks		= ARRAY_SIZE(top_div_clks),
	.nr_clk_ids		= TOP_NR_CLK,
	.clk_regs		= top_clk_regs,
	.nr_clk_regs		= ARRAY_SIZE(top_clk_regs),
};

static void __init exynos3475_cmu_top_init(struct device_node *np)
{
	samsung_cmu_register_one(np, &top_cmu_info);
}
CLK_OF_DECLARE(exynos3475_cmu_top, "samsung,exynos3475-cmu-top",
		exynos3475_cmu_top_init);
