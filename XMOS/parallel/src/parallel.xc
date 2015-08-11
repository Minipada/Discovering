/*
 * Test_Going_parallel.xc
 *
 *  Created on: Aug 10, 2015
 *      Author: david
 */


#include <stdio.h>

void task(unsigned n) {
  printf("Hello world from task number %u\n", n);
}

// Statements in parallel
int main() {

    par(size_t i = 0; i < 4; i++)
      task(i);

  return 0;
}
