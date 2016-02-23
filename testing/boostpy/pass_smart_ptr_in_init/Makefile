base = $(shell pwd)

DERIVED = $(base)/derived

CXX_FLAGS = -g -std=c++11

PYTHON_LD_FLAGS = `python-config --ldflags`
PYTHON_INCLUDE_FLAGS = `python-config --includes`

BOOST_INC = /usr/include
BOOST_LIB = /usr/lib/
BOOST_LD_FLAGS = -L$(BOOST_LIB) -lboost_python
BOOST_INCLUDE_FLAGS = -I$(BOOST_INC)

HELLO_IMPLEMENTATION_O = $(DERIVED)/hello.o
HELLO_MODULE_O = $(DERIVED)/hello_module.o
HELLO_SO = $(DERIVED)/libHello.so
HELLO_PYD = $(DERIVED)/hello.so

HELLO_LD_FLAGS = -L$(DERIVED) -lHello

ALL_INCLUDE_FLAGS = $(BOOST_INCLUDE_FLAGS) $(PYTHON_INCLUDE_FLAGS)
ALL_LD_FLAGS = $(PYTHON_LD_FLAGS) $(BOOST_LD_FLAGS) $(HELLO_LD_FLAGS)


main: $(HELLO_SO) setup main.cpp
	g++ $(CXX_FLAGS) -o $(DERIVED)/test main.cpp $(ALL_INCLUDE_FLAGS) $(ALL_LD_FLAGS) 

$(HELLO_SO): $(HELLO_MODULE_O) $(HELLO_IMPLEMENTATION_O) setup
	g++ $(CXX_FLAGS) -shared -Wl,--export-dynamic $(HELLO_MODULE_O) $(HELLO_IMPLEMENTATION_O) $(ALL_INCLUDE_FLAGS) -o $(HELLO_SO)
	@ln -f $(HELLO_SO) $(HELLO_PYD)

$(HELLO_MODULE_O): hello_module.cpp hello.hpp setup 
	g++ $(CXX_FLAGS) $(ALL_INCLUDE_FLAGS) -fPIC -c hello_module.cpp -o $(HELLO_MODULE_O)

$(HELLO_IMPLEMENTATION_O): hello.cpp hello.hpp setup 
	g++ $(CXX_FLAGS) $(ALL_INCLUDE_FLAGS) -fPIC -c hello.cpp -o $(HELLO_IMPLEMENTATION_O)

.PHONY: setup
setup:
	mkdir -p $(DERIVED)
	touch $(DERIVED)/__init__.py

.PHONY: clean
clean:
	@rm -rf $(DERIVED)

.PHONY: pytest
pytest: $(HELLO_SO)
	@echo ""
	@python test.py

.PHONY: test
test: main
	@echo ""
	@./derived/test
