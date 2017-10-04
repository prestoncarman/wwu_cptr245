OBJS = lab1.o

default: $(OBJS)
	g++ -std=c++11 -o lab1 $(OBJS)

test: 
	./lab1

