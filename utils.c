//utils.c

//make some useful funcs, just copy and paste them
//im not guuna make this a lib

#include<stdio.h>
#include<stdlib.h>
#include<stdarg.h>

double* new_array(int n, ...);
void putarray(char* title, double* arr, int n);

int main(int argc, char** argv) {

  double* arr;
  double* ary;
  
  arr = new_array(3, 42.3, 3.14, 2.7);
  ary = new_array(5, 341.2345, 2342.3, 3452.234, 3.234, .23);

  putarray("arr: ", arr);
  putarray("ary: ", ary);
  
}

double* new_array(int n, ...) {

  double* ret;
  int i;
  va_list elements;
  
  ret = (double*)malloc(n*sizeof(double));
  if( ret==NULL ) {
    return(NULL);
  }

  va_start(elements);
  for(i=0; i<n; i++) {
    ret[i] = va_arg(elements, double);
  }

  va_end(elements);
  return(ret);
}

void putarray(char* title, double* arr, int n) {

  int i;
  
  printf("%s[", title);
  for(i=0; i<n-1; i++) {
    printf("%lf, ", arr[i]);
  }
  printf("%lf]\n", arr[n-1]);

}
