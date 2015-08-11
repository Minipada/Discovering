/*
 * Timed output on a po.xc
 *
 *  Created on: Aug 11, 2015
 *      Author: david
 */


#include <stdio.h>
#include <xs1.h>
#include <platform.h>

port p1 = XS1_PORT_4F;

void doToggle(out port toggle) {
  int count;
  toggle <: 0 @ count;    // timestamped output
  while (1) {
    count += 3;
    toggle @ count <: 1;  // timed output
    count += 2;
    toggle @ count <: 0;  // timed output
  }
}


/*
 * The rate at which data is output to a port can be controlled by using one of
 * the xCORE’s pool of timer resources. This example uses a timer to toggle the
 * output of port toggle_port every 500ms.
 * Output the value of variable state to port toggle_port.
*/

int main() {

    doToggle(p1);
    return 0;
}
