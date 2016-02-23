# ATTN: ../ is kinda hacky...
BASE = $(shell pwd)/../

CXX = g++

DERIVED = $(BASE)/derived

EXECUTABLE = $(DERIVED)/ircbot

PYTHON_LD_FLAGS = `python-config --ldflags`
PYTHON_INCLUDE_FLAGS = `python-config --includes`

BOOST_INC = /usr/include
BOOST_LIB = /usr/lib/
BOOST_LD_FLAGS = -L$(BOOST_LIB) -lboost_python
BOOST_INCLUDE_FLAGS = -I$(BOOST_INC)

GTEST_LD_FLAGS = -L/opt/gtest/lib -lgtest -lgtest_main -lpthread -lgmock
GTEST_INCLUDE_FLAGS = -I/opt/gtest/include -I/opt/gtest/include

SRC_FILES = $(BASE)/src/IrcConnector.cpp $(BASE)/src/PingResponder.cpp $(BASE)/src/OperationManager.cpp $(BASE)/src/HighlightHandler.cpp $(BASE)/src/PythonModule.cpp
HEADER_FILES = $(BASE)/include/PingResponder.hpp $(BASE)/include/IrcConnector.hpp $(BASE)/include/assert.hpp $(BASE)/include/Operation.hpp $(BASE)/include/OperationManager.hpp $(BASE)/include/HighlightHandler.hpp 

IRCBOT_LD_FLAGS_NO_PYTHON = -L$(DERIVED) -lPingResponder -lIrcConnector -lOperationManager -lHighlightHandler -lPythonOperation 
IRCBOT_LD_FLAGS = $(IRCBOT_LD_FLAGS_NO_PYTHON) -lpyircbot

INCLUDES = -I/usr/include -I$(BASE)/include $(PYTHON_INCLUDE_FLAGS) $(BOOST_INCLUDE_FLAGS) $(GTEST_INCLUDE_FLAGS)
LINKS = $(BOOST_LD_FLAGS) $(PYTHON_LD_FLAGS) $(IRCBOT_LD_FLAGS) -lpthread $(GTEST_LD_FLAGS)

CXX_FLAGS = -std=c++11 -g3 -DDEBUG

OBJECTS = 

simple_test: simple_test.o $(DERIVED)/pyircbot.o $(DERIVED)/pyircbot.o $(DERIVED)/IrcConnector.o $(DERIVED)/PingResponder.o $(DERIVED)/OperationManager.o $(DERIVED)/HighlightHandler.o $(DERIVED)/PythonOperation.o
	$(CXX) $(CXX_FLAGS) -o $@ $< $(INCLUDES) $(LINKS)	
	./$@

simple_test.o: simple_test.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDES) -fPIC -c $< -o $@

clean:
	rm -f  *.o simple_test
