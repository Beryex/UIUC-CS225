CXX = g++
LD = g++

WARNINGS = -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable
CXXFLAGS = -std=c++1y -g -O0 $(WARNINGS) -MMD -MP -c

LDFLAGS = -std=c++1y  -lpthread
ASANFLAGS = -fsanitize=address -fno-omit-frame-pointer

OBJS_DIR = .objs

TEST_OBJS = hashes.o textfile.o
OBJS_TEST = tests/basic.o hashes.o textfile.o

all: hash

hash: main.o  
	$(LD) $(LDFLAGS) $^ -o ./q10


# Pattern rules for object files
$(OBJS_DIR)/%-asan.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $(ASANFLAGS) $< -o $@
$(OBJS_DIR)/%.o: %.cpp | $(OBJS_DIR)
	$(CXX) $(CXXFLAGS) $< -o $@


# Create directories
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)


# Executable dependencies
hash: $(patsubst %.o, $(OBJS_DIR)/%.o, $(TEST_OBJS))
test: $(patsubst %.o, $(OBJS_DIR)/%.o, $(TEST_OBJS))
# Include automatically generated dependencies
-include $(OBJS_DIR)/*.d
-include tests/*.d

test: $(OBJS_TEST)
	$(LD) $(OBJS_TEST) $(LDFLAGS) -o test

doc: $(wildcard *.h) $(wildcard *.cpp)
	-doxygen lab_hash.doxygen

clean:
	-rm -rf doc *.o  *.d  test hash q10 .objs */*.o */*.d

.PHONY: all doc clean tidy nonasan asan data
