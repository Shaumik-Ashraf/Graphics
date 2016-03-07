#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"

#define TO_RADIAN(x) (x*(3.141592/180))
#define TO_DEGREE(x) (x*(180/3.141592))

int main() {

  screen s;
  color c;
 
  
  c.red = 0;
  c.green = MAX_COLOR;
  c.blue = 0;
  
  clear_screen(s);


  //octant 1
  draw_line( 0, 0, XRES-1, YRES - 75, s, c);

  //octant 2
  draw_line( 0, 0, XRES - 75, YRES-1, s, c); 

  //octant 8
  draw_line( 0, YRES-1, XRES-1, 75, s, c);  
  //octant 7
  draw_line( 0, YRES-1, XRES - 75, 0, s, c);

  c.green = 0;
  c.blue = MAX_COLOR;
  //octant 5
  draw_line( XRES - 1, YRES - 1, 0, 75, s, c);
  //octant 6
  draw_line( XRES - 1, YRES -1, 75, 0, s, c);
  //octant 4
  draw_line( XRES - 1, 0, 0, YRES - 75, s, c);
  //octant 3
  draw_line( XRES - 1, 0, 75, YRES - 1, s, c);
  
  c.blue = 0;
  c.red = MAX_COLOR;
  //y = x, y = -x
  draw_line( 0, 0, XRES - 1, YRES - 1, s, c);
  draw_line( 0, YRES - 1, XRES - 1, 0, s, c);

  //horizontal, vertical line
  draw_line( 0, YRES / 2, XRES - 1, YRES / 2, s, c);
  draw_line(XRES/2, 0, XRES/2, YRES-1, s, c);
  
//*/

  //display(s);
  save_extension(s, "lines.png");
  //save_ppm(s, "lines.ppm");

  //Draw gallery line submission
  
  clear_screen(s);
  
  
  int i, j, k;
  int theta = 30;
  int dtheta = 15;
  int x=XRES, y=0;
  int tx, ty;
  
  c.red = 0;
  c.green = 0;
  c.blue = MAX_COLOR;
  
  for(i=0; i<50; i++) {
  	
  	draw_line(0, 0, x, y, s, c);
  	
  	theta += dtheta;
  	dtheta -= (50-i);
  	if( dtheta < 2 ) {
  		dtheta = 2;
  	}
  	
  	tx = x;
  	ty = y;
  	
  	x = (int)(tx*cos( TO_RADIAN(theta) ) - ty*sin( TO_RADIAN(theta) ));
  	y = (int)(tx*sin( TO_RADIAN(theta) ) + ty*cos( TO_RADIAN(theta) ));
  	
  	//x*= i;
  	//y*= i;
  	
  }
  
  save_extension(s, "gallery_lines.png");
  
}  
