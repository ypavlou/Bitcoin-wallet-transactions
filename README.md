# Bitcoin-wallet-transactions
This is an implementation of a program that can accept, process, record and answer questions about Bitcoin transactions, considering  a set of <b>data structures </b> (hash
tables, linked lists, binanry trees) that allow the entry and queries in a large volume of type records.

 ##  Compilation: 
  ``` Ruby
  make
```
Remove object files: 
 ``` Ruby
  make clean
```
 ##  Run:
  ``` Ruby
./bitcoin -a bitCoinBalancesFile -t transactionsFile -v bitCoinValue -h1 senderHashtableNumOfEntries -h2 receiverHashtableNumOfEntries -b bucketSize

```
- bitCoinValue: value of bitcoin.
- senderHashtable1NumOfEntries: number of entries in senders hash table.
- receiverHashtable1NumOfEntries: number of entries in receiver hash table.
- bucketSize: number of Bytes for each bucket of hash table.
- bitCoinBalancesFile: initial wallet balances of users in bitcoin network, each line must be a list of bitcoin ids. e.g Kylian 456 767 898
- transactionsFile: file with a number of transaction requests to be processed. e.g 889 Maria Kylian 50 25-12-2018 20:08

## Commands for operations
 Request transaction: 
 ``` Ruby
  ./requestTransaction senderWalletID receiverWalletID amount date time
```
or: 
 ``` Ruby
./requestTransactions senderWalletID receiverWalletID amount date time;
senderWalletID2 receiverWalletID2 amount2 date2 time2;
…
senderWalletIDn receiverWalletIDn amountn daten timen;
```
or: 
 ``` Ruby
 ./requestTransactions inputFile
```
 Find earnings of walletID:
 ``` Ruby
  ./findEarnings walletID [time1][year1][time2][year2]
```
Find amount of successful payments of walletID:
 ``` Ruby
  ./findPayments walletID [time1][year1][time2][year2]
```
Find current amount in walletID:
 ``` Ruby
  ./walletStatus walletID
```

Find current status of a bitcoinID(initial value, number of transactions used, balance):
 ``` Ruby
  ./bitCoinStatus bitCoinID
```
Find  trace of a bitcoinID:
 ``` Ruby
  ./traceCoin bitCoinID
```
Exit:
 ``` Ruby
  ./exit

```



