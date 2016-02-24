#include <stdio.h>
#include <stdlib.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

//
void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {

	int x=x0, y=y0;
	int A=y1-y0, B=(-1)*(x1-x0);
	int d;

	if( !(x0<x1) ) {
		draw_line(x1, y1, x0, y0, s, c);
	}
	
	if( x0==x1 ) { //vertical case - CAUSING SEG FAULT
	//	while(y<y1) {
	//		plot(s, c, x, y);
	//		y++;
	//	}
	}
	else if( y0==y1 ) {  //horizontal case
		while(x<=x1) {
			plot(s, c, x, y);
			x++;
		}
	}
	else if( A == x1-x0 ) { //diagonal case (slope=1)
		while(x<=x1) {
			plot(s, c, x, y);
			x++;
			y++;
		}
	}
	else if( A == B ) { //diagonal case (slope=-1)
		while(x<=x1) {
			plot(s, c, x, y);
			x++;
			y--;
		}
	}
	else if( (0 < A) && (A < x1-x0) ) { //octant I
		d = (2*A) + B;

		while(x<=x1) {
			
			plot(s, c, x, y);
			
			if( d>0 ) {
				y += 1;
				d += (2*B);
			}
		
			x += 1;
			d += (2*A);

		} //close loop
	}
	else if( A > x1-x0 ) { //octant II
		d = A + (2*B);

		while(y<=y1) {
			
			plot(s, c, x, y);
			
			if( d<0 ) { 
				x+=1;
				d+=(2*A);
			}
		
			y+=1;
			d+=(2*B);

		} //close loop
	}
	else;/* if( A < B ) { //octant III case
		d = A + (2*B);

		while(y<=y1) {
			
			plot(s, c, x, y);
			
			if( d<0 ) { 
				x-=1;
				d+=(2*A);
			}
		
			y+=1;
			d+=(2*B);

		} //close loop
	}
	else if( B < A && A < 0 ) {  //octant IV case
		d = (2*A) + B;

		while(x<=x1) {
			
			plot(s, c, x, y);
			
			if( d>0 ) {
				y -= 1;
				d += (2*B);
			}
		
			x += 1;
			d += (2*A);

		} //close loop
	}
	else;*/

}

