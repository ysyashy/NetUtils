#include "RC4.h"
#include <cstring>
#include <iostream>

namespace yang {

void RC4::setKey(const char *key, int keyLen)
{
	_keyLen = keyLen;
	memcpy(_key, key, keyLen);

	unsigned char k[MAX_LEN] = { 0 };
	for (int i = 0; i < MAX_LEN; i++) {
		_box[i] = i;
		k[i] = _key[i % _keyLen];
	}

	unsigned char tmp = 0;
	for (int i = 0, j = 0; i < MAX_LEN; i++) {
		j = (j + _box[i] + k[i]) % MAX_LEN;
		std::swap(_box[i], _box[j]);
	}
}
void RC4::encrpyt(char *data, int len)
{
	rc4((unsigned char *)data, len);
}
void RC4::decrpyt(char *data, int len)
{
	rc4((unsigned char *)data, len);
}
RC4::RC4()
{
	memset(_key, 0x00, sizeof(_key));
	memset(_box, 0x00, sizeof(_box));
}


RC4::~RC4()
{
}

void RC4::rc4(unsigned char * data, int len)
{
	unsigned char tBox[MAX_LEN] = { 0 };
	memcpy(tBox, _box, MAX_LEN);

	int i = 0, j = 0, t = 0;
	unsigned long k = 0;
	for (k = 0; k < len; k++) {
		i = (i + 1) % MAX_LEN;
		j = (j + tBox[i]) % MAX_LEN;
		std::swap(tBox[i], tBox[j]);
		t = (tBox[i] + tBox[j]) % MAX_LEN;
		data[k] ^= tBox[t];
	}
}

}
