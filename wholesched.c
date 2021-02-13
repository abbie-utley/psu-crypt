#include "defs.h"

//function for doing everything
void wholesched(unsigned long entire_key, long unsigned int text )
{

  unsigned int rvalues[4];            //rvalues ouputted from whiting step
  unsigned int hold;                  //hold for the switcheroo of the rvalues
  long unsigned int yvalues;          //need y values for the end
  long unsigned int ciphertext;       //64 bit concat of ciphertext
  int j;                              //counter for byte arrays

  //next step is to call the whiting step
  text = whiting(entire_key, text);
//  printf("%lx\n", entire_key);

  j = 3;
  for(int i = 0; i < 4; ++i)
  {
    rvalues[i] = text >> (j*16) & 0xFFFF;
    --j;
  }

  //start rounds for encryption
  for(int i = 0; i < 16; ++i)
  { 
//    printf("\nRound %d: \n", i);
    F_function(rvalues[0], rvalues[1], i);
//    printf("fvalues: %hx, %hx\n", fvalues[0], fvalues[1]);
    hold = (fvalues[0] ^ rvalues[2]);
    rvalues[2] = rvalues[0];
    rvalues[0] = hold;
    hold = (fvalues[1] ^ rvalues[3]);
    rvalues[3] = rvalues[1];
    rvalues[1] = hold;
//    printf("new rvalues: %hx, %hx, %hx, %hx\n", rvalues[0], rvalues[1], rvalues[2], rvalues[3]);
  }

  //generate new y's from the16 rounds of encryption
  yvalues = ((unsigned long)rvalues[2] << 48);
  yvalues += ((unsigned long)rvalues[3] << 32);
  yvalues += (rvalues[0] << 16);
  yvalues += rvalues[1];

  //XOR them with the key to make the ciphertext
  //key is in unsigned chars, need in unsigned ints
  printf("yvalues: %lx\n", yvalues);
  printf("%lx", entire_key);
  ciphertext = (yvalues ^ entire_key);
  printf("\nciphertext: %lx\n", ciphertext);

}

//regular whiting function
long unsigned int whiting(long unsigned int og_key, long unsigned int text)
{
  return (og_key ^ text);
}

