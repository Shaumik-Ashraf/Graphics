#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

/*======== void add_polygon() ==========
Inputs:   struct matrix *surfaces
         double x0
         double y0
         double z0
         double x1
         double y1
         double z1
         double x2
         double y2
         double z2  
Returns: 
Adds the vertices (x0, y0, z0), (x1, y1, z1)
and (x2, y2, z2) to the polygon matrix. They
define a single triangle surface.

04/16/13 13:05:59
jdyrlandweaver
====================*/
void add_polygon( struct matrix *polygons, 
		  double x0, double y0, double z0, 
		  double x1, double y1, double z1, 
		  double x2, double y2, double z2 ) {

  add_point( polygons, x0, y0, z0 );
  add_point( polygons, x1, y1, z1 );
  add_point( polygons, x2, y2, z2 );
  
}

/*======== void draw_polygons() ==========
Inputs:   struct matrix *polygons
          screen s
          color c  
Returns: 
Goes through polygons 3 points at a time, drawing 
lines connecting each points to create bounding
triangles

04/16/13 13:13:27
jdyrlandweaver
====================*/
void draw_polygons( struct matrix *polygons, screen s, color c ) {

  int i;

  for(i=0; i<polygons->lastcol-3 ; i+=3) {
    //Draw P_i to P_i+1
    draw_line( polygons->m[0][i], polygons->m[1][i],
	       polygons->m[0][i+1], polygons->m[1][i+1],
	       s, c );

    //Draw P_i+1 to P_i+2
    draw_line( polygons->m[0][i+1], polygons->m[1][i+1],
	       polygons->m[0][i+2], polygons->m[1][i+2],
	       s, c );

    //Draw P_i+2 to P_i
    draw_line( polygons->m[0][i+2], polygons->m[1][i+1],
	       polygons->m[0][i], polygons->m[1][i+1],
	       s, c );
    //hopefully this works...
  }

}


/*======== void add_sphere() ==========
  Inputs:   struct matrix * points
            double cx
	    double cy
	    double r
	    double step  
  Returns: 

  adds all the points for a sphere with center 
  (cx, cy) and radius r.

  should call generate_sphere to create the
  necessary points

  jdyrlandweaver
  ====================*/
void add_sphere( struct matrix * points, 
		 double cx, double cy, double r, 
		 int step ) {

  struct matrix * temp;
  int lat, longt;
  int index;
  double x, y, z;
  int num_steps;

  num_steps = MAX_STEPS / step;

  temp = new_matrix( 4, num_steps * num_steps );
  //generate the points on the sphere
  generate_sphere( temp, cx, cy, r, step );

  int latStop, longStop, latStart, longStart;
  latStart = 0;
  latStop = num_steps;
  longStart = 0;
  longStop = num_steps;

  for ( lat = latStart; lat < latStop; lat++ ) {
    for ( longt = longStart; longt < longStop; longt++ ) {

      index = lat * (num_steps+1) + longt;
      /*
      add_edge( points, temp->m[0][index],
		temp->m[1][index],
		temp->m[2][index],
		temp->m[0][index] + 1,
		temp->m[1][index] + 1,
		temp->m[2][index] );
      */

      add_polygon( points, 
		   temp->m[0][index],
		   temp->m[1][index],
		   temp->m[2][index],

		   temp->m[0][index+1],
		   temp->m[1][index+1],
		   temp->m[2][index+1],

		   temp->m[0][index+num_steps+1],
		   temp->m[1][index+num_steps+1],
		   temp->m[2][index+num_steps+1]
		   );

      add_polygon( points, 
		   temp->m[0][index],
		   temp->m[1][index],
		   temp->m[2][index],

		   temp->m[0][index+num_steps+1],
		   temp->m[1][index+num_steps+1],
		   temp->m[2][index+num_steps+1],

		   temp->m[0][index+num_steps],
		   temp->m[1][index+num_steps],
		   temp->m[2][index+num_steps]
		   );
      
    }//end points only
  }
  free_matrix(temp);
}

/*======== void generate_sphere() ==========
  Inputs:   struct matrix * points
            double cx
	    double cy
	    double r
	    double step  
  Returns: 

  Generates all the points along the surface of a 
  sphere with center (cx, cy) and radius r

  Adds these points to the matrix parameter

  03/22/12 11:30:26
  jdyrlandweaver
  ====================*/
void generate_sphere( struct matrix * points, 
		      double cx, double cy, double r, 
		      int step ) {

  int circle, rotation;
  double x, y, z, circ, rot;

  int rotStart = step * 0;
  int rotStop = MAX_STEPS;
  int circStart = step * 0;
  int circStop = MAX_STEPS;
  
  for ( rotation = rotStart; rotation < rotStop; rotation += step ) {
    rot = (double)rotation / MAX_STEPS;
    for ( circle = circStart; circle < circStop; circle+= step ) {

      circ = (double)circle / MAX_STEPS;
      x = r * cos( 2 * M_PI * circ ) + cx;
      y = r * sin( 2 * M_PI * circ ) *
	cos( 2 * M_PI * rot ) + cy;
      z = r * sin( 2 * M_PI * circ ) *
	sin( 2 * M_PI * rot );

      add_point( points, x, y, z);
    }
  }
}    

/*======== void add_torus() ==========
  Inputs:   struct matrix * points
            double cx
	    double cy
	    double r1
	    double r2
	    double step  
  Returns: 

  adds all the points required to make a torus
  with center (cx, cy) and radii r1 and r2.

  should call generate_torus to create the
  necessary points

  03/22/12 13:34:03
  jdyrlandweaver
  ====================*/
void add_torus( struct matrix * points, 
		double cx, double cy, double r1, double r2, 
		int step ) {

  struct matrix * temp;
  int lat, longt;
  int index;
  int num_steps;
  
  num_steps = MAX_STEPS / step;

  temp = new_matrix( 4, num_steps * num_steps );
  //generate the points on the torus
  generate_torus( temp, cx, cy, r1, r2, step );

  int latStop, longtStop, latStart, longStart;
  latStart = 0;
  longStart = 0;
  latStop = num_steps;
  longtStop = num_steps;
  for ( lat = 0; lat < num_steps; lat++ )
    for ( longt = 0; longt < num_steps; longt++ ) {
      
      index = lat * num_steps + longt;
      
      add_edge( points, temp->m[0][index],
		temp->m[1][index],
		temp->m[2][index],
		temp->m[0][index] + 1,
		temp->m[1][index] + 1,
		temp->m[2][index] );
    }//end points only
}

/*======== void generate_torus() ==========
  Inputs:   struct matrix * points
            double cx
	    double cy
	    double r
	    double step  
  Returns: 

  Generates all the points along the surface of a 
  tarus with center (cx, cy) and radii r1 and r2

  Adds these points to the matrix parameter

  03/22/12 11:30:26
  jdyrlandweaver
  ====================*/
void generate_torus( struct matrix * points, 
		     double cx, double cy, double r1, double r2, 
		     int step ) {

  double x, y, z, circ, rot;
  int circle, rotation;

  double rotStart = step * 0;
  double rotStop = MAX_STEPS;
  double circStart = step * 0;
  double circStop = MAX_STEPS;

  for ( rotation = rotStart; rotation < rotStop; rotation += step ) {
    rot = (double)rotation / MAX_STEPS;
    for ( circle = circStart; circle < circStop; circle+= step ) {

      circ = (double)circle / MAX_STEPS;
      x = cos( 2 * M_PI * rot ) *
	( r1 * cos( 2 * M_PI * circ ) + r2 ) + cx;
      y = r1 * sin( 2 * M_PI * circ ) + cy;
      z = sin( 2 * M_PI * rot ) *
	( r1 * cos( 2 * M_PI * circ ) + r2 );

      add_point( points, x, y, z );
    }
  }
}

/*======== void add_box() ==========
  Inputs:   struct matrix * points
            double x
	    double y
	    double z
	    double width
	    double height
	    double depth
  Returns: 

  add the points for a rectagular prism whose 
  upper-left corner is (x, y, z) with width, 
  height and depth dimensions.

  jdyrlandweaver
  ====================*/
void add_box( struct matrix * points,
	      double x, double y, double z,
	      double width, double height, double depth ) {

  double x2, y2, z2;
  x2 = x + width;
  y2 = y - height;
  z2 = z - depth;

  /*
  add_edge( points, 
	    x, y, z, 
	    x, y, z );
  add_edge( points, 
	    x, y2, z, 
	    x, y2, z );
  add_edge( points, 
	    x2, y, z, 
	    x2, y, z );
  add_edge( points, 
	    x2, y2, z, 
	    x2, y2, z );
  add_edge( points, 
	    x, y, z2, 
	    x, y, z2 );
  add_edge( points, 
	    x, y2, z2, 
	    x, y2, z2 );
  add_edge( points, 
	    x2, y, z2, 
	    x2, y, z2 );
  add_edge( points, 
	    x2, y2, z2, 
	    x2, y2, z2 );
  */

  /*
    A = x, y, z
    B = x2, y, z
    C = x2, y2, z
    D = x, y2, z
    E = x, y2, z2
    F = x, y, z2,
    G = x2, y, z2,
    H = x2, y2, z2
   */
  
  //ADC
  add_polygon( points,
		x, y, z,
		x, y2, z,
		x2, y2, z );

  //ABC
  add_polygon( points,
		x2, y2, z,
		x2, y, z,
		x, y, z );

  //AFD
  add_polygon( points,
	       x, y, z,
	       x, y, z2,
	       x, y2, z );

  //DFE
  add_polygon( points,
	       x, y2, z,
	       x, y, z2,
	       x, y2, z2 );
  
  //EGH
  add_polygon( points,
	       x, y2, z2,
	       x2, y, z2,
	       x2, y2, z2 );

  //EFG
  add_polygon( points,
	       x, y2, z2,
	       x, y, z2,
	       x2, y, z2 );

  //HBC
  add_polygon( points,
	       x2, y2, z2,
	       x2, y, z,
	       x2, y2, z );

  //HGB
  add_polygon( points,
	       x2, y2, z2,
	       x2, y, z2,
	       x2, y, z );

  
}
  
/*======== void add_circle() ==========
  Inputs:   struct matrix * points
            double cx
	    double cy
	    double y
	    double step  
  Returns: 


  03/16/12 19:53:52
  jdyrlandweaver
  ====================*/
void add_circle( struct matrix * points, 
		 double cx, double cy, 
		 double r, double step ) {
  
  double x0, y0, x, y, t;
  
  x0 = cx + r;
  y0 = cy;

  for ( t = step; t <= 1; t+= step ) {
    
    x = r * cos( 2 * M_PI * t ) + cx;
    y = r * sin( 2 * M_PI * t ) + cy;
    
    add_edge( points, x0, y0, 0, x, y, 0 );
    x0 = x;
    y0 = y;
  }

  add_edge( points, x0, y0, 0, cx + r, cy, 0 );
}

/*======== void add_curve() ==========
Inputs:   struct matrix *points
         double x0
         double y0
         double x1
         double y1
         double x2
         double y2
         double x3
         double y3
         double step
         int type  
Returns: 

Adds the curve bounded by the 4 points passsed as parameters
of type specified in type (see matrix.h for curve type constants)
to the matrix points

03/16/12 15:24:25
jdyrlandweaver
====================*/
void add_curve( struct matrix *points, 
		double x0, double y0, 
		double x1, double y1, 
		double x2, double y2, 
		double x3, double y3, 
		double step, int type ) {

  double x, y, t;
  struct matrix * xcoefs;
  struct matrix * ycoefs;
  
  //generate the coeficients
  if ( type == BEZIER_MODE ) {
    ycoefs = generate_curve_coefs(y0, y1, y2, y3, BEZIER_MODE);
    xcoefs = generate_curve_coefs(x0, x1, x2, x3, BEZIER_MODE);
  }

  else {
    xcoefs = generate_curve_coefs(x0, x1, x2, x3, HERMITE_MODE);
    ycoefs = generate_curve_coefs(y0, y1, y2, y3, HERMITE_MODE);
  }

  /*
  printf("a = %lf b = %lf c = %lf d = %lf\n", xcoefs->m[0][0],
         xcoefs->m[1][0], xcoefs->m[2][0], xcoefs->m[3][0]);
  */

  for (t=step; t <= 1; t+= step) {
    
    x = xcoefs->m[0][0] * t * t * t + xcoefs->m[1][0] * t * t
      + xcoefs->m[2][0] * t + xcoefs->m[3][0];

    y = ycoefs->m[0][0] * t * t * t + ycoefs->m[1][0] * t * t
      + ycoefs->m[2][0] * t + ycoefs->m[3][0];

    add_edge(points, x0, y0, 0, x, y, 0);
    x0 = x;
    y0 = y;
  }

  free_matrix(xcoefs);
  free_matrix(ycoefs);
}

/*======== void add_point() ==========
Inputs:   struct matrix * points
         int x
         int y
         int z 
Returns: 
adds point (x, y, z) to points and increment points.lastcol
if points is full, should call grow on points
====================*/
void add_point( struct matrix * points, double x, double y, double z) {
  
  if ( points->lastcol == points->cols )
    grow_matrix( points, points->lastcol + 100 );

  points->m[0][points->lastcol] = x;
  points->m[1][points->lastcol] = y;
  points->m[2][points->lastcol] = z;
  points->m[3][points->lastcol] = 1;

  points->lastcol++;
}

/*======== void add_edge() ==========
Inputs:   struct matrix * points
          int x0, int y0, int z0, int x1, int y1, int z1
Returns: 
add the line connecting (x0, y0, z0) to (x1, y1, z1) to points
should use add_point
====================*/
void add_edge( struct matrix * points, 
	       double x0, double y0, double z0, 
	       double x1, double y1, double z1) {
  add_point( points, x0, y0, z0 );
  add_point( points, x1, y1, z1 );
}

/*======== void draw_lines() ==========
Inputs:   struct matrix * points
         screen s
         color c 
Returns: 
Go through points 2 at a time and call draw_line to add that line
to the screen
====================*/
void draw_lines( struct matrix * points, screen s, color c) {

  int i;

  if ( points->lastcol < 2 ) {

    printf("Need at least 2 points to draw a line!\n");
    return;
  }

  for ( i = 0; i < points->lastcol - 1; i+=2 ) {

    draw_line( points->m[0][i], points->m[1][i], 
	       points->m[0][i+1], points->m[1][i+1], s, c);

    //FOR DEMONSTRATION PURPOSES ONLY
    //draw extra pixels so points can actually be seen
    /*
    draw_line( points->m[0][i]+1, points->m[1][i], 
	       points->m[0][i+1]+1, points->m[1][i+1], s, c);
    draw_line( points->m[0][i], points->m[1][i]+1, 
	       points->m[0][i+1], points->m[1][i+1]+1, s, c);
    draw_line( points->m[0][i]-1, points->m[1][i], 
	       points->m[0][i+1]-1, points->m[1][i+1], s, c);
    draw_line( points->m[0][i], points->m[1][i]-1, 
	       points->m[0][i+1], points->m[1][i+1]-1, s, c);
    draw_line( points->m[0][i]+1, points->m[1][i]+1, 
	       points->m[0][i+1]+1, points->m[1][i+1]+1, s, c);
    draw_line( points->m[0][i]-1, points->m[1][i]+1, 
	       points->m[0][i+1]-1, points->m[1][i+1]+1, s, c);
    draw_line( points->m[0][i]-1, points->m[1][i]-1, 
	       points->m[0][i+1]-1, points->m[1][i+1]-1, s, c);
    draw_line( points->m[0][i]+1, points->m[1][i]-1, 
	       points->m[0][i+1]+1, points->m[1][i+1]-1, s, c);
    */
  } 	       
}


void draw_line(int x0, int y0, int x1, int y1, screen s, color c) {
 
  int x, y, d, dx, dy;

  x = x0;
  y = y0;
  
  //swap points so we're always draing left to right
  if ( x0 > x1 ) {
    x = x1;
    y = y1;
    x1 = x0;
    y1 = y0;
  }

  //need to know dx and dy for this version
  dx = (x1 - x) * 2;
  dy = (y1 - y) * 2;

  //positive slope: Octants 1, 2 (5 and 6)
  if ( dy > 0 ) {

    //slope < 1: Octant 1 (5)
    if ( dx > dy ) {
      d = dy - ( dx / 2 );
  
      while ( x <= x1 ) {
	plot(s, c, x, y);

	if ( d < 0 ) {
	  x = x + 1;
	  d = d + dy;
	}
	else {
	  x = x + 1;
	  y = y + 1;
	  d = d + dy - dx;
	}
      }
    }

    //slope > 1: Octant 2 (6)
    else {
      d = ( dy / 2 ) - dx;
      while ( y <= y1 ) {

	plot(s, c, x, y );
	if ( d > 0 ) {
	  y = y + 1;
	  d = d - dx;
	}
	else {
	  y = y + 1;
	  x = x + 1;
	  d = d + dy - dx;
	}
      }
    }
  }

  //negative slope: Octants 7, 8 (3 and 4)
  else { 

    //slope > -1: Octant 8 (4)
    if ( dx > abs(dy) ) {

      d = dy + ( dx / 2 );
  
      while ( x <= x1 ) {

	plot(s, c, x, y);

	if ( d > 0 ) {
	  x = x + 1;
	  d = d + dy;
	}
	else {
	  x = x + 1;
	  y = y - 1;
	  d = d + dy + dx;
	}
      }
    }

    //slope < -1: Octant 7 (3)
    else {

      d =  (dy / 2) + dx;

      while ( y >= y1 ) {
	
	plot(s, c, x, y );
	if ( d < 0 ) {
	  y = y - 1;
	  d = d + dx;
	}
	else {
	  y = y - 1;
	  x = x + 1;
	  d = d + dy + dx;
	}
      }
    }
  }
}


//=================================================================helper functions======================================================================

/* do_i_draw_it
 * parameters: (x0,y0,z0) (x1,y1,z1) and (x2,y2,z2) are points P0 P1 P2 respectively
 * return: returns 1 if polygon of P0 P1 P2 is facing you, 0 if not
 * Backface culling method 
 */
int do_i_draw_it(double x0, double y0, double z0,
		 double x1, double y1, double z1,
		 double x2, double y2, double z2,
		 double view_x, double view_y, double view_z) {

  double v0_x, v0_y, v0_z; //vector_0 coordinates
  double v1_x, v1_y, v1_z; //vector_1 coordinates
  double surface_normal[3];
  double view_vector[3];
  
  //set vector_0, P0 to P1
  v0_x = x1 - x0;
  v0_y = y1 - y0;
  v0_z = z1 - z0;

  //set vector_1 P0 to P2
  v1_x = x2 - x0;
  v1_y = y2 - y0;
  v2_z = z2 - z0;

  //compute cross product

  
}

