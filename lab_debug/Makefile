EXENAME = sketchify

MAIN_FILE = main.cpp

# Flags:
CXXFLAGS = -std=c++1y -c -g -O0 -Wall -Wextra -pedantic -ffloat-store
LDFLAGS = -std=c++1y -lpthread -lm
CXX = g++
LD = g++

# Discover files in dir...
CPP_FILES += $(wildcard *.cpp) 
CPP_FILES += $(wildcard cs225/*.cpp)
CPP_FILES += $(wildcard cs225/lodepng/*.cpp)

OBJ_FILES += $(CPP_FILES:.cpp=.o)


# Discover files for testing...
TEST_CPP += $(filter-out $(MAIN_FILE),$(CPP_FILES))
TEST_CPP += $(wildcard tests/*.cpp)

TEST_OBJ = $(TEST_CPP:.cpp=.o)


# Rules
all: $(EXENAME)

$(EXENAME): $(OBJ_FILES)
	$(LD) $(OBJ_FILES) $(LDFLAGS) -o $(EXENAME)

test: $(TEST_OBJ)
	$(LD) $(TEST_OBJ) $(LDFLAGS) -o test

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) $< -o $@

clean :
	-rm -f *.o $(EXENAME) test tests/*.o cs225/*.o cs225/lodepng/*.o



