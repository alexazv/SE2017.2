#include <stdio.h>
#include "BlockChain.h"

int main()
{
    BlockChainCreate();

    mineNewBlock(1,2, 10);
    mineNewBlock(2, 3, 20);
    mineNewBlock(3, 4, 50);

    ICBlock last = copyLastBlock();
    ICBlock index = copyBlock(1);

    printf("%d", checkBlockChainValidity());

    writeLog();


    return 0;
}
