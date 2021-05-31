#include "Tree.h"
TreeNode* createTree(int num,char* wallet_id){
    TreeNode* t = malloc(sizeof(struct TreeNode));
    if(t==NULL){
        printf("No memory.\n");
        exit(-1);
    }
    strcpy(t->wallet_id,wallet_id);
    t->value = num;
    t->transaction =NULL;
    t->left = NULL;
    t->right = NULL;
    return t;
}

void addSenderReceiver(TreeNode** node,int num,char* sender,char* receiver, transaction* trans){
    if(*node==NULL) return;

    addSenderReceiver(&(*node)->left,num,sender,receiver,trans);
    addSenderReceiver(&(*node)->right,num,sender,receiver,trans);
    //postorder traversal

    if (  strcmp((*node)->wallet_id,sender) == 0 && (*node)->left == NULL&& (*node)->right ==NULL && (*node)->value >=num && found == 0 ){

        (*node)->left =malloc(sizeof(struct TreeNode)); //allocate space for the left-sender node
        if((*node)->left==NULL){
            printf("No memory.\n");
            exit(-1);
        }

        strcpy((*node)->left->wallet_id,receiver);
        (*node)->left->value = num;
        (*node)->left->transaction = trans;
        (*node)->left->left = NULL;
        (*node)->left->right = NULL;

        (*node)->right =malloc(sizeof(struct TreeNode));     //allocate space for the right-receiver node
        if((*node)->right==NULL){
            printf("No memory.\n");
            exit(-1);
        }

        strcpy((*node)->right->wallet_id,sender);
        (*node)->right->value = (*node)->value - num;
        (*node)->right->transaction =NULL;
        (*node)->right->left = NULL;
        (*node)->right->right = NULL;
        found =1;
    }
}

void printTree(TreeNode* node){
    if (node == NULL)
        return;

    // first recur on left subtree
    printTree(node->left);

    // then recur on right subtree
    printTree(node->right);

    // now deal with the node
    printf("This bitCoin has walletID : %s and value %d \n",node->wallet_id ,node->value);

}
void printTreeTransactions(TreeNode* node){
    if (node == NULL)
        return;

    // first recur on left subtree
    printTreeTransactions(node->left);

    // then recur on right subtree
    printTreeTransactions(node->right);

    // now deal with the node
    if(node->transaction!=NULL) {
        printf("%s %s %s  %d %s %s\n", node->transaction->transactionID, node->transaction->senderWalletID,node->transaction->receiverWalletID, node->transaction->value, node->transaction->date,node->transaction->time);
    }
}

void findNum(TreeNode* node,char* walletID){
    if (node == NULL)
        return;

    // first recur on left subtree
    findNum(node->left,walletID);

    // then recur on right subtree
    findNum(node->right,walletID);

    // now deal with the node
    if(strcmp(node->wallet_id,walletID)!=0){
        transNum+=1;
    }
}

void findLeaves(TreeNode* node,char* walletID){
    if(node==NULL){
        return;
    }
    if(node->left==NULL && node->right==NULL){      //find a leaf
        if(strcmp(node->wallet_id,walletID)==0) {           //if the walletid is  the same as root's id
            unspent += node->value;
        }
    }
    if(node->left)
        findLeaves(node->left,walletID);
    if(node->right)
        findLeaves(node->right,walletID);
}

void freeTree(TreeNode* root){
    if(root==NULL)
        return;

    freeTree(root->left);

    freeTree(root->right);

    free(root);            //postorder

}