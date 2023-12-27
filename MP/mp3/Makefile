EXE = mp3

OBJS_DIR = .objs

CPP_FILES += main.cpp
CPP_FILES += $(wildcard cs225/*.cpp)
CPP_FILES += $(wildcard cs225/lodepng/*.cpp)
OBJS += $(CPP_FILES:.cpp=.o)

CPP_TESTS += $(filter-out main.cpp, $(CPP_FILES))
CPP_TESTS += $(wildcard tests/*.cpp)
OBJS_TEST = $(CPP_TESTS:.cpp=.o)

CXX = g++
LD = g++
WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS = -std=c++11 -g -O0 $(WARNINGS) -c # -ffloat-store
LDFLAGS = -std=c++11 -lpthread
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

$(EXE): $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXE)

$(EXE)-asan: $(OBJS)
	$(LD) $(OBJS:.o=.o-asan.o) $(MAIN_OBJ)-asan.o $(ASANFLAGS) $(LDFLAGS) -o $(EXE)-asan

test: $(OBJS_TEST)
	$(LD) $(OBJS_TEST) $(LDFLAGS) -o test

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) $< -o $@
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $(<:.o=.o-asan.o) -o $@-asan.o

all: $(EXE) test

clean:
	rm -rf $(EXE) $(EXE)-asan test *.o tests/*.o cs225/*.o cs225/lodepng/*.o

.PHONY: all $(EXE) test clean
