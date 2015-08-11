/*
 * Test_Interfaces.xc
 *
 *  Created on: Aug 11, 2015
 *      Author: david
 */

#include <stdio.h>


/**
 Arrays of interfaces can be declared to provide a multiple connections
 between tasks. Individual elements of the array can be passed to tasks
 or the whole array can be passed on. In the following example, the
 array is passed to 'task3' which connects to both 'task1' and 'task2'.
**/

interface my_interface {
  void fA(int x, int y);
  void fB(float x);
};

/**
    The tasks given an element of the array use the interface end as
    normal.
**/
void client_int_1(client interface my_interface i)
{
  // 'i' is the client end of the connection,
  // let's communicate with the other end.
  i.fA(5, 10);
}

/**
    The tasks given an element of the array use the interface end as
    normal.
**/
void client_int_2(client interface my_interface i)
{
  // 'i' is the client end of the connection,
  // let's communicate with the other end.
  i.fB(0.10);
}

/**
 The server end can select over the entire array by using a pattern
 variable in the case within the select. The syntax is:

    case c[int i].msg(int x):
       // handle the case
       ...
       break;

 Here, the variable 'i' is declared as a subscript to the array 'c'
 which means that the case will select over the entire array and wait
 for a message from one of the elements.

 When a message is received, 'i' is set to the index of the array
 element that the message came in on.
**/
void server_int(interface my_interface server intf_[number_interface], unsigned number_interface) {
   while (1) {
     // wait for either fA or fB over either connection.

       for (int i = 0; i < number_interface; i++)
       {
         select {
             case intf_[int i].fA(int x, int y):
               printf("Received fA on interface end i%d: %d, %d\n", i, x, y);
               break;
             case intf_[int i].fB(float x):
               printf("Received fB on interface end i%d: %f\n", i, x);
               break;
         }
       }

   }
}

int main(void)
{
  interface my_interface intf_[2];
  par {
    client_int_1(intf_[0]); // task1
    client_int_2(intf_[1]); // task2
    server_int(intf_, 2);
  }
  return 0;
}
