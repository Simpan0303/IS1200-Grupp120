/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/


#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6



int COLUMN_COUNT = 0; // Global var for columns printed
void print_number(int value) {
    printf("%10d ", value); 
    
    COLUMN_COUNT++;
    if (COLUMN_COUNT == COLUMNS) {
        printf("\n");
        COLUMN_COUNT = 0; // reset column count
    }
}

int is_prime(int n) {
    if (n <= 1) return 0; // not prime
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0; // not prime
    }
    return 1; // else prime
}


void print_primes(int n){
  // Should print out all prime numbers less than 'n'
  // with the following formatting. Note that
  // the number of columns is stated in the define
  // COLUMNS

  /*
  printf("%10d ", 2);
  printf("%10d ", 3);
  printf("%10d ", 5);
  printf("%10d ", 7);
  printf("%10d ", 11);
  printf("%10d ", 13);
  printf("\n");
  printf("%10d ", 17);
  printf("%10d ", 19);
  printf("\n");
  */

  for (int i = 0; i < n; i++) {
    if (is_prime(i)) {
      print_number(i);
    }
  }
  if (COLUMN_COUNT > 0) { // if there are numbers left to print, print newline
      printf("\n");
  }
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  if(argc == 2)
    print_primes(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}

 