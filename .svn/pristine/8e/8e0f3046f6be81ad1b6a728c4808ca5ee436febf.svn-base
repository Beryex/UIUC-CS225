EXENAME = poly
OBJS = polynomial.o cubic.o main.o

CXX = g++
CXXFLAGS = -std=c++1y -c -g -O0 -Wall -Wextra -pedantic
LD = g++
LDFLAGS = -std=c++1y  -lpng -lpthread -lm

all : $(EXENAME)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

polynomial.o : polynomial.cpp polynomial.h 
	$(CXX) $(CXXFLAGS) polynomial.cpp 

cubic.o : polynomial.cpp polynomial.h cubic.cpp cubic.h 
	$(CXX) $(CXXFLAGS) cubic.cpp
	
main.o : main.cpp polynomial.cpp polynomial.h cubic.cpp cubic.h
	$(CXX) $(CXXFLAGS) main.cpp

clean :
	-rm -f *.o $(EXENAME)
