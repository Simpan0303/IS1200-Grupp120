

#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6


// Print number function
int COLUMN_COUNT = 0; // Global var for columns printed
void print_number(int value) {
    printf("%10d ", value); 
    
    COLUMN_COUNT++;
    if (COLUMN_COUNT == COLUMNS) {
        printf("\n");
        COLUMN_COUNT = 0; // reset column count

    }
}

// distance amount
int prime_count = 0;
int distance_amount = 0;

// instead of print_primes, print_sieves
// An algorithm: "Sieve of Eratosthenes"
void print_sieves(int n){
    // Should print out all prime numbers less than 'n'
    // with the following formatting. Note that
    // the number of columns is stated in the define
    // COLUMNS

    // Create an array of n elements, all set to 1
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        arr[i] = 1;
    }

    // Set the first two elements to 0
    arr[0] = 0;
    arr[1] = 0;

    // Loop through the array

    
    for (int i = 2; i * i < n; i++) { // loop for each prime number
        if (arr[i] == 1) {
            for (int j = i * i; j < n; j += i) { // loop for each multiple of the prime number
                arr[j] = 0;
            }
        }
    }
    


    // Print the prime numbers
    int distance = 0;
    int previous_prime = 2; // first prime
    for (int i = 3; i < n; i++) {
        if (arr[i] == 1 ) {
            prime_count++;
            // print distance value between n and n+1
            // stop when comparing to last el
            distance = i - previous_prime;
            previous_prime = i;
            distance_amount += distance;
            print_number(distance);
        }
    }
    if (COLUMN_COUNT > 0) { // if there are numbers left to print, print newline
        printf("\n");
    }

    // Free the array
    free(arr);
}

// print average distance
void print_average(int n) {
    if (prime_count > 0) {
        double average = (double)distance_amount / prime_count;
        printf("Average distance: %.2f\n", average);
    }
}


// main
int main(int argc, char *argv[]){
    if(argc == 2) {
        print_sieves(atoi(argv[1]));
        print_average(atoi(argv[1])); // to print average
    } else
        printf("Please state an interger number.\n");

    //
    return 0;
}

