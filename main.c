#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "cipher.h"

#define USAGE "./human4b --hex/--bin HEXKEY\n--hex: Print output in hex\n--bin: Print output in ASCII equivalent of binary output\nEach HEXKEY digit is a hex number between 0 and 15 inclusive, separated by spaces and the length is to be 3N + 1 where N is natural number"

uint8_t get_hex(char c);
int main(int argc, char **argv)
{
	if(argc != 3 || (strlen(argv[2]) - 1) % 3 != 0)
	{
		printf("%s\n", USAGE);
		return 0;
	}
	else
	{
		int bin_format = 0;
		if(!strcmp(argv[1], "--bin"))
		{
			bin_format = 1;
		}
		else if(strcmp(argv[1], "--hex"))
		{
			printf("%s\n", USAGE);
			exit(-1);
		}
		
		
		size_t keylen = strlen(argv[2]);
		uint8_t key[keylen];
		int should_exit = 0;
		for(int i = 0; i < keylen; i++)
		{
			uint8_t num = get_hex(argv[2][i]);
			if(num > 15)
			{
				should_exit = 1;
				printf("Key character in position #%d is not in the range 0 - 15 inclusive\n", i);
			}
			else
			{
				key[i] = num;
			}
		}
		
		if(should_exit)
		{
			exit(-1);
		}
		else
		{
			uint8_t stream[256];
			generate_keystream(stream, 256, key, keylen);
			
			if(bin_format)
			{
				for(int i = 0; i < 256; i += 2)
				{
					char outc = stream[i] << 4;
					outc |= stream[i + 1];
					
					printf("%c", outc);
					fflush(stdout);
				}
				
				printf("\n");
			}
			else
			{
				for(int i = 0; i < 256; i++)
				{
					printf("%01X", stream[i]);
					fflush(stdout);
				}
				
				printf("\n");
			}
		}
		
	}

	return 0;
}

uint8_t get_hex (char c)
{
	switch(c)
	{
		case '0':
			return 0;
		case '1':
			return 1;
		case '2':
			return 2;
		case '3':
			return 3;
		case '4':
			return 4;
		case '5':
			return 5;
		case '6':
			return 6;
		case '7':
			return 7;
		case '8':
			return 8;
		case '9':
			return 9;
		case 'A':
			return 10;
		case 'B':
			return 11;
		case 'C':
			return 12;
		case 'D':
			return 13;
		case 'E':
			return 14;
		case 'F':
			return 15;
		default:
			return 16;
	}
}
