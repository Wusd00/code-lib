#include<openssl/evp.h>
#include <openssl/ossl_typ.h>
#include<iostream>

using namespace std;

#pragma comment(lib,"libssl.lib")
#pragma comment(lib,"libcrypto.lib")

int sm3(unsigned char* input, int in_len, unsigned char* digest)
{
	unsigned char output[256] = "";
	unsigned int out_len = 8;
	void* text = input;

	EVP_MD_CTX* ctx = EVP_MD_CTX_new();
	EVP_DigestInit_ex(ctx, EVP_sm3(), NULL);
	EVP_DigestUpdate(ctx, text, in_len);
	EVP_DigestFinal_ex(ctx, output, &out_len);

	for (int i = 0; i < 32; i++)
		digest[i] = output[i];
	return 0;
}

//code above this line are copied from (sm3 birthday attact.cpp)

int rho()
{
	unsigned char inite[13] = "202000460051";
	unsigned char step1[32]="", step2[32] = "";
	unsigned int i,limit;

	sm3(inite, 12, step1);
	sm3(step1, 32, step2);
	i = 0;
	limit = pow(2, 16);

	while (step1[0] != step2[0] || step1[1] != step2[1])
	{
		sm3(step1, 32, step1);
		sm3(step2, 32, step2);
		sm3(step2, 32, step2);
		i++;
		cout << i << endl;
		if (i > limit)
			break;
	}
	if (step1[0] == step2[0] && step1[1] == step2[1])
		cout << "Find a collision!\n";

	return 0;
}

int main()
{
	rho();
	return 0;
}