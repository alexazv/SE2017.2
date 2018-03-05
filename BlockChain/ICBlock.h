/*
 * block.h
 *
 *  Created on: 24 de fev de 2018
 *      Author: matheustenorio
 */

#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <openssl/sha.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define HASH_SIZE        SHA256_DIGEST_LENGTH
#define ADDRESS_SIZE     8
#define BLOCK_DATA_SIZE ((ADDRESS_SIZE * 2) + 4)
#define BLOCK_SIZE      ((HASH_SIZE * 2) + BLOCK_DATA_SIZE)

#define HASH_STR_SIZE       ((HASH_SIZE * 2) + 2)
#define ADDRESS_STR_SIZE    ((ADDRESS_SIZE * 2) + 2)
#define BLOCK_DATA_STR_SIZE ((BLOCK_DATA_SIZE * 2) + 6 + 4)
#define BLOCK_STR_SIZE 		((HASH_STR_SIZE * 2) + BLOCK_DATA_STR_SIZE + 9)

/****************UTIL TYPES*******************/

typedef struct {
	unsigned char hash[HASH_SIZE];
} ICHash;

typedef uint64_t ICAddress;

/**************CORE TYPES********************/

typedef struct {
	ICAddress senderAddress;
	ICAddress receiverAddress;
	int amout;
} ICBlockData;

typedef struct {
	ICHash hash;
	ICHash previousHash;
	ICBlockData data;
} ICBlock;

/**********HASH UTILITIES FUNCTIONS**************/
void ICHashCreate(ICHash *hash, ICBlockData *blockData, ICHash *previousHash);
bool ICHashEquals(ICHash *hash1, ICHash *hash2);
void ICHashCopy(ICHash *target, ICHash *source);

/***********TO STRING FUNCTIONS*****************/

//0x00000000000000000000000000000000000000000000000000000000000000
int ICHashToString(char *output, ICHash *hash);

//0x0000000000000000
int ICAddressToString(char *output, ICAddress address);

//[senderAddress|receiverAddress|amount in hexa]
int ICBlockDataToString(char *output, ICBlockData *blockData);

//{\n\thash\n\tpreviousHash\n\tdata\n}
int ICBlockToString(char *output, ICBlock *block);

#endif //__BLOCK_H__
