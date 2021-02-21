#include "defs.h"

int key_schedule(unsigned char * og_key, char flag)
{
  //which bit to take
  int k = 0;            //to keey track of what to mod
  int bit_totake = 0;   //to find out what bit to take

  for(int i = 0; i < 16; ++i)
  {
    if(flag == 'e')
    {
      for(int j = 0; j < 12; ++j)
      {
        if(k == 4)
          k = 0;
        bit_rotation_left(og_key);
        bit_totake = mod_func(i, k);
        keysched[i][j] = og_key[7-bit_totake];
        ++k;
      }
    }
    else
    {
      for(int j = 11; j >=0; --j)
      {
        if(k == 4)
          k = 0;
        bit_totake = mod_func(i, k);
        keysched[i][j] = og_key[bit_totake];
        ++k;
        bit_rotation_right(og_key);
      }
    }
  }

  display_keysched();


  return 1;

}

//mod function for key schedule
int mod_func(int round, int keynum)
{
  int func = 4*round+keynum;
  return func % 8;
}

//for bit rotation in key schedule for encryption
void bit_rotation_left(unsigned char * key)
{
  int bigFlag = 0;            //When rotating to find if key needs a 1 on the end

  for(int i = 0; i < 8; ++i)
  {
    if(i == 0)
    {
      if(key[0] >= 128)
        bigFlag = 1;
      key[0] = key[0] << 1;
      continue;
    }
    if(key[i] >= 128)
      ++key[i-1];
    key[i] = key[i] << 1;
    if(i == 7 && bigFlag == 1)
      ++key[7];
  }
  
}

//for bit rotation for decryption
void bit_rotation_right(unsigned char * key)
{
  int bigFlag = 0;

  for(int i = 7; i >= 0; --i)
  {
    if(i == 7)
    {
      if((key[7] % 2) == 1)
        bigFlag = 1;
      key[7] = key[7] >> 1;
      continue;
    }
    if((key[i] % 2) ==1)
      key[i+1] += 128;
    key[i] = key[i] >> 1;
    if(i == 0 && bigFlag == 1)
      key[0] += 128;
  }

}

//used to display the key schedule
void display_keysched()
{
  for(int i = 0; i < 16; ++i)
  {
    for(int j = 0; j < 12; ++j)
    {
      printf("%hhx  ", keysched[i][j]);
    }
    printf("\n");
  }
}
