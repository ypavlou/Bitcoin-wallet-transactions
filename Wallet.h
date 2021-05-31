
#ifndef SYSPRO_1_WALLET_H
#define SYSPRO_1_WALLET_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct list_Node{
    char bitCoinId[50];
    int value;
    struct list_Node *next;
}Node;
void add_ListNode(Node**, char*, int);
typedef struct Bucket{
    char userid[50];
    int balance;
   Node* BitCoinList;

}Bucket;
typedef struct bucketList_Node{
    int num;
    int current_entries;
    Bucket bucketContent[4];
    struct bucketList_Node* next;
}bucketList;

void addBucket(bucketList**, char*,int, int);
void insertInBuckets(bucketList** , char* ,int, int);
void  increaseBalance(Bucket* ,int );
void printBuckets(bucketList*, int );
bucketList* FindLast(bucketList**);
void deleteBuckets(bucketList**);
void printaBucket(bucketList** ,int );
void hashTable_Insert(bucketList**,char*,int,int,int);
bucketList** create_HashTable(int, int);
unsigned long hashfunction(unsigned char *);
void insertInBitCoinList(Node **, char*, int );
bucketList*  findIn_HashTable(bucketList** ,char* ,int );
Bucket* findIn_Buckets(bucketList* ,char* ,int );
void printBitCoinList(Node* );
void deleteListWallet(Node**);
bool findBitCoin(bucketList**  ,char* ,int ,int );
Node* findBitCoinV(Node* ,int);
#endif //SYSPRO_1_WALLET_H
