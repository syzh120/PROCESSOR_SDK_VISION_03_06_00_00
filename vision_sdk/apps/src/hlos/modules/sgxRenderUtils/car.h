/*
 *******************************************************************************
 *
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 */

#ifndef _CAR_H_
#define _CAR_H_

#ifdef __cplusplus
extern "C" {
#endif

int car_init();
int car_deinit();
void car_draw(int viewport_id);
void car_updateView(int viewport_id);
void car_change();
void car_getScreenLimits(int *xmin, int *xmax, int *ymin, int *ymax);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /*   _CAR_H_    */
