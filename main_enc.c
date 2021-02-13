//This will have the encryption key schedule, but the rest of it will be done in a separate place
#include "defs.h"

int main(int argc, char* argv[])
{
  //make sure the arguments are correct. For now, just two argument
  if(argc < 3 || argc > 3)
  {
    printf("Please attach the %d textfiles specfied by the README\n", 2);
    return 0;
  }
 
  //local variables
  u_int8_t key_og[8];                 //byte array for key
  unsigned long entire_key;           //64 bit key
  int j = 7;                          //variable for placing things in byte arrayss
  long unsigned int plaintext;        //64 bit to hold plaintext

  //opens the file to read only, and gets the key in
  FILE *fp = fopen(argv[1], "r");
  fscanf(fp, "%lx", &entire_key);
  fclose(fp);

  //put entire_key into the byte array
  for(int i = 0; i < 8; ++i)
  {
    key_og[i] = entire_key >> (j*8) & 0xFF;
    --j;
  }

  //first step is to implement the key schedule
  if(e_key_schedule(key_og) < 0)
  {
    printf("Key schedule failed");
    return 0;
  }


  //loops through and encrypts a little at a time
  //opens the plaintext file to read only

  /********************** CURRENTLY ATTEMPTING TO LOOP THROUGH THE PLAINTEXT ****************/
/*  FILE *fp1 = fopen(argv[2], "rb");

  if(fp1)
  {
    fread(&plaintext, 8, 1, fp1);
    wholesched(entire_key, plaintext);
//    printf("%lx", plaintext);
  }
  fclose(fp1);
*/

  /*if(fp1)
  {
    do
    {
      plaintext = fgetc(fp1);
      if(EOF != plaintext)
      {
        printf("%ld", plaintext);
//        wholesched(entire_key, plaintext);
      }
    } while(EOF != plaintext);
    fclose(fp1);
  }
  printf("\n");*/

  

/*  do
  {
    fscanf(fp1, "%lx\n", &plaintext);
    printf("\n\n%lx\n\n", plaintext);
    wholesched(entire_key, plaintext);
  }
  while(!feof(fp1));
  fclose(fp1);
  */

  //Afterwards it's all the same so all of the rest of it is going to go somewhere else
  //maybe


}
