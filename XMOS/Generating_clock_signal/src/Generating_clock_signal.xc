/*
 * Generating_clock_signal.xc
 *
 *  Created on: Aug 11, 2015
 *      Author: david
 */


#include <xs1.h>
#include <stdio.h>

out port outP     = XS1_PORT_4F;
out port outClock = XS1_PORT_1A;
clock    clk      = XS1_CLKBLK_1;
//on tile[0] : out port explorer_leds = XS1_PORT_4F;

int main(void) {

  // Minimum between 25 / 126 = 0.1983 (valid)
  // and 15/76 = 0.1973 (non valid)
  configure_clock_rate(clk, 25, 126);
  configure_out_port(outP, clk, 0);
  configure_port_clock_output(outClock, clk);
  start_clock(clk);

  /*
   * The difference between the two times gives you the number of timer ticks elapsed.
   * This method can be used to measure durations of up to 2^32 -1 timer ticks
   * (approximately 42 seconds).
   */
  int time_old, time_new;
  timer t;
  t :> time_old;
  for (int i = 0; i < 5; i++)
  {
    outP <: i;
    t :> time_new;
    printf("Ding %d!\n", time_new - time_old);
    time_old = time_new;
  }

  return 0;
}
