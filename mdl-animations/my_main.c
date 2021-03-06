/*========== my_main.c ==========

  This is the only file you need to modify in order
  to get a working mdl project (for now).

  my_main.c will serve as the interpreter for mdl.
  When an mdl script goes through a lexer and parser, 
  the resulting operations will be in the array op[].

  Your job is to go through each entry in op and perform
  the required action from the list below:

  frames: set num_frames (in misc_headers.h) for animation

  basename: set name (in misc_headers.h) for animation

  vary: manipluate knob values between two given frames
  over a specified interval

  set: set a knob to a given value
  
  setknobs: set all knobs to a given value

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

/*======== void first_pass()) ==========
  Inputs:   
  Returns: 

  Checks the op array for any animation commands
  (frames, basename, vary)
  
  Should set num_frames and basename if the frames 
  or basename commands are present

  If vary is found, but frames is not, the entire
  program should exit.

  If frames is found, but basename is not, set name
  to some default value, and print out a message
  with the name being used.

  jdyrlandweaver
  ====================*/
void first_pass() {
  
  extern int num_frames; //from misc_headers.h
  extern char name[];    //also from misc_headers.h

  int found_frames = 0;
  int found_basenam = 0;
  int found_vary = 0;
  int i;

  for(i=0; i<lastop; i++) {
    switch( op[i].opcode ) {
    case FRAMES:
      if( found_frames ) {
	printf("Warning: multiple frame settings\n");
	break;
      }
      found_frames = 1;
      num_frames = op[i].op.frames.num_frames;
      break;
    case BASENAME:
      if( found_basenam ) {
	printf("Warning: multiple basenames\n");
	break;
      }
      found_basenam = 1;
      strncpy(name, op[i].op.basename.p->name, 128);
      break;
    case VARY:
      found_vary = 1;
    default:
      break;
    }
  }

  if( found_vary && !found_frames ) {
    printf("Error: using vary command in non-animation\n");
    exit(1);
  }

  if( found_frames && !found_basenam ) {
    printf("Warning: no basename specified; setting name to \"nemo\"\n");
    strcpy(name, "nemo");
  }

  if( !found_frames ) {
    printf("Warning: no frames specifies; assumine image (1 frame)\n");
    num_frames = 1;
  }
  
}

/*======== struct vary_node ** second_pass()) ==========
  Inputs:   
  Returns: An array of vary_node linked lists

  In order to set the knobs for animation, we need to keep
  a seaprate value for each knob for each frame. We can do
  this by using an array of linked lists. Each array index
  will correspond to a frame (eg. knobs[0] would be the first
  frame, knobs[2] would be the 3rd frame and so on).

  Each index should contain a linked list of vary_nodes, each
  node contains a knob name, a value, and a pointer to the
  next node.

  Go through the opcode array, and when you find vary, go 
  from knobs[0] to knobs[frames-1] and add (or modify) the
  vary_node corresponding to the given knob with the
  appropirate value. 

  05/17/12 09:29:31
  jdyrlandweaver
  ====================*/
struct vary_node ** second_pass() {

  extern int num_frames;
  extern struct vary_node* nav;

  int i, j, start, end, x, y;
  struct vary_node** ret;

  ret = (struct vary_node**)malloc(sizeof(struct vary_node*) * num_frames);
  if( ret==NULL ) { printf("Error, Memory Error\n"); exit(1); }

  for(i=0; i<num_frames; i++) {
    ret[i] = NULL;
  }

  for(i=0; i<lastop; i++) {
    if( op[i].opcode == VARY ) {
      start = op[i].op.vary.start_frame;
      end = op[i].op.vary.end_frame;
      x = op[i].op.vary.start_val;
      y = op[i].op.vary.end_val;

      for(j=start; j<end; j++) { //iterate thru array (frames)
		struct vary_node* nav;
				
		if( ret[j]==NULL ) { //if first node of list
		  ret[j]=(struct vary_node*)malloc(sizeof(struct vary_node));
		  if( ret[j]==NULL ) { printf("Error, memory error\n"); exit(1); }
		  else nav = ret[j];
		}
		else {
		  nav = ret[j];
		  while( nav->next != NULL ) { nav = nav->next; }
		  nav->next = (struct vary_node*)malloc(sizeof(struct vary_node));
		  if( (nav->next)==NULL ) { printf("Error, memory error\n"); exit(1); }
		  nav = nav->next;
		}
				
		//nav is now at allocated "empty" vary_node
				
		strcpy(nav->name, op[i].op.vary.p->name);
		nav->value = x + (int)((y-x)*((j-start)/(float)(end-start)));  //!!!!
		nav->next = NULL;
		//*/
      } //close nested for-loop
      
    } //close if VARY
  } //close for-loop

  return( ret );
}


/*======== void print_knobs() ==========
  Inputs:   
  Returns: 

  Goes through symtab and display all the knobs and their
  currnt values

  jdyrlandweaver
  ====================*/
void print_knobs() {
  
  int i;

  printf( "ID\tNAME\t\tTYPE\t\tVALUE\n" );
  for ( i=0; i < lastsym; i++ ) {

    if ( symtab[i].type == SYM_VALUE ) {
      printf( "%d\t%s\t\t", i, symtab[i].name );

      printf( "SYM_VALUE\t");
      printf( "%6.2f\n", symtab[i].s.value);
    }
  }
}


/*======== void my_main() ==========
  Inputs:
  Returns: 

  This is the main engine of the interpreter, it should
  handle most of the commands in mdl.

  If frames is not present in the source (and therefore 
  num_frames is 1, then process_knobs should be called.

  If frames is present, the enitre op array must be
  applied frames time. At the end of each frame iteration
  save the current screen to a file named the
  provided basename plus a numeric string such that the
  files will be listed in order, then clear the screen and
  reset any other data structures that need it.

  Important note: you cannot just name your files in 
  regular sequence, like pic0, pic1, pic2, pic3... if that
  is done, then pic1, pic10, pic11... will come before pic2
  and so on. In order to keep things clear, add leading 0s
  to the numeric portion of the name. If you use sprintf, 
  you can use "%0xd" for this purpose. It will add at most
  x 0s in front of a number, if needed, so if used correctly,
  and x = 4, you would get numbers like 0001, 0002, 0011,
  0487

  05/17/12 09:41:35
  jdyrlandweaver
  ====================*/
void my_main( int polygons ) {

  int i, f, j;
  double step;
  double xval, yval, zval, knob_value;
  struct matrix *transform;
  struct matrix *tmp;
  struct stack *s;
  screen t;
  color g;

  struct vary_node **knobs;
  struct vary_node *vn;
  char frame_name[128];

  //num_frames = 1;
  step = 5;
 
  g.red = 0;
  g.green = 255;
  g.blue = 255;

  clear_screen(t);
  s = new_stack();
  tmp = new_matrix(4,4);
  
  first_pass();
  printf("first pass complete.\n");
  knobs = second_pass();
  printf("second pass complete.\n");

  print_knobs();

  //print my knobs =============
  for( i=0; i<num_frames; i++ ) {
    vn = knobs[j];
    printf("%i:[", i);
    while(vn!=NULL) {
      printf("%s-", vn->name);
      vn = vn->next;
    }
    printf("]\n");
  }
  //===========================
  
  if( num_frames!=1 ) { //if animation
    printf("Processing animation...\n");
	
    if( num_frames > 9999 ) {
      printf("Warning: max number of frames (9999) exceeded\n");
    }

    printf("looping:\n");
    for( j=0; j<num_frames; j++) {
      printf("drawing frame %i... \n", j);  
      for (i=0;i<lastop;i++) {
		vn = knobs[j];
		switch (op[i].opcode) {
	
		case SPHERE:
		  add_sphere( tmp,op[i].op.sphere.d[0], //cx
			      op[i].op.sphere.d[1],  //cy
			      op[i].op.sphere.d[2],  //cz
			      op[i].op.sphere.r,
			      step);
		  //apply the current top origin
		  matrix_mult( s->data[ s->top ], tmp );
		  //print_matrix(tmp); //debug
		  draw_polygons( tmp, t, g );
		  tmp->lastcol = 0;  //reset tmp
		  break;
	
		case TORUS:
		  add_torus( tmp, op[i].op.torus.d[0], //cx
			     op[i].op.torus.d[1],     //cy
			     op[i].op.torus.d[2],    //cz
			     op[i].op.torus.r0,
			     op[i].op.torus.r1,
			     step);
		  matrix_mult( s->data[ s->top ], tmp );
		  draw_polygons( tmp, t, g );
		  tmp->lastcol = 0;
		  break;
	
		case BOX:
		  add_box( tmp, op[i].op.box.d0[0],
			   op[i].op.box.d0[1],
			   op[i].op.box.d0[2],
			   op[i].op.box.d1[0],
			   op[i].op.box.d1[1],
			   op[i].op.box.d1[2]);
		  matrix_mult( s->data[ s->top ], tmp );
		  draw_polygons( tmp, t, g );
		  tmp->lastcol = 0;
		  break;
	
		case LINE:
		  add_edge( tmp, op[i].op.line.p0[0],
			    op[i].op.line.p0[1],
			    op[i].op.line.p0[1],
			    op[i].op.line.p1[0],
			    op[i].op.line.p1[1],
			    op[i].op.line.p1[1]);
		  draw_lines( tmp, t, g );
		  tmp->lastcol = 0;
		  break;
	
		case MOVE:
		  //get the factors
		  xval = op[i].op.move.d[0];
		  yval =  op[i].op.move.d[1];
		  zval = op[i].op.move.d[2];
	
		  transform = make_translate( xval, yval, zval );
		  //multiply by the existing origin
		  matrix_mult( s->data[ s->top ], transform );
		  //put the new matrix on the top
		  copy_matrix( transform, s->data[ s->top ] );
		  free_matrix( transform );
		  break;
	
		case SCALE:
		
		  xval = op[i].op.scale.d[0];
		  yval = op[i].op.scale.d[1];
		  zval = op[i].op.scale.d[2];
		  
		  if( op[i].op.scale.p != NULL ) { //var motion
		  	while( vn!=NULL ) {
		  		if( strcmp(op[i].op.scale.p->name, vn->name)==0 ) {
		  			xval *= (vn->value);
		  			yval *= (vn->value);
		  			zval *= (vn->value);
		  			
		  			transform = make_scale(xval, yval, zval);
					matrix_mult( s->data[ s->top ], transform );
					copy_matrix( transform, s->data[ s->top ] );
					break;
		  		}
		  		else vn = vn->next;
		  	}
		  }
		  else {  //regular transformation
		  	transform = make_scale(xval, yval, zval);
			matrix_mult( s->data[ s->top ], transform );
			copy_matrix( transform, s->data[ s->top ] );
		  }
		  
		  vn = knobs[j];
		  free_matrix(transform);
		  break;
		
		case ROTATE:
		  xval = op[i].op.rotate.degrees * ( M_PI / 180 );
		  yval = op[i].op.rotate.axis;
	
		  if( op[i].op.rotate.p!=NULL ) { //var motion
		  	while( vn!=NULL ) {
		  		if( strcmp(op[i].op.rotate.p->name, vn->name)==0 ) {
		  			xval *= (vn->value);
					break;
		  		}
		  		else vn = vn->next;
		  	}
		  }
	
		  //get the axis
		  if ( op[i].op.rotate.axis == 0 ) 
		    transform = make_rotX( xval );
		  else if ( op[i].op.rotate.axis == 1 ) 
		    transform = make_rotY( xval );
		  else if ( op[i].op.rotate.axis == 2 ) 
		    transform = make_rotZ( xval );

		  vn = knobs[j];
		  free_matrix( transform );
		  break;
	
		case PUSH:
		  push( s );
		  break;
		case POP:
		  pop( s );
		  break;
		case SAVE:
		  save_extension( t, op[i].op.save.p->name );
		  break;
		case DISPLAY:
		  display( t );
		  break;
		} //close switch
      } //close for-loop
	
      //save frame
      sprintf(frame_name, "anim/%s%04d%s", name, j, ".png");
      printf("Saving frame %s\n", frame_name);
      save_extension(t, frame_name);
    }

  }
  else { //else drawing only picture
    printf("drawing picture...\n");
    for (i=0;i<lastop;i++) {

      switch (op[i].opcode) {

      case SPHERE:
	add_sphere( tmp,op[i].op.sphere.d[0], //cx
		    op[i].op.sphere.d[1],  //cy
		    op[i].op.sphere.d[2],  //cz
		    op[i].op.sphere.r,
		    step);
	//apply the current top origin
	matrix_mult( s->data[ s->top ], tmp );
	draw_polygons( tmp, t, g );
	tmp->lastcol = 0;
	break;

      case TORUS:
	add_torus( tmp, op[i].op.torus.d[0], //cx
		   op[i].op.torus.d[1],     //cy
		   op[i].op.torus.d[2],    //cz
		   op[i].op.torus.r0,
		   op[i].op.torus.r1,
		   step);
	matrix_mult( s->data[ s->top ], tmp );
	draw_polygons( tmp, t, g );
	tmp->lastcol = 0;
	break;

      case BOX:
	add_box( tmp, op[i].op.box.d0[0],
		 op[i].op.box.d0[1],
		 op[i].op.box.d0[2],
		 op[i].op.box.d1[0],
		 op[i].op.box.d1[1],
		 op[i].op.box.d1[2]);
	matrix_mult( s->data[ s->top ], tmp );
	draw_polygons( tmp, t, g );
	tmp->lastcol = 0;
	break;

      case LINE:
	add_edge( tmp, op[i].op.line.p0[0],
		  op[i].op.line.p0[1],
		  op[i].op.line.p0[1],
		  op[i].op.line.p1[0],
		  op[i].op.line.p1[1],
		  op[i].op.line.p1[1]);
	draw_lines( tmp, t, g );
	tmp->lastcol = 0;
	break;

      case MOVE:
	//get the factors
	xval = op[i].op.move.d[0];
	yval =  op[i].op.move.d[1];
	zval = op[i].op.move.d[2];
		  
	transform = make_translate( xval, yval, zval );
	//multiply by the existing origin
	matrix_mult( s->data[ s->top ], transform );
	//put the new matrix on the top
	copy_matrix( transform, s->data[ s->top ] );
	free_matrix( transform );
	break;

      case SCALE:
	xval = op[i].op.scale.d[0];
	yval = op[i].op.scale.d[1];
	zval = op[i].op.scale.d[2];
		  
	transform = make_scale( xval, yval, zval );
	matrix_mult( s->data[ s->top ], transform );
	//put the new matrix on the top
	copy_matrix( transform, s->data[ s->top ] );
	free_matrix( transform );
	break;

      case ROTATE:
	xval = op[i].op.rotate.degrees * ( M_PI / 180 );

	//get the axis
	if ( op[i].op.rotate.axis == 0 ) 
	  transform = make_rotX( xval );
	else if ( op[i].op.rotate.axis == 1 ) 
	  transform = make_rotY( xval );
	else if ( op[i].op.rotate.axis == 2 ) 
	  transform = make_rotZ( xval );

	matrix_mult( s->data[ s->top ], transform );
	//put the new matrix on the top
	copy_matrix( transform, s->data[ s->top ] );
	free_matrix( transform );
	break;

      case PUSH:
	push( s );
	break;
      case POP:
	pop( s );
	break;
      case SAVE:
	save_extension( t, op[i].op.save.p->name );
	break;
      case DISPLAY:
	display( t );
	save_extension( t, "DEBUG.ppm");  //REMOVE LATER
	break;
      } //close switch

    } //close for-loop
  } //close else
  
  free_stack( s );
  free_matrix( tmp );
  //free_matrix( transform );
}
