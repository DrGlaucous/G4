
#include <Arduino.h>

//guess what? TWO_PI is already defined in Arduino.h!
//#define TWO_PI 6.2831998


//contains lightweight implementations of sin() and cos() via lookup table
//unit circle represented with 256 degrees and a radius of +-512

short sinTbl[0x100];

void InitTrigTbl()
{
    for (int i = 0; i < 0x100; ++i)
            sinTbl[i] = (short)(sin(i * TWO_PI / 256.0) * 512.0);
}

short GetSin(unsigned char deg)
{
	return sinTbl[deg];
}

short GetCos(unsigned char deg)
{
	deg += 0x40;//90 degree offset
	return sinTbl[deg];
}



