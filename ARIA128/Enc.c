#include "Enc.h"

void F0(byte text[Nb], byte key[Nk])
{
	for (int i = 0; i < Nb; i++)
		text[i] ^= key[i];

	text[0] = S1[text[0]];
	text[1] = S1[text[1]];
	text[2] = S1[text[2]];
	text[3] = S1[text[3]];

	text[4] = S2[text[4]];
	text[5] = S2[text[5]];
	text[6] = S2[text[6]];
	text[7] = S2[text[7]];

	text[8] = Inv_S1[text[8]];
	text[9] = Inv_S1[text[9]];
	text[10] = Inv_S1[text[10]];
	text[11] = Inv_S1[text[11]];

	text[12] = Inv_S2[text[12]];
	text[13] = Inv_S2[text[13]];
	text[14] = Inv_S2[text[14]];
	text[15] = Inv_S2[text[15]];

	for (int i = 0; i< Nb; i++)
	{
		for (int j = 0; j < Nb; j++)
			text[i] ^= Involution[i][j] * text[j];
	}

}			   
void Fe(byte text[Nb], byte key[Nk])
{
	for (int i = 0; i < Nb; i++)
		text[i] ^= key[i];

	text[0] = Inv_S1[text[0]];
	text[1] = Inv_S1[text[1]];
	text[2] = Inv_S1[text[2]];
	text[3] = Inv_S1[text[3]];

	text[4] = Inv_S2[text[4]];
	text[5] = Inv_S2[text[5]];
	text[6] = Inv_S2[text[6]];
	text[7] = Inv_S2[text[7]];

	text[8] = S1[text[8]];
	text[9] = S1[text[9]];
	text[10] = S1[text[10]];
	text[11] = S1[text[11]];

	text[12] = S2[text[12]];
	text[13] = S2[text[13]];
	text[14] = S2[text[14]];
	text[15] = S2[text[15]];

	for (int i = 0; i < Nb; i++)
	{
		for (int j = 0; j < Nb; j++)
			text[i] ^= Involution[i][j] * text[j];
	}
}
void Ff(byte text[Nb], byte key[Nk])
{
	for (int i = 0; i < Nb; i++)
		text[i] ^= key[i];

	text[0] = Inv_S1[text[0]];
	text[1] = Inv_S1[text[1]];
	text[2] = Inv_S1[text[2]];
	text[3] = Inv_S1[text[3]];

	text[4] = Inv_S2[text[4]];
	text[5] = Inv_S2[text[5]];
	text[6] = Inv_S2[text[6]];
	text[7] = Inv_S2[text[7]];

	text[8] = S1[text[8]];
	text[9] = S1[text[9]];
	text[10] = S1[text[10]];
	text[11] = S1[text[11]];

	text[12] = S2[text[12]];
	text[13] = S2[text[13]];
	text[14] = S2[text[14]];
	text[15] = S2[text[15]];

	for (int i = 0; i < Nb; i++)
		text[i] ^= key[i];
}

void Rot_L(byte text[Nb], int num)
{
	 
}

void Rot_R(byte text[Nb], int num)
{

}

void Enc_KeySchedule(byte key[Nk], byte Rkey[Nb][Nk])
{
	byte W0[16];
	byte W1[16];
	byte W2[16];
	byte W3[16];
	byte Kr[16] = { 0, };

	memcpy(W0, key, Nk);
	F0(W0, C1);
	for (int i = 0; i < 16; i++)
		W1[i] = W0[i] ^ Kr[i];

	Fe(W1, C2);
	for (int i = 0; i < 16; i++)
		W2[i] = W0[i] ^ W1[i];

	F0(W2, C3);
	for (int i = 0; i < 16; i++)
		W3[i] = W2[i] ^ W1[i];



}
void Encryption(byte plain[Nb], byte cipher[Nb], byte key[Nk]);