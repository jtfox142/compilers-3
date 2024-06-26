CC = g++

CFLAGS = -Wall -std=c++11

statSem: p3.o scanner.o parser.o tree.o statSem.o symbolTable.o
	$(CC) $(CFLAGS) -o statSem p3.o scanner.o parser.o tree.o statSem.o symbolTable.o

p3.o: p3.cpp parser.cpp parser.hpp scanner.cpp scanner.hpp tree.hpp token.hpp statSem.cpp statSem.hpp
	$(CC) $(CFLAGS) -c p3.cpp

parser.o: parser.cpp parser.hpp tree.cpp tree.hpp node.hpp scanner.cpp scanner.hpp token.hpp
	$(CC) $(CFLAGS) -c parser.cpp

statSem.o: parser.cpp parser.hpp statSem.cpp statSem.hpp symbolTable.cpp symbolTable.hpp token.hpp
	$(CC) $(CFLAGS) -c statSem.cpp

symbolTable.o: symbolTable.cpp symbolTable.hpp token.hpp
	$(CC) $(CFLAGS) -c symbolTable.cpp

tree.o: tree.cpp tree.hpp node.hpp
	$(CC) $(CFLAGS) -c tree.cpp

scanner.o: scanner.cpp scanner.hpp token.hpp
	$(CC) $(CFLAGS) -c scanner.cpp

clean: 
	rm *.o statSem