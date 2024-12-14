/*
 * Copyright (C) 2020 Zhao, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 */
#include "ddp_dsi.h"

/*
struct LCM_setting_table {
	unsigned int cmd;
	unsigned char count;
	unsigned char para_list[64];
};
*/

struct ddp_lcm_write_cmd_table dimming_on[1] = {
	{0x53, 1, {0x2C} },
	};
/*****************************truly HBM start*********************/
struct LCM_setting_table truly_hbm_off[1] = {
	{0x51, 2, {0x06,0x28} },
};
struct LCM_setting_table truly_hbm1_on[1] = {
	{0x51, 2, {0x06,0xc5} },
};
struct LCM_setting_table truly_hbm2_on[1] = {
	{0x51, 2, {0x07,0x62} },
};
struct LCM_setting_table truly_hbm3_on[1] = {
	{0x51, 2, {0x07,0xFF} },
};
/*****************************truly HBM end**************************/

/*****************************boe HBM start***********************/
struct LCM_setting_table boe_hbm_off[1] = { //2047-1617=430, 430/3=143
	{0x51, 2, {0xca,0x02} }, //1617=0x651, 0x651<<1=0xca2, 0x2&0xe=0x2
};
struct LCM_setting_table boe_hbm1_on[1] = {
	{0x51, 2, {0xdc,0x00} }, //1760=0x6e0, 0x6e0<<1=0xdc0, 0x0&0xe=0x0
};
struct LCM_setting_table boe_hbm2_on[1] = {
	{0x51, 2, {0xf1,0x04} }, //1903=0x78a, 0x78a<<1=0xf14, 0x4&0xe=0x4
};
struct LCM_setting_table boe_hbm3_on[1] = {
	{0x51, 2, {0xff,0x02} }, //2047=0x7ff, 0x7ff<<1=0xffe, 0xe&0xe=0xe
};
/*****************************boe HBM end**************************/

struct ddp_lcm_write_cmd_table cabc_level0[] = {
	{0x55, 1, {0x00} },
};
struct ddp_lcm_write_cmd_table cabc_level1[] = {
	{0x55, 1, {0x01} },
};
struct ddp_lcm_write_cmd_table cabc_level2[] = {
	{0x55, 1, {0x02} },
};
struct ddp_lcm_write_cmd_table cabc_level3[] = {
	{0x55, 1, {0x03} },
};

//write unlock
struct LCM_setting_table cabc_write_unlock_3rd[] = {
	{0xB0, 0x01, {0x04}},
};
struct LCM_setting_table cabc_write_lock_3rd[] = {
	{0xB0, 0x01, {0x03}},
};

struct LCM_setting_table cabc_D6_3rd[] = {
	{0xD6, 0x01, {0x00}},
};

//ui
struct LCM_setting_table cabc1_on_3rd[] = {
	{0xB8, 0x06, {0x02,0x8E,0x40,0x10,0x39,0x26}},
};
struct LCM_setting_table cabc1_off_3rd[] = {
	{0xB8, 0x06, {0x02,0x8E,0x40,0x10,0x39,0x00}},
};
//movie
struct LCM_setting_table cabc2_on_3rd[] = {
	{0xB9, 0x06, {0x02,0x7B,0x6A,0x10,0x4B,0x72}},
};
struct LCM_setting_table cabc2_off_3rd[] = {
	{0xB9, 0x06, {0x02,0x7B,0x6A,0x10,0x4B,0x00}},
};
//still
struct LCM_setting_table cabc3_on_3rd[] = {
	{0xBA, 0x06, {0x02,0x8C,0x60,0x10,0x5F,0xE8}},
};
struct LCM_setting_table cabc3_off_3rd[] = {
	{0xBA, 0x06, {0x02,0x8C,0x60,0x10,0x5F,0x00}},
};


struct LCM_setting_table cabc1_3rd[] = {
	{0x55, 1, {0x01} },
};
struct LCM_setting_table cabc2_3rd[] = {
	{0x55, 1, {0x02} },
};
struct LCM_setting_table cabc3_3rd[] = {
	{0x55, 1, {0x03} },
};

//ui
struct LCM_setting_table cabc_ui_on_4th[] = {
	{0x55, 1, {0x01}},
};
//movie
struct LCM_setting_table cabc_mov_on_4th[] = {
	{0x55, 1, {0x03}},
};
//still
struct LCM_setting_table cabc_still_on_4th[] = {
	{0x55, 1, {0x02}},
};
//cabc off
struct LCM_setting_table cabc_off_on_4th[] = {
	{0x55, 1, {0x00}},
};