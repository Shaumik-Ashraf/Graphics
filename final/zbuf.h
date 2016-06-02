/* zbuf.h
Headerfile to implement zbuffering
Shaumik Ashraf 6/2/16
*/

#ifndef _ZBUF_H_
#define _ZBUF_H_

#include"ml6.h"

typedef zbuffer double[XRES][YRES];

void add_zbuf(zbuffer zbuf, double x, double y, double z);


#endif
