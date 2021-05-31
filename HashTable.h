#ifndef SYSPRO_1_HASHTABLE_H
#define SYSPRO_1_HASHTABLE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Transaction.h"
typedef struct bucket{
    char userid[50];
    listNode* transactionList;

}bucket;
typedef struct bucketListNode{
    int num;
    int current_entries;
    bucket* bucketContent;
    struct bucketListNode* next;
}bucketListNode;

void addBucketNode(bucketListNode**, char*, int);
void insertInBucket(bucketListNode** , char* , int);
void printBucketList(bucketListNode*, int );
bucketListNode* FindLastNode(bucketListNode**);
void deleteBucketList(bucketListNode**,int);
void printBucket(bucketListNode** ,int );
void hashTableInsert(bucketListNode**,char*,int,int);
bucketListNode** createHashTable(int, int);
unsigned long hash(unsigned char *);
void insertInTrasactionList(listNode **,char* , char* , char* , int , char* , char* );
bucketListNode*  findInHashTable(bucketListNode** ,char* ,int );
bucket* findInBuckets(bucketListNode* ,char* ,int );
#endif //SYSPRO_1_HASHTABLE_H



