//includes all the functions correlating to the ftable
//create, display, and get
#include "defs.h"

//designed to get at the specific spot
unsigned char Ftable(unsigned char to_find)
{
  unsigned char row = to_find >> 4;       //for the row of the ftable
  unsigned char column = to_find << 4;    //for the column of the ftable
  column = column >> 4;

  create_ftable();
//  display_ftable();

  return F_table[row][column];
}

//for the creation of the ftable, reads from txt file
void create_ftable()
{
  FILE *fp = fopen("ftable.txt", "r");

  for(int i = 0; i < 16; ++i)
  {
    for(int j = 0; j < 16; ++j)
      fscanf(fp, "%hhx,", &F_table [i][j]);
  }
  fclose(fp);
}

//for display of ftable used for debugging
void display_ftable()
{
  for(int i = 0; i < 16; ++i)
  {
    for(int j = 0; j < 16; ++j)
      printf("0x%hhx,", F_table[i][j]);
    printf("\n");
  }
}

