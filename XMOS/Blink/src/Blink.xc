/*
 * Test_Blink.xc
 *
 *  Created on: Aug 10, 2015
 *      Author: david
 */

#include <platform.h>
#include <xs1.h>
#include <timer.h>

#define D2_D8_OFF 0
#define D2_GREEN_LED 1
#define D8_BLUE_LED 2
#define D8_GREEN_LED 4
#define D8_RED_LED 8

port p = XS1_PORT_4F;

int main() {
  while (1) {
     // The <: operator outputs a value to a port
     // 4 bits port
     p <: D2_D8_OFF;
     delay_milliseconds(200);

     p <: D2_GREEN_LED;
     delay_milliseconds(200);

     p <: D8_BLUE_LED;
     delay_milliseconds(200);

     p <: D8_GREEN_LED;
     delay_milliseconds(200);

     p <: D8_RED_LED;
     delay_milliseconds(200);

     p <: D8_RED_LED | D8_BLUE_LED;
     delay_milliseconds(200);

     p <: D8_GREEN_LED | D8_BLUE_LED;
     delay_milliseconds(200);

     p <: D8_GREEN_LED | D8_BLUE_LED | D8_RED_LED;
     delay_milliseconds(200);
  }
  return 0;
}
