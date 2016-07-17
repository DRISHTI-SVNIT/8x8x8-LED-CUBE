#ifndef CUBE_H
#define CUBE_H
#define CUBE_SIZE 8
#define CUBE_BYTES 64
#define AXIS_X 0x78
#define AXIS_Y 0x79
#define AXIS_Z 0x7a


volatile unsigned char cube[CUBE_SIZE][CUBE_SIZE];
volatile unsigned char fb[CUBE_SIZE][CUBE_SIZE];

#endif

