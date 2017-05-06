all: cprinter verque mergestock

cprinter: cprinter.cc
	g++ -std=c++11 -pthread cprinter.cc -o cprinter

verque: verque.cc
	g++ verque.cc -o verque

mergestock: mergestock.cc mergestockclient.cc
	g++ -std=c++11 mergestock.cc -o server
	g++ -std=c++11 mergestockclient.cc -o client

clean:
	rm -f cprinter verque
