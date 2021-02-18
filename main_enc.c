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
  char *buffer;                       //buffer to put the whole thing in
  long file_size;                     //file size
  size_t result;                      //for reading in the whole file
  int length;                         //for keeping track of how much plaintext there is
  int temp;                           //for how many times to loop
  char temp2[8];                      //to send through to get hex


  //opens the file to read only, and gets the key in
  FILE *fp = fopen(argv[1], "r");
  fscanf(fp, "%lx", &entire_key);
  fclose(fp);

  //clear the ciphertext file
  FILE *f = fopen("ciphertext.txt", "w");
  fclose(f);

  //put entire_key into the byte array
  for(int i = 0; i < 8; ++i)
  {
    key_og[i] = entire_key >> (j*8) & 0xFF;
    --j;
  }

  //first step is to implement the key schedule
  if(key_schedule(key_og, 'e') < 0)
  {
    printf("Key schedule failed");
    return 0;
  }


  //loops through and encrypts a little at a time
  //opens the plaintext file to read only
/**************The following code was borrowed from http://www.cplusplus.com/reference/cstdio/fread************************/
  //the point of this is to read in the file and put it all in a buffer
  FILE *fp1 = fopen(argv[2], "rb");

  if(fp1)
  {
    fseek(fp1, 0, SEEK_END);
    file_size = ftell(fp1);
    rewind(fp1);

    buffer = (char*)malloc(sizeof(char)*file_size);
    if(buffer == NULL)
      return -1;
    result = fread(buffer, 1, file_size, fp1);
    if(result != file_size)
      return -1;
  }
/**************End of borrowed code*************************/
  else
  {
    perror("Cannot open file");
    return -1;
  }

  //For readability purposes, the plaintext and key and ciphertext are all displayed here
  //even though the ciphertext also gets written to a file
  printf("plaintext: %s\nkey: %lx\nciphertext: ", buffer, entire_key);

  //Check to see if the buffer starts with 0x
  //if it does, it's hex and read it in as hex
  if(buffer[0] == 48 && buffer[1] == 120)
  {
    rewind(fp1);
    fscanf(fp1, "%lx", &plaintext);
    wholesched(entire_key, plaintext, 'e');
  }

  //if it's not, read it in as plaintext, and convert to hex.
  //Loop through to send it to the whole schedule 64 bits at a time
  else
  {
    length = (strlen(buffer) - 1);
    temp = length/8;
    for(int i = 0; i < temp; ++i)
    {
      memcpy(temp2, (buffer+i), 8);
      plaintext = convert_to_hex(temp2);
      wholesched(entire_key, plaintext, 'e');
    }
    if(length % 8 != 0)
    {
      memcpy(temp2, (buffer+(temp*8)), 8);
      plaintext = pad_zeroes(temp2);
      wholesched(entire_key, plaintext, 'e');
    }
  }
  printf("\n");
  free(buffer);
  fclose(fp1);

}
