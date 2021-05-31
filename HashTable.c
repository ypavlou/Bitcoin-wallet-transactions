#include "HashTable.h"
 void addBucketNode(bucketListNode** head, char* key, int bucketEntries){
     bucketListNode* current = *head;
     //printf("einai: %d\n",bucketEntries);
     if(current==NULL){  //create the first node
         current = malloc(sizeof(bucketListNode));
         if (current == NULL) {
             exit(-1);
         }
         current->next = NULL;      //initialize as NULL the next node
         current-> bucketContent = malloc(bucketEntries* sizeof(bucket)); //allocate space for bucket
         if(current->bucketContent == NULL){
             printf("No memory.\n");
             exit(-1);
         }
         strcpy(current->bucketContent[0].userid,key);
         for(int i=0;i<bucketEntries;i++) {
             strcpy(current->bucketContent[i].userid,"0");
             current->bucketContent[i].transactionList =NULL;
         }
         current->num = 1;
         current->current_entries = 0; //there are no entries we just initialized the first place of bucket list with "0"
         *head = current;

         return;

     }
     //adding a new node at the end of the list
     while (current->next != NULL) {     //finding last node
         current = current->next;
     }
     current->next = malloc(sizeof(bucketListNode)); //allocate space for the new node
     if(current->next==NULL){
         printf("No memory.\n");
         exit(-1);
     }
     current->next->next = NULL;    //initialize as NULL the next node

     current->next-> bucketContent = malloc(bucketEntries* sizeof(bucket)); //allocate space for bucket
     if(current->bucketContent == NULL){
         printf("No memory.\n");
         exit(-1);
     }
     for(int i=0;i<bucketEntries;i++) {
         strcpy(current->next->bucketContent[i].userid,"0");
         current->next->bucketContent[i].transactionList =NULL;
     }
     current->next->num = (current->num)+1;     //to find which node of bucket list is from the previous
     strcpy(current->next->bucketContent[0].userid,key);

     current->next->current_entries = 1;        //just inserted an id in the first place of bucket array

}

void printBucket(bucketListNode** node,int i){
    printf("einai : %s tou bucket %d\n",((*node)->bucketContent[i].userid),(*node)->num);
}
void printBucketList(bucketListNode* head,int bucketEntries){
    bucketListNode* temp = head;
    if(temp == NULL){
        printf("List of buckets is empty\n");
        return;
    }
    for(temp = head; temp != NULL; temp = temp->next){
        for(int i=0;i<bucketEntries;i++){
            if(strcmp(temp->bucketContent[i].userid,"0")!=0) {
                printf("mpainei me bucket %d\n",temp->num);
                printf("Einai o %s\t", temp->bucketContent[i].userid);
                printList(temp->bucketContent[i].transactionList);
            }
        }
    }

}

bucketListNode* FindLastNode(bucketListNode** head){
    bucketListNode* temp = *head;
    while (temp->next != NULL) {     //finding last node
        temp = temp->next;
    }
    return temp;
}
void deleteBucketList(bucketListNode** head, int bucketEntries){
    bucketListNode* current = *head;
    bucketListNode* next;
    while (current != NULL) {
        next = current->next;
        for(int i=0;i<bucketEntries;i++) {
            deleteList(&current->bucketContent[i].transactionList);       //delete transacion List of this node
        }
        free(current->bucketContent);
        free(current);
        current = next;
    }
    *head = NULL;
}
void insertInBucket(bucketListNode** node, char* key,int place){ //insert in a place of the bucket array
    strcpy((*node)->bucketContent[place].userid, key);
    (*node)->current_entries ++;
}
int checkSpace(bucketListNode* node, char* key,int bucketEntries){
    if((node)->current_entries < bucketEntries){    //if the bucket's current entries are less than the size of bucket array
        insertInBucket(&node, key, (node)->current_entries);    //insert in current bucket
        return 1;
    }else{
        addBucketNode(&node,key,bucketEntries);     //else create a new bucket and copy the id in the first position of bucket array
        return 2;
    }
}

void hashTableInsert(bucketListNode** hashTable,char *userId,int HashtableNumOfEntries,int bucketEntries){
    int position=hash((unsigned char*)userId)%HashtableNumOfEntries;
    bucketListNode *last = hashTable[position];
//    printf(" to hash key moy einai %d\n",position);
    last = FindLastNode(&last);
    checkSpace(last,userId,bucketEntries);
   // printBucketList(hashTable[position],bucketEntries);
   // free(last);
}
bucketListNode** createHashTable(int hashEntries,int bucketEntries) {
    bucketListNode** array;
    array = malloc(hashEntries * sizeof(bucketListNode));
    if (array == NULL) {
        printf("No memory.\n");
        exit(-1);
    }
    for (int i = 0; i < hashEntries; i++) {
        array[i]=NULL;
        addBucketNode(&array[i],"0",bucketEntries);       //creates the first bucket array for every place of the array hashtable ,
        // and initializes the first place of the bucket array with "0"
    }

    return array;

}

unsigned long hash(unsigned char *str){
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}
void insertInTrasactionList(listNode **head,char* transactionID, char* senderWalletID, char* receiverWalletID, int value, char* date, char* time){
    addNode(head,transactionID,senderWalletID,receiverWalletID,value,date,time);
}

bucketListNode*  findInHashTable(bucketListNode** hashTable,char* userId,int HashtableNumOfEntries){
    int position=hash((unsigned char*)userId)%HashtableNumOfEntries;
    return hashTable[position];
}
bucket* findInBuckets(bucketListNode* buckets,char* userId,int bucketEntries){
    bucketListNode *temp= buckets;
    while(temp!=NULL) {
        for (int i = 0; i < bucketEntries; i++) {
            if (strcmp(temp->bucketContent[i].userid, userId) == 0) {
                return &temp->bucketContent[i];
            }
        }
        temp=temp->next;
    }
//    printf("%s userId is not on this bucket list.\n",userId);
    return NULL;
}