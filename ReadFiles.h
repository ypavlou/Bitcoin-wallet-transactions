

#ifndef SYSPRO_1_READFILES_H
#define SYSPRO_1_READFILES_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ListofTrees.h"
#include "Wallet.h"
#include "HashTable.h"
#include "requestTransactions.h"

void ReadBitCoinsFile(FILE*, ListNodeT**,int,bucketList **,int ,int );
void ReadTransactionsFile(FILE*,bucketListNode**,bucketListNode**,int,int,int,bucketList ** ,int,int,ListNodeT*);
#endif //SYSPRO_1_READFILES_H
