// Copyright (c) 2015, XMOS Ltd, All rights reserved
/**
How to use the select statement with a timeout
----------------------------------------------

A select statement waits for one of a set of inputs to become ready,
performs the selected input and then executes a corresponding body of
code. There are however occasions when it is not reasonable to wait on
one of the inputs to become ready.  In this instance a timer can be
used to exit the select statement if no input has become ready within
a defined timeout period.
**/


#include <platform.h>
#include <print.h>
#include <xs1.h>

#define TIMEOUT_PERIOD 50000;
in port port_input = XS1_PORT_4E; // buttons

int main(void)
{
  unsigned port_input_data = 0;
  timer t;
  unsigned time;

 /** The current 'time' is input from timer 't'.  The value of 'time' is
     then extended by the 'TIMEOUT_PERIOD' to give a time in the future.
  **/
  t :> time;
  time += TIMEOUT_PERIOD;

/**
  If data is available from the port before the 'TIMEOUT_PERIOD' expires
  then the port_input case is executed and the data can be printed out.
  However, if no data becomes available within the 'TIMEOUT_PERIOD' then
  the timeout case is executed and the select statement exits with no
  input received from the port.
**/

  select {
    case port_input when pinsneq(port_input_data) :> port_input_data :
      printstr("Input received on port_input : ");
      printintln(port_input_data);
      break;
    case t when timerafter(time) :> void :
      printstrln("Select statement timeout waiting on input.");
      break;
  }


  return 0;
}

