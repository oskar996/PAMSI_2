CC = g++

graf: graf.o grafL.o grafM.o kolejka.o kolejkaL.o
	$(CC) -o graf graf.o grafL.o grafM.o kolejka.o kolejkaL.o

graf.o: grafL.hpp grafM.hpp 
	$(CC) -c -o graf.o graf.cpp

grafL.o: kolejkaL.hpp lista.hpp
	$(CC) -c -o grafL.o grafL.cpp

grafM.o: kolejka.hpp lista.hpp
	$(CC) -c -o grafM.o grafM.cpp

kolejka.o:
	$(CC) -c -o kolejka.o kolejka.cpp 

kolejkaL.o:
	$(CC) -c -o kolejkaL.o kolejkaL.cpp 

clean:
	del -f *.o graf.exe