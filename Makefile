CXX = g++                     
CXXFLAGS = -Wall -std=c++17    
LDFLAGS =                      

SRC = batputer.cpp                 
OBJ = $(SRC:.cpp=.o)           
EXEC = batputer            

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $(EXEC) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

rebuild: clean all
