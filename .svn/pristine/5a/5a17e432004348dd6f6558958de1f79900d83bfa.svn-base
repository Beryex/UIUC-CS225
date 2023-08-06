EXE_DSETS = testdsets
EXE_SQUAREMAZE = testsquaremaze

CPP_FILES_DSET_STUDENT = dsets.cpp
CPP_FILES_DEST_PROVIDED = testdsets.cpp
CPP_FILES_SQUAREMAZE_STUDENT = dsets.cpp
CPP_FILES_SQUAREMAZE_STUDENT += maze.cpp
CPP_FILES_SQUAREMAZE_PROVIDED = testsquaremaze.cpp
CPP_FILES_SQUAREMAZE_PROVIDED += $(wildcard cs225/*.cpp)
CPP_FILES_SQUAREMAZE_PROVIDED += $(wildcard cs225/lodepng/*.cpp)

OBJS += $(CPP_FILES_DSET_STUDENT:.cpp=.o)
OBJS += $(CPP_FILES_DEST_PROVIDED:.cpp=.o)

OBJS_SQUAREMAZE +=$(CPP_FILES_SQUAREMAZE_STUDENT:.cpp=.o)
OBJS_SQUAREMAZE +=$(CPP_FILES_SQUAREMAZE_PROVIDED:.cpp=.o)

CPP_TESTS += $(wildcard dsets.cpp)
CPP_TESTS += $(wildcard maze.cpp)
CPP_TESTS += $(wildcard cs225/*.cpp)
CPP_TESTS += $(wildcard cs225/lodepng/*.cpp)
CPP_TESTS += $(wildcard tests/*.cpp)
OBJS_TEST = $(CPP_TESTS:.cpp=.o)


CXX = g++
LD = g++
WARNINGS = #-Wall -Werror -Wextra -Wno-unused-parameter -Wno-unused-variable #-Wfatal-errors -pedantic
CXXFLAGS = -std=c++11 -g -O3 $(WARNINGS) -MP -MMD -c
LDFLAGS = -std=c++11 -lpthread
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

all: $(EXE_DSETS) $(EXE_SQUAREMAZE)

# MP7.1
$(EXE_DSETS): $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXE_DSETS)
# MP7.2
$(EXE_SQUAREMAZE): $(OBJS_SQUAREMAZE)
	$(LD) $(OBJS_SQUAREMAZE) $(LDFLAGS) -o $(EXE_SQUAREMAZE)
test: $(OBJS_TEST)
	$(LD) $(OBJS_TEST) $(LDFLAGS) -o test

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) $< -o $@

# include auto-generated dependencies
-include *.d
-include tests/*d

clean:
	rm -rf $(EXE_DSETS) $(EXE_SQUAREMAZE) *.exe test *.o *.d tests/*.o tests/*.d cs225/*.d cs225/*.o cs225/lodepng/*.o cs225/lodepng/*.d


.PHONY: clean
