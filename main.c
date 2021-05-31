#include <stdio.h>
#include <stdlib.h>
#include "Transaction.h"
#include "HashTable.h"
#include "Wallet.h"
#include "Tree.h"
#include "ReadFiles.h"
#include "requestTransactions.h"
#include "FindPayments.h"
#include "FindEarnings.h"
#include "WalletStatus.h"
#include "bitCoinStatus.h"
#include "TraceCoin.h"
#include "CheckTimeDate.h"
#include <time.h>
int transaction_number =1;
int main(int argc,char* argv[]) {

    FILE* bitCoinBalancesFile=NULL;
    char b[256];
    char t[256];
    FILE* transactionsFile=NULL;
    int bitCoinValue = 0,senderHashtableNumOfEntries = 0, receiverHashtableNumOfEntries = 0,bucketSize = 0;
    if(argc > 13){
        printf("Command Execution Failed\n");
        exit(1);
    }
    else if(argc == 13){
        for(int i=1; i< argc; i+=2) {//read input from command line
            if (strcmp(argv[i], "-a") == 0) {
                strcpy(b,argv[i+1]);


            } else if (strcmp(argv[i], "-t") == 0) {
                strcpy(t,argv[i+1]);

            } else if (strcmp(argv[i], "-v") == 0) {
                bitCoinValue = atoi(argv[i+1]);
            } else if (strcmp(argv[i], "-h1") == 0) {
                senderHashtableNumOfEntries = atoi(argv[i+1]);
            } else if (strcmp(argv[i], "-h2") == 0) {
                receiverHashtableNumOfEntries = atoi(argv[i+1]);
            } else if (strcmp(argv[i], "-b") == 0) {
                bucketSize = atoi(argv[i+1]);
            }
        }
    }
    else{
        printf("Command Execution Failed\n");
        exit(-1);
    }


    int HashEntries=10,BucketEntries=4;

    bitCoinBalancesFile = fopen(b, "r");        //open bitcoin balances file
    if (bitCoinBalancesFile == NULL) {
        exit(EXIT_FAILURE);
    }
    ListNodeT* treeList = NULL; //list of bitcoin trees
    bucketList ** WalletHashTable;
    WalletHashTable =  create_HashTable(HashEntries,BucketEntries);

    ReadBitCoinsFile(bitCoinBalancesFile,&treeList,bitCoinValue,WalletHashTable,HashEntries,BucketEntries);
    fclose(bitCoinBalancesFile);



    transactionsFile = fopen(t, "r");
    if (transactionsFile == NULL) {
        exit(EXIT_FAILURE);
    }

    int bucketEntries = (bucketSize -(sizeof(int) + sizeof(int) + sizeof(bucketList*)) )/ sizeof(Bucket);     //calculate the number of entries for the bucket arrays
    bucketListNode** senderHashtable=NULL; //receiver hash table
    senderHashtable = createHashTable(senderHashtableNumOfEntries,bucketEntries);

    bucketListNode** receiverHashtable; //sender hash table
    receiverHashtable = createHashTable(receiverHashtableNumOfEntries,bucketEntries);

    ReadTransactionsFile(transactionsFile,senderHashtable,receiverHashtable,senderHashtableNumOfEntries,receiverHashtableNumOfEntries,bucketEntries,WalletHashTable,BucketEntries,HashEntries,treeList);
    fclose(transactionsFile);

    char* option=NULL;
    option = malloc(256*sizeof(char));
    printf("\nEnter an Option\n");
    scanf("%[^\n]%*c",option);
    while(strcmp(option,"exit")){
        char* temp=strdup(option);
        char* op=strtok(temp," ");

        if(!strcmp(op,"walletStatus")){
            op=strtok(NULL," \n\t");
            char* walletID = strdup(op);
            walletStatus(walletID,WalletHashTable,HashEntries,BucketEntries);
            free(walletID);

        }
        else if(!strcmp(op,"bitCoinStatus")){
            op=strtok(NULL," \n\t");
            char* bitCoinID=strdup(op);
            bitCoinStatus(bitCoinID,treeList );
            free(bitCoinID);
        }
        else if(!strcmp(op,"traceCoin")){
            op=strtok(NULL," \n\t");
            char* bitCoinID=strdup(op);
            traceCoin(bitCoinID,treeList);
            free(bitCoinID);
        }
        else if(!strcmp(op,"findPayments")) {
            size_t length = strlen(option);
            int characters[256] = {0};
            int found_time = 0,found_date=0;
            for (int i = 0; i < length; i++) {
                characters[(int) (option[i])]++;
            }
            for(int i=0;i<256;i++){//check all characters
                if(i == ':')
                    found_time = i;     //find the place o each one
                if(i == '-')
                    found_date = i;
            }
            int flag =0;
            if ( characters[found_time] == 1 || characters[found_date] == 2 ) {   // check if their number is correct
                printf("Invalid syntax please retry\n");
                flag = 1;
            }


            if (flag != 1){
                if (characters[found_date]==4 && characters[found_time] ==2 ) { //both time kai date
                    op = strtok(NULL, " \n\t");
                    char *WalletID = strdup(op);

                    op = strtok(NULL, " \n\t");
                    char *time1 = strdup(op);
                    op = strtok(NULL, " \n\t");
                    char *date1 = strdup(op);

                    op = strtok(NULL, " \n\t");
                    char *time2 = strdup(op);
                    op = strtok(NULL, " \n\t");
                    char *date2 = strdup(op);

                    findPaymentsDateTime(senderHashtable, WalletID, senderHashtableNumOfEntries, bucketEntries, time1,
                                         time2, date1, date2);
                    free(WalletID);
                    free(time1);
                    free(time2);
                    free(date1);
                    free(date2);

                }
                else if (characters[found_time] == 2) { //only time
                    op = strtok(NULL, " \n\t");
                    char *WalletID = strdup(op);
                    op = strtok(NULL, " \n\t");
                    char *time1 = strdup(op);
                    op = strtok(NULL, " \n\t");
                    char *time2 = strdup(op);
                    findPaymentsTime(senderHashtable,WalletID,senderHashtableNumOfEntries,bucketEntries,time1,time2);
                    free(WalletID);
                    free(time1);
                    free(time2);

                }
                else if (characters[found_date]==4) { //only date
                    op = strtok(NULL, " \n\t");
                    char *WalletID = strdup(op);
                    op = strtok(NULL, " \n\t");
                    char *date1 = strdup(op);
                    op = strtok(NULL, " \n\t");
                    char *date2 = strdup(op);
                    findPaymentsDate(senderHashtable,WalletID,senderHashtableNumOfEntries,bucketEntries,date1,date2);
                    free(WalletID);
                    free(date1);
                    free(date2);
                }else{
                    op = strtok(NULL, " \n\t"); //only walletID
                    char *WalletID = strdup(op);
                    findPayments(senderHashtable,WalletID,senderHashtableNumOfEntries,bucketEntries);
                    free(WalletID);
                }
            }
        }
        else if(!strcmp(op,"findEarnings")) {
            size_t length = strlen(option);
            int characters[256] = {0};
            int found_time = 0,found_date=0;
            for (int i = 0; i < length; i++) {
                characters[(int) (option[i])]++;
            }
            for(int i=0;i<256;i++){//check all characters
                if(i == ':')
                    found_time = i;     //find the place o each one
                if(i == '-')
                    found_date = i;
            }
            int flag =0;
            if ( characters[found_time] == 1 || characters[found_date] == 2 ) {   // check if their number is correct
                printf("Invalid syntax please retry\n");
                flag = 1;
            }


            if (flag != 1){
                if (characters[found_date]==4 && characters[found_time] ==2 ) { //both time kai date
                    op = strtok(NULL, " \n\t");
                    char *WalletID = strdup(op);

                    op = strtok(NULL, " \n\t");
                    char *time1 = strdup(op);
                    op = strtok(NULL, " \n\t");
                    char *date1 = strdup(op);

                    op = strtok(NULL, " \n\t");
                    char *time2 = strdup(op);
                    op = strtok(NULL, " \n\t");
                    char *date2 = strdup(op);

                    findEarningsDateTime(receiverHashtable,WalletID,receiverHashtableNumOfEntries,bucketEntries,time1,time2,date1,date2);
                    free(WalletID);
                    free(time1);
                    free(time2);
                    free(date1);
                    free(date2);

                }
                else if (characters[found_time] == 2) { //only time
                    op = strtok(NULL, " \n\t");
                    char *WalletID = strdup(op);
                    op = strtok(NULL, " \n\t");
                    char *time1 = strdup(op);
                    op = strtok(NULL, " \n\t");
                    char *time2 = strdup(op);
                    findEarningsTime(receiverHashtable,WalletID,receiverHashtableNumOfEntries,bucketEntries,time1,time2);
                    free(WalletID);
                    free(time1);
                    free(time2);

                }
                else if (characters[found_date]==4) { //only date
                    op = strtok(NULL, " \n\t");
                    char *WalletID = strdup(op);
                    op = strtok(NULL, " \n\t");
                    char *date1 = strdup(op);
                    op = strtok(NULL, " \n\t");
                    char *date2 = strdup(op);
                    findEarningsDate(receiverHashtable,WalletID,receiverHashtableNumOfEntries,bucketEntries,date1,date2);
                    free(WalletID);
                    free(date1);
                    free(date2);
                }else{
                    op = strtok(NULL, " \n\t"); //only walletID
                    char *WalletID = strdup(op);
                    findEarnings(receiverHashtable,WalletID,receiverHashtableNumOfEntries,bucketEntries);
                    free(WalletID);
                }
            }
        }
        else if(!strcmp(op,"requestTransaction")) {

            size_t length = strlen(option);
            int characters[256] = {0};
            int found_time = 0;
            for (int i = 0; i < length; i++) {
                characters[(int) (option[i])]++;
            }
            for(int i=0;i<256;i++){//check all characters
                if(i == ':')
                    found_time = i;     //find the place of ':'

            }

            op = strtok(NULL, " \n\t");
            char *senderWalletID = strdup(op);
            op = strtok(NULL, " \n\t");
            char *receiverWalletID = strdup(op);
            op = strtok(NULL, " \n\t");
            char *value = strdup(op);
            if(characters[found_time] > 0){    //if there is no : found in line there are no time and date given
                op = strtok(NULL, " \n\t");
                char *date;
                char* time1;
                date = strdup(op);
                op = strtok(NULL, " \n\t");
                time1 = strdup(op);
                strcpy(last_transaction.date,"00-00-00");
                strcpy(last_transaction.time,"00:00");
                lastTransaction transaction1;
                strcpy(transaction1.date,last_transaction.date);
                strcpy(transaction1.time,last_transaction.time);
                if(checkTimeTransaction(time1,date)== true){
                    char trans[50];
                    sprintf(trans,"%d",transaction_number);
                    transaction_number++;
                    requestTransaction(trans, senderWalletID, receiverWalletID, value, date, time1, senderHashtable,receiverHashtable, senderHashtableNumOfEntries,receiverHashtableNumOfEntries, bucketEntries, WalletHashTable,BucketEntries,HashEntries, treeList);
                }
                free(date);
                free(time1);
            }else{
                time_t T =time(NULL);
                struct tm tm = *localtime(&T);
                char date[50],time1[20];
                strftime(date,sizeof(date),"%d-%m-%y",&tm);
                strftime(time1,sizeof(time1),"%H:%M",&tm);

                strcpy(last_transaction.date,"00-00-00");
                strcpy(last_transaction.time,"00:00");
                lastTransaction transaction1;
                strcpy(transaction1.date,last_transaction.date);
                strcpy(transaction1.time,last_transaction.time);
                if(checkTimeTransaction(time1,date)== true){
                    char trans[50];
                    sprintf(trans,"%d",transaction_number);
                    transaction_number++;
                    requestTransaction(trans, senderWalletID, receiverWalletID, value, date, time1, senderHashtable,receiverHashtable, senderHashtableNumOfEntries,receiverHashtableNumOfEntries, bucketEntries, WalletHashTable,BucketEntries,HashEntries, treeList);
                }

            }
            free(senderWalletID);
            free(receiverWalletID);
            free(value);

        }
        else if(!strcmp(op,"requestTransactions")) {
            if(strchr(option,';')!=NULL){
                int found =0;
                while(strchr(option,';')!=NULL){
                    char *senderWalletID;
                    char *receiverWalletID;
                    char *value;
                    size_t length = strlen(option);
                    int characters[256] = {0};
                    int found_time = 0;
                    for (int i = 0; i < length; i++) {
                        characters[(int) (option[i])]++;
                    }
                    for(int i=0;i<256;i++){//check all characters
                        if(i == ':')
                            found_time = i;     //find the place of ':'

                    }

                    if(found==0){
                        found=1;
                        op = strtok(NULL, " \n\t");
                        senderWalletID = strdup(op);
                        op = strtok(NULL, " \n\t");
                        receiverWalletID = strdup(op);
                        op = strtok(NULL, " \n\t");
                        value = strdup(op); //requestTransactions johnsmith imwatchingyou 10 21-02-2019 11:35;
                    }else{
                        op = strtok(option, " ");
                        printf("%s \n",op);
                        senderWalletID = strdup(op);
                        op = strtok(NULL, " \n\t");
                        receiverWalletID = strdup(op);
                        op = strtok(NULL, "; \n\t");
                        value = strdup(op);
                    }


                    if(characters[found_time] > 0){    //if there is no : found in line there are no time and date given
                        op = strtok(NULL, " \n\t");
                        char *date;
                        char* time1;
                        date = strdup(op);
                        op = strtok(NULL, "; \n\t");
                        time1 = strdup(op);
                        strcpy(last_transaction.date,"00-00-00");
                        strcpy(last_transaction.time,"00:00");
                        lastTransaction transaction1;
                        strcpy(transaction1.date,last_transaction.date);
                        strcpy(transaction1.time,last_transaction.time);
                        if(checkTimeTransaction(time1,date)== true){
                            char trans[50];
                            sprintf(trans,"%d",transaction_number);
                            transaction_number++;
                            requestTransaction(trans, senderWalletID, receiverWalletID, value, date, time1, senderHashtable,receiverHashtable, senderHashtableNumOfEntries,receiverHashtableNumOfEntries, bucketEntries, WalletHashTable,BucketEntries,HashEntries, treeList);
                        }
                        free(date);
                        free(time1);
                    }else{
                        time_t T =time(NULL);
                        struct tm tm = *localtime(&T);
                        char date[50],time1[20];
                        strftime(date,sizeof(date),"%d-%m-%y",&tm);
                        strftime(time1,sizeof(time1),"%H:%M",&tm);

                        strcpy(last_transaction.date,"00-00-00");
                        strcpy(last_transaction.time,"00:00");
                        lastTransaction transaction1;
                        strcpy(transaction1.date,last_transaction.date);
                        strcpy(transaction1.time,last_transaction.time);
                        if(checkTimeTransaction(time1,date)== true){
                            char trans[50];
                            sprintf(trans,"%d",transaction_number);
                            transaction_number++;
                            requestTransaction(trans, senderWalletID, receiverWalletID, value, date, time1, senderHashtable,receiverHashtable, senderHashtableNumOfEntries,receiverHashtableNumOfEntries, bucketEntries, WalletHashTable,BucketEntries,HashEntries, treeList);
                        }

                    }
                    free(senderWalletID);
                    free(receiverWalletID);
                    free(value);
                    printf("Give another transaction or type 'e'\n");
                    scanf("%[^\n]%*c",option);
                }
            }else{ //it is an inputfile
                FILE * fp;
                char * line = NULL;
                size_t len = 0;
                ssize_t read;
                char* token=NULL;
                op = strtok(NULL, " \n\t");
                fp = fopen(op, "r");
                if(fp==NULL){
                    printf("Error opening file\n");
                    exit(-1);
                }



                while ((read = getline(&line, &len, fp)) != -1) {
                    char* transactionID;
                    char *senderWalletID;
                    char *receiverWalletID;
                    char *value;
                    size_t length = strlen(line);
                    int characters[256] = {0};
                    int found_time = 0;
                    for (int i = 0; i < length; i++) {
                        characters[(int) (line[i])]++;
                    }
                    for(int i=0;i<256;i++){//check all characters
                        if(i == ':')
                            found_time = i;     //find the place of ':'

                    }
                    op = strtok(line, " \n\t");
                    senderWalletID = strdup(op);
                    op = strtok(NULL, " \n\t");
                    receiverWalletID = strdup(op);
                    op = strtok(NULL, " \n\t");
                    value = strdup(op);

                    if(characters[found_time] > 0){    //if there is no : found in line there are no time and date given
                        op = strtok(NULL, " \n\t");
                        char *date;
                        char* time1;
                        date = strdup(op);
                        op = strtok(NULL, "; \n\t");
                        time1 = strdup(op);
                        strcpy(last_transaction.date,"00-00-00");
                        strcpy(last_transaction.time,"00:00");
                        lastTransaction transaction1;
                        strcpy(transaction1.date,last_transaction.date);
                        strcpy(transaction1.time,last_transaction.time);
                        if(checkTimeTransaction(time1,date)== true){
                            char trans[50];
                            sprintf(trans,"%d",transaction_number);
                            transaction_number++;
                            requestTransaction(trans, senderWalletID, receiverWalletID, value, date, time1, senderHashtable,receiverHashtable, senderHashtableNumOfEntries,receiverHashtableNumOfEntries, bucketEntries, WalletHashTable,BucketEntries,HashEntries, treeList);
                        }
                        free(date);
                        free(time1);
                    }else{
                        time_t T =time(NULL);
                        struct tm tm = *localtime(&T);
                        char date[50],time1[20];
                        strftime(date,sizeof(date),"%d-%m-%y",&tm);
                        strftime(time1,sizeof(time1),"%H:%M",&tm);

                        strcpy(last_transaction.date,"00-00-00");
                        strcpy(last_transaction.time,"00:00");
                        lastTransaction transaction1;
                        strcpy(transaction1.date,last_transaction.date);
                        strcpy(transaction1.time,last_transaction.time);
                        if(checkTimeTransaction(time1,date)== true){
                            char trans[50];
                            sprintf(trans,"%d",transaction_number);
                            transaction_number++;
                            requestTransaction(trans, senderWalletID, receiverWalletID, value, date, time1, senderHashtable,receiverHashtable, senderHashtableNumOfEntries,receiverHashtableNumOfEntries, bucketEntries, WalletHashTable,BucketEntries,HashEntries, treeList);
                        }

                    }
                    free(senderWalletID);
                    free(receiverWalletID);
                    free(value);


                }

                free(token);


                if (line)
                    free(line);
            }
        }


        free(temp);
        scanf("%[^\n]%*c",option);
    }
    free(option);
    //delete everything
    for(int j=0;j < senderHashtableNumOfEntries;j++){ //delete senderHashtable
        deleteBucketList(&senderHashtable[j],bucketEntries);
    }
    free(senderHashtable);
    for(int j=0;j < receiverHashtableNumOfEntries;j++){ //delete receiverHashTable
        deleteBucketList(&receiverHashtable[j],bucketEntries);
    }
    free(receiverHashtable);

    for(int j=0;j < HashEntries;j++){ //delete walletsHashTable
        deleteBuckets(&WalletHashTable[j]);
    }
    free(WalletHashTable);

    freeListofTrees(&treeList);

    return 0;
}
