#include "TraceCoin.h"
void traceCoin(char* bitCoinId,ListNodeT* head){
    ListNodeT* ta = findInTreeListB(head,bitCoinId);
    if(ta!=NULL){
        printTreeTransactions(ta->Tree);
    }else{
        printf("BitCoin %s is not registered\n",bitCoinId);
    }
}