

#ifndef SYSPRO_1_TRANSACTION_H
#define SYSPRO_1_TRANSACTION_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct lastTransaction{
    char date[20];
    char time[20];
}lastTransaction;
lastTransaction last_transaction;
typedef struct transaction{
    char transactionID[50];
    char senderWalletID[50];
    char receiverWalletID[50];
    int value;
    char date[50];
    char time[50];
}transaction;
typedef struct listNode{
    transaction data;
    struct listNode* next;
}listNode;
void addNode(listNode** , char* , char* , char* , int , char* , char* );
void printList(listNode* );
transaction * findTransaction(listNode* ,char* ,char* ,int ,char* ,char* );
void deleteList(listNode** );
#endif //SYSPRO_1_TRANSACTION_H
