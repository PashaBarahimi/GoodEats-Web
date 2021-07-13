OBJECT_DIR = obj
OBJECT_PATH = ./$(OBJECT_DIR)
SOURCE_PATH = ./src
INCLUDE_PATH = $(SOURCE_PATH)/include

include ../cc.mk

vpath %.hpp $(INCLUDE_PATH)
vpath %.cpp $(SOURCE_PATH)

OBJECTS = Chef.o Filter.o GoodEatsErrors.o Recipe.o Shelf.o System.o User.o

.PHONY: all clean make-objects make-dir

all: make-dir make-objects

make-dir:
	mkdir -p $(OBJECT_DIR)

make-objects: $(addprefix $(OBJECT_PATH)/, $(OBJECTS))

$(OBJECT_PATH)/Chef.o: Chef.cpp Chef.hpp Recipe.hpp AlgorithmSideFunctions.hpp
	$(CPP) -c $< -o $@

$(OBJECT_PATH)/Filter.o: Filter.cpp Filter.hpp Recipe.hpp
	$(CPP) -c $< -o $@

$(OBJECT_PATH)/GoodEatsErrors.o: GoodEatsErrors.cpp GoodEatsErrors.hpp
		$(CPP) -c $< -o $@

$(OBJECT_PATH)/Recipe.o: Recipe.cpp Recipe.hpp User.hpp Chef.hpp Filter.hpp AlgorithmSideFunctions.hpp
		$(CPP) -c $< -o $@

$(OBJECT_PATH)/Shelf.o: Shelf.cpp Shelf.hpp Recipe.hpp AlgorithmSideFunctions.hpp
		$(CPP) -c $< -o $@

$(OBJECT_PATH)/System.o: System.cpp System.hpp Chef.hpp Filter.hpp GoodEatsErrors.hpp Recipe.hpp Shelf.hpp User.hpp
		$(CPP) -c $< -o $@

$(OBJECT_PATH)/User.o: User.cpp User.hpp Shelf.hpp
		$(CPP) -c $< -o $@

clean:
	rm -rf $(OBJECT_DIR) &> /dev/null
