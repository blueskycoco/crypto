//#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "rc4.h"
#define swap_byte(a, b) { RC4_INT swapByte = (*a); (*a) = (*b); (*b) = swapByte; }

#define swap_state(n) { \
	index2 = (key_data_ptr[index1] + state[(n)] + index2) % 256; \
	swap_byte(&state[(n)], &state[index2]); \
	if (++index1 == key_data_len) index1 = 0; \
}
void RC4_set_key(RC4_KEY *key, RC4_INT key_data_len, const unsigned char *key_data_ptr)
{
	RC4_INT index1;
	RC4_INT index2;
	RC4_INT *state;
	RC4_INT counter;

	state = &key->state[0];
	for(counter = 0; counter < 256; counter++)
		state[counter] = counter;
	key->x = 0;
	key->y = 0;
	index1 = 0;
	index2 = 0;
	for(counter = 0; counter < 256; counter += 4) {
		swap_state(counter);
		swap_state(counter + 1);
		swap_state(counter + 2);
		swap_state(counter + 3);
	}
}
void RC4(RC4_KEY *key, RC4_INT buffer_len, const unsigned char *buffer_ptr, unsigned char *out)
{
	RC4_INT x;
	RC4_INT y;
	RC4_INT *state;
	RC4_INT counter;

	x = key->x;
	y = key->y;

	state = &key->state[0];
	for(counter = 0; counter < buffer_len; counter ++)
		{
			x = (x + 1);
			y = (state[x] + y) % 256;
			swap_byte(&state[x], &state[y]);
			*out++ = buffer_ptr[counter] ^ state[(state[x] + state[y]) % 256];
		}
	key->x = x;
	key->y = y;
}

