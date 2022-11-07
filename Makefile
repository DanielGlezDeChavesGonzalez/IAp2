CXX = g++
CXXFLAGS = -Wall -Werror -Wextra -pedantic -std=c++17 -g 
LDFLAGS =  

SRC = main.cpp grid.cpp
OBJ = $(SRC:.cc=.o)
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf *.o $(EXEC)