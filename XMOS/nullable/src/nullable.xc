/*
 * nullable.xc
 *
 *  Created on: Aug 11, 2015
 *      Author: david
 */

#include <stdio.h>
#include <xs1.h>
#include <platform.h>

port p1 = XS1_PORT_4F;

/*
 * Resource types (e.g. ports, timers etc) and reference types can be made nullable.
 * This means that their value could be a normal value or could be the special
 * value null. The ? type operator creates a nullable type.
 */

void function_with_authorized_null_port(port ?p)
{
  if (!isnull(p)) {
    printf("Outputting to port\n");
    p <: 0;
  } else {
    printf("Not Outputting to port\n");
  }
}

/*
 * The isnull function tests whether a variable of nullable type is null or not.
 * Functions taking nullable arguments can either be passed a value or the null value:
 */
int main() {

    function_with_authorized_null_port(null);
    function_with_authorized_null_port(p1);

    return 0;
}
