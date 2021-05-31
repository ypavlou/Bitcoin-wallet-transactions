#include "ReadFiles.h"


void ReadTransactionsFile(FILE* in, bucketListNode** senderHashtable,bucketListNode** receiverHashtable,int senderNumOfEntries,int receiverNumOfEntries,int bucketEntries,bucketList ** Wallettable,int bucketentries,int hashentries,ListNodeT* treeList){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char* token=NULL;
    fp = in;

    char transactionID[50];
    char senderWalletID[50];
    char  receiverWalletID[50];
    char date[50];
    char time[50];
    char value[50];
    strcpy(last_transaction.date,"00-00-00");
    strcpy(last_transaction.time,"00:00");

    while ((read = getline(&line, &len, fp)) != -1) {
        char delim[] = " ";
        int i = 1;
        for (token = strtok(line, delim); token; token = strtok(NULL, delim)){
            if(i==1) {
                sscanf(token,"%s", transactionID);
            }else if(i==2){
                sscanf(token,"%s", senderWalletID);
            }else if(i==3){
                sscanf(token,"%s", receiverWalletID);
            }else if(i==4){
                sscanf(token,"%s", value);
            }else if(i==5){
                sscanf(token," %s", date);
            }else if(i==6){
                sscanf(token," %s", time);
            }
            i++;
        }
        requestTransaction(transactionID, senderWalletID, receiverWalletID, value, date, time, senderHashtable,receiverHashtable, senderNumOfEntries, receiverNumOfEntries, bucketEntries, Wallettable,bucketentries, hashentries, treeList);
    }

    free(token);


    if (line)
        free(line);
}


void ReadBitCoinsFile(FILE* in,ListNodeT** head,int value,bucketList ** table,int HashtableNumOfEntries,int bucketEntries){
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    char* token;
    fp = in;
    if (fp == NULL)
        exit(EXIT_FAILURE);


    while ((read = getline(&line, &len, fp)) != -1) {
        char delim[] = " ";
        char userId[50];
        char bitCoinId[50];
        int flag = 0;
        for (token = strtok(line, delim); token; token = strtok(NULL, delim)){
            if(flag == 0){
                sscanf(token,"%s",userId);
                hashTable_Insert(table,userId,value,HashtableNumOfEntries,bucketEntries);
                flag = 1;
            }else{
                sscanf(token,"%s",bitCoinId);
                if(findBitCoin(table,bitCoinId,HashtableNumOfEntries, bucketEntries)== true){
                    printf("Id %s already exists program terminated\n",bitCoinId);
                    exit(0);
                }
                Bucket* temp =findIn_Buckets(findIn_HashTable(table,userId,HashtableNumOfEntries),userId,bucketEntries);    //insert in wallet hash table
                increaseBalance(temp,value);
                printf("Just added bitCoin %s with walletId %s\n",bitCoinId,userId);
                insertInBitCoinList(&temp->BitCoinList,bitCoinId,value);


                addNodeT(head,value,userId,bitCoinId);  //add bitCoin in list and create the tree of this bitcoin id


            }
        }


    }
    free(token);
    printf("\n");



    if (line)
        free(line);
}