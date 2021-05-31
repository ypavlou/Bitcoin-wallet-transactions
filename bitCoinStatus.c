#include "bitCoinStatus.h"
void bitCoinStatus(char* bitCoinId,ListNodeT* head){
    ListNodeT* ta = findInTreeListB(head,bitCoinId);
    if(ta!=NULL) {
        printf("The initial value of bitCoin %s is : %d\n", bitCoinId,ta->Tree->value);
        transNum=0;
        findNum(ta->Tree,ta->Tree->wallet_id);
        printf("The number of total transactions that %s has been involved is: %d\n",bitCoinId,transNum);
        transNum=0;
        unspent=0;
        findLeaves(ta->Tree,ta->Tree->wallet_id);
        printf("The total unspent value of  %s is: %d\n",bitCoinId,unspent);
        unspent=0;
        printf("\n");
    }else{
        printf("BitCoin %s is not registered\n",bitCoinId);
    }

}