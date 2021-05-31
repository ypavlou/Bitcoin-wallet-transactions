#ifndef SYSPRO_1_TREE_H
#define SYSPRO_1_TREE_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Transaction.h"
typedef struct  TreeNode{
    int value;
    char wallet_id[50];
    transaction* transaction;       //a pointer to a transaction of the current bitCoin
    struct  TreeNode *left;
    struct  TreeNode *right;
}TreeNode;
TreeNode* createTree(int,char*);
int found ;
void addSenderReceiver(TreeNode** ,int, char* ,char*,transaction*);
void printTree(TreeNode*);
int transNum;
void findNum(TreeNode* ,char*);
int unspent;
void findLeaves(TreeNode*,char*);
void printTreeTransactions(TreeNode* );
void freeTree(TreeNode*);
#endif //SYSPRO_1_TREE_H
