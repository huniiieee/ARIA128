#include "type.h"
#include "Dec.h"
#include "Enc.h"

void Decryption(byte cipher[Nb], byte plain[Nb], byte key[Nk])
{
	byte Rkey[Nr + 1][Nk] = { 0, };
	byte tmp[Nb] = { 0, };
	byte zero[Nb] = { 0, };
	Enc_KeySchedule(key, Rkey);
	F0(cipher, Rkey[12]);
	for (int k = 1; k < Nr ; k++)
	{
		memcpy(tmp, zero, Nb);
		for (int i = 0; i < Nb; i++)
		{
			for (int j = 0; j < Nb; j++)
				tmp[i] ^= Involution[i][j] * Rkey[k][j];
		}
		memcpy(Rkey[k], tmp, Nb);
	}

	Fe(cipher, Rkey[11]);
	F0(cipher, Rkey[10]);
	Fe(cipher, Rkey[9]);
	F0(cipher, Rkey[8]);
	Fe(cipher, Rkey[7]);
	F0(cipher, Rkey[6]);
	Fe(cipher, Rkey[5]);
	F0(cipher, Rkey[4]);
	Fe(cipher, Rkey[3]);
	F0(cipher, Rkey[2]);
	Ff(cipher, Rkey[1], Rkey[0]);
	memcpy(plain, cipher, Nb);
}
