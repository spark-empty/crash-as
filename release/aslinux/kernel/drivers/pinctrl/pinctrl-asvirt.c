/**
 * AS - the open source Automotive Software on https://github.com/parai
 *
 * Copyright (C) 2016  AS <parai@foxmail.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */
/* ============================ [ INCLUDES  ] ====================================================== */
#define DEBUG
#include <linux/init.h>
#include <linux/module.h>
#include <linux/irq.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/err.h>
#include <linux/pinctrl/pinctrl.h>
#include <linux/pinctrl/pinmux.h>
#include <linux/pinctrl/consumer.h>
#include <linux/pinctrl/machine.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>
#include <linux/bitops.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>
/* ============================ [ MACROS    ] ====================================================== */
#define ASVIRT_PIN_GROUP(n, p)  \
	{			\
		.name = n,	\
		.pins = p,	\
		.num_pins = ARRAY_SIZE(p),	\
	}

#define ASVIRT_PMX_FUNCTION(n, g)		\
	{					\
		.name = n,			\
		.groups = g,			\
		.num_groups = ARRAY_SIZE(g),	\
	}

#define DRIVER_NAME "pinmux-as"
/* ============================ [ TYPES     ] ====================================================== */
 /**
 * struct asvirt_pin_group - describes a ASVIRT pin group
 * @name: the name of this specific pin group
 * @pins: an array of discrete physical pins used in this group, taken
 *	from the driver-local pin enumeration space
 * @num_pins: the number of pins in this group array, i.e. the number of
 *	elements in .pins so we can iterate over that array
 */
struct asvirt_pin_group {
	const char *name;
	const unsigned int *pins;
	const unsigned num_pins;
};

struct asvirt_pmx_func {
	const char *name;
	const char * const *groups;
	const unsigned num_groups;
};

struct asvirt_pinctrl_data
{
	const u32 magic;
	const char* driver_name;

	const struct asvirt_pin_group *grps;
	int grps_cnt;

	const struct asvirt_pmx_func *funcs;
	int funcs_cnt;
};

/**
 * @dev: a pointer back to containing device
 * @virtbase: the offset to the controller in virtual memory
 */
struct asvirt_pmx {
	struct device *dev;
	struct pinctrl_dev *pmx;
	u32 idx;
	const struct asvirt_pinctrl_data* pinctrl_data;
};
/* ============================ [ DECLARES  ] ====================================================== */
static int asvirt_get_groups_count(struct pinctrl_dev *pctldev);
static const char *asvirt_get_group_name(struct pinctrl_dev *pctldev,
				       unsigned selector);
static int asvirt_get_group_pins(struct pinctrl_dev *pctldev,
				unsigned selector,
				const unsigned **pins,
				unsigned *num_pins);
static void asvirt_pin_dbg_show(struct pinctrl_dev *pctldev,
				struct seq_file *s, unsigned offset);
static int asvirt_dt_node_to_map(struct pinctrl_dev *pctldev,
				 struct device_node *np_config,
				 struct pinctrl_map **map, unsigned *num_maps);
static void asvirt_dt_free_map(struct pinctrl_dev *pctldev,
		struct pinctrl_map *map, unsigned num_maps);

static int asvirt_pinmux_set_mux(struct pinctrl_dev *pmxdev,
				unsigned selector,
				unsigned group);
static int asvirt_pinmux_get_funcs_count(struct pinctrl_dev *pmxdev);
static const char *asvirt_pinmux_get_func_name(struct pinctrl_dev *pctldev,
					  unsigned selector);
static int asvirt_pinmux_get_groups(struct pinctrl_dev *pctldev,
				unsigned selector,
				const char * const **groups,
				unsigned * const num_groups);
static int asvirt_pinmux_request_gpio(struct pinctrl_dev *pmxdev,
	struct pinctrl_gpio_range *range, unsigned offset);

static int asvirt_pctl_probe(struct platform_device *pdev);
/* ============================ [ DATAS     ] ====================================================== */
static const struct pinctrl_pin_desc asvirt_pads[] = {
	PINCTRL_PIN(0, "pin0"),
	PINCTRL_PIN(1, "pin1"),
	PINCTRL_PIN(2, "pin2"),
	PINCTRL_PIN(3, "pin3"),
	PINCTRL_PIN(4, "pin4"),
	PINCTRL_PIN(5, "pin5"),
	PINCTRL_PIN(6, "pin6"),
	PINCTRL_PIN(7, "pin7"),
	PINCTRL_PIN(8, "pin8"),
	PINCTRL_PIN(9, "pin9"),
	PINCTRL_PIN(10, "pin10"),
	PINCTRL_PIN(11, "pin11"),
	PINCTRL_PIN(12, "pin12"),
	PINCTRL_PIN(13, "pin13"),
	PINCTRL_PIN(14, "pin14"),
	PINCTRL_PIN(15, "pin15")
};
static const unsigned int pingrp0_pins[] = { 0 , 1 , 2 , 3 };
static const unsigned int pingrp1_pins[] = { 4 , 5 , 6 , 7 };
static const unsigned int pingrp2_pins[] = { 8 , 9 ,10 ,11 };
static const unsigned int pingrp3_pins[] = {12 ,13 ,14 ,15 };
static const struct asvirt_pin_group asvirt_pin_groups[] = {
	ASVIRT_PIN_GROUP("pingrp0", pingrp0_pins),
	ASVIRT_PIN_GROUP("pingrp1", pingrp1_pins),
	ASVIRT_PIN_GROUP("pingrp2", pingrp2_pins),
	ASVIRT_PIN_GROUP("pingrp3", pingrp3_pins)
};

static const char * const pingrp0_fname[] = { "pingrp0","grp0-func2" };
static const char * const pingrp1_fname[] = { "pingrp1" };
static const char * const pingrp2_fname[] = { "pingrp2","grp2-func2" };
static const char * const pingrp3_fname[] = { "pingrp3" };

static const struct asvirt_pmx_func asvirt_pmx_functions[] = {
	ASVIRT_PMX_FUNCTION("general pingrp0", pingrp0_fname),
	ASVIRT_PMX_FUNCTION("general pingrp1", pingrp1_fname),
	ASVIRT_PMX_FUNCTION("general pingrp2", pingrp2_fname),
	ASVIRT_PMX_FUNCTION("general pingrp3", pingrp3_fname),
};

static struct asvirt_pinctrl_data as_pinctrl_data=
{
	.magic = 0xdeadbeef,
	.driver_name = "pinctrl-asvirt",
	.grps = asvirt_pin_groups,
	.grps_cnt = ARRAY_SIZE(asvirt_pin_groups),

	.funcs = asvirt_pmx_functions,
	.funcs_cnt = ARRAY_SIZE(asvirt_pin_groups)
};

static struct of_device_id asvirt_pctl_of_match[] = {
	{ .compatible = "as,virtual-pinctrl", .data = &as_pinctrl_data },
};

static struct platform_driver asvirt_pctl_driver = {
	.driver = {
		.name = " "DRIVER_NAME,
		.owner = THIS_MODULE,
		.of_match_table = asvirt_pctl_of_match,
	},
	.probe = asvirt_pctl_probe,
};

static struct pinctrl_ops asvirt_pctrl_ops = {
	.get_groups_count = asvirt_get_groups_count,
	.get_group_name = asvirt_get_group_name,
	.get_group_pins = asvirt_get_group_pins,
	.pin_dbg_show = asvirt_pin_dbg_show,
	.dt_node_to_map = asvirt_dt_node_to_map,
	.dt_free_map = asvirt_dt_free_map,
};

static struct pinmux_ops asvirt_pinmux_ops = {
	.set_mux = asvirt_pinmux_set_mux,
	.get_functions_count = asvirt_pinmux_get_funcs_count,
	.get_function_name = asvirt_pinmux_get_func_name,
	.get_function_groups = asvirt_pinmux_get_groups,
	.gpio_request_enable = asvirt_pinmux_request_gpio,
};

static struct pinctrl_desc asvirt_pinmux_desc = {
	.name = DRIVER_NAME,
	.pctlops = &asvirt_pctrl_ops,
	.pmxops = &asvirt_pinmux_ops,
	.owner = THIS_MODULE,
    .pins  = asvirt_pads,
    .npins = ARRAY_SIZE(asvirt_pads),
};
/* ============================ [ LOCALS    ] ====================================================== */
/* Returns the count of total number of groups registered
 * TODO: research how it was called and used */
static int asvirt_get_groups_count(struct pinctrl_dev *pctldev)
{
	struct asvirt_pmx *spmx = pinctrl_dev_get_drvdata(pctldev);

	pr_debug("asvirt_get_groups_count of pinctrl.%d\n",spmx->idx);

	return spmx->pinctrl_data->grps_cnt;
}

/* return the group name of the pin group */
static const char *asvirt_get_group_name(struct pinctrl_dev *pctldev,
				       unsigned selector)
{
	struct asvirt_pmx *spmx = pinctrl_dev_get_drvdata(pctldev);

	pr_debug("asvirt_get_group_name of pinctrl.%d\n",spmx->idx);

	return spmx->pinctrl_data->grps[selector].name;
}
/* return an array of pins corresponding to a certain
 *	group selector @pins, and the size of the array in @num_pins
 */
static int asvirt_get_group_pins(struct pinctrl_dev *pctldev,
				unsigned selector,
				const unsigned **pins,
				unsigned *num_pins)
{
	struct asvirt_pmx *spmx = pinctrl_dev_get_drvdata(pctldev);

	pr_debug("asvirt_get_group_pins of pinctrl.%d\n",spmx->idx);
	*pins = spmx->pinctrl_data->grps[selector].pins;
	*num_pins = spmx->pinctrl_data->grps[selector].num_pins;
	return 0;
}
/* optional debugfs display hook that will provide per-device
 *	info for a certain pin in debugfs
 */
static void asvirt_pin_dbg_show(struct pinctrl_dev *pctldev,
				struct seq_file *s, unsigned offset)
{
	struct asvirt_pmx *spmx = pinctrl_dev_get_drvdata(pctldev);
	seq_printf(s, spmx->pinctrl_data->driver_name);
}
/*  parse a device tree "pin configuration node", and create
 *	mapping table entries for it. These are returned through the @map and
 *	@num_maps output parameters. This function is optional, and may be
 *	omitted for pinctrl drivers that do not support device tree.
 */
static int asvirt_dt_node_to_map(struct pinctrl_dev *pctldev,
				 struct device_node *np_config,
				 struct pinctrl_map **map, unsigned *num_maps)
{
	struct asvirt_pmx *spmx = pinctrl_dev_get_drvdata(pctldev);
	struct device_node *np;
	struct property *prop;
	const char *function, *group;
	int ret, index = 0, count = 0;

	/* calculate number of maps required */
	for_each_child_of_node(np_config, np) {
		ret = of_property_read_string(np, "as,function", &function);
		if (ret < 0)
			return ret;

		ret = of_property_count_strings(np, "as,pins");
		if (ret < 0)
			return ret;

		count += ret;
	}

	if (!count) {
		dev_err(spmx->dev, "No child nodes passed via DT\n");
		return -ENODEV;
	}

	*map = kzalloc(sizeof(**map) * count, GFP_KERNEL);
	if (!*map)
		return -ENOMEM;

	for_each_child_of_node(np_config, np) {
		of_property_read_string(np, "as,function", &function);
		of_property_for_each_string(np, "as,pins", prop, group) {
			(*map)[index].type = PIN_MAP_TYPE_MUX_GROUP;
			(*map)[index].data.mux.group = group;
			(*map)[index].data.mux.function = function;
			index++;
		}
	}

	*num_maps = count;
	return 0;
}
/* free mapping table entries created via @dt_node_to_map. The
 *	top-level @map pointer must be freed, along with any dynamically
 *	allocated members of the mapping table entries themselves. This
 *	function is optional, and may be omitted for pinctrl drivers that do
 *	not support device tree.
 */
static void asvirt_dt_free_map(struct pinctrl_dev *pctldev,
		struct pinctrl_map *map, unsigned num_maps)
{
	kfree(map);
}

static void asvirt_pinmux_endisable(struct asvirt_pmx *spmx,
					unsigned selector, bool enable)
{

}
/* enable a certain muxing function with a certain pin group. The
 *	driver does not need to figure out whether enabling this function
 *	conflicts some other use of the pins in that group, such collisions
 *	are handled by the pinmux subsystem. The @func_selector selects a
 *	certain function whereas @group_selector selects a certain set of pins
 *	to be used. On simple controllers the latter argument may be ignored
 */
static int asvirt_pinmux_set_mux(struct pinctrl_dev *pmxdev,
				unsigned selector,
				unsigned group)
{
	/* okay, as I see the pinctrl-sirf ingore the group_selector */
	struct asvirt_pmx *spmx = pinctrl_dev_get_drvdata(pmxdev);
	asvirt_pinmux_endisable(spmx, selector, true);

	pr_debug("asvirt_pinmux_set_mux(%d,%d) of pinctrl.%d\n",selector,group,spmx->idx);
	return 0;
}

static int asvirt_pinmux_get_funcs_count(struct pinctrl_dev *pmxdev)
{
	struct asvirt_pmx *spmx = pinctrl_dev_get_drvdata(pmxdev);
	pr_debug("asvirt_pinmux_get_funcs_count of pinctrl.%d\n",spmx->idx);
	return spmx->pinctrl_data->funcs_cnt;
}

static const char *asvirt_pinmux_get_func_name(struct pinctrl_dev *pctldev,
					  unsigned selector)
{
	struct asvirt_pmx *spmx = pinctrl_dev_get_drvdata(pctldev);
	pr_debug("asvirt_pinmux_get_func_name(%d) of pinctrl.%d\n",selector,spmx->idx);
	return spmx->pinctrl_data->funcs[selector].name;
}

static int asvirt_pinmux_get_groups(struct pinctrl_dev *pctldev,
				unsigned selector,
				const char * const **groups,
				unsigned * const num_groups)
{
	struct asvirt_pmx *spmx = pinctrl_dev_get_drvdata(pctldev);
	*groups = spmx->pinctrl_data->funcs[selector].groups;
	*num_groups = spmx->pinctrl_data->funcs[selector].num_groups;
	pr_debug("asvirt_pinmux_get_groups of pinctrl.%d\n",spmx->idx);
	return 0;
}

static int asvirt_pinmux_request_gpio(struct pinctrl_dev *pmxdev,
	struct pinctrl_gpio_range *range, unsigned offset)
{
	struct asvirt_pmx *spmx;

	int group = range->id;

	spmx = pinctrl_dev_get_drvdata(pmxdev);

	/* here go on to set mode to GPIO */
	pr_debug("asvirt_pinmux_request_gpio group(%d) of pinctrl.%d\n",group,spmx->idx);

	return 0;
}

static int asvirt_pctl_probe(struct platform_device *pdev)
{
	int ret;
	struct asvirt_pmx *spmx;
	struct device_node *np = pdev->dev.of_node;
	const struct asvirt_pinctrl_data *pdata;
	u32 regs[2];

	/* Create state holders etc for this driver */
	spmx = devm_kzalloc(&pdev->dev, sizeof(*spmx), GFP_KERNEL);
	if (!spmx)
		return -ENOMEM;

	spmx->dev = &pdev->dev;

	platform_set_drvdata(pdev, spmx);

	/* check pinctrl-sirf, it call of_iomap to map the register memory area,
	 * but this is a virtual platform but keep the almost the same
	 * DTS as sirf atlas6, so use API of_property_read_u32_array to
	 * get the information.
	 */
	ret = of_property_read_u32_array(np,"reg",regs,2);

	if(ret)
	{
		dev_err(&pdev->dev, "could not get the reg info from DTS ret=%d\n",ret);
		ret = -EINVAL;
		goto out_no_pmx;
	}
	/* store the idx of the pinctrl */
	spmx->idx = regs[0];

	/* this is that used to support different kind of chips of the same vendor */
	pdata = of_match_node(asvirt_pctl_of_match, np)->data;
	spmx->pinctrl_data = pdata;
	/* Now register the pin controller and all pins it handles */
	spmx->pmx = pinctrl_register(&asvirt_pinmux_desc, &pdev->dev, spmx);
	if (!spmx->pmx) {
		dev_err(&pdev->dev, "could not register ASVIRT pinmux driver\n");
		ret = -EINVAL;
		goto out_no_pmx;
	}

	dev_info(&pdev->dev, "initialized ASVIRT pinmux driver\n");

	return 0;

out_no_pmx:
	return ret;
}
static int __init asvirt_pctl_init(void)
{
	return platform_driver_register(&asvirt_pctl_driver);
}
/* ============================ [ FUNCTIONS ] ====================================================== */

subsys_initcall(asvirt_pctl_init);
