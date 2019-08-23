#all: test.cpp i s att o ll
all: test.cpp
	$(COMPILER) -std=c++11 -g -o test test.cpp $(LEVEL)
	time ./test

LEVEL=-O0
COMPILER= clang++

i:test.cpp
	 $(COMPILER) -E test.cpp -o test.i $(LEVEL)

ll:test.cpp
	 $(COMPILER) -S -emit-llvm test.cpp $(LEVEL)

s:test.cpp
	 $(COMPILER) -S -mllvm --x86-asm-syntax=intel test.cpp $(LEVEL)

att:test.cpp
	 $(COMPILER) -S test.cpp -o test_att.s $(LEVEL)

o:test.cpp
	 $(COMPILER) -c test.cpp -o test.o $(LEVEL)

clean:
	rm -f peda* .gdb*