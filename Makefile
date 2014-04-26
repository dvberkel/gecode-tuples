binaries: tuple

tuple: tuple.o
	g++ -o tuple -L/usr/local/lib/  tuple.o -lgecodekernel -lgecodesearch -lgecodeint

tuple.o:
	g++ -I/usr/local/include/ -c tuple.cpp

clean:
	rm -rf tuple.o tuple