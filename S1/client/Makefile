# Makefile for the socket programming tutorial 
#

CXX=g++
CXXFLAGS= -std=c++0x -g -fprofile-arcs -ftest-coverage

SRC_DIR = src

SRC_INCLUDE = include
INCLUDE = -I ${SRC_INCLUDE}

CLIENT_TEST = Client

all : $(CLIENT_TEST)

$(CLIENT_TEST): $(SRC_DIR)
	$(CXX) $(CXXFLAGS) -o $(CLIENT_TEST) $(INCLUDE) \
	$(SRC_DIR)/*.cpp
clean:
	rm Client -rf *~ $(SRC)/*.o $(TEST_SRC)/*.o *.gcov *.gcda *.gcno \ #rm -f *.o simple_server simple_client
