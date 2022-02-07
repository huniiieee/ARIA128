#ifndef _ENC_H_
#define _ENC_H_

#include "type.h"
#include "STable.h"

void F0(byte text[Nb], byte key[Nk]);
void Fe(byte text[Nb], byte key[Nk]);
void Ff(byte text[Nb], byte key1[Nk], byte key2[Nk]);
void Rot_L(byte text[Nb], int num);
void Rot_Xor(byte text1[Nb], byte text2[Nb], byte result[Nb], int num);
void Enc_KeySchedule(byte key[Nk]);
void Encryption(byte plain[Nb], byte cipher[Nb], byte key[Nk]);
#endif