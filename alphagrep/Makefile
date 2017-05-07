all: cprinter verque mergestock mergestockclient filesplit

cprinter: cprinter.cc
	g++ -std=c++11 -pthread cprinter.cc -o cprinter

verque: verque.cc
	g++ verque.cc -o verque

mergestock: mergestock.cc
	g++ -std=c++11 mergestock.cc -o mergestock

mergestockclient: mergestockclient.cc
	g++ -std=c++11 mergestockclient.cc -o mergestockclient

filesplit: filesplit.cc
	g++ -g -std=c++11 filesplit.cc -o filesplit

clean:
	rm -f cprinter verque mergestock mergestockclient filesplit
