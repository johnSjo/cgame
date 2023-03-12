#include <conio.h>
#include <stdio.h>
#include <time.h>

#define CONTROL_8253      0x43
#define CONTROL_WORD      0x3c
#define SYSTEM_CLOCK_RATE 1.1931817E+6

#define CLOCK_COUNTER     0x40

#define DEFAULT_FREQUENCY 0xffff

#define LOW_BYTE(n) (n & 0x00ff)
#define HIGH_BYTE(n) (n>>8) // book is using ((n>>8) & 0x00ff) but I don't see why, if it becomes an issue -> change it back to book version

void Change_Timer(unsigned int new_count) {
  outport(CONTROL_8253, CONTROL_WORD);

  outport(CLOCK_COUNTER, LOW_BYTE(new_count));
  outport(CLOCK_COUNTER, HIGH_BYTE(new_count));
}

void main(){
  unsigned int frequency = 10000;
  unsigned int count = SYSTEM_CLOCK_RATE / frequency;

  Change_Timer(count);

  printf("\n%u", sizeof(CLOCKS_PER_SEC));
  printf("\n%f", CLOCKS_PER_SEC);
  printf("\nSYSTEM_CLOCK_RATE: %f", SYSTEM_CLOCK_RATE);
  printf("\nCount: %u", count);
  printf("\nCount: 0x%x", count);

  while(!kbhit()){}
}