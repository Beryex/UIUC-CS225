EXE = lab_gdb2

OBJS_DIR = .objs

MAIN_OBJ = main.o

CPP_FILES += skipNode.cpp skipList_given.cpp skipList.cpp
CPP_FILES += $(wildcard cs225/*.cpp)
CPP_FILES += $(wildcard cs225/lodepng/*.cpp)
OBJS += $(CPP_FILES:.cpp=.o)

CPP_TESTS += $(filter-out main.cpp, $(CPP_FILES))
CPP_TESTS += $(wildcard tests/*.cpp)
OBJS_TEST = $(CPP_TESTS:.cpp=.o)

CXX = g++
LD = g++
WARNINGS = -pedantic -Wall  -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS = -std=c++1y  -g -O0 $(WARNINGS) -c
LDFLAGS = -std=c++1y -lpthread
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

EXAMPLEFLAGS = $(WARNINGS) -std=c++1y -g -O0




all: $(EXE) $(EXE)-asan examples

examples: list playground recurse swap switch loop

################# EXAMPLES

loop: gdb-examples/loop.cpp
	$(CXX) $(EXAMPLEFLAGS) $(LDFLAGS) gdb-examples/loop.cpp -o loop

list: gdb-examples/list.cpp
	$(CXX) $(EXAMPLEFLAGS) $(LDFLAGS) gdb-examples/list.cpp -o list

playground: gdb-examples/playground.cpp
	$(CXX) $(EXAMPLEFLAGS) $(LDFLAGS) gdb-examples/playground.cpp -o playground
	
recurse: gdb-examples/recurse.cpp
	$(CXX) $(EXAMPLEFLAGS) $(LDFLAGS) gdb-examples/recurse.cpp -o recurse

swap: gdb-examples/swap.cpp
	$(CXX) $(EXAMPLEFLAGS) $(LDFLAGS) gdb-examples/swap.cpp -o swap

switch: gdb-examples/switch.cpp
	$(CXX) $(EXAMPLEFLAGS) $(LDFLAGS) gdb-examples/switch.cpp -o switch

################# LAB CODE

$(EXE): $(OBJS) $(MAIN_OBJ)
	$(LD) $(OBJS) $(MAIN_OBJ) $(LDFLAGS) -o $(EXE)

$(EXE)-asan: $(OBJS) $(MAIN_OBJ) 
	$(LD) $(OBJS:.o=.o-asan.o) $(MAIN_OBJ)-asan.o $(ASANFLAGS) $(LDFLAGS) -o $(EXE)-asan

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) $< -o $@
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $(<:.o=.o-asan.o) -o $@-asan.o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $(<:.o=.o-asan.o) -o $@-asan.o

################# TEST CODE
test: $(OBJS_TEST)
	$(LD) $(OBJS_TEST) $(LDFLAGS) -o test


clean:
	rm -rf $(EXE) $(EXE)-asan *.o tests/*.o cs225/*.o cs225/lodepng/*.o *.d list swap switch recurse list playground loop test

tidy: clean
	rm -rf out-degenerate.png out-structure.png

