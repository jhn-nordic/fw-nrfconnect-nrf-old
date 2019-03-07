/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: LicenseRef-BSD-5-Clause-Nordic
 */

#include <misc/util.h>
#include <soc.h>

#include "port_state.h"


static const struct pin_state port0_on[] = {

{30,  0}, /* LED3 */
};




static const struct pin_state port0_off[] = {
	{30,  1}, /* LED3 */
};




const struct port_state port_state_on[] = {
	{
		.name     = DT_GPIO_P0_DEV_NAME,
		.ps       = port0_on,
		.ps_count = ARRAY_SIZE(port0_on),
	},

};

const size_t port_state_on_size = ARRAY_SIZE(port_state_on);

const struct port_state port_state_off[] = {
	{
		.name     = DT_GPIO_P0_DEV_NAME,
		.ps       = port0_off,
		.ps_count = ARRAY_SIZE(port0_off),
	},

};

const size_t port_state_off_size = ARRAY_SIZE(port_state_off);
