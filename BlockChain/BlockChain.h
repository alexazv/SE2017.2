/*
 Code created 2018/03/04
 Author: Alexandre Azevedo
*/

#ifndef __BLOCKCHAIN_H__
#define __BLOCKCHAIN_H__
#endif


#include "ICBlock.h"

void BlockChainCreate();

ICBlock copyLastBlock();

ICBlock copyBlock(uint8_t index);

ICBlock * copyBlockChain(uint8_t * sizeOutput);

bool mineNewBlock(ICAddress sender, ICAddress receiver, int amount);

void writeLog();

bool checkBlockChainValidity();
