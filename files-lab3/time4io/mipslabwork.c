/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */




#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

volatile int *trise;
volatile int *porte;
void labinit( void )
{
  volatile int *trise = (volatile int*) 0xbf886100; // Define a volatile pointer to TRIS register of Port E
  *trise &= 0xFF00; // Set bits 7 through 0 as outputs

  porte = (volatile int*) 0xbf886110; // Define a volatile pointer to PORTE register
  *porte = 0; // Initialize the value to 0

  TRISD |= 0x0FE0;
}

void labwork( void )
{
  (*porte)++; // Increment PORTE to update the LED status

  // Button press processing
  int btns = getbtns(); // buttons
  int sws = getsw(); // switches

  if (btns & 0x4) { // if button 4 is pressed
    int sws_value = sws & 0xF; // Get the value of SW4 through SW1
    mytime = (mytime & 0x0FFF) | (sws_value << 12);
  }
  if (btns & 0x2) { // if button 3 is pressed
    int sws_value = sws & 0xF; // Get the value of SW4 through SW1
    mytime = (mytime & 0xF0FF) | (sws_value << 8);
  }
  if (btns & 0x1) { // if button 2 is pressed
    int sws_value = sws & 0xF; // Get the value of SW4 through SW1
    mytime = (mytime & 0xFF0F) | (sws_value << 4);
  }




  delay( 1000 );
  time2string(textstring, mytime);
  display_string(3, textstring);
  display_update();
  tick(&mytime);
  display_image(96, icon);
  
}

/*
--- Assignment 1 ---
• Test pressing BTN3 and BTN2 at the same time. What happens? Why?
- All inputs change att the same time since the if statements are not mutually exclusive.


• Three device-registers for input/output control are TRISE, TRISESET, and TRISECLR.
Their functions are related. How? What are the differences?
- TRISE is the register for controlling the direction of the pins on Port E. TRISESET and TRISECLR are used to set and clear the bits of the TRISE register.


• In the generated assembly code, in which MIPS register will the return values from
functions getbtns and getsw be placed in. You should be able to answer this question
without debugging the generated assembly code.
- The return values will be placed in register v0. Why? 
Because the return value is a 32-bit integer, 
and the MIPS calling convention states that the return value
 of a function should be placed in register v0.


• In this exercise, we explained which bits that should be used in Port D and Port E. How can
you find this information in the PIC32 and ChipKIT manuals? Be prepared to demonstrate
how to find this information in the manuals.
Advice: check the lecture slides from lecture 5 for ideas.
- The information can be found in the "PIC32 Family Reference Manual" and the "PIC32MX3XX/4XX Family Data Sheet".
The information can be found by searching for the specific register names, such as "TRISE" and "PORTE".



*/


