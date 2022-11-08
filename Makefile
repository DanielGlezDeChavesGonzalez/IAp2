CXX = g++
CXXFLAGS = -std=c++17 -g 
LDFLAGS = 

SRC = main.cpp grid.cpp nodo.cpp
OBJ = $(SRC:.cc=.o)
EXEC = main

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(OBJ) $(LBLIBS)

clean:
	rm -rf *.o $(EXEC)