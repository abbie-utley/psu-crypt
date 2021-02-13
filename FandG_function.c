#include "defs.h"

//F function designed for the F values. Calls G function
//purpose of the function is to fill up the global variable of fvalues
void F_function(unsigned int r0, unsigned int r1, int round)
{
  unsigned int T0;            //T0 value used for F function
  unsigned int T1;            //T1 value, also used for F function
  unsigned int key_concat1;   //need to  concat the keys for the F0 and F1 functions
  unsigned int key_concat2;   //see above

  T0 = G_function(r0, keysched[round][0], keysched[round][1], keysched[round][2], keysched[round][3], round);
  T1 = G_function(r1, keysched[round][4], keysched[round][5], keysched[round][6], keysched[round][7], round);
//  printf("tvalues: %hx, %hx\n", T0, T1);

  key_concat1 = (keysched[round][8] << 8) | (keysched[round][9]);
  key_concat2 = (keysched[round][10] << 8) | (keysched[round][11]);

  fvalues[0] = (T0 + (2*T1) + key_concat1) % 65536;
  fvalues[1] = ((2*T0) + T1 + key_concat2) % 65536;

}

//G function, designed for the G values, calls Ftable
unsigned int G_function(unsigned int r, unsigned int key0, unsigned int key1, unsigned int key2, unsigned int key3, int round)
{
  unsigned char gvalues[6];
  gvalues[0] = r >> 8;
  gvalues[1] = r;

  gvalues[2] = ((Ftable(gvalues[1] ^ key0)) ^ gvalues[0]);
  gvalues[3] = (Ftable(gvalues[2] ^ key1)) ^ gvalues[1];

  gvalues[4] = (Ftable(gvalues[3] ^ key2)) ^ gvalues[2];
  gvalues[5] = (Ftable(gvalues[4] ^ key3)) ^ gvalues[3];

  
//  printf("gvalues: %hhx, %hhx, %hhx, %hhx, %hhx, %hhx\n", gvalues[0], gvalues[1], gvalues[2], gvalues[3], gvalues[4], gvalues[5]);

  return ((gvalues[4] << 8) + gvalues[5]);

}

  
