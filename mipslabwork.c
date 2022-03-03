

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
// #include "sineapproxes.c"

float sines[] = {0.500000, 0.504000, 0.507999, 0.511998, 0.515996, 0.519992, 
  0.523986, 0.527977, 0.531966, 0.535951, 0.539933, 0.543911, 0.547885, 
  0.551854, 0.555817, 0.559775, 0.563727, 0.567673, 0.571612, 0.575544, 
  0.579468, 0.583384, 0.587292, 0.591191, 0.595081, 0.598962, 0.602832, 
  0.606693, 0.610542, 0.614381, 0.618208, 0.622023, 0.625827, 0.629617, 
  0.633395, 0.637159, 0.640910, 0.644646, 0.648368, 0.652075, 0.655767, 
  0.659444, 0.663104, 0.666748, 0.670376, 0.673986, 0.677579, 0.681155, 
  0.684712, 0.688250, 0.691770, 0.695271, 0.698752, 0.702213, 0.705654, 
  0.709075, 0.712474, 0.715853, 0.719210, 0.722544, 0.725857, 0.729147, 
  0.732414, 0.735658, 0.738878, 0.742075, 0.745247, 0.748394, 0.751517, 
  0.754615, 0.757687, 0.760734, 0.763754, 0.766748, 0.769715, 0.772656, 
  0.775569, 0.778454, 0.781312, 0.784141, 0.786942, 0.789715, 0.792458, 
  0.795173, 0.797857, 0.800512, 0.803137, 0.805732, 0.808296, 0.810829, 
  0.813331, 0.815801, 0.818241, 0.820648, 0.823023, 0.825366, 0.827677, 
  0.829954, 0.832199, 0.834410, 0.836588, 0.838733, 0.840843, 0.842920, 
  0.844962, 0.846969, 0.848942, 0.850880, 0.852783, 0.854651, 0.856483, 
  0.858279, 0.860040, 0.861765, 0.863453, 0.865106, 0.866721, 0.868300, 
  0.869842, 0.871348, 0.872816, 0.874246, 0.875640, 0.876996, 0.878314, 
  0.879594, 0.880836, 0.882040, 0.883206, 0.884334, 0.885423, 0.886474, 
  0.887486, 0.888459, 0.889394, 0.890289, 0.891146, 0.891963, 0.892741, 
  0.893480, 0.894180, 0.894840, 0.895461, 0.896042, 0.896583, 0.897085, 
  0.897547, 0.897970, 0.898352, 0.898695, 0.898998, 0.899261, 0.899484, 
  0.899667, 0.899810, 0.899914, 0.899977, 0.900000, 0.899983, 0.899926, 
  0.899829, 0.899693, 0.899516, 0.899299, 0.899043, 0.898746, 0.898410, 
  0.898033, 0.897617, 0.897161, 0.896666, 0.896131, 0.895556, 0.894942, 
  0.894288, 0.893594, 0.892862, 0.892090, 0.891279, 0.890428, 0.889539, 
  0.888611, 0.887644, 0.886638, 0.885593, 0.884510, 0.883389, 0.882229, 
  0.881030, 0.879794, 0.878520, 0.877208, 0.875858, 0.874471, 0.873046, 
  0.871584, 0.870085, 0.868548, 0.866975, 0.865365, 0.863719, 0.862036, 
  0.860317, 0.858562, 0.856771, 0.854945, 0.853083, 0.851186, 0.849253, 
  0.847286, 0.845284, 0.843247, 0.841176, 0.839071, 0.836932, 0.834760, 
  0.832553, 0.830314, 0.828042, 0.825736, 0.823399, 0.821028, 0.818626, 
  0.816192, 0.813726, 0.811229, 0.808701, 0.806142, 0.803552, 0.800932, 
  0.798282, 0.795602, 0.792893, 0.790154, 0.787386, 0.784589, 0.781764, 
  0.778911, 0.776030, 0.773121, 0.770185, 0.767222, 0.764232, 0.761216, 
  0.758174, 0.755106, 0.752012, 0.748893, 0.745750, 0.742581, 0.739389, 
  0.736172, 0.732932, 0.729669, 0.726382, 0.723073, 0.719742, 0.716389, 
  0.713014, 0.709618, 0.706201, 0.702763, 0.699305, 0.695827, 0.692329, 
  0.688812, 0.685277, 0.681722, 0.678150, 0.674560, 0.670952, 0.667327, 
  0.663686, 0.660028, 0.656354, 0.652664, 0.648960, 0.645240, 0.641506, 
  0.637757, 0.633995, 0.630220, 0.626431, 0.622630, 0.618817, 0.614991, 
  0.611154, 0.607306, 0.603448, 0.599579, 0.595700, 0.591811, 0.587913, 
  0.584007, 0.580092, 0.576169, 0.572239, 0.568301, 0.564356, 0.560405, 
  0.556448, 0.552485, 0.548517, 0.544544, 0.540567, 0.536586, 0.532601, 
  0.528613, 0.524621, 0.520628, 0.516632, 0.512635, 0.508636, 0.504637, 
  0.500637, 0.496637, 0.492637, 0.488639, 0.484641, 0.480645, 0.476650, 
  0.472658, 0.468669, 0.464683, 0.460701, 0.456722, 0.452748, 0.448778, 
  0.444814, 0.440855, 0.436902, 0.432955, 0.429015, 0.425082, 0.421157, 
  0.417239, 0.413330, 0.409429, 0.405538, 0.401656, 0.397784, 0.393922, 
  0.390070, 0.386230, 0.382401, 0.378583, 0.374778, 0.370986, 0.367206, 
  0.363439, 0.359687, 0.355948, 0.352224, 0.348514, 0.344820, 0.341141, 
  0.337478, 0.333831, 0.330201, 0.326588, 0.322992, 0.319414, 0.315854, 
  0.312312, 0.308789, 0.305285, 0.301801, 0.298337, 0.294892, 0.291468, 
  0.288066, 0.284684, 0.281324, 0.277985, 0.274669, 0.271375, 0.268105, 
  0.264857, 0.261633, 0.258433, 0.255257, 0.252105, 0.248978, 0.245877, 
  0.242801, 0.239750, 0.236725, 0.233727, 0.230756, 0.227811, 0.224894, 
  0.222004, 0.219141, 0.216307, 0.213502, 0.210725, 0.207977, 0.205258, 
  0.202568, 0.199909, 0.197279, 0.194680, 0.192111, 0.189573, 0.187066, 
  0.184590, 0.182146, 0.179733, 0.177353, 0.175005, 0.172689, 0.170406, 
  0.168156, 0.165940, 0.163756, 0.161607, 0.159491, 0.157409, 0.155361, 
  0.153348, 0.151370, 0.149426, 0.147518, 0.145644, 0.143806, 0.142004, 
  0.140238, 0.138507, 0.136813, 0.135155, 0.133534, 0.131949, 0.130401, 
  0.128890, 0.127416, 0.125979, 0.124580, 0.123218, 0.121894, 0.120608, 
  0.119359, 0.118149, 0.116977, 0.115843, 0.114748, 0.113691, 0.112673, 
  0.111693, 0.110752, 0.109851, 0.108988, 0.108164, 0.107380, 0.106635, 
  0.105929, 0.105262, 0.104635, 0.104048, 0.103500, 0.102992, 0.102524, 
  0.102095, 0.101706, 0.101357, 0.101048, 0.100778, 0.100549, 0.100359, 
  0.100210, 0.100100, 0.100031, 0.100001, 0.100012, 0.100062, 0.100152, 
  0.100283, 0.100453, 0.100664, 0.100914, 0.101204, 0.101534, 0.101904, 
  0.102314, 0.102763, 0.103252, 0.103781, 0.104350, 0.104958, 0.105606, 
  0.106293, 0.107019, 0.107785, 0.108590, 0.109434, 0.110317, 0.111239, 
  0.112200, 0.113199, 0.114238, 0.115315, 0.116430, 0.117584, 0.118776, 
  0.120006, 0.121274, 0.122581, 0.123924, 0.125306, 0.126725, 0.128181, 
  0.129674, 0.131205, 0.132772, 0.134376, 0.136016, 0.137693, 0.139407, 
  0.141156, 0.142941, 0.144762, 0.146618, 0.148510, 0.150437, 0.152399, 
  0.154395, 0.156426, 0.158492, 0.160591, 0.162725, 0.164892, 0.167093, 
  0.169327, 0.171594, 0.173894, 0.176227, 0.178592, 0.180989, 0.183418, 
  0.185879, 0.188371, 0.190894, 0.193448, 0.196033, 0.198648, 0.201294, 
  0.203969, 0.206674, 0.209408, 0.212171, 0.214963, 0.217784, 0.220633, 
  0.223509, 0.226414, 0.229345, 0.232304, 0.235290, 0.238302, 0.241340, 
  0.244404, 0.247493, 0.250608, 0.253748, 0.256912, 0.260101, 0.263314, 
  0.266550, 0.269810, 0.273093, 0.276398, 0.279726, 0.283076, 0.286447, 
  0.289840, 0.293254, 0.296688, 0.300143, 0.303618, 0.307113, 0.310626, 
  0.314159, 0.317710, 0.321280, 0.324867, 0.328472, 0.332094, 0.335733, 
  0.339389, 0.343060, 0.346747, 0.350449, 0.354167, 0.357899, 0.361645, 
  0.365405, 0.369178, 0.372965, 0.376764, 0.380575, 0.384399, 0.388234, 
  0.392080, 0.395937, 0.399804, 0.403682, 0.407569, 0.411465, 0.415370, 
  0.419284, 0.423206, 0.427135, 0.431072, 0.435015, 0.438965, 0.442921, 
  0.446883, 0.450850, 0.454822, 0.458799, 0.462780, 0.466764, 0.470752, 
  0.474743, 0.478736, 0.482731, 0.486728, 0.490727, 0.494726};

double DUTYCYCLE = 0.1; // 10%
int direction = 1; // Positive direction for LFO first

float e9 = 0.000000001; 

int LFOcounter = 0;
int arpdelay = 0;

char debugN[1];

int frequency;
char frequencychar[3];

/*short notefreq[] = {262, 294, 330, 349, 392, 440, 494};
char note[] = "CDEFGAB";*/

// char note[] = "aAbcCdDefFgG"; 
   char note[] = "DefFgGaAbcCd";

// short a4 = 440;
   short D0 = 156; 
double twelthroot2 = 1.059463094359;

char chosennote[] = "A";

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
  PR2 = 10000; // Period = PR2 (Kanske skriva 1999?)

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
  PR3 = 3125; // One second with 1:256 pre-scale

  // Start the timer
  T3CONSET = 0x8000; 

}

void ocinit ( void ){
  // Source: PIC32 FRM Section 16: Output Compare mode
  OC1CON = 0x0000;  // Turn off OC1 while doing setup 
  OC1R = PR2 / 2;   // Initialize primary Compare register
  OC1RS = PR2 / 2;  // Initialize secondary Compare register
  // The dutycycle is half of the timers period
  
  // OCM<2:0> = 110 -> PWM mode on OC1; Fault pin disabled
  // OCTSEL = 0 -> Timer 2
  // First four bits = 0110
  OC1CONSET = 0x06;

  OC1CONSET = 0x8000; // Turn OC1 on
}



void adcinit (void){
  AD1PCFGCLR = (1 << 2); // AN2 som egentligen är A0
  AD1CSSLCLR = 0xFF; // Clearar för säkerhets skull
  AD1CSSLSET = (1 << 2); // Sätter AN2(A0) till analog

  AD1CON2SET = 1 << 2 | 1 << 10; // Kollar analog signal på en kanal (A0)
                                 // | och aktiverar auto-scan
  AD1CON1SET = 1 << 1; // Start sampling
  AD1CON1CLR = 1; // Clear done bit

  AD1CON1SET = (0x7 << 5) | (1 << 2); // Auto convert and auto sample.
  AD1CON3SET = (0x2) | (20 << 8); // ADCS conversion clock select | SAMC auto sample time

  AD1CON1SET = 1 << 15; // Start ADC module
}

void ioinit( void ){
  TRISECLR = 0xff;  // Initialize LEDs as output
  TRISDSET = 0x7f0; // e) Bits 5-11 assigned as inputs
                    // Other bits left untouched
}

/* Lab-specific initialization goes here */
void labinit( void ){
  ioinit();
  tmrinit();
  ocinit();
  adcinit();

  enable_interrupt();
  return;
}


void periodcalc ( int freq ){
  PR2 = (int) 1/(freq * 8 * 12.5 * e9);
}

// Returns current frequency
int freqcalc (){
  /*int freq = 1/(PR2 * 8 * 12.5 * e9);
  freq = freq / 1;*/
  return (int) 1/(PR2 * 8 * 12.5 * e9);
}

// if freq-20 < [0] && if freq+20 > [0]

void visuals ( void ){
  frequency = freqcalc();
  // The length is 7

  // Approximating natural logarithm with taylor series
  double x1 = (frequency/D0 - 1);
  double x2 = (twelthroot2-1);

  int N = (x1 - (x1*x1) / 2) / (x2 - (x2*x2)/2);

  *debugN = N + '0';
  *chosennote = note[N % 12];
   



  /*int i = 0;
  for(i = 0; i < 7; i++){
    if(frequency % notefreq[i] == 0 || frequency % notefreq[i] - 1 == 0 || frequency % notefreq[i] + 1 == 0){
      *chosennote = note[i];
    }
    else{
      *chosennote = 'x';
    }
  }*/
}

void arpchord( short first, short second, short third){
  //First chord:
  // A = 440
  // C# = 554(.37)
  // E = 659(.25)
  // static int notechoice = 0;


  //Delay
  if(IFS(0) & 0x1000){
    IFSCLR(0) = 0x1000;
    arpdelay++;
  }

  if(arpdelay < 10)
    periodcalc(first);
  
  else if(arpdelay < 20)
    periodcalc(second);
  
  else if(arpdelay < 30)
    periodcalc(third);

  if(arpdelay >= 30)
    arpdelay = 0;
}

// LFO (Low-frequency-oscillator represented in a triangle-shape)
void triangleLFO ( void ){
  if(IFS(0) & 0x1000){
    IFSCLR(0) = 0x1000;
    LFOcounter++;
  }

  if(LFOcounter == 3){
    if(direction){ 
    // Positive direction  
      if(DUTYCYCLE < 0.9) 
      // As long as The dutycycle is less than 90% we increase
        DUTYCYCLE += 0.00254;
      else{
        direction = 0;
      }
    }
    else{
      // Negative direction
      if(DUTYCYCLE > 0.1)
      // As long as the dutycycle is bigger than 10% we decrease
        DUTYCYCLE -= 0.00254;
      else{
        direction = 1;
      }
    }
    LFOcounter = 0;
  }
  else if(LFOcounter > 3){
    DUTYCYCLE = 0.5;
    LFOcounter = 0;
  }
}

void sineLFO ( void ){
  if(IFS(0) & 0x1000){
    IFSCLR(0) = 0x1000;
    LFOcounter++;
  }

  if(LFOcounter >= 631){
    LFOcounter = 0;
  }

  DUTYCYCLE = sines[LFOcounter];
}

void time4synth( void ){

  int getbutton = getbtns();
  int getswitches = getsw();

  // Will only vary between one and zero
  static short newbutton;
  static short oldButton = 1; 
  static short LFOType = 1;

  PORTE = (PORTE & 0xf00) | (PORTD & 0x01) * 255;
  // Clear PORTEs first bit, and copy bit from PORTD onto this. 

  OC1RS = PR2 * DUTYCYCLE;
  // PR2 = ADC1BUF0 * 64; // Tar bort här för att inte alltid ändra pitch (arpfallet)
  

  // Change the period, i.e frequency, i.e pitch
  // PR2 maximum capacity is 65 535
  // ADC1BUF0 maximum capacity is 1023
  // PR2 can be incremented in steps of 64 (65 535/1023 ~= 64)


  if(getswitches & 0x08){
    PR2 = ADC1BUF0 * 64;
    DUTYCYCLE = 0.75; // 75%
  }

  // SW3 - LFO mode
  if(getswitches & 0x04){
    PR2 = ADC1BUF0 * 64; // Pitchändring
    // Triangle dutycycle LFO - BTN 4
    newbutton = (getbutton >> 2) & 0x01;
    // Toggles the button
    if(oldButton == 0 && newbutton == 1){
      if(LFOType == 1){
        LFOType = 0;
      }
      else{
        LFOType = 1;
      }
    }

  /*  *note = (char) LFOType + '0'; 
    display_string( 3, note );*/

    if(LFOType){
      triangleLFO();
    }
    else{
      sineLFO();
    }
    oldButton = newbutton;
  }

  // SW2 - Arpeggiator mode

  if(getswitches & 0x02){
    // Här används PR3 som hastighet för arpeggiatorn
    // Potentiometern kontrollerar hastigheten av arpeggiatorn
    // genom att ändra perioden (PR3) istället för pitchen
    PR3 = ADC1BUF0 * 6.4; 
    arpchord(440, 554, 659);
  }

  if(getswitches & 0x01){
    DUTYCYCLE = 0.1;
  }
}

void labwork( void ) {
  visuals();

  // 262
  // 262 / 100 = 2
  // (262%100) / 10 = 6
  // (262%10) = 2

  frequencychar[0] = frequency / 100 + '0';
  frequencychar[1] = (frequency % 100) / 10 + '0';
  frequencychar[2] = frequency % 10 + '0';

  display_update();
  display_string( 3, frequencychar );
  display_string( 2, chosennote );
  display_string( 1, chosennote );
  display_string(0, debugN);

  // display_string( 2, LFOarray );
  // timeoutcount = 0;
  // thenewOGsoundofkista();
  time4synth();
  
}





// Sine approxes


void thenewOGsoundofkista( void ){
  if(PR2<10000){
    PR2++;
  }
  else{
    PR2 = 6000;
  }
}





//grejvyard

/*if(arpdelay == 100){
    if(notechoice == 3)
      notechoice = 0;

    if(notechoice == 0)
      periodcalc(first);
    
    if(notechoice == 1)
      periodcalc(second);
    
    if(notechoice == 2)
      periodcalc(third);
    
    notechoice++;

    arpdelay = 0;*/


  // BTN4
  /*if(getbutton & 0x04){
    periodcalc(440); // 440 = A
    *note = 0x41;
  }
  // Pressing BTN3 changes the second digit of mytime with values of switches
  if(getbutton & 0x02){
    periodcalc(523); // 523.251 = C
    *note = 0x43; 
  }

  // Pressing BTN2 changes the second digit of mytime with values of switches
  if(getbutton & 0x01){
    periodcalc(587); // 587.33 = D
    *note = 0x44;
  }*/