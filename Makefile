OBJS=llist.o main.o

llist: $(OBJS)
		g++ -std=c++11 -g -fno-elide-constructors -o $@ $^

.cpp.o:
		g++ -std=c++11 -I. -g -fno-elide-constructors -c -o $@ $<
clean:
		rm -f *.o llist

