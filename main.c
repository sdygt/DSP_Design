#include <stdio.h>
#include <inttypes.h>
#include "main.h"
/*
 * hello.c
 */

int16_t in_buf[BUF_SIZE];
int16_t out_buf[BUF_SIZE];

static void processing(int *input, int *output);
static int16_t a_law( int16_t lin);
static int16_t get_chord(int16_t v); 
static void load();
static void save();

int main(void) {
	int16_t *input = &in_buf[0];
    int16_t *output = &out_buf[0];
    puts("Init!");
    while(TRUE){
        load();
        processing(input,output);
        save();
    }
    
	return 0;
}
static void processing(int *input, int *output)
{
    int size = BUF_SIZE;
    while(size--){
        *output++ = a_law(*input++) ;
    }

}


int16_t a_law(int16_t lin){
    int16_t log = 0;
    log |= (lin & 0x8000); //copy sign bit to log first

    /*
     * Calculate the chord of log value
     * eg. s000 01ab cdxx xxxx (int16_t) 
     => (~s)011 abcd ???? ???? (lower 8 bits ignored)
     * so chord == 0b011 == 5
     * */

    int16_t chord = get_chord(lin & 0x7fff); //clear sign bit of lin
    log |= (chord << 12);
    // Chord complete.
    
    const int shift_LUT[8] ={4, 4, 3, 2, 1, 0, -1, -2};
    log |= (lin << shift_LUT[chord]);
    log >>= 8; //shift result to lower byte.
    log &= 0x00FF; // purge higher byte.

    return log;

}


int16_t get_chord(register int16_t v)
{
    const unsigned int b[] = {0x2, 0xC, 0xF0, 0xFF00};
    const unsigned int S[] = {1, 2, 4, 8};
    int i;

    register int16_t r = 0; // result of log2(v) will go here
    for (i = 3; i >= 0; i--)
    {
      if (v & b[i])
      {
        v >>= S[i];
        r |= S[i];
      } 
    }
    int16_t chord = 8 - (15 - r);
    chord = (chord > 0) ? chord : 0;
    return chord; //return
}


static void load()
{

    return;
}


static void save()
{

    return;
}
