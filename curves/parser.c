#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "parser.h"


/*======== void parse_file () ==========
Inputs:   char * filename 
          struct matrix * transform, 
          struct matrix * pm,
          screen s
Returns: 

Goes through the file named filename and performs all of the actions listed in that file.
The file follows the following format:
     Every command is a single character that takes up a line
     Any command that requires arguments must have those arguments in the second line.
     The commands are as follows:
         line: add a line to the edge matrix - 
	    takes 6 arguemnts (x0, y0, z0, x1, y1, z1)
	 circle: add a circle to the edge matrix - 
	    takes 3 arguments (cx, cy, r)
	 hermite: add a hermite curve to the edge matrix -
	    takes 8 arguments (x0, y0, x1, y1, x2, y2, x3, y3)
	 bezier: add a bezier curve to the edge matrix -
	    takes 8 arguments (x0, y0, x1, y1, x2, y2, x3, y3)
	 ident: set the transform matrix to the identity matrix - 
	 scale: create a scale matrix, 
	    then multiply the transform matrix by the scale matrix - 
	    takes 3 arguments (sx, sy, sz)
	 translate: create a translation matrix, 
	    then multiply the transform matrix by the translation matrix - 
	    takes 3 arguments (tx, ty, tz)
	 xrotate: create an x-axis rotation matrix,
	    then multiply the transform matrix by the rotation matrix -
	    takes 1 argument (theta)
	 yrotate: create an y-axis rotation matrix,
	    then multiply the transform matrix by the rotation matrix -
	    takes 1 argument (theta)
	 zrotate: create an z-axis rotation matrix,
	    then multiply the transform matrix by the rotation matrix -
	    takes 1 argument (theta)
	 apply: apply the current transformation matrix to the 
	    edge matrix
	 display: draw the lines of the edge matrix to the screen
	    display the screen
	 save: draw the lines of the edge matrix to the screen
	    save the screen to a file -
	    takes 1 argument (file name)
	 quit: end parsing

See the file script for an example of the file format


IMPORTANT MATH NOTE:
the trig functions int math.h use radian mesure, but us normal
humans use degrees, so the file will contain degrees for rotations,
be sure to conver those degrees to radians (M_PI is the constant
for PI)
====================*/
void parse_file ( char * filename, 
                  struct matrix * transform, 
                  struct matrix * pm,
                  screen s) {

  FILE *f;
  char line[256];
  
  clear_screen(s);

  if ( strcmp(filename, "stdin") == 0 ) 
    f = stdin;
  else
    f = fopen(filename, "r");
  
  while ( fgets(line, 255, f) != NULL ) {
    line[strlen(line)-1]='\0';
    printf(":%s:\n",line);

    if( strcmp(line, "line")==0 ) {
      //assume paramter format: x0<SPACE>y0<SPACE>x1<SPACE>y1<NEWLINE>

      int x0, y0, x1, y1;
      
      fgets(line, 255, f);
      sscanf(line, "%i %i %i %i\n", &x0, &y0, &x1, &y1);

      add_edge(pm, x0, y0, 0, x1, y1, 0);
      
    }
    else if( strcmp(line, "circle")==0 ) {

    }
    else if( strcmp(line, "hermite")==0 ) {

    }
    else if( strcmp(line, "bezier")==0 ) {

    }
    else if( strcmp(line, "ident")==0 ) {
      ident(transform);
    }
    else if( strcmp(line, "scale")==0 ) {
      //param format: x-scale-factor<space>y-scale-factor<space>z-scale-factor
      
      struct matrix* scale_matrix;
      double xs, ys, zs;

      fgets(line, 255, f);
      sscanf(line, "%lf %lf %lf", &xs, &ys, &zs);

      scale_matrix = make_scale(xs, ys, zs);
      matrix_mult( transform, scale_matrix );

      free_matrix(scale_matrix);
      
    }
    else if( strcmp(line, "translate")==0 ) {
      //param format: x-translate<space>y-translate<space>z-translate
      struct matrix* trans_mat;
      double x, y, z;

      fgets(line, 255, f);
      sscanf(line, "%lf %lf %lf", &x, &y, &z);
      
      trans_mat = make_translate(x, y, z);
      matrix_mult(transform, trans_mat);

      free_matrix(trans_mat);
		  
    }
    else if( strcmp(line, "xrotate")==0 ) {
      //param format: angle-of-rotation-degrees
      struct matrix* rot_mat;
      double th;

      fgets(line, 255, f);
      sscanf(line, "%lf", &th);

      rot_mat = make_rotX(theta); //check if I hav to convert to radians here
      matrix_mult(transform, rot_mat);

      free_matrix(rot_mat);

    }
    else if( strcmp(line, "yrotate")==0 ) {
      //param format: angle-of-rotation-degrees
      struct matrix* rot_mat;
      double th;

      fgets(line, 255, f);
      sscanf(line, "%lf", &th);

      rot_mat = make_rotY(theta); //check if I hav to convert to radians here
      matrix_mult(transform, rot_mat);

      free_matrix(rot_mat);

    }
    else if( strcmp(line, "zrotate")==0 ) {
      //param format: angle-of-rotation-degrees
      struct matrix* rot_mat;
      double th;

      fgets(line, 255, f);
      sscanf(line, "%lf", &th);

      rot_mat = make_rotZ(theta); //check if I hav to convert to radians here
      matrix_mult(transform, rot_mat);

      free_matrix(rot_mat);

    }
    else if( strcmp(line, "apply")==0 ) {
      
    }
    else if( strcmp(line, "display")==0 ) {

    }
    else if( strcmp(line, "save")==0 ) {

    }
    else if( strcmp(line, "quit")==0 ) {
      break;
    }
    else {
      printf("Command not recognized\n");
    }
   
  } //close while-loop

}

  
