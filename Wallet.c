#include "Wallet.h"
void addBucket(bucketList** head, char* key,int balance,int bucketEntries){
    bucketList* current = *head;
    if(current==NULL){  //create the first node
        current = malloc(sizeof(bucketList));
        if (current == NULL) {
            exit(-1);
        }
        current->next = NULL;      //initialize as NULL the next node

        for(int i=0;i<bucketEntries;i++) {
            strcpy(current->bucketContent[i].userid, "0");
            current->bucketContent[i].balance = 0;
            current->bucketContent[i].BitCoinList = NULL;
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
    current->next = malloc(sizeof(bucketList)); //allocate space for the new node
    if(current->next==NULL){
        printf("No memory.\n");
        exit(-1);
    }
    current->next->next = NULL;    //initialize as NULL the next node
    for(int i=0;i<bucketEntries;i++) {
        strcpy(current->next->bucketContent[i].userid,"0");
        current->next->bucketContent[i].balance =0;
        current->next->bucketContent[i].BitCoinList =NULL;
    }
    current->next->num = (current->num)+1;     //to find which node of bucket list is from the previous
    current->next->bucketContent[0].balance =0;
    strcpy(current->next->bucketContent[0].userid,key);
    current->next->current_entries = 1;        //just inserted an id in the first place of bucket array

}

void printaBucket(bucketList** node,int i){
    printf("einai : %s tou bucket %d\n",((*node)->bucketContent[i].userid),(*node)->num);
}
void printBuckets(bucketList* head,int bucketEntries){
    bucketList* temp = head;
    if(temp == NULL){
        printf("List of buckets is empty\n");
        return;
    }
    for(temp = head; temp != NULL; temp = temp->next){

        for(int i=0;i<bucketEntries;i++) {
            if(strcmp(temp->bucketContent[i].userid,"0")!=0) {
                printf("Einai o %s me balance %d\n", temp->bucketContent[i].userid,temp->bucketContent[i].balance);
                printBitCoinList(temp->bucketContent[i].BitCoinList);
            }
        }
    }
}
bucketList* FindLast(bucketList** head){
    bucketList* temp = *head;
    while (temp->next != NULL) {     //finding last node
        temp = temp->next;
    }
    return temp;
}
void deleteBuckets(bucketList** head){
    bucketList* current = *head;
    bucketList* next;
    while (current != NULL) {
        next = current->next;
        for(int i=0;i<4;i++){
            deleteListWallet(&current->bucketContent[i].BitCoinList);
        }
        free(current);
        current = next;
    }
    *head = NULL;
}
void insertInBuckets(bucketList** node ,char* key,int balance,int place){ //insert in a place of the bucket array
    strcpy((*node)->bucketContent[place].userid, key);
    (*node)->current_entries ++;
}
void  increaseBalance(Bucket* b,int value){
    b->balance+=value;
}
int checkS(bucketList* node, char* key,int balance,int bucketEntries){
    if((node)->current_entries < bucketEntries){    //if the bucket's current entries are less than the size of bucket array
        insertInBuckets(&node, key,balance, (node)->current_entries);    //insert in current bucket
        return 1;
    }else{
        addBucket(&node,key,balance,bucketEntries);     //else create a new bucket and copy the id in the first position of bucket array
        return 2;
    }
}

void hashTable_Insert(bucketList** hashTable,char* userId,int balance,int HashtableNumOfEntries,int bucketEntries){
    int position=hashfunction((unsigned char*)userId)%HashtableNumOfEntries;
    bucketList *last = hashTable[position];
    last = FindLast(&last);
    checkS(last,userId,balance,bucketEntries);
}
bucketList** create_HashTable(int hashEntries,int bucketEntries) {
    bucketList** array;
    array = malloc(hashEntries * sizeof(bucketList));
    if (array == NULL) {
        printf("No memory.\n");
        exit(-1);
    }
    for (int i = 0; i < hashEntries; i++) {
        array[i]=NULL;
        addBucket(&array[i],"0",0,bucketEntries);       //creates the first bucket array for every place of the array hashtable ,
        // and initializes the first place of the bucket array with "0"
    }

    return array;

}

unsigned long hashfunction(unsigned char *str){
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}
void add_ListNode(Node **head,char* key, int val){
    Node * current = *head;
    if(current == NULL){        //adding at the start of the list
        current=malloc(sizeof(Node));
        if(current==NULL){
            printf("No memory.\n");
            exit(-1);
        }

        strcpy(current->bitCoinId,key);
        current->next =NULL;
        current->value= val;
        *head =current;
        return;

    }

    //adding a node at the end of the list

    while (current->next != NULL) {     //finding last node
        current = current->next;
    }
    current->next = malloc(sizeof(Node)); //allocate space for the new node
    if(current->next==NULL){
        printf("No memory.\n");
        exit(-1);
    }
    strcpy(current->next->bitCoinId,key);
    current->next->value=val;
    current->next->next = NULL;

}
void printBitCoinList(Node* head){
    Node* temp = head;
    if(temp == NULL){
        printf("List of bitCoins is empty\n");
        return;
    }
    for(temp = head; temp!= NULL; temp = temp->next){

        printf("%s %d\n",temp->bitCoinId,temp->value);
    }

}
void insertInBitCoinList(Node **head, char*key, int val){
        add_ListNode(head,key,val);
}

bucketList*  findIn_HashTable(bucketList** hashTable,char* userId,int HashtableNumOfEntries){
    int position=hashfunction((unsigned char*)userId)%HashtableNumOfEntries;
    return hashTable[position];
}
Bucket* findIn_Buckets(bucketList* buckets,char* userId,int bucketEntries){
    bucketList *temp= buckets;
    while(temp!=NULL) {
        for (int i = 0; i < bucketEntries; i++) {
            if (strcmp(temp->bucketContent[i].userid, userId) == 0) {
                return &temp->bucketContent[i];
            }
        }
        temp=temp->next;
    }
    printf("%s userId is not on this bucket list.\n",userId);
    return NULL;
}
bool findBitCoinList(Node* head,char* bitCoinId){
    Node* temp = head;
    if(temp == NULL){
        return false;
    }
    for(temp = head; temp!= NULL; temp = temp->next){

       if(strcmp(temp->bitCoinId,bitCoinId) == 0){
           return true;
       }
    }
    return false;
}
bool findBitCoin(bucketList** hashTable,char* bitCoinId,int HashtableNumOfEntries,int bucketEntries){

    bucketList* temp = hashTable[0];
    if(temp == NULL){
        //printf("List of buckets is empty\n");
        return false;
    }
    for(int position=0; position<HashtableNumOfEntries; position++){
        for (temp = hashTable[position]; temp != NULL; temp = temp->next) {

            for (int i = 0; i < bucketEntries; i++) {
                if (findBitCoinList(temp->bucketContent[i].BitCoinList, bitCoinId) == true) {
                    return true;
                }
            }
        }
    }
    return false;

}
Node* findBitCoinV(Node* list,int value){
    Node* temp=list;
    while(temp!=NULL){
        if(temp->value>=value){
            return temp;
        }
        temp=temp->next;
    }
    return NULL;
}
void deleteListWallet(Node** head){
    Node* current = *head;
    Node* next;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}