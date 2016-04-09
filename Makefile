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

SQLITE_LD_FLAGS = -lsqlite3

SRC_FILES = $(BASE)/src/IrcConnector.cpp $(BASE)/src/PingResponder.cpp $(BASE)/src/OperationManager.cpp $(BASE)/src/HighlightHandler.cpp $(BASE)/src/CommandHandler.cpp $(BASE)/src/PythonModule.cpp $(BASE)/src/SqlConnector.cpp $(BASE)/src/ConfigurationManager.cpp 

HEADER_FILES = $(BASE)/include/PingResponder.hpp $(BASE)/include/IrcConnectorInterface.hpp $(BASE)/include/IrcConnector.hpp $(BASE)/include/assert.hpp $(BASE)/include/Operation.hpp $(BASE)/include/OperationManager.hpp $(BASE)/include/HighlightHandler.hpp $(BASE)/include/CommandHandler.hpp $(BASE)/include/SqlConnector.hpp $(BASE)/include/ConfigurationManager.hpp 

IRCBOT_LD_FLAGS_NO_PYTHON = -L$(DERIVED) -lPingResponder -lIrcConnector -lOperationManager -lHighlightHandler -lCommandHandler -lSqlConnector -lConfigurationManager -lPythonOperation 
IRCBOT_LD_FLAGS = $(IRCBOT_LD_FLAGS_NO_PYTHON) -lpyircbot

INCLUDES = -I/usr/include -I$(BASE)/include $(PYTHON_INCLUDE_FLAGS) $(BOOST_INCLUDE_FLAGS)
LINKS = $(BOOST_LD_FLAGS) $(PYTHON_LD_FLAGS) $(IRCBOT_LD_FLAGS) -lpthread ${SQLITE_LD_FLAGS}

DEBUGFLAGS = -std=c++11 -g3 -DDEBUG

CXX_FLAGS = -std=c++11 #-O3

DEPEND = $(DERIVED)/depend.mk

all: so $(EXECUTABLE) python_so

debug: CXX_FLAGS = $(DEBUGFLAGS)
debug: all

$(EXECUTABLE): so python_so main.cpp
	$(CXX) $(CXX_FLAGS) -o $(EXECUTABLE) main.cpp $(INCLUDES) $(LINKS)

$(DEPEND): $(SRC_FILES) $(DERIVED)
	$(CXX) $(CXX_FLAGS) $(INCLUDES) -MM $(SRC_FILES)>>$(DEPEND);

python_so: $(DERIVED)/libpyircbot.so so

$(DERIVED)/libpyircbot.so: $(DERIVED)/pyircbot.o so
	$(CXX) $(CXX_FLAGS) -shared -Wl,--export-dynamic -o $@ $(DERIVED)/pyircbot.o $(INCLUDES) $(IRCBOT_LD_FLAGS_NO_PYTHON)
	@ln -f $@ $(DERIVED)/pyircbot.so

$(DERIVED)/pyircbot.o: $(BASE)/src/PythonModule.cpp so
	$(CXX) $(CXX_FLAGS) $(INCLUDES) -fPIC -c $< -o $@

so: $(DEPEND) $(DERIVED) $(DERIVED)/libIrcConnector.so $(DERIVED)/libPingResponder.so $(DERIVED)/libOperationManager.so $(DERIVED)/libHighlightHandler.so $(DERIVED)/libCommandHandler.so $(DERIVED)/libSqlConnector.so $(DERIVED)/libConfigurationManager.so $(DERIVED)/libPythonOperation.so

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

$(DERIVED)/libCommandHandler.so: $(DERIVED)/CommandHandler.o
	$(CXX) $(CXX_FLAGS) -shared -Wl,--export-dynamic $< $(INCLUDES) -o $@

$(DERIVED)/CommandHandler.o: $(BASE)/src/CommandHandler.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDES) -fPIC -c $< -o $@

$(DERIVED)/libPythonOperation.so: $(DERIVED)/PythonOperation.o 
	$(CXX) $(CXX_FLAGS) -shared -Wl,--export-dynamic $< $(INCLUDES) -o $@

$(DERIVED)/PythonOperation.o: $(BASE)/src/PythonOperation.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDES) -fPIC -c $< -o $@

$(DERIVED)/libSqlConnector.so: $(DERIVED)/SqlConnector.o
	$(CXX) $(CXX_FLAGS) -shared -Wl,--export-dynamic $< $(INCLUDES) -o $@

$(DERIVED)/SqlConnector.o: $(BASE)/src/SqlConnector.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDES) -fPIC -c $< -o $@

$(DERIVED)/libConfigurationManager.so: $(DERIVED)/ConfigurationManager.o
	$(CXX) $(CXX_FLAGS) -shared -Wl,--export-dynamic $< $(INCLUDES) -o $@

$(DERIVED)/ConfigurationManager.o: $(BASE)/src/ConfigurationManager.cpp
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

