#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
/*
In this file, write a C function that returns the status of the toggle-switches on the board, with the
following specification.
Function prototype: int getsw( void );
Parameter: none.
Return value: The four least significant bits of the return value should contain data from switches
SW4, SW3, SW2, and SW1. SW1 corresponds to the least significant bit. All other bits of the return
value must be zero.
Notes: The function getsw will never be called before Port D has been correctly initialized. The
switches SW4 through SW1 are connected to bits 11 through 8 of Port D. 
*/
volatile uint32_t *portDAddress = (volatile uint32_t *) &PORTD;



/*
g) In file time4io.c, add a C function that returns the current status of the push-buttons BTN2,
BTN3, and BTN4 with the following specification1
.
Function prototype: int getbtns(void);
Parameter: none.
Return value: The 3 least significant bits of the return value must contain current data from push
buttons BTN4, BTN3, and BTN2. BTN2 corresponds to the least significant bit. All other bits of
the return value must be zero.
Notes: The function getbtns will never be called before Port D has been correctly initialized. The
buttons BTN4, BTN3, and BTN2, are connected to bits 7, 6 and 5 of Port D.
*/

// Function to get the status of the switches
int getsw(void) {
    return ((PORTD >> 8) & 0xF); // Shift right 8 bits and mask with 0xF to get the 4 least significant bits
}

// Function to get the status of the buttons
int getbtns(void) {
    return ((PORTD >> 5) & 0x7); // Shift right 5 bits and mask with 0x7 to get the 3 least significant bits
}
