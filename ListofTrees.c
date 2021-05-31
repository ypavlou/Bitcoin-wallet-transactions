#include "ListofTrees.h"
void addNodeT(ListNodeT** head ,int num,char* wallet_id, char* bitCoinid){

    ListNodeT * current = *head;
    if(current == NULL){        //adding at the start of the list
        current=malloc(sizeof(ListNodeT));
        if(current==NULL){
            printf("No memory.\n");
            exit(-1);
        }
        current->next =NULL;
        current->Tree = createTree(num,wallet_id);
        strcpy(current->bitCoinid,bitCoinid);
        *head =current;
        return;

    }

    //adding a node at the end of the list

    while (current->next != NULL) {     //finding last node
        current = current->next;
    }
    current->next = malloc(sizeof(ListNodeT)); //allocate space for the new node
    if(current->next==NULL){
        printf("No memory.\n");
        exit(-1);
    }
    current->next->next = NULL;
    current->next->Tree = createTree(num,wallet_id);
    strcpy(current->next->bitCoinid,bitCoinid);
}

void printListT(ListNodeT* head){
    ListNodeT* temp = head;
    if(temp == NULL){
        printf("List of bitcoin trees is empty\n");
        return;
    }
    for(temp = head; temp!= NULL; temp = temp->next){

        printf("To bitCoinId: %s kai ta exei o %s\n",temp->bitCoinid,temp->Tree->wallet_id);

       printTree(temp->Tree);
    }
}
ListNodeT* findInTreeList(ListNodeT* head,char* walletId){
    ListNodeT* temp = head;
    if(temp == NULL){
        printf("List of bitcoin trees is empty\n");
        return NULL;
    }
    while (temp!=NULL){
        if(strcmp(temp->Tree->wallet_id,walletId)==0){
            return temp;
        }
        temp=temp->next;
    }
    return NULL;
}

ListNodeT* findInTreeListB(ListNodeT* head,char* bitCoinID){
    ListNodeT* temp = head;
    if(temp == NULL){
        printf("List of bitcoin trees is empty\n");
        return NULL;
    }
    while (temp!=NULL){
        if(strcmp(temp->bitCoinid,bitCoinID)==0){
            return temp;
        }
        temp=temp->next;
    }
    printf("BitCoin %s is not in list\n",bitCoinID);
    return NULL;
}
void freeListofTrees(ListNodeT** head){
    ListNodeT* current = *head;
    ListNodeT* next;
    while (current != NULL)
    {
        next = current->next;
        freeTree(current->Tree);
        free(current);
        current = next;
    }
    *head = NULL;
}