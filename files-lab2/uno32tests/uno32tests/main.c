/* main.c

   This file written 2015 by F Lundevall and David Broman

   Latest update 2015-09-15 by David Broman

   For copyright and licensing, see file COPYING */

#include <stddef.h>   /* Declarations of integer sizes and the like, part 1 */
#include <stdint.h>   /* Declarations of integer sizes and the like, part 2 */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */

void saveinfo(char s[], void * a, size_t ns );
void showinfo(void);
void u32init(void);

int gv; /* Global variable. */
int in = 3; /* Global variable, initialized to 4711. */

void fun(int param)
{
  param++;
  saveword( "AF1: param", &param );
  gv = param; /* Change the value of a global variable. */
}

/* This is the main function */
int main()
{
  /* Local variables. */
  int m;
  int * p; /* Declare p as pointer, so that p can hold an address. */
  char cs[ 9 ] = "Bonjour!";
  char * cp = cs; /* Declare cp as pointer, initialise cp to point to cs */

  /* Do some calculation. */
  gv = 4;
  m = gv + in;

  /* Check the addresses and values of some variables and stuff */
  saveword( "AM1: gv", &gv );
  saveword( "AM2: in", &in );
  saveword( "AM3: fun", &fun );
  saveword( "AM4: main", &main );

  p = &m;

  /* Check p and m */
  saveword( "AM5: p", &p );
  saveword( "AM6: m", &m );

  /* Change *p */

  *p = *p + 1;

  /* Check p and m */
  saveword( "AM7: p", &p );
  saveword( "AM8: m", &m );

  p = (int*)cp;   /* Casting a char pointer to an integer pointer */

  saveword( "AM9: p", &p );

  savebyte( "AM10: cs[0]", &cs[0] );
  savebyte( "AM11: cs[1]", &cs[1] );
  savebyte( "AM12: cs[2]", &cs[2] );
  savebyte( "AM13: cs[3]", &cs[3] );

  *p = 0x1234abcd; /* It starts to get interesting... */

  savebyte( "AM14: cs[0]", &cs[0] );
  savebyte( "AM15: cs[1]", &cs[1] ); 
  savebyte( "AM16: cs[2]", &cs[2] );
  savebyte( "AM17: cs[3]", &cs[3] );

  fun(m);

  /* Re-check the addresses and values of m and gv */
  saveword( "AM18: m", &m );
  saveword( "AM19: gv", &gv );

  showinfo();
}


/*
p = (int*)cp; get the value of cp, which is the address of cs[0].
So p points to cs[0].
0x6A6E6F42 is 4 bytes, so it is an int.

What is stored in cs?
cs is an array of chars, so it stores 8 bytes.
Char is retrieved from:
char cs[ 9 ] = "Bonjour!";
char * cp = cs; 
So cs[0] = 'B', cs[1] = 'o', cs[2] = 'n', cs[3] = 'j', cs[4] = 'o', cs[5] = 'u', cs[6] = 'r', cs[7] = '!', cs[8] = '\0'

AM10: 
    cs[0]
    Adress: 0xA0003FEC
    Data: 0x42
  
AM11:
    cs[1]
    Adress: 0xA0003FED
    Data: 0x6F

AM12:
    cs[2]
    Adress: 0xA0003FEE
    Data: 0x6E
  
AM13:
    cs[3]
    Adress: 0xA0003FEF
    Data: 0x6A




*p = 0x1234abcd;

AM14: 
    cs[0]
    Adress: 0xA0003FEC
    Data: 0xCD
  
AM15:
    cs[1]
    Adress: 0xA0003FED
    Data: 0xAB

AM16:
    cs[2]
    Adress: 0xA0003FEE
    Data: 0x34
  
AM17:
    cs[3]
    Adress: 0xA0003FEF
    Data: 0x12


OBS! 
The value of *p is the value of the variable p is pointing to, which is m.
So *p = *p + 1; is the same as m = m + 1;.

*/