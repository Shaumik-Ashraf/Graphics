//picmaker.c
//make pictures in pbm

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

void mkpic0(int fd, char* buffer, int bufmax);

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
  
  mkpic1(fd, buffer, 256);
  
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
	      memset(buffer, '\0', 256);
	    }
	    write(fd, "\n", 2);
	}

}


