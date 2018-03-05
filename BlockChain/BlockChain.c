/*
 Code created 2018/03/04
 Author: Alexandre Azevedo
 */

#include "BlockChain.h"
#include <time.h>
#include <stdio.h>

#define BLOCKCHAIN_MAX_SIZE 100

static ICBlock blockChain[BLOCKCHAIN_MAX_SIZE];
static uint8_t currentSize=0;

void BlockChainCreate(){

    //reset blockChain
    memset(blockChain, 0, sizeof(blockChain));

    //create new genesis block
    ICBlock genesis;

    genesis.data = (ICBlockData){0, 0, 0};
    genesis.previousHash = (ICHash){0};

    ICHashCreate(&genesis.hash, &genesis.data, &genesis.previousHash);

    blockChain[0] = genesis;

    //update blockchain size
    currentSize = 1;
}

ICBlock copyLastBlock(){

    //returns null if chain has not yet been created
    if(currentSize == 0){
        ICBlock nullBlock;
        return nullBlock;
    }

    return blockChain[currentSize-1];
}

ICBlock copyBlock(uint8_t index){

    //returns null if index is out of bounds
    if(index > currentSize-1 || index == 0){
        ICBlock nullBlock;
        return nullBlock;
    }

    return blockChain[index];
}

ICBlock * copyBlockChain(uint8_t *sizeOutput){

    ICBlock * blockChainCopy;
    memcpy(blockChainCopy, blockChain, sizeof(blockChain));
    size = currentSize;
    return blockChainCopy;
}

bool mineNewBlock(ICAddress sender, ICAddress receiver, int amount){

    //stop if has reached max size
    if(currentSize+1 == BLOCKCHAIN_MAX_SIZE)
        return false;

    //create new block
    ICBlock newBlock;

    newBlock.data = (ICBlockData){sender, receiver, amount};
    ICHashCopy(&newBlock.previousHash, &blockChain[currentSize-1].hash);

    ICHashCreate(&newBlock.hash, &newBlock.data, &newBlock.previousHash);

    blockChain[currentSize] = newBlock;


    //update size
    currentSize++;

    return true;
}

void writeLog(){

    char blockInfo[BLOCK_STR_SIZE];
    FILE *log = fopen("log.txt", "ab+"); //creates file if it doest not exist

    //print current time
    {
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        fprintf(log, "Log created at: %d-%d-%d %d:%d:%d\n",
                tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    }

    for(uint8_t i = 0; i < currentSize; i++){

        fprintf(log, "{\n");

        //print index
        fprintf(log, "Block index: %d\n", i);

        //print block info
        ICBlockToString(blockInfo, &blockChain[i]);
        fprintf(log, "%s\n", blockInfo);

        fprintf(log, "}\n");
    }

    fprintf(log, "=======================\n");

    fclose(log);
}

bool checkBlockChainValidity(){
    for(int i = 1; i < currentSize; i++){
        ICHash calculatedHash;

        ICHashCreate(&calculatedHash, &blockChain[i].data, &blockChain[i].previousHash);

        if (!ICHashEquals(&blockChain[i].previousHash , &blockChain[i-1].hash) ||
                !ICHashEquals(&blockChain[i].hash , &calculatedHash))
                return false;
    }
    return true;
}


