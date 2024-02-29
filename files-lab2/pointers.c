#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global variables
char* text1 = "This is a string.";
char* text2 = "Yet another thing.";
int list1[19];
int list2[19];
int count = 0; //= 0; // fix

// Function to copy ASCII codes of text into list and increment count
void copycodes(char* text, int* list, int* count) {
  //int len = strlen(text);
  /*
  int len = 0;
  while (text[len] != '\0') { // ger 80 bits för text2
    len++;
  }
  */
  int len = 19; // 80 bits

  // Copy ASCII codes of text into list and increment count
  for (int i = 0; i < len; i++) {
    if (text[i] == '\0') {
      break;
    }
    (list + i) = (int) text[i];
    (count)++;
  }
}

// Function to call copycodes for text1 and text2
void work(void) {
  copycodes(text1, list1, &count);
  copycodes(text2, list2, &count);
}


// --- Functions below are unchanged ---

// Function to print ASCII codes and corresponding characters in a list
void printlist(const int* lst) {
  printf("ASCII codes and corresponding characters.\n");
  while (lst != 0) {
    printf("0x%03X '%c' ",lst, (char)lst);
    lst++;
  }
  printf("\n");
}

void endian_proof(const char c) {
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n",
    (int)c, (int)(c + 1), (int)(c + 2), (int)(c + 3));
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
