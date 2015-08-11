/*
 * Combinable_functions.xc
 *
 *  Created on: Aug 11, 2015
 *      Author: david
 */

#include <stdio.h>
#include <xs1.h>
#include <platform.h>

interface my_interface {
  void fA(int x, int y);
  void fB(float x);
};

/*
 * Combinable functions represent tasks that can be combined to run on a single logical core.
 * If a tasks ends in an never-ending loop containing a select statement,
 * it represents a task that continually reacts to events:
 */

void task1(interface my_interface server args) {
    printf("Initialization\n");
  while (1) {
    select {
      case args.fA(int x, int y) :
          printf("T1 - Case 1\n");
        break;
      case args.fB(float x) :
          printf("T1 - Case 2\n");
        break;
    }
  }
}

void task2(interface my_interface server args) {
    printf("Initialization\n");
  while (1) {
    select {
      case args.fA(int x, int y) :
          printf("T2 - Case 1\n");
        break;
      case args.fB(float x) :
          printf("T2 - Case 2\n");
        break;
    }
  }
}

/*
 * These kind of tasks can be marked as combinable by adding a special attribute:
 * A combinable function must obey the following restrictions:

    The function must have void return type.
    The last statement of the function must be a while(1)-select statement.

 *
 */

[[combinable]]
void counter_task(char *taskId, int n) {
  int count = 0;
  timer tmr;
  unsigned time;
  tmr :> time;
  // This task perfoms a timed count a certain number of times, then exits
  while (1) {
    select {
    case tmr when timerafter(time) :> int now:
      printf("Counter tick at time %x on task %s\n", now, taskId);
      count++;
      if (count >= n)
        return;
      time += 1000;
      break;
    }
  }
}

/*
 * Several combinable functions can be run in parallel with a combined par.
 * This will run them on the same logical core using co-operative multitasking:
 */

int main() {
  [[combine]]
  par {
    counter_task("task1", 5);
    counter_task("task2", 2);
  }
  return 0;
}
/*
 * You cannot use the [[combine]] attribute directly in a par with tile placements
 *  but can nest par statements:
  int main(void) {
  par {
    on tile[0]: task1( ... );
    on tile[1]: task2( ... );
    on tile[1]:
      [[combine]]
      par {
        task3( ... );
        task4( ... );
      }
  }
  return 0;
}
 * The above program will run task1 on a logical core on tile[0] and task2 on
 * its own logical core on tile[1]. A further logical core on tile[1] will run
 * both task3 and task4 by using co-operative multitasking.
 */
