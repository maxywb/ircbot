base = $(shell pwd)

DERIVED = $(base)/derived

CXX_FLAGS = -g -std=c++11

PYTHON_LD_FLAGS = `python-config --ldflags`
PYTHON_INCLUDE_FLAGS = `python-config --includes`

# location of the Boost Python include files and library
BOOST_INC = /usr/include
BOOST_LIB = /usr/lib/
BOOST_LD_FLAGS = -L$(BOOST_LIB) -lboost_python
BOOST_INCLUDE_FLAGS = -I$(BOOST_INC)

TARGET = hello

DERIVED_OBJECT = $(DERIVED)/$(TARGET).o
DERIVED_MODULE = $(DERIVED)/$(TARGET).so

ALL_INCLUDE_FLAGS = $(BOOST_INCLUDE_FLAGS) $(PYTHON_INCLUDE_FLAGS)
ALL_LD_FLAGS = $(PYTHON_LD_FLAGS) $(BOOST_LD_FLAGS) -L$(DERIVED)


main: $(DERIVED_MODULE) setup main.cpp
	g++ $(CXX_FLAGS) -o test main.cpp $(ALL_INCLUDE_FLAGS) $(ALL_LD_FLAGS) 

$(DERIVED_MODULE): $(DERIVED_OBJECT) setup
	g++ $(CXX_FLAGS) -shared -Wl,--export-dynamic $(DERIVED_OBJECT) $(ALL_INCLUDE_FLAGS) -o $(DERIVED_MODULE)

$(DERIVED_OBJECT): $(TARGET).cpp setup
	g++ $(CXX_FLAGS) $(ALL_INCLUDE_FLAGS) -fPIC -c $(TARGET).cpp -o $(DERIVED_OBJECT)

.PHONY: setup
setup:
	mkdir -p $(DERIVED)
	touch $(DERIVED)/__init__.py

.PHONY: clean
clean:
	@rm -r $(DERIVED)

.PHONY: pytest
pytest: $(DERIVED_MODULE) main
	@echo ""
	@python test.py

.PHONY: test
test: $(DERIVED_MODULE) main
	@echo ""
	@./test
