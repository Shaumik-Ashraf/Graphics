//scanline.h
//add scanline conversion

#ifndef _SCANLINE_H_
#define _SCANLINE_H_

#include"ml6.h"
#include"zbuf.h"

void h_scanline_conversion( screen s, zbuffer zbuf, color c,
                            double x0, double y0, double z0,
                            double x1, double y1, double z1,
                            double x2, double y2, double z2 );

void v_scanline_conversion( screen s, zbuffer zbuf, color c,
                            double x0, double y0, double z0,
                            double x1, double y1, double z1,
                            double x2, double y2, double z2 );


#endif

