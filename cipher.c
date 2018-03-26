#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "cipher.h"
#include "rot.h"

void perform_ks_rounds(uint8_t *x, uint8_t *y, uint8_t *z)
{
	uint8_t a = x[0];
	uint8_t b = y[0];
	uint8_t c = z[0];
	
	if(a > 15 || b > 15 || c > 15)
	{
		printf("Error when perform_ks_rounds function called!\nSome parameters were not in the 0-15 inclusive range.\nNumbers (for debug):\n%d\n%d\n%d\n", a, b, c);
		exit(-1);
	}
	for(int i = 0; i < 32; i++)
	{
		a = a ^ b;
		b = b ^ c;
		c = c ^ a;
		
		a = ROTR4(a, 1);
		b = ROTR4(b, 3);
		c = ROTR4(c, 2);
		
		a = (a + b) % 16;
		b = (b + c) % 16;
		c = (a + c) % 16;
	}
	
	*x = a;
	*y = b;
	*z = c;
}

uint8_t generate_keybit(uint8_t pos, uint8_t *key, size_t keylen)
{
	if(keylen == 0 || (keylen - 1) % 3 != 0)
	{
		printf("Error when generate_keybit function called!\nthe keylen parameter is not of length 3N + 1 where N is a natural number (key length of 0 is not allowed).\n");
		exit(-1);
	}
	else if(key[0] == 0)
	{
		printf("Error when generate_keybit function called!\nThe intended keyspace does not allow for 0 being the first key char. An explanation of this can be found online\n");
		exit(-3);
	}
	
	for(size_t i = 0; i < keylen; i++)
	{
		if(key[i] < 0 || key[i] > 15)
		{
			printf("Error when generate_keybit function called!\nall key chars must be in the range 0-15 inclusive.\n");
			exit(-1);
		}
	}
	
	uint8_t a = pos % 16;
	uint8_t b = ((pos - a) / 16) % 16;
	uint8_t c = key[0];
	perform_ks_rounds(&a, &b, &c);
	
	for(size_t i = 0; i < (keylen - 1) / 3; i++)
	{
		a = a ^ key[3*i + 1];
		b = b ^ key[3*i + 2];
		c = b ^ key[3*i + 3];
		
		perform_ks_rounds(&a, &b, &c);
	}
	
	//Seems like a waste of psuedo-randomness but I'm scared to change anything now (if anyone can try b^c or a^b^c or some other combination which works, their name shall appear here (and elsewhere) and I shall be happier and less nervous.
	return c;
}

void generate_keystream(uint8_t *stream, size_t streamlen, uint8_t *key, size_t keylen)
{
	if(keylen == 0 || (keylen - 1) % 3 != 0)
	{
		printf("Error when generate_keystream function called!\nEither length of key is not of length 3N + 1 (where N is a natural number) or keylength is 0!\n");
		exit(-3);
	}
	else if(key[0] == 0)
	{
		printf("Error when generate_keystream function called!\nThe intended keyspace does not allow for 0 being the first key char. An explanation of this can be found online\n");
		exit(-3);
	}
	else if(streamlen == 0)
	{
		printf("Error when generate_keystream function called!\nstreamlen must be larger than 0.\n");
		exit(-3);
	}
	else
	{
		for(uint8_t i = 0; i < (streamlen - 1); i++)
		{
			stream[i] = generate_keybit(i, key, keylen);
		}
	}
}
