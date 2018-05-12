#ifndef __YNAG_RC4_H
#define __YNAG_RC4_H
namespace yang {

class RC4 {
public:
    void setKey(const char *key, int keyLen);
	void encrpyt(char *data, int len);
	void decrpyt(char *data, int len);
	RC4();
	~RC4();
private:
	void rc4(unsigned char *data, int len);
private:
	static const int MAX_LEN = 256;

	unsigned char _key[MAX_LEN];
	int _keyLen;
	unsigned char _box[MAX_LEN];
};

}

#endif

