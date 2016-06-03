//scanline.c
//implement scanline conversion
//Shaumik Ashraf, 6/3/16

#include"scanline.h"

#include"ml6.h"
#include"zbuf.h"


void h_scanline_conversion( screen s, zbuffer zbuf, color c,
                            double x0, double y0, double z0,
                            double x1, double y1, double z1,
                            double x2, double y2, double z2 ) {

    double btm_x, btm_y, btm_z;
    double mid_x, mid_y, mid_z;
    double top_x, top_y, top_z;

    //identify bottom, middle, and top points
    if( y0 < y1 && y0 < y2 ) {
	//point0 is on bottom
	btm_x = x0;
	btm_y = y0;
	btm_z = z0;

	if( y1 < y2 ) {
		//point1 is in middle
		mid_x = x1;
		mid_y = y1;
		mid_z = z1;

		//point2 is on top
		top_x = x2;
		top_y = y2;
		top_z = z2;
	}
	else {
		//point1 is on top
		top_x = x1;
		top_y = y1;
		top_z = z1;

		//point2 is in middle
		mid_x = x2;
		mid_y = y2;
		mid_z = z2;
	}
    }
    else if( y1 < y0 && y1 < y2 ) {
	//point1 is on bottom
	btm_x = x1;
	btm_y = y1;
	btm_z = z1;

	if( y0 < y2 ) {
		//point0 is in middle
		mid_x = x0;
		mid_y = y0;
		mid_z = z0;

		//point2 is on top
		top_x = x2;
		top_y = y2;
		top_z = z2;
	}
	else {
		//point0 is on top
		top_x = x0;
		top_y = y0;
		top_z = z0;

		//point2 is in middle
		mid_x = x2;
		mid_y = y2;
		mid_z = z2;
	}
    }
    else if( y1==y0 && y1<y2 ){
	//point0 and point 1 are on bottom

	//let point0 be on bottom
	btm_x = x0;
	btm_y = y0;
	btm_z = z0;

	//let point1 be on middle
	mid_x = x1;
	mid_y = y1;
	mid_z = z1;

	//point2 is on top
	top_x = x2;
	top_y = y2;
	top_z = z2;
    }
    else {
	//point2 is on bottom
	btm_x = x2;
	btm_y = y2;
	btm_z = z2;

	if( y0 < y1 ) {
		//point0 is middle
		mid_x = x0;
		mid_y = y0;
		mid_z = z0;

		//point1 is top

	}
	else {
		//point0 is top
		top_x = x0;
		top_y = y0;
		top_z = z0;

		//point1 is middle
		mid_x = x1;
		mid_y = y1;
		mid_z = z1;
	}
    }

}

void v_scanline_conversion( screen s, zbuffer zbuf, color c,
                            double x0, double y0, double z0,
                            double x1, double y1, double z1,
                            double x2, double y2, double z2 );


