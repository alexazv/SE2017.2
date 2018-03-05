/*
 * block.c
 *
 *  Created on: 24 de fev de 2018
 *      Author: matheustenorio
 */

#include "ICBlock.h"

static unsigned char __tempData[HASH_STR_SIZE + BLOCK_DATA_STR_SIZE];

/***************PRIVATE FUNCTIONS*****************/
int hexaToString(char *output, uint64_t data, uint8_t sizeInBytes) {
	uint64_t mask = 0xFFUL << (8*(sizeInBytes-1));
	char byteStr[2];
	int size = 0;

	output[0] = '\0';
	byteStr[0] = '\0';
	for (int i = 0; i < sizeInBytes; ++i) {
		sprintf(byteStr, "%02x", (uint8_t)((data & mask) >> ((sizeInBytes-i-1)*8)));
		strcat(output, byteStr);
		mask = mask >> 8;
		size += 2;
	}

	return size;
}

/***************PUBLIC FUNCTIONS*****************/
void ICHashCreate(ICHash *hash, ICBlockData *data, ICHash *previousHash) {
	int offset = 0;

	offset += ICBlockDataToString(__tempData+offset, data);
	offset += ICHashToString(__tempData+offset, previousHash);

	unsigned char *tempHash = SHA256(__tempData, strlen(__tempData), 0);

	memcpy(hash->hash, tempHash, HASH_SIZE);
}

bool ICHashEquals(ICHash *hash1, ICHash *hash2) {
	bool result = true;

	for (int i = 0; i < HASH_SIZE; ++i) {
		if (hash1->hash[i] == hash2->hash[i]) continue;

		result = false;
		break;
	}

	return result;
}

void ICHashCopy(ICHash *target, ICHash *source) {
	memcpy(target->hash, source->hash, HASH_SIZE);
}

int ICHashToString(char *output, ICHash *hash) {
	int offset = 2;

	output[0] = '\0';

	strcat(output, "0x");
	for (int i = 0; i < HASH_SIZE; ++i) {
		offset += hexaToString(output+offset, hash->hash[i], sizeof(unsigned char));
	}

	return offset;
}

int ICAddressToString(char *output, ICAddress address) {
	int offset = 2;

	output[0] = '\0';

	strcat(output, "0x");
	offset += hexaToString(output+offset, address, ADDRESS_SIZE);

	return offset;
}

int ICBlockDataToString(char *output, ICBlockData *blockData) {
	int offset = 0;

	output[0] = '\0';

	strcat(output, "[");
	offset++;

	offset += ICAddressToString(output+offset, blockData->senderAddress);

	strcat(output, "|");
	offset++;

	offset += ICAddressToString(output+offset, blockData->receiverAddress);

	strcat(output, "|0x");
	offset += 3;

	offset += hexaToString(output+offset, blockData->amout, sizeof(int));

	strcat(output, "]");
	offset++;

	return offset;
}

int ICBlockToString(char *output, ICBlock *block) {
	int offset = 0;

	output[0] = '\0';

	strcat(output, "{\n\t");
	offset += 3;

	offset += ICHashToString(output+offset, &block->hash);

	strcat(output, "\n\t");
	offset += 2;

	offset += ICHashToString(output+offset, &block->previousHash);

	strcat(output, "\n\t");
	offset += 2;

	offset += ICBlockDataToString(output+offset, &block->data);

	strcat(output, "\n}");
	offset += 2;

	return BLOCK_STR_SIZE;
}
