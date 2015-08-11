// Copyright (c) 2015, XMOS Ltd, All rights reserved
#include <print.h>
/**
How to pass arrays over interface calls
---------------------------------------

Interface functions can take array arguments like normal functions:
**/


interface my_interface {
  void msg(int a[]);
};

/**
The client end can pass an array into the function:
**/


void task1(client interface my_interface c)
{
  int a[5] = {0,1,2,3,4};
  c.msg(a);
}

/**
On the server end the select case can access elements of the array.
The compiler may translate that array access into xCONNECT inter-task
communication in the hardware.
**/

void task2(server interface my_interface c)
{
  select {
  case c.msg(int a[]):
    printintln(a[2]);
    printintln(a[3]);
    break;
  }
}


int main() {
  interface my_interface c;
  par {
    task1(c);
    task2(c);
  }
  return 0;
}
