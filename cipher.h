#ifndef __CIPHER_H__
#define __CIPHER_H__


//Documentation:
//Performs 32 rounds on current keystream numbers *x, *y and *z and modifies original values
void perform_ks_rounds(uint8_t *x, uint8_t *y, uint8_t *z);

//Documentation:
//Generates a key stream bit for a position 0 - 255 (8-bit position) from given key, nonce is to be applied directly as part of the key (e.g. first 3 key numbers are a unique nonce). First key number must not be 0
uint8_t generate_keybit(uint8_t pos, uint8_t *key, size_t keylen);

//Documentation:
//Generates a keystream of 255 4-bit integers. Nonce (for getting another stream from the same 'password') is to be applied directly as part of the key (e.g. first 3 key numbers are a unique nonce). First key number must not be 0. If stream length is 0 the maximum possible keystream is generated from the key.
void generate_keystream(uint8_t *stream, size_t streamlen, uint8_t *key, size_t keylen);
#endif
