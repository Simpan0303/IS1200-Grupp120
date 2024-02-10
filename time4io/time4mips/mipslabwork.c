/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */


/*
PIC32 ChipKit
In file mipslabwork.c, add code in function labinit to initialize Port E so that bits 7 through 0
of Port E are set as outputs (i.e., the 8 least significant bits). These bits are connected to 8 green
LEDs on the Basic IO Shield. Register TRISE has address 0xbf886100.You should initialize the
port using your own volatile pointer, that is, you should not use the definitions in pic32mx.h, yet.
Do not change the function (direction) of any other bits of Port E.
*/

/*
  In file mipslabwork.c, add code in function labwork to increase the binary value shown on the
  8 green LEDs once each time the function tick is called. Initialize the value to 0, so that the LEDs
  show how many "ticks" have occurred since the program was started. See below. You should use
  your own volatile pointer. Register PORTE has address 0xbf886110
*/

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
/* Lab-specific initialization goes here */
void labinit( void )
{
  TRISD |= 0x0FE0

  volatile int *trise = (volatile int*) 0xbf886100; // Define a volatile pointer to TRIS register of Port E
  *trise &= 0xFF00; // Set bits 7 through 0 as outputs

  porte = (volatile int*) 0xbf886110; // Define a volatile pointer to PORTE register
  *porte = 0; // Initialize the value to 0
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  delay( 1000 );
  time2string( textstring, mytime );
  display_string( 3, textstring );
  display_update();
  tick( &mytime );
  display_image(96, icon);





  (*porte)++; // Increase the binary value shown on the 8 green LEDs
}




