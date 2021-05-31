#
# In order to execute this "Makefile" just type "make"
#

OBJS    = bitCoinStatus.o CheckTimeDate.o main.o FindEarnings.o FindPayments.o HashTable.o ListofTrees.o ReadFiles.o  requestTransactions.o TraceCoin.o Transaction.o Tree.o Wallet.o WalletStatus.o
SOURCE  = bitCoinStatus.c CheckTimeDate.c main.c FindEarnings.c FindPayments.c HashTable.c ListofTrees.c ReadFiles.c  requestTransactions.c TraceCoin.c Transaction.c Tree.c Wallet.c WalletStatus.c
HEADER  = bitCoinStatus.h CheckTimeDate.h FindEarnings.h FindPayments.h HashTable.h ListofTrees.h ReadFiles.h  requestTransactions.h TraceCoin.h Transaction.h Tree.h Wallet.h WalletStatus.h
OUT     = bitcoin

CC      = gcc
FLAGS   = -g -c 
# -g option enables debugging mode
# -c flag generates object code for separate files

all: 	$(OBJS)
		$(CC) -g $(OBJS) -o $(OUT)

# create/compile the individual files >>separately<<
bitCoinStatus.o: bitCoinStatus.c
	$(CC) $(FLAGS) bitCoinStatus.c

CheckTimeDate.o: CheckTimeDate.c
	$(CC) $(FLAGS) CheckTimeDate.c

main.o: main.c
	$(CC) $(FLAGS) main.c

FindEarnings.o: FindEarnings.c
	$(CC) $(FLAGS) FindEarnings.c

FindPayments.o: FindPayments.c
	$(CC) $(FLAGS) FindPayments.c

HashTable.o: HashTable.c
	$(CC) $(FLAGS) HashTable.c

ListofTrees.o: ListofTrees.c
	$(CC) $(FLAGS) ListofTrees.c

ReadFiles.o: ReadFiles.c
	$(CC) $(FLAGS) ReadFiles.c

requestTransactions.o: requestTransactions.c
	$(CC) $(FLAGS) requestTransactions.c

TraceCoin.o: TraceCoin.c
	$(CC) $(FLAGS) TraceCoin.c

Transaction.o: Transaction.c
	$(CC) $(FLAGS) Transaction.c

Tree.o: Tree.c
	$(CC) $(FLAGS) Tree.c

Wallet.o: Wallet.c
	$(CC) $(FLAGS) Wallet.c

WalletStatus.o: WalletStatus.c
	$(CC) $(FLAGS) WalletStatus.c

# clean house
clean:
	rm -f $(OBJS) $(OUT)

# do a bit of accounting
count:
	wc $(SOURCE) $(HEADER)
