base = $(shell pwd)

DERIVED = $(base)/derived

CXX_FLAGS = -g -std=c++11

PYTHON_LD_FLAGS = `python-config --ldflags`
PYTHON_INCLUDE_FLAGS = `python-config --includes`

# location of the Boost Python include files and library
BOOST_INC = /usr/include
BOOST_LIB = /usr/lib/

# compile mesh classes
TARGET = hello

DERIVED_OBJECT = $(DERIVED)/$(TARGET).o
DERIVED_MODULE = $(DERIVED)/$(TARGET).so

$(DERIVED_MODULE): $(DERIVED_OBJECT) setup
	g++ $(CXX_FLAGS) -shared -Wl,--export-dynamic $(DERIVED_OBJECT) -L$(BOOST_LIB) -lboost_python $(PYTHON_FLAGS) -L$(DERIVED) -o $(DERIVED_MODULE)

$(DERIVED_OBJECT): $(TARGET).cpp setup
	g++ $(CXX_FLAGS) $(PYTHON_INCLUDE_FLAGS) -I$(BOOST_INC) -fPIC -c $(TARGET).cpp -o $(DERIVED_OBJECT)

.PHONY: setup
setup:
	mkdir -p $(DERIVED)
	touch $(DERIVED)/__init__.py

.PHONY: clean
clean:
	@rm -r $(DERIVED)

.PHONY: test
test: $(DERIVED_MODULE)
	@echo ""
	@python test.py
