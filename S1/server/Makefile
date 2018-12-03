# Makefile for the socket programming tutorial 
#

CXX=g++
CXXFLAGS= -std=c++0x -g -fprofile-arcs -ftest-coverage

SRC_DIR = src

SRC_INCLUDE = include
INCLUDE = -I ${SRC_INCLUDE}

SERVER_TEST = Server

.PHONY: all
all : $(SERVER_TEST)

# default rule for compiling .cc to .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

$(SERVER_TEST): $(SRC_DIR) $(SRC_DIR)
	$(CXX) $(CXXFLAGS) -o $(SERVER_TEST) $(INCLUDE) \
	$(SRC_DIR)/*.cpp

test: $(SERVER_TEST)
	$(SERVER_TEST)

clean:
	rm Server -rf *~ $(SRC)/*.o $(TEST_SRC)/*.o *.gcov *.gcda *.gcno \ #rm -f *.o simple_server simple_client
