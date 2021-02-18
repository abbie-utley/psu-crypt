#include "defs.h"

int main(int argc, char* argv[])
{
  //make sure the files that are read in are the correct amount
  if(argc < 3 || argc > 3)
  {
    printf("Please add the 2 files specified by the README.");
    return 0;
  }

  //variables
  long unsigned int entire_key;
  unsigned char key_og[8];
  int j = 7;
  long unsigned int ciphertext;
  char * buffer;
  int file_size;
  size_t result;
  int length;

  //opens the file to read only, and gets the key in
  FILE *fp = fopen(argv[1], "r");
  fscanf(fp, "%lx", &entire_key);
  fclose(fp);

  //clear the plaintext file
  FILE *f = fopen("plaintext.txt", "w");
  fclose(f);


  //put entire_key into the byte array
  for(int i = 0; i < 8; ++i)
  {
    key_og[i] = entire_key >> (j*8) & 0xFF;
    --j;
  }

  //first step is to implement the key schedule
  if(key_schedule(key_og, 'd') < 0)
  {
    printf("Key schedule failed");
    return 0;
  }

  //next step is to go through the ciphertext
/**************The following code was borrowed from http://www.cplusplus.com/reference/cstdio/fread************************/
  FILE *fp1 = fopen(argv[2], "r");

  
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
    fclose(fp1);
/**************End of borrowed code*************************/
  }
  else
  {
    perror("cannot open file");
    return -1;
  }
  length = strlen(buffer);
  length /= 16;
  char* ptr_start = buffer;
  char* ptr_end = buffer;
  printf("buffer: %s\n", buffer);

  printf("ciphertext in hex: ");
  for(int i = 0; i < length; ++i)
  {
    ptr_end += 16;
    ciphertext = strtoul(ptr_start, NULL, 16);
//    printf("%lx", ciphertext);
    ptr_start +=16;
    wholesched(entire_key, ciphertext, 'd');
  }
  free(buffer);
}
