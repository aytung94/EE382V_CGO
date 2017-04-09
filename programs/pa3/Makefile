CXXFLAGS = $(shell llvm-config --cxxflags) -fno-rtti
CXX = clang++

all: live.so

live.o: live.cpp live.h LivenessFrame.cpp LivenessFrame.h DataFlowFrame.h Makefile
	$(CXX) $(CXXFLAGS) live.cpp LivenessFrame.cpp -c 
live.so: live.o
	$(CXX) -shared $^ -o $@
clean:
	rm -f *.o *.so
