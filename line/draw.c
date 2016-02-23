#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

//
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {


	int x=x0, y=y0;
	int A=y1-y0, B=x1-x0;
	int d;


	//octant I
	d = 2*A + B;

	while(x<=x1) {
		
		plot(s, c, x, y);
		
		if( d>0 ) {
			y += 1;
			d += (2*B);
		}
	
		x += 1;
		d += (2*A);

	}

	

	/*
	//octant II
	d=A+2*B;

	while(y<=y1) {
		
		plot(s, c, x, y);
		
		if( d>0 ) { //CHECK!!!!
			x+=1;
			d+=(2*A);
		}
	
		y+=1;
		d+=(2*B);

	}
	*/

}

