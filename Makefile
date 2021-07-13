SYSTEM_PATH = ./goodEatsSystem
SERVER_PATH = ./goodEatsServer
OBJECT_PATH = obj
TEMPLATE_PATH = ./.template

include cc.mk

OUTPUT = goodeats.out

SYSTEM_OBJECTS = Chef.o Filter.o GoodEatsErrors.o Recipe.o Shelf.o System.o User.o
SERVER_OBJECTS = main.o handlers.o route.o server.o request.o response.o template_parser.o utilities.o

.PHONY: all makeall link clean clean-system clean-server run

all: makeall link

makeall:
	$(MAKE) -C $(SYSTEM_PATH) all
	$(MAKE) -C $(SERVER_PATH) all

link: $(addprefix $(SYSTEM_PATH)/$(OBJECT_PATH)/, $(SYSTEM_OBJECTS)) $(addprefix $(SERVER_PATH)/$(OBJECT_PATH)/, $(SERVER_OBJECTS))
	$(CPP) $^ -o $(OUTPUT)

run:
	./$(OUTPUT)

clean: clean-server clean-system
	rm -rf $(TEMPLATE_PATH) $(OUTPUT) &> /dev/null

clean-server:
	$(MAKE) -C $(SERVER_PATH) clean

clean-system:
	$(MAKE) -C $(SYSTEM_PATH) clean
