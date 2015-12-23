base = $(shell pwd)

derived = $(base)/derived

executable = $(derived)/ircbot

includes = -I/usr/include -I$(base)/include

links = -L$(derived) -lpthread

src_files = $(base)/src/IrcConnector.cpp main.cpp $(base)/src/PingResponder.cpp $(base)/src/OperationManager.cpp $(base)/src/HighlightHandler.cpp
include_files = $(base)/include/PingResponder.hpp $(base)/include/IrcConnector.hpp $(base)/include/assert.hpp $(base)/include/Operation.hpp $(base)/include/OperationManager.hpp $(base)/include/HighlightHandler.hpp

debugFlags = -g -DDEBUG
ndebugFlags = -O3 -DNDEBUG

CXX_FLAGS = -std=c++11 $(debugFlags) 

all: main.cpp $(src_files) $(include_files) setup
	@echo make all
	$(CXX) $(CXX_FLAGS) -o $(executable) $(src_files) $(includes) $(links)

.PHONY: setup
setup:
	mkdir -p derived

.PHONY: clean
clean:
	@rm -r $(derived)
	@rm $(executable)

.PHONY: run
run: all
	$(executable)
