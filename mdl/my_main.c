/*========== my_main.c ==========

  This is the only file you need to modify in order
  to get a working mdl project (for now).

  my_main.c will serve as the interpreter for mdl.
  When an mdl script goes through a lexer and parser, 
  the resulting operations will be in the array op[].

  Your job is to go through each entry in op and perform
  the required action from the list below:

  push: push a new origin matrix onto the origin stack
  pop: remove the top matrix on the origin stack

  move/scale/rotate: create a transformation matrix 
                     based on the provided values, then 
		     multiply the current top of the
		     origins stack by it.

  box/sphere/torus: create a solid object based on the
                    provided values. Store that in a 
		    temporary matrix, multiply it by the
		    current top of the origins stack, then
		    call draw_polygons.

  line: create a line based on the provided values. Store 
        that in a temporary matrix, multiply it by the
	current top of the origins stack, then call draw_lines.

  save: call save_extension with the provided filename

  display: view the image live
  
  jdyrlandweaver
  =========================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "parser.h"
#include "symtab.h"
#include "y.tab.h"

#include "misc_headers.h"
#include "matrix.h"
#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "stack.h"

void my_main( int polygons ) {

  int i;
  double step;
  double xval, yval, zval;
  struct matrix *transform;
  struct matrix *tmp;
  struct stack *s;
  screen t;
  color g;
  double *tp;  //temp pointer

  s = new_stack();
  tmp = new_matrix(4, 1000);
  clear_screen( t );

  for (i=0;i<lastop;i++) {  
    switch (op[i].opcode) 
	case COMMENT:
		//ignore
		break;
	case PUSH:
		push(s); //check
		break;
	case POP:
		pop(s); //check
		break;
	case MOVE:
		xval = op[i].op.move.d[0];
		yval = op[i].op.move.d[1];
		zval = op[i].op.move.d[2];
		transform = make_translate(xval, yval, zval);
		matrix_mult(transform, s->data[s->top]);
		free_matrix(transform);
		break;
	case SCALE:
		xval = op[i].op.scale.d[0];
		yval = op[i].op.scale.d[1];
		zval = op[i].op.scale.d[2];
		transform = make_scale(xval, yval, zval);
		matrix_mult(transform, s->data[s->top]);
		free_matrix(transform);
		break;
	case ROTATE:
		xval = op[i].op.rotate.degrees;
		switch( op[i].op.rotate.axis ) {
			case 0: //x-axis
				transform = make_rotX(xval);
				break;
			case 1: //y-axis
				transform = make_rotY(xval);
				break;
			case 2: //z-axis
				transform = make_rotZ(xval);
				break;
			default:	break;
		}
		matrix_mult(transform, s->data[s->top]);
		free_matrix(transform);
		break;
	case BOX:
		xval = op[i].op.box.d0[0];
		yval = op[i].op.box.d0[1];
		zval = op[i].op.box.d0[2];
		tp = (double*)op[i].op.box.d1;
		add_box(tmp, xval, yval, zval, tp[0], tp[1], tp[2]);
		matrix_mult(s->data[s->top], tmp);
		draw_polygons(tmp, t, g);
		break;
	case SPHERE:
		tp = op[i].op.sphere.d;
		generate_sphere
		break;
	case TORUS:
		break;
	case LINE:
		break;
	case SAVE:
		break;
	case DISPLAY:
		break;
	default:
		fprintf(stdout, "Unrecognized opcode...\n");
		break;
    }
  }
}
