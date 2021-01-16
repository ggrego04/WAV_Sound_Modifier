#ifndef ENCRYPTION_H
#define ENCRYPTION_H
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "wave.h"

int encodeText(char *wavfile,char *filename);
int getBit(char *m,int n);
int* createPermutationFunction(int N, unsigned int systemkey);

#endif