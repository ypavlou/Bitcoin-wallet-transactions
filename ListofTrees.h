
#ifndef SYSPRO_1_LISTOFTREES_H
#define SYSPRO_1_LISTOFTREES_H

#include "Tree.h"
typedef struct ListNodeT{
    TreeNode* Tree;
    char bitCoinid[50];
    struct ListNodeT* next;
}ListNodeT;
void addNodeT(ListNodeT**  ,int ,char*,char*);
void printListT(ListNodeT* );
ListNodeT* findInTreeList(ListNodeT*,char*);
ListNodeT* findInTreeListB(ListNodeT* ,char* );
void freeListofTrees(ListNodeT** );
#endif //SYSPRO_1_LISTOFTREES_H
