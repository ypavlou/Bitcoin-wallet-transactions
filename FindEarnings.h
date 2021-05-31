

#ifndef SYSPRO_FINDEARNINGS_H
#define SYSPRO_FINDEARNINGS_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "HashTable.h"
void findEarnings( bucketListNode** ,char* walletID,int ,int );
void findEarningsTime(bucketListNode** ,char* ,int ,int ,char* ,char*);
void findEarningsDate(bucketListNode** ,char* ,int ,int ,char* ,char*);
void findEarningsDateTime(bucketListNode** ,char* ,int ,int ,char* ,char *,char* ,char*);

#endif //SYSPRO_FINDEARNINGS_H
