#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global variables
char* text1 = "This is a string.";
char* text2 = "Yet another thing.";
int* list1;
int* list2;
int* count; //= 0; // fix

// Function to copy ASCII codes of text into list and increment count
void copycodes(char* text, int** list) {
  int len = strlen(text);

  // Allocate memory for list
  *list = (int*) malloc(sizeof(int) * len);

  // Copy ASCII codes of text into list and increment count
  for (int i = 0; i < len; i++) {
    (*list)[i] = (int) text[i];
    *count++;
  }
}

// Function to call copycodes for text1 and text2
void work(void) {
  copycodes(text1, &list1);
  copycodes(text2, &list2);
}


// --- Functions below are unchanged ---

// Function to print ASCII codes and corresponding characters in a list
void printlist(const int* lst) {
  printf("ASCII codes and corresponding characters.\n");
  while (*lst != 0) {
    printf("0x%03X '%c' ", *lst, (char)*lst);
    lst++;
  }
  printf("\n");
}

void endian_proof(const char* c) {
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n",
    (int)*c, (int)*(c + 1), (int)*(c + 2), (int)*(c + 3));
}

int main(void) {
  work();

  printf("\nlist1: ");
  printlist(list1);
  printf("\nlist2: ");
  printlist(list2);
  printf("\nCount = %d\n", count);

  endian_proof((char*) &count);

  return 0;
}
