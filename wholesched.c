#include "defs.h"

//function for doing everything
void wholesched(unsigned long entire_key, long unsigned int text, char flag)
{

  unsigned int rvalues[4];            //rvalues ouputted from whiting step
  unsigned int hold;                  //hold for the switcheroo of the rvalues
  long unsigned int yvalues;          //need y values for the end
  long unsigned int text_output;      //64 bit concat of the output - plain or cipher
  int j;                              //counter for byte arrays
  unsigned char temp[8];              //byte array for the conversion of the plaintext in decryption

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
  //printf("yvalues: %lx\n", yvalues);
 // printf("key: %lx\n", entire_key);
  text_output = (yvalues ^ entire_key);

  if(flag == 'e')
  {
    printf("%lx", text_output);
    FILE *fp2 = fopen("ciphertext.txt", "a");
    fprintf(fp2, "%lx\n", text_output);
    fclose(fp2);
  }
  else
  {
    FILE *fp3 = fopen("plaintext.txt", "a");
    printf("\nHex plaintext: %lx\n", text_output);
  //  printf("If the plaintext you wished to decrypt was originally in hex, it's not going to print something pretty to plaintext.txt\n");

    j = 7;
    printf("\nplaintext in ascii: "); 
    for(int i = 0; i < 8; ++i)
    {
      temp[i] = text_output >> (j*8) & 0xFF;
      --j;
    }
    for(int i = 0; i < 8; ++i)
    {
      printf("%c", temp[i]);
      fprintf(fp3, "%c", temp[i]);
    }
    printf("\n");
    fclose(fp3);
  }
    

}

//regular whiting function
long unsigned int whiting(long unsigned int og_key, long unsigned int text)
{
  return (og_key ^ text);
}

long unsigned int convert_to_hex(char* to_convert)
{
  long unsigned int hold;
  int j = 7;

  for(int i = 0; i < 8; ++i)
  {
    if(i == 0)
      hold = ((unsigned long)to_convert[i] << (j*8));
    else
      hold += ((unsigned long)to_convert[i] << (j*8));
    --j;
  }
  return hold;
}


long unsigned int pad_zeroes(char* to_convert)
{
  int length;
  long unsigned int hold;
  int j = 7;

  length = (strlen(to_convert)-1);
  for(int i = 0; i < 8; ++i)
  {
    if(i == 0)
      hold = ((unsigned long)to_convert[i] << (j*8));
    else if(i < length)
      hold += ((unsigned long)to_convert[i] << (j*8));
    else
      hold += 0x00;
    --j;
  }
  return hold;

}
