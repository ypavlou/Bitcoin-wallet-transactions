#include "requestTransactions.h"

void requestTransaction(char* transactionID,char*senderWalletID ,char*receiverWalletID,char* value,char* date,char* time ,bucketListNode** senderHashtable,bucketListNode** receiverHashtable,int senderNumOfEntries,int receiverNumOfEntries,int bucketEntries,bucketList ** Wallettable,int bucketentries,int hashentries,ListNodeT* treeList){

    Bucket* temp =findIn_Buckets(findIn_HashTable(Wallettable,senderWalletID,hashentries),senderWalletID,bucketentries);
    if(temp!=NULL) {
        if (temp->balance >= atoi(value)) {

            if (findInBuckets(findInHashTable(senderHashtable, senderWalletID, senderNumOfEntries), senderWalletID,bucketEntries) == NULL) {  //if receiver id is not already in hashtable
                hashTableInsert(senderHashtable, senderWalletID, senderNumOfEntries, bucketEntries);
            }
            bucket* foundBucket = findInBuckets(findInHashTable(senderHashtable, senderWalletID, senderNumOfEntries),senderWalletID,bucketEntries);


            insertInTrasactionList(&foundBucket->transactionList, transactionID, senderWalletID, receiverWalletID,atoi(value), date, time); //insert in transactionList

            //Same for receiver hash table

            if (findInBuckets(findInHashTable(receiverHashtable, receiverWalletID, receiverNumOfEntries),receiverWalletID, bucketEntries) ==NULL) {  //if receiver id is not already in hashtable
                hashTableInsert(receiverHashtable, receiverWalletID, receiverNumOfEntries, bucketEntries);
            }

            insertInTrasactionList(&findInBuckets(findInHashTable(receiverHashtable, receiverWalletID, receiverNumOfEntries),
                                                  receiverWalletID, bucketEntries)->transactionList, transactionID, senderWalletID,receiverWalletID, atoi(value), date, time);

            Node* foundBitCoin= findBitCoinV(temp->BitCoinList,atoi(value));        //find the first bitcoin that can make the transaction
            if(foundBitCoin!=NULL){
                printf("Transaction %s %s %d %s %s is done.\n",senderWalletID,receiverWalletID,atoi(value),date,time);
                foundBitCoin->value=foundBitCoin->value-atoi(value);
                temp->balance = temp->balance -atoi(value); //the transaction is done so, decrease the balance of sender's wallet
                found = 0;
                ListNodeT *ta = findInTreeListB(treeList, foundBitCoin->bitCoinId);

                 transaction* t =findTransaction(foundBucket->transactionList,senderWalletID,receiverWalletID,atoi(value),date,time);

                addSenderReceiver(&ta->Tree, atoi(value), senderWalletID,receiverWalletID,t); //adds sender receiver in bitcoin tree for current transaction
                found = 0;
            }
        } else {
            printf("User %s has not enough bitCoins for this transaction, transaction cannot be complete. \n",senderWalletID);
        }
    }  else{printf("User %s is not registered transaction cannot be complete.\n",senderWalletID);}

}