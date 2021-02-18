#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//data structure for key schedule
u_int8_t keysched[12][16];

//data structure for ftable
unsigned char* F_table[16][16];

//data structure for fvalues
unsigned int fvalues[2];

//keyschedule.c
int key_schedule(unsigned char *, char);
int mod_func(int, int);
void bit_rotation_left(unsigned char *);
void bit_rotation_right(unsigned char *);
//implemented for debugging
void display_keysched(void);

//wholesched.c
void wholesched(unsigned long, long unsigned int, char);
long unsigned int whiting(long unsigned int, long unsigned int);
long unsigned int convert_to_hex(char*);
long unsigned int pad_zeroes(char*);

//F_function.c
void F_function(unsigned int, unsigned int, int);
unsigned int G_function(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, int);

//ftable.c
unsigned char Ftable(unsigned char);
void create_ftable(void);
void display_ftable(void);
