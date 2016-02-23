BASE = $(shell pwd)

CXX = g++

DERIVED = $(BASE)/derived

EXECUTABLE = $(DERIVED)/ircbot

PYTHON_LD_FLAGS = `python-config --ldflags`
PYTHON_INCLUDE_FLAGS = `python-config --includes`

BOOST_INC = /usr/include
BOOST_LIB = /usr/lib/
BOOST_LD_FLAGS = -L$(BOOST_LIB) -lboost_python
BOOST_INCLUDE_FLAGS = -I$(BOOST_INC)

SRC_FILES = $(BASE)/src/IrcConnector.cpp $(BASE)/src/PingResponder.cpp $(BASE)/src/OperationManager.cpp $(BASE)/src/HighlightHandler.cpp $(BASE)/src/PythonModule.cpp

HEADER_FILES = $(BASE)/include/PingResponder.hpp $(BASE)/include/IrcConnector.hpp $(BASE)/include/assert.hpp $(BASE)/include/Operation.hpp $(BASE)/include/OperationManager.hpp $(BASE)/include/HighlightHandler.hpp 

IRCBOT_LD_FLAGS = -lPingResponder -lIrcConnector -lOperationManager -lHighlightHandler -lPythonOperation -lpyircbot

INCLUDES = -I/usr/include -I$(BASE)/include $(PYTHON_INCLUDE_FLAGS) $(BOOST_INCLUDE_FLAGS)
LINKS = $(BOOST_LD_FLAGS) $(PYTHON_LD_FLAGS) -L$(DERIVED) $(IRCBOT_LD_FLAGS) -lpthread 

DEBUGFLAGS = -g -DDEBUG
NDEBUGFLAGS = -O3 -DNDEBUG

CXX_FLAGS = -std=c++11 $(DEBUGFLAGS) 

DEPEND = $(DERIVED)/depend.mk

all: so $(EXECUTABLE)

$(EXECUTABLE): so python_so main.cpp
	$(CXX) $(CXX_FLAGS) -o $(EXECUTABLE) main.cpp $(INCLUDES) $(LINKS)

$(DEPEND): $(SRC_FILES) # ATTN: doesn't properly depend on $(DERIVED)
	$(CXX) $(CXX_FLAGS) $(INCLUDES) -MM $<>>$(DEPEND);

python_so: $(DERIVED)/libpyircbot.so so

$(DERIVED)/libpyircbot.so: $(DERIVED)/pyircbot.o
	$(CXX) $(CXX_FLAGS) -shared -Wl,--export-dynamic $< $(INCLUDES) -o $@ 
	@ln -f $@ $(DERIVED)/pyircbot.so

$(DERIVED)/pyircbot.o: $(BASE)/src/PythonModule.cpp 
	$(CXX) $(CXX_FLAGS) $(INCLUDES) -fPIC -c $< -o $@

so: $(DEPEND) $(DERIVED) $(DERIVED)/libIrcConnector.so $(DERIVED)/libPingResponder.so $(DERIVED)/libOperationManager.so $(DERIVED)/libHighlightHandler.so $(DERIVED)/libPythonOperation.so

$(DERIVED)/libIrcConnector.so: $(DERIVED)/IrcConnector.o
	$(CXX) $(CXX_FLAGS) -shared -Wl,--export-dynamic $< $(INCLUDES) -o $@

$(DERIVED)/IrcConnector.o: $(BASE)/src/IrcConnector.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDES) -fPIC -c $< -o $@

$(DERIVED)/libPingResponder.so: $(DERIVED)/PingResponder.o
	$(CXX) $(CXX_FLAGS) -shared -Wl,--export-dynamic $< $(INCLUDES) -o $@

$(DERIVED)/PingResponder.o: $(BASE)/src/PingResponder.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDES) -fPIC -c $< -o $@

$(DERIVED)/libOperationManager.so: $(DERIVED)/OperationManager.o
	$(CXX) $(CXX_FLAGS) -shared -Wl,--export-dynamic $< $(INCLUDES) -o $@

$(DERIVED)/OperationManager.o: $(BASE)/src/OperationManager.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDES) -fPIC -c $< -o $@

$(DERIVED)/libHighlightHandler.so: $(DERIVED)/HighlightHandler.o
	$(CXX) $(CXX_FLAGS) -shared -Wl,--export-dynamic $< $(INCLUDES) -o $@

$(DERIVED)/HighlightHandler.o: $(BASE)/src/HighlightHandler.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDES) -fPIC -c $< -o $@

$(DERIVED)/libPythonOperation.so: $(DERIVED)/PythonOperation.o 
	$(CXX) $(CXX_FLAGS) -shared -Wl,--export-dynamic $< $(INCLUDES) -o $@

$(DERIVED)/PythonOperation.o: $(BASE)/src/PythonOperation.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDES) -fPIC -c $< -o $@


### misc and testing

misc: misc/make_db.cpp setup
	@echo make misc
	$(CXX) $(CXX_FLAGS) -o $(DERIVED)/misc misc/make_db.cpp  $(LINKS) #$(SRC_FILES) $(INCLUDES)

.PHONY: $(DERIVED)
$(DERIVED): 
	@mkdir -p derived
	@touch $(DERIVED)/__init__.py

.PHONY: clean
clean:
	@rm -rf $(DERIVED)

.PHONY: run
run: all
	$(EXECUTABLE)

