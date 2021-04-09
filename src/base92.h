#ifndef base92_h
#define base92_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
unsigned char base92chr_encode(unsigned char byt);

unsigned char base92chr_decode(unsigned char byt);

unsigned char *base92encode(unsigned char *str, size_t len);

unsigned char *base92decode(unsigned char *str, size_t *len);
#endif /* base92_h */
