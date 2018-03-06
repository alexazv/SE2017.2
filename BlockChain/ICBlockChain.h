/*
 Code created 2018/03/04
 Author: Alexandre Azevedo
*/

#ifndef __BLOCKCHAIN_H__
#define __BLOCKCHAIN_H__
#endif


#include "ICBlock.h"

void ICBlockChainCreate();

ICBlock ICBlockChainGetLastBlock();

ICBlock ICBlockChainGetBlock(uint8_t index);

ICBlock * ICBlockChainGetChain(uint8_t *sizeOutput);

bool ICBlockChainCreateBlock(ICAddress sender, ICAddress receiver, int amount);

void ICBlockChainWriteLog();

bool ICBlockChainCheckValidity();
