#include<openssl/evp.h>
#include <openssl/ossl_typ.h>
#include<iostream>

using namespace std;

#pragma comment(lib,"libssl.lib")
#pragma comment(lib,"libcrypto.lib")

int sm3(unsigned char* input,int in_len,unsigned char* digest)
{
	unsigned char output[256] = "";
	unsigned int out_len = 8;
	void* text = input;

	EVP_MD_CTX* ctx = EVP_MD_CTX_new();
	EVP_DigestInit_ex(ctx, EVP_sm3(), NULL);
	EVP_DigestUpdate(ctx, text, in_len);
	EVP_DigestFinal_ex(ctx, output, &out_len);

	for (int i = 0; i < 16; i++)
		digest[i] = output[i];
	return 0;
}

int birthday_attact_reduced_sm3()
//The reduced sm3 is 'round' bytes
{
	unsigned char flag[13] = "202000460051";
	unsigned char temp[16] = "", tag[16] = "", re[16] = "";
	unsigned int i, j, k;

	sm3(flag, 12, tag);

	sm3(tag, 16, temp);
	j = 0;
	k = pow(2, 16);
	while (re[0] != tag[0] || re[1] != tag[1])
	{
		j++;
		sm3(temp, 16, re);
		for (i = 0; i < 4; i++)
			temp[i] = re[i];
		cout << j << endl;
		if (j > k)
			break;
	}
	if (re[0] == tag[0] && re[1] == tag[1])
		cout << "Find a collision!\n";

	/*
	for(j=0;j<256;j++)
	{
		cout << "Find a collision!\n";
		cout << "sm(202000460051)=sm(char(" << i << "))\n";
	}
	*/

	return 0;
}


int main()
{
	birthday_attact_reduced_sm3();
}
