#include "Transaction.h"


void addNode(listNode** head, char* transactionID, char* senderWalletID, char* receiverWalletID, int value, char* date, char* time){
    transaction *t = malloc(sizeof(transaction));       //allocating memory and initializing transactions values
    if(t==NULL){
        printf("No memory.\n");
        exit(-1);
    }

    strcpy(t->transactionID,transactionID);

    strcpy(t->senderWalletID,senderWalletID);

    strcpy(t->receiverWalletID,receiverWalletID);

    t->value = value;

    strcpy(t->date,date);

    strcpy(t->time,time);

    listNode * current = *head;
    if(current == NULL){        //adding at the start of the list
        current=malloc(sizeof(listNode));
        if(current==NULL){
            printf("No memory.\n");
            exit(-1);
        }
        current->next =NULL;
        current->data = *t;
        *head =current;
        free(t);
        return;

    }

    //adding a node at the end of the list

    while (current->next != NULL) {     //finding last node
        current = current->next;
    }
    current->next = malloc(sizeof(listNode)); //allocate space for the new node
    if(current->next==NULL){
        printf("No memory.\n");
        exit(-1);
    }
    current->next->next = NULL;
    current->next->data = *t;
    free(t);
}
void printList(listNode* head){
    listNode* temp = head;
    if(temp == NULL){
        printf("List of transactions is empty\n");
        return;
    }
    for(temp = head; temp!= NULL; temp = temp->next){

        printf("%s %s %s %d %s %s\n", (temp->data).transactionID ,(temp->data).senderWalletID,(temp->data).receiverWalletID,(temp->data).value,(temp->data).date,(temp->data).time);
    }

}
void deleteList(listNode** head){
    listNode* current = *head;
    listNode* next;
    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}
transaction * findTransaction(listNode* head,char* sender,char* receiver,int value,char* date,char* time){
    listNode* temp =head;
    while (temp!=NULL){
        if(strcmp(temp->data.senderWalletID ,sender)==0 && strcmp(temp->data.receiverWalletID ,receiver)==0) {
            if(temp->data.value==value && strcmp(temp->data.date ,date)==0 && strcmp(temp->data.time ,time)==0){
                return &temp->data;
            }
        }
        temp= temp->next;
    }

}