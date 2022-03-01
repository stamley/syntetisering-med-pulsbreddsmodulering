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
// #include "time4io.c"

double DUTYCYCLE = 0.1; // 10%
int direction = 1; // Positive direction for LFO first

float e9 = 0.000000001; 

int LFOcounter = 0;


char note[] = "A  ";

/* Interrupt Service Routine */
void user_isr( void ){
  return;
}

void tmrinit( void ){
  // Initialize timer 2 for timeouts every 100 ms (10 timeouts per second)
  
  // 1. Clearing the ON control bit to disable the timer
  T2CONCLR = 0x8000;

  // 2. Clearing TCS control bit to select internal PBCLK (clock) source
  T2CONCLR = 0x0002; 
  
  // 3. Setting bits 4-6 to 000 - 111 depending on wished pre-scale
  T2CONSET = 0x0030; // 1:8
                     // 10 000 000 = 10 MHz
                     // period = PR2 * N * 12.5 ns = 10000 * 4 * 12.5 * 10^-9
                     // 0.001 = 10^-3 = 1 ms = 1000 µs
                     // f = 1/1000 µs = 1 kHz

                     // 12.5 ns pga klockhastigheten, men stämmer det?
                     // PR2 egentligen 2000 - 1 ?

  TMR2 = 0x0; // Clear timer register
  
  // Loading the period register with the desired 16-bit match value.
  PR2 = 5000; // Period = PR2 (Kanske skriva 1999?)

  // Start the timer
  T2CONSET = 0x8000; 


  /* -- Second timer initialization --*/

  // 1. Clearing the ON control bit to disable the timer
  T3CONCLR = 0x8000;

  // 2. Clearing TCS control bit to select internal PBCLK (clock) source
  T3CONCLR = 0x0002; 

  // 3. Setting bits 4-6 to 000 - 111 depending on wished pre-scale
  T3CONSET = 0x0070;  // 1:256
                      // 80 MHz / 256 = 312 500 c/s

  // Clear timer register
  TMR3 = 0x0; 

  // Index 12 in family data sheet p. 51
  IFSCLR(0) = 0x00001000; // Clear the timer interrupt status flag
  IECSET(0) = 0x00001000; // Enable timer interrupts 

  // Load period register with desired 16-bit match value (Set period)
  PR3 = 312.5; // One second with 1:256 pre-scale

  // Start the timer
  T3CONSET = 0x8000; 

}

void ocinit ( void ){
  // Source: PIC32 FRM Section 16: Output Compare mode
  OC1CON = 0x0000;  // Turn off OC1 while doing setup 
  OC1R = 2500;    // Initialize primary Compare register
  OC1RS = 2500;   // Initialize secondary Compare register

  // ocm<2:0> = 110 -> PWM mode on OC1; Fault pin disabled
  // OCTSEL = 0 -> Timer 2
  // First four bits = 0110
  OC1CONSET = 0x06;

  OC1RS = PR2 / 2;

  // Turn OC1 on
  OC1CONSET = 0x8000;
}



void adcinit (void){
  AD1PCFGCLR = (1 << 2); // AN2 som egentligen är A0
  AD1CSSLCLR = 0xFF; // Clearar för säkerhets skull
  AD1CSSLSET = (1 << 2); // Sätter AN2(A0) till analog

  AD1CON2SET = 1 << 2 | 1 << 10; // Kollar på en kanal, och aktiverar auto-scan
  AD1CON1SET = 1 << 1; // Start sampliiing
  AD1CON1CLR = 1; // Clear done bit

  AD1CON1SET = (0x7 << 5) | (1 << 2); // Auto convert and auto sample.
  AD1CON3SET = (0x2) | (20 << 8); // ADCS conversion clock select | SAMC auto sample time

  AD1CON1SET = 1 << 15; // Start ADC module
}

/* Lab-specific initialization goes here */
void labinit( void ){
  TRISDSET = 0x7f0; // e) Bits 5-11 assigned as inputs
                    // Other bits left untouched
  tmrinit();
  ocinit();
  adcinit();

  enable_interrupt();
  return;
}

void thenewOGsoundofkista( void ){
  if(PR2<10000){
    PR2++;
  }
  else{
    PR2 = 6000;
  }
}

void freqcalc ( int freq ){
  PR2 = (int) 1/(freq * 8 * 12.5 * e9);
  OC1RS = PR2 / DUTYCYCLE; 
}

void time4synth( void ){

  int getbutton = getbtns();
  int getswitches = getsw();


  if(IFS(0) & 0x1000){
    IFSCLR(0) = 0x1000;
    LFOcounter++;
  }
  if(LFOcounter == 3){
    if(direction){ 
    // Positive direction  
      if(DUTYCYCLE < 0.9) 
      // As long as The dutycycle is less than 90% we increase
        DUTYCYCLE += 0.001;
      else{
        direction = 0;
      }
    }
    else{
      if(DUTYCYCLE > 0.1)
      // As long as the dutycycle is bigger than 10% we decrease
        DUTYCYCLE -= 0.001;
      else{
        direction = 1;
      }
    }

    LFOcounter = 0;
  }

  OC1RS = PR2 * DUTYCYCLE;

  PR2 = 1000 + ADC1BUF0 * 100;  
  // Change the period, i.e frequency, i.e pitch

  // BTN4
  if(getbutton & 0x04){
    freqcalc(440); // 440 = A
    *note = 0x41;
  }
  // Pressing BTN3 changes the second digit of mytime with values of switches
  if(getbutton & 0x02){
    freqcalc(523); // 523.251 = C
    *note = 0x43; 
  }

  // Pressing BTN2 changes the second digit of mytime with values of switches
  if(getbutton & 0x01){
    freqcalc(587); // 587.33 = D
    *note = 0x44;
  }

  if(getswitches & 0x08){
    DUTYCYCLE = 0.75; // 75%
  }

  if(getswitches & 0x04){
    DUTYCYCLE = 0.5; // 50%
  }

  if(getswitches & 0x02){
    DUTYCYCLE = 0.25; // 25%
  }

  if(getswitches & 0x01){
    DUTYCYCLE = 0.1;
    /*char buffer[] = "";
    for(int i = 0; i < 10; i++){
      *buffer = ADC1BUF0 & (0x1 << i);
      buffer++;
    }
    */
  }
}

void labwork( void ) {
  
  display_update();
  display_string( 3, note );
  // display_string( 2, LFOarray );
  // timeoutcount = 0;
  // thenewOGsoundofkista();
  time4synth();
  
}


