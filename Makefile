all:
	g++ -I. -I/cygdrive/d/HTNHUNG/BTL/systemc/include -L. -L/cygdrive/d/HTNHUNG/BTL/systemc/lib-cygwin -o main main.cpp -lsystemc -lm
	./main.exe
clean:
	rm -f main.exe
	rm -f trace.vcd