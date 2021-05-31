
#ifndef SYSPRO_FINDPAYMENTS_H
#define SYSPRO_FINDPAYMENTS_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "HashTable.h"
void findPayments( bucketListNode** ,char* ,int ,int );
void findPaymentsTime(bucketListNode** ,char* ,int ,int ,char* ,char*);
void findPaymentsDate(bucketListNode** ,char* ,int ,int ,char* ,char*);
void findPaymentsDateTime(bucketListNode** ,char* ,int ,int ,char* ,char *,char* ,char*);
#endif //SYSPRO_FINDPAYMENTS_H
