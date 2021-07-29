OBJECT_PATH = obj
SOURCE_PATH = ./src
INCLUDE_PATH = $(SOURCE_PATH)/include

#--------------------------------------------

include ../vars.mk

vpath %.hpp $(INCLUDE_PATH)
vpath %.cpp $(SOURCE_PATH)

OBJECTS = Chef.o Filter.o GoodEatsErrors.o Recipe.o Shelf.o System.o User.o

#--------------------------------------------

.PHONY: all clean make-objects

all: $(OBJECT_PATH) make-objects

make-objects: $(addprefix $(OBJECT_PATH)/, $(OBJECTS))

#--------------------------------------------

$(OBJECT_PATH)/Chef.o: Chef.cpp Chef.hpp Recipe.hpp AlgorithmSideFunctions.hpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJECT_PATH)/Filter.o: Filter.cpp Filter.hpp Recipe.hpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJECT_PATH)/GoodEatsErrors.o: GoodEatsErrors.cpp GoodEatsErrors.hpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJECT_PATH)/Recipe.o: Recipe.cpp Recipe.hpp User.hpp Chef.hpp Filter.hpp AlgorithmSideFunctions.hpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJECT_PATH)/Shelf.o: Shelf.cpp Shelf.hpp Recipe.hpp AlgorithmSideFunctions.hpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJECT_PATH)/System.o: System.cpp System.hpp Chef.hpp Filter.hpp GoodEatsErrors.hpp Recipe.hpp Shelf.hpp User.hpp
	$(CC) $(CPPFLAGS) -c $< -o $@

$(OBJECT_PATH)/User.o: User.cpp User.hpp Shelf.hpp
	$(CC) $(CPPFLAGS) -c $< -o $@


$(OBJECT_PATH): ; $(MKDIR) $@

#--------------------------------------------

clean:
	$(RMDIR) $(OBJECT_PATH) > $(NULL_DEVICE)
