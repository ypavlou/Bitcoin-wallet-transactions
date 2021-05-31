
#include "FindEarnings.h"

void findEarnings( bucketListNode** receiverHashtable,char* walletID,int receiverNumOfEntries,int bucketEntries){
    bucket* found =findInBuckets(findInHashTable(receiverHashtable, walletID, receiverNumOfEntries),walletID, bucketEntries);
    if(found ==NULL ){
        printf("User %s not register cannot display payments.\n",walletID);
        exit(1);
    }
    if(found->transactionList==NULL){
        printf("User %s has no successful payments\n",walletID);
        return;
    }
    int total = 0;
    listNode* temp = found->transactionList;
    while (temp!=NULL){
        total+=temp->data.value;
        temp= temp->next;
    }
    printf("User's %s successful earnings are:\n",walletID);
    printList(found->transactionList);
    printf("User's %s total earnings are:%d\n\n",walletID,total);
    printf("\n");
}
void findEarningsTime(bucketListNode** receiverHashtable,char* walletID,int receiverNumOfEntries,int bucketEntries,char* t1,char* t2){
    char delim[] = ":";
    int h1,m1,h2,m2; //hour minute for t1,t2

    char time1[50];
    char time2[50];

    strcpy(time1,t1);
    strcpy(time2,t2);

    char *ptr = strtok(time1, delim);
    h1= (int) strtol(ptr, (char **)NULL, 10);
    ptr = strtok(NULL, delim);
    m1 = (int) strtol(ptr, (char **)NULL, 10);// split t1 to : and store it in as 2 ints for hour and minute


    ptr = strtok(time2, delim);
    h2= (int) strtol(ptr, (char **)NULL, 10);
    ptr = strtok(NULL, delim);
    m2 = (int) strtol(ptr, (char **)NULL, 10); // split t1 to : and store it in as 2 ints for hour and minute

    bucket* found =findInBuckets(findInHashTable(receiverHashtable, walletID, receiverNumOfEntries),walletID, bucketEntries);  //find the walletID in hastable
    if(found ==NULL ){
        printf("User %s not register cannot display payments.\n",walletID);
        exit(1);
    }
    if(found->transactionList==NULL){
        printf("User %s has no successful payments\n",walletID);
        return;
    }

    int total = 0;
    int h3,m3;
    printf("User's %s successful earnings are:\n",walletID);
    listNode* temp = found->transactionList;
    char tempTime[50];
    strcpy(tempTime,temp->data.time);//so we don't split with strtok the data of the structure

    while (temp!=NULL){ //parse transaction list
        strcpy(tempTime,temp->data.time);//so we don't split with strtok the data of the structure

        ptr = strtok(tempTime, delim);           //split time to : and store it in as 2 ints for hour and minute
        h3 = (int) strtol(ptr, (char **)NULL, 10);
        ptr = strtok(NULL, delim);
        m3 = (int) strtol(ptr, (char **)NULL, 10);
        if(h3>=h1 && h3<=h2){
            if(m3>=m1 && m3<=m2){
                printf("%s %s %s %d %s %s\n", (temp->data).transactionID ,(temp->data).senderWalletID,(temp->data).receiverWalletID,(temp->data).value,(temp->data).date,(temp->data).time);
                total+=temp->data.value;
            }
        }

        temp= temp->next;
    }
    printf("User's %s total earnings are:%d\n\n",walletID,total);

    // free(ptr);


}


void findEarningsDate(bucketListNode** receiverHashtable,char* walletID,int receiverNumOfEntries,int bucketEntries,char* date1,char* date2){
    char delim[] = "-";
    int d1,m1,y1,d2,m2,y2; //day month year for date1,date2

    char temp_date1[50];
    char temp_date2[50];

    strcpy(temp_date1,date1);
    strcpy(temp_date2,date2);

    char *ptr = strtok(temp_date1, delim);
    d1= (int) strtol(ptr, (char **)NULL, 10);
    ptr = strtok(NULL, delim);
    m1 = (int) strtol(ptr, (char **)NULL, 10);// split date1 to - and store it in as 3 ints
    ptr = strtok(NULL, delim);
    y1 = (int) strtol(ptr, (char **)NULL, 10);



    ptr = strtok(temp_date2, delim);
    d2= (int) strtol(ptr, (char **)NULL, 10);
    ptr = strtok(NULL, delim);
    m2 = (int) strtol(ptr, (char **)NULL, 10);// split date2 to - and store it in as 3 ints
    ptr = strtok(NULL, delim);
    y2 = (int) strtol(ptr, (char **)NULL, 10);

    bucket* found =findInBuckets(findInHashTable(receiverHashtable, walletID, receiverNumOfEntries),walletID, bucketEntries);  //find the walletID in hastable
    if(found ==NULL ){
        printf("User %s not register cannot display payments.\n",walletID);
        exit(1);
    }
    if(found->transactionList==NULL){
        printf("User %s has no successful payments\n",walletID);
        return;
    }

    int total = 0;
    int d3,m3,y3;

    printf("User's %s successful earnings are:\n",walletID);
    listNode* temp = found->transactionList;
    char tempDate[50];
    strcpy(tempDate,temp->data.date); //so we don't split with strtok the data of the structure

    while (temp!=NULL){ //parse transaction list
        strcpy(tempDate,temp->data.date); //so we don't split with strtok the data of the structure

        ptr = strtok(tempDate, delim);           //split time to : and store it in as 2 ints for hour and minute
        d3 = (int) strtol(ptr, (char **)NULL, 10);
        ptr = strtok(NULL, delim);
        m3 = (int) strtol(ptr, (char **)NULL, 10);
        ptr = strtok(NULL, delim);
        y3 = (int) strtol(ptr, (char **)NULL, 10);
        if(y3>=y1 && y3<=y2){
            if(m3>=m1 && m3<=m2){
                if(d3>=d1 && d3<=d2) {
                    printf("%s %s %s %d %s %s\n", (temp->data).transactionID, (temp->data).senderWalletID,(temp->data).receiverWalletID, (temp->data).value, (temp->data).date, (temp->data).time);
                    total += temp->data.value;
                }
            }
        }

        temp= temp->next;
    }
    printf("User's %s total earnings are:%d\n\n",walletID,total);
}
void findEarningsDateTime(bucketListNode** receiverHashtable,char* walletID,int receiverNumOfEntries,int bucketEntries,char* t1,char *t2,char* date1,char* date2){
    char delim[] = ":";
    int h1,mo1,h2,mo2; //hour minute for t1,t2

    char time1[50];
    char time2[50];

    strcpy(time1,t1);
    strcpy(time2,t2);

    char temp_date1[50];
    char temp_date2[50];

    strcpy(temp_date1,date1);
    strcpy(temp_date2,date2);


    char *ptr = strtok(time1, delim);
    h1= (int) strtol(ptr, (char **)NULL, 10);
    ptr = strtok(NULL, delim);
    mo1 = (int) strtol(ptr, (char **)NULL, 10);// split t1 to : and store it in as 2 ints for hour and minute


    ptr = strtok(time2, delim);
    h2= (int) strtol(ptr, (char **)NULL, 10);
    ptr = strtok(NULL, delim);
    mo2 = (int) strtol(ptr, (char **)NULL, 10); // split t1 to : and store it in as 2 ints for hour and minute
    char delim2[] ="-";

    int d1,m1,y1,d2,m2,y2; //day month year for date1,date2

    ptr = strtok(temp_date1, delim2);
    d1= (int) strtol(ptr, (char **)NULL, 10);
    ptr = strtok(NULL, delim2);
    m1 = (int) strtol(ptr, (char **)NULL, 10);// split date1 to - and store it in as 3 ints
    ptr = strtok(NULL, delim2);
    y1 = (int) strtol(ptr, (char **)NULL, 10);



    ptr = strtok(temp_date2, delim2);
    d2= (int) strtol(ptr, (char **)NULL, 10);
    ptr = strtok(NULL, delim2);
    m2 = (int) strtol(ptr, (char **)NULL, 10);// split date2 to - and store it in as 3 ints
    ptr = strtok(NULL, delim2);
    y2 = (int) strtol(ptr, (char **)NULL, 10);



    bucket* found =findInBuckets(findInHashTable(receiverHashtable, walletID, receiverNumOfEntries),walletID, bucketEntries);  //find the walletID in hastable
    if(found ==NULL ){
        printf("User %s not register cannot display payments.\n",walletID);
        exit(1);
    }
    if(found->transactionList==NULL){
        printf("User %s has no successful payments\n",walletID);
        return;
    }
    int total = 0;
    int h3,mo3;
    int d3,m3,y3;
    printf("User's %s successful earnings are:\n",walletID);
    listNode* temp = found->transactionList;
    char tempTime[50];
    char tempDate[50];
    strcpy(tempTime,temp->data.time);
    strcpy(tempDate,temp->data.date); //so we don't split with strtok the data of the structure
    while (temp!=NULL){ //parse transaction list
        strcpy(tempTime,temp->data.time);
        strcpy(tempDate,temp->data.date);

        ptr = strtok(tempTime, delim);           //split time to : and store it in as 2 ints for hour and minute
        h3 = (int) strtol(ptr, (char **)NULL, 10);
        ptr = strtok(NULL, delim);
        mo3 = (int) strtol(ptr, (char **)NULL, 10);

        ptr = strtok(tempDate, delim2);
        d3 = (int) strtol(ptr, (char **)NULL, 10);
        ptr = strtok(NULL, delim2);
        m3 = (int) strtol(ptr, (char **)NULL, 10);
        ptr = strtok(NULL, delim2);
        y3 = (int) strtol(ptr, (char **)NULL, 10);
        if(h3>=h1 && h3<=h2 && mo3>=mo1 && mo3<=mo2) {
            if (y3 >= y1 && y3 <= y2) {
                if (m3 >= m1 && m3 <= m2) {
                    if (d3 >= d1 && d3 <= d2) {
                        printf("%s %s %s %d %s %s\n", (temp->data).transactionID, (temp->data).senderWalletID,(temp->data).receiverWalletID, (temp->data).value, (temp->data).date, (temp->data).time);
                        total += temp->data.value;
                    }
                }
            }
        }

        temp= temp->next;
    }
    printf("User's %s total payments are:%d\n\n",walletID,total);
}
