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
int timeoutcount = 0; // Declare timeoutcount as a global variable
/* Lab-specific initialization goes here */
void labinit( void )
{
  TRISD |= 0x0FE0;

  volatile int *trise = (volatile int*) 0xbf886100; // Define a volatile pointer to TRIS register of Port E
  *trise &= 0xFF00; // Set bits 7 through 0 as outputs

  porte = (volatile int*) 0xbf886110; // Define a volatile pointer to PORTE register
  *porte = 0; // Initialize the value to 0

  T2CON = 0x0; // Stop the timer and clear the control register
  TMR2 = 0x0; // Clear the timer register
  PR2 = 31250; // Load the period register with the value for 100ms
  T2CONSET = 0x70; // 1:256 Set prescaler (choose value based on calculation)
  IFSCLR(0) = 0x100; // Clear Timer 2 interrupt flag
  IECSET(0) = 0x100; // Enable Timer 2 interrupt
  T2CONSET = 0x8000; // Start Timer 2


}

void labwork( void )
{
  // Check for timeout event (Timer 2)
  if (IFS(0) & 0x100) {
    IFSCLR(0) = 0x100; // Clear the timeout event flag
    timeoutcount++;

    // Update the display every 10 timeouts (1 second) --- CONTROLS SPEED ---
    if (timeoutcount >= 10) {
      timeoutcount = 0;
      time2string(textstring, mytime);
      display_string(3, textstring);
      display_update();
      tick(&mytime);

      (*porte)++; // Increment PORTE to update the LED status
    }
  }
  int btns = getbtns(); // buttons
  int sws = getsw(); // switches

  if (btns & 0x4) { // if button 4 is pressed
    int sws_value = sws & 0xF; // Get the value of SW4 through SW1
    mytime = (mytime & 0x0FFF) | (sws_value << 12);
    time2string(textstring, mytime);
    display_string(3, textstring);
    display_update();
  }
  if (btns & 0x2) { // if button 3 is pressed
    int sws_value = sws & 0xF; // Get the value of SW4 through SW1
    mytime = (mytime & 0xF0FF) | (sws_value << 8);
    time2string(textstring, mytime);
    display_string(3, textstring);
    display_update();
  }
  if (btns & 0x1) { // if button 2 is pressed
    int sws_value = sws & 0xF; // Get the value of SW4 through SW1
    mytime = (mytime & 0xFF0F) | (sws_value << 4);
    time2string(textstring, mytime);
    display_string(3, textstring);
    display_update();
  }
}
/* // WITHOUT MODIFICATION
void labwork( void )
{

  // Check for timeout event (Timer 2)
  if (IFS(0) & 0x100) {
    IFSCLR(0) = 0x100; // Clear the timeout event flag
    timeoutcount++;

    // Update the display every 10 timeouts (1 second) --- CONTROLS SPEED ---
    if (timeoutcount >= 10) {
      timeoutcount = 0;
      time2string(textstring, mytime);
      display_string(3, textstring);
      display_update();
      tick(&mytime);

      (*porte)++; // Increment PORTE to update the LED status
    }
  }

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
}
*/



/*
--- Assignment 2 ---

When the time-out event-flag is a "1", how does your code reset it to "0"?
• What would happen if the time-out event-flag was not reset to "0" by your code? Why?
- The code resets the time-out event-flag to "0" by using the IFSCLR(0) = 0x100; instruction. 
If the time-out event-flag was not reset to "0" by the code, 
the code would not be able to detect the next time-out event, 
as the flag would still be set to "1" and the code would not enter the if-statement that checks for the time-out event-flag.
Why is IFSCLR(0) set to 0x100 and not any other value?
The IFSCLR(0) is set to 0x100 because the time-out event-flag is located at bit 8 of the IFS(0) register. 
The IFSCLR(0) = 0x100 instruction clears the time-out event-flag by setting bit 8 of the IFS(0) register to "0".



• Which device-register (or registers) must be written to define the time between time-out
events? Describe the function of that register (or of those registers).
- The PR2 register must be written to define the time between time-out events.
Because the PR2 register is the period register for Timer 2,
writing to it sets the time between time-out events.


• If you press BTN3 quickly, does the time update reliably? Why, or why not? If not, would
that be easy to change? If so, how?
- If you press BTN3 quickly, the time does not update reliably.
This is because the code only updates the time every 10 time-out events (1 second).
To make the time update reliably when BTN3 is pressed quickly,
the code could be changed to update the time every time the BTN3 is pressed.
For example one could call time2string, display_string and display_update
each time a button is called.


*/