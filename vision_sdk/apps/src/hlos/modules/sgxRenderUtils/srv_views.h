#ifndef __SRV_VIEWS_H
#define __SRV_VIEWS_H

//Joystick button - view
//16 -1 =  left
//16 +1 = right
//17 -1 = front
//17 +1 = back
//292 1 = Zoom out
//293 1 = Zoom in
//290 1 = blindspot left
//291 1 = blindspot right
//6 0 = Enable joystick
//6 anything else = disable joystick

#define MAX_SRV_VIEWS 10

#define SRV_VIEW_ZOOMED_OUT 0
#define SRV_VIEW_ZOOMED_IN 1
#define SRV_VIEW_FRONT 2
#define SRV_VIEW_BACK 3
#define SRV_VIEW_LEFT 4
#define SRV_VIEW_RIGHT 5
#define SRV_VIEW_BS_LEFT 6
#define SRV_VIEW_BS_RIGHT 7

typedef struct _srv_coords_t
{
	float camx;
	float camy;
	float camz;
	float targetx;
	float targety;
	float targetz;
	float anglex;
	float angley;
	float anglez;
} srv_coords_t;

void srv_views_init();
#endif
