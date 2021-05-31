#include "WalletStatus.h"
void walletStatus(char* walletID,bucketList ** table,int HashtableNumOfEntries,int bucketEntries){
    Bucket* temp =findIn_Buckets(findIn_HashTable(table,walletID,HashtableNumOfEntries),walletID,bucketEntries);
    printf("User's %s wallet status is %d\n",walletID,temp->balance);
}