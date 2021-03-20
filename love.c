/******************************************************************************
 * Copyright (C) 2020		Alejandro Colomar <alx.manpages@gmail.com>    *
 * SPDX-License-Identifier:	BSD-2-Clause				      *
 ******************************************************************************/


/******************************************************************************
 ******* headers **************************************************************
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include <sys/param.h>

#define ALX_NO_PREFIX
#include <libalx/alx/robot-ur/ur.h>
#include <libalx/base/errno.h>
#include <libalx/base/stdlib.h>


/******************************************************************************
 ******* macros ***************************************************************
 ******************************************************************************/
#define ROBOT_IP	"192.168.0.1"
#define ROBOT_PORT	"30002"
#define MIN_DELAY	(100 * 1000)
#define DELAY		(MAX(3 * 1000 * 1000, MIN_DELAY))
#define TIMEOUT		(3 * 1000 * 1000)


/******************************************************************************
 ******* enum / struct / union ************************************************
 ******************************************************************************/


/******************************************************************************
 ******* static prototypes ****************************************************
 ******************************************************************************/


/******************************************************************************
 ******* main *****************************************************************
 ******************************************************************************/
int	main	(void)
{
	struct Alx_UR		*ur;
	struct Alx_UR_Pose	far;
	struct Alx_UR_Pose	out, down, left, upleft, center, upright, right;
	int			status;

	far	= UR_POSE_INIT_JOINTS(-0.106, -1.476, 1.346, -2.664, -2.224, -0.264);
	out	= UR_POSE_INIT_XYZ(-0.357, 0.127, 0.473, -1.538, 0.710, 0.485);
	down	= UR_POSE_INIT_XYZ(-0.351, 0.196, 0.482, -1.605, 0.730, 0.549);
	left	= UR_POSE_INIT_XYZ(-0.386, 0.196, 0.533, -1.375, 0.814, 0.923);
	upleft	= UR_POSE_INIT_XYZ(-0.364, 0.196, 0.565, -1.236, 0.881, 1.024);
	center	= UR_POSE_INIT_XYZ(-0.360, 0.200, 0.548, -1.295, 0.926, 0.785);
	upright	= UR_POSE_INIT_XYZ(-0.338, 0.202, 0.567, -1.181, 0.991, 0.854);
	right	= UR_POSE_INIT_XYZ(-0.320, 0.201, 0.542, -1.408, 0.883, 0.579);

	status	= EXIT_FAILURE;

	if (ur_init(&ur, ROBOT_IP))
		goto enotcon;

	if (ur_movej(ur, &far, TIMEOUT))
		goto out;
	if (ur_movej(ur, &out, TIMEOUT))
		goto out;

	if (ur_movel(ur, &down, TIMEOUT))
		goto out;
	if (ur_movel(ur, &left, TIMEOUT))
		goto out;
	if (ur_movec(ur, &upleft, &center, TIMEOUT))
		goto out;
	if (ur_movec(ur, &upright, &right, TIMEOUT))
		goto out;
	if (ur_movel(ur, &down, TIMEOUT))
		goto out;

	if (ur_movel(ur, &out, TIMEOUT))
		goto out;
	if (ur_movej(ur, &far, TIMEOUT))
		goto out;

	if (ur_puts(ur, "Hola bb"))
		goto out;
	if (ur_halt(ur, TIMEOUT))
		goto out;

	status	= EXIT_SUCCESS;
out:
	status	|= ur_deinit(ur);
enotcon:
	perrorx("out");
	return	status;
}


/******************************************************************************
 ******* static function definitions ******************************************
 ******************************************************************************/


/******************************************************************************
 ******* end of file **********************************************************
 ******************************************************************************/

