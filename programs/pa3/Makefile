CXXFLAGS = $(shell llvm-config --cxxflags) -fno-rtti
CXX = clang++

all: live.so reach.so



LivenessFrame.o: LivenessFrame.cpp LivenessFrame.h DataFlowFrame.h Makefile
	$(CXX) $(CXXFLAGS) LivenessFrame.cpp -c -o $@   
live.o: live.cpp live.h Makefile
	$(CXX) $(CXXFLAGS) live.cpp -c -o $@ 
live.so: live.o LivenessFrame.o
	$(CXX) -shared $^ -o $@
    
ReachingDefinitionsFrame.o: ReachingDefinitionsFrame.cpp ReachingDefinitionsFrame.h DataFlowFrame.h Makefile
	$(CXX) $(CXXFLAGS) ReachingDefinitionsFrame.cpp -c -o $@    
reach.o: reach.cpp reach.h Makefile
	$(CXX) $(CXXFLAGS) reach.cpp -c -o $@    
reach.so: reach.o ReachingDefinitionsFrame.o
	$(CXX) -shared $^ -o $@    
    
clean:
	rm -f *.o *.so
