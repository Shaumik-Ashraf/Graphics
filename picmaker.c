//picmaker.c
//make pictures in pbm

#include<stdio.h>
#include<math.h>
#include<unistd.h>
#include<fcntl.h>

#define SQR(x) ((x)*(x))
#define SQRSUM(x, y) (SQR(x)+SQR(y))

void mkpic0(int fd, char* buffer, int bufmax);
void mkpic1(int fd, char* buffer, int bufmax);
void mkpic2(int fd, char* buffer, int bufmax);
void mkpic3(int fd, char* buffer, int bufmax);
void mkpic4(int fd, char* buffer, int bufmax);

int main(int argc, char* argv[]) {

  int i, j, fd;
  char buffer[256];

  if( argc < 2 ) {
    fprintf(stderr, "Error, no file name arg\n");
    return(1);
  }
  
  if( (fd=open(argv[1], O_CREAT|O_TRUNC|O_WRONLY, 0644))<0 ) {
    perror("Error opening file: ");
    fprintf(stderr, "\n");
    return(1);
  } 

  //create header
  strcpy(buffer, "P3\n500 500 255\n");
  write(fd, buffer, strlen(buffer));
  memset(buffer, '\0', 256);
  
  mkpic3(fd, buffer, 256);
  
  close(fd);
  
  return(0);
}

void mkpic0(int fd, char* buffer, int bufmax) {

	int i, j;

	for(i=0; i<500; i++) {
	    for(j=0; j<500; j++) {
	      strcpy(buffer, "200 0 200 ");
	      write(fd, buffer, strlen(buffer));
	      memset(buffer, '\0', 256);
	    }
	    write(fd, "\n", 2);
	  }

}

void mkpic1(int fd, char* buffer, int bufmax) {

	int i, j;

	for(i=0; i<500; i++) {
	    for(j=0; j<500; j++) {
	      strcpy(buffer, "255 105 180 ");
	      write(fd, buffer, strlen(buffer));
	      memset(buffer, '\0', bufmax);
	    }
	    write(fd, "\n", 2);
	}

}

void mkpic2(int fd, char* buffer, int bufmax) {
	
	int i, j;
	
	for(i=0; i<500; i++) {
		for(j=0; j<500; j++) {
			sprintf(buffer, "%i %i %i ", 0, 0, (int)(sin((double)i)*255) );
			write(fd, buffer, strlen(buffer));
			memset(buffer, '\0', bufmax);
	    }
	    write(fd, "\n", 2);
	}
	
}

void mkpic3(int fd, char* buffer, int bufmax) {
	
	int i, j, b;
	
	for(i=0; i<500; i++) {
		for(j=0; j<500; j++) {
			sprintf(buffer, "%i %i %i ", (int)(cos((double)(j*0.07))*255), 0, (int)(sin((double)(i*0.7))*255) );
			write(fd, buffer, strlen(buffer));
			memset(buffer, '\0', bufmax);
	    }
	    write(fd, "\n", 2);
	}
	
}

void mkpic4(int fd, char* buffer, int bufmax) {
	
	int i, j, r=0, g=0, b=0;
	
	for(i=0; i<500; i++) {
		for(j=0; j<500; j++) {
			
			if( (SQRSUM(i, j)) < sqrt(300) ) {
				g = (int)(sin(SQRSUM(i, j) * 3.141592 / 600 )*255);
			}
			
			if( SQRSUM(i, (j-500)) < sqrt(200) ) {
				r = (int)(sin(SQRSUM(i, j) * 3.141592 / 600 )*255);
			}
			
			if( SQRSUM((i-500), j) < sqrt(150) ) {
				b = (int)(sin(SQRSUM(i, j) * 3.141592 / 600 )*255);
			}
			
			sprintf(buffer, "%i %i %i ", r, g, b );
			write(fd, buffer, strlen(buffer));
			memset(buffer, '\0', bufmax);
	    }
	    write(fd, "\n", 2);
	}
	
}
