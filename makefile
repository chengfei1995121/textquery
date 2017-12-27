query:textquery.o Query_base.h test.o
	g++ -o query textquery.o Query_base.h test.o -std=c++11
textquery.o:textquery.cc textquery.h
	g++ -c textquery.cc textquery.h -std=c++11
test.o:test.cpp 
	g++ -c test.cpp -std=c++11
clean:
	rm -rf *.o
