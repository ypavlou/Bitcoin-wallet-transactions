#include "CheckTimeDate.h"
bool checkTimeTransaction(char* time2,char* date2){ //1 for last transaction 2 for current
    int h1,min1,h2,min2; //hour minute for t1,t2
    int d1,m1,y1,d2,m2,y2; //day month year for date1,date2
    char date1[50];
    char time1[50];
    char temp_date2[50];
    char temp_time2[50];

    strcpy(date1,last_transaction.date);
    strcpy(time1,last_transaction.time);

    strcpy(temp_date2,date2);
    strcpy(temp_time2,time2);


    char delim[] = ":";

    char *ptr = strtok(time1, delim);
    h1= (int) strtol(ptr, (char **)NULL, 10);
    ptr = strtok(NULL, delim);
    min1 = (int) strtol(ptr, (char **)NULL, 10);// split t1 to : and store it in as 2 ints for hour and minute


    ptr = strtok(temp_time2, delim);
    h2= (int) strtol(ptr, (char **)NULL, 10);
    ptr = strtok(NULL, delim);
    min2 = (int) strtol(ptr, (char **)NULL, 10); // split t1 to : and store it in as 2 ints for hour and minute

    char delim2[] ="-";

    ptr = strtok(date1, delim2);
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

    if(y2 > y1) {
        strcpy(last_transaction.date,date2);
        strcpy(last_transaction.time,time2);
        return true;

    }else if(y2 == y1) {
        if (m2 > m1) {
            strcpy(last_transaction.date,date2);
            strcpy(last_transaction.time,time2);
            return true;

        } else if (m2 == m1) {
            if (d2 > d1) {
                strcpy(last_transaction.date,date2);
                strcpy(last_transaction.time,time2);
                return true;

            } else if(d2 == d1){
                if(h2 > h1){
                    strcpy(last_transaction.date,date2);
                    strcpy(last_transaction.time,time2);
                    return true;

                } else if(h2 == h1){
                    if(min2 > min1) {
                        strcpy(last_transaction.date,date2);
                        strcpy(last_transaction.time,time2);
                        return true;
                    }
                }
            }
        }
    }
    return false;

}