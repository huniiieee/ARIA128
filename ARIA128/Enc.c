#include "Enc.h"

void F0(byte text[Nb], byte key[Nk])
{
	byte tmp[Nb] = { 0, };
	for (int i = 0; i < Nb; i++)
		text[i] ^= key[i];
	

	text[0] = S1[text[0]];
	text[1] = S2[text[1]];
	text[2] = Inv_S1[text[2]];
	text[3] = Inv_S2[text[3]];

	text[4] = S1[text[4]];
	text[5] = S2[text[5]];
	text[6] = Inv_S1[text[6]];
	text[7] = Inv_S2[text[7]];

	text[8] = S1[text[8]];
	text[9] = S2[text[9]];
	text[10] = Inv_S1[text[10]];
	text[11] = Inv_S2[text[11]];

	text[12] = S1[text[12]];
	text[13] = S2[text[13]];
	text[14] = Inv_S1[text[14]];
	text[15] = Inv_S2[text[15]];

	for (int i = 0; i< Nb; i++)
	{
		for (int j = 0; j < Nb; j++)
			tmp[i] ^= Involution[i][j] * text[j];
	}
	memcpy(text, tmp, Nb);
}			   
void Fe(byte text[Nb], byte key[Nk])
{
	byte tmp[Nb] = { 0, };
	for (int i = 0; i < Nb; i++)
		text[i] ^= key[i];

	text[0] = Inv_S1[text[0]];
	text[1] = Inv_S2[text[1]];
	text[2] = S1[text[2]];
	text[3] = S2[text[3]];

	text[4] = Inv_S1[text[4]];
	text[5] = Inv_S2[text[5]];
	text[6] = S1[text[6]];
	text[7] = S2[text[7]];

	text[8] = Inv_S1[text[8]];
	text[9] = Inv_S2[text[9]];
	text[10] = S1[text[10]];
	text[11] = S2[text[11]];

	text[12] = Inv_S1[text[12]];
	text[13] = Inv_S2[text[13]];
	text[14] = S1[text[14]];
	text[15] = S2[text[15]];

	for (int i = 0; i < Nb; i++)
	{
		for (int j = 0; j < Nb; j++)
			tmp[i] ^= Involution[i][j] * text[j];
	}
	memcpy(text, tmp, Nb);

}

void Ff(byte text[Nb], byte key1[Nk], byte key2[Nk])
{
	for (int i = 0; i < Nb; i++)
		text[i] ^= key1[i];

	text[0] = Inv_S1[text[0]];
	text[1] = Inv_S2[text[1]];
	text[2] = S1[text[2]];
	text[3] = S2[text[3]];

	text[4] = Inv_S1[text[4]];
	text[5] = Inv_S2[text[5]];
	text[6] = S1[text[6]];
	text[7] = S2[text[7]];

	text[8] = Inv_S1[text[8]];
	text[9] = Inv_S2[text[9]];
	text[10] = S1[text[10]];
	text[11] = S2[text[11]];

	text[12] = Inv_S1[text[12]];
	text[13] = Inv_S2[text[13]];
	text[14] = S1[text[14]];
	text[15] = S2[text[15]];

	for (int i = 0; i < Nb; i++)
		text[i] ^= key2[i];
}

void Rot_L(byte text[Nb], int num)
{
	int r = num % 8;
	int q = num / 8;
	byte tmp[Nb] = { 0, };
	memcpy(tmp, text, Nb);
	if (r == 0)
	{
		for (int i = 0; i < Nb; i++)
			text[i] = tmp[(i + q)%Nb];
	}
	else
	{
		for (int i = 0; i < Nb; i++)
			text[i] = (byte)((tmp[(i + q)%Nb] << r)) | (byte)(((tmp[(i + q + 1)%Nb] >> (8 - r))));
	}
}

void Rot_Xor(byte text1[Nb], byte text2[Nb],byte result[Nb], int num)
{

	Rot_L(text2, num);
	for (int i = 0; i < Nb; i++)
		result[i] = text1[i] ^ text2[i];
	Rot_L(text2, 128 - num);

		
}

void Enc_KeySchedule(byte key[Nk], byte Rkey[Nr+1][Nk])
{
	byte W0[16];
	byte W1[16];
	byte W2[16];
	byte W3[16];
	byte Kr[16] = { 0, };
	byte tmp[16] = { 0, };

	memcpy(W0, key, Nk);
	memcpy(tmp, key, Nk);

	F0(tmp, C1);

	for (int i = 0; i < 16; i++)
		W1[i] = tmp[i] ^ Kr[i];

	memcpy(tmp, W1, Nk);

	Fe(tmp, C2);

	for (int i = 0; i < 16; i++)
		W2[i] = W0[i] ^ tmp[i];
	

	memcpy(tmp, W2, Nk);

	F0(tmp, C3);
	for (int i = 0; i < 16; i++)
		W3[i] = tmp[i] ^ W1[i];
	
	
	Rot_Xor(W0, W1, Rkey[0], 128 - 19);
	Rot_Xor(W1, W2, Rkey[1], 128 - 19);
	Rot_Xor(W2, W3, Rkey[2], 128 - 19);
	Rot_Xor(W3, W0, Rkey[3], 128 - 19);
	Rot_Xor(W0, W1, Rkey[4], 128 - 31);
	Rot_Xor(W1, W2, Rkey[5], 128 - 31);
	Rot_Xor(W2, W3, Rkey[6], 128 - 31);
	Rot_Xor(W3, W0, Rkey[7], 128 - 31);
	Rot_Xor(W0, W1, Rkey[8], 61);
	Rot_Xor(W1, W2, Rkey[9], 61);
	Rot_Xor(W2, W3, Rkey[10], 61);
	Rot_Xor(W3, W0, Rkey[11], 61);
	Rot_Xor(W0, W1, Rkey[12], 31);
	

}
void Encryption(byte plain[Nb], byte cipher[Nb], byte key[Nk])
{
	byte Rkey[Nr + 1][Nk] = { 0, };
	Enc_KeySchedule(key, Rkey);
	F0(plain, Rkey[0]);
	Fe(plain, Rkey[1]);
	F0(plain, Rkey[2]);
	Fe(plain, Rkey[3]);
	F0(plain, Rkey[4]);
	Fe(plain, Rkey[5]);
	F0(plain, Rkey[6]);
	Fe(plain, Rkey[7]);
	F0(plain, Rkey[8]);
	Fe(plain, Rkey[9]);
	F0(plain, Rkey[10]);
	Ff(plain, Rkey[11], Rkey[12]);
	memcpy(cipher, plain, Nb);
}