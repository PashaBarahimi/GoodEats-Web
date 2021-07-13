OBJECT_DIR = obj
OBJECT_PATH = ./$(OBJECT_DIR)

include ../cc.mk

OBJECTS = main.o handlers.o route.o server.o request.o response.o template_parser.o utilities.o

.PHONY: all clean make-objects make-dir

all: make-dir make-objects

make-dir:
	mkdir -p $(OBJECT_DIR)

make-objects: $(addprefix $(OBJECT_PATH)/, $(OBJECTS))

$(OBJECT_PATH)/main.o: goodeats/main.cpp goodeats/include/handlers.hpp ../goodEatsSystem/src/include/System.hpp
	$(CPP) -c $< -o $@

$(OBJECT_PATH)/handlers.o: goodeats/handlers.cpp goodeats/include/handlers.hpp ../goodEatsSystem/src/include/System.hpp
	$(CPP) -c $< -o $@

$(OBJECT_PATH)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CPP) -c $< -o $@

$(OBJECT_PATH)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CPP) -c $< -o $@

$(OBJECT_PATH)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CPP) -c $< -o $@

$(OBJECT_PATH)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CPP) -c $< -o $@
	
$(OBJECT_PATH)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CPP) -c $< -o $@

$(OBJECT_PATH)/utilities.o: utils/utilities.cpp utils/utilities.hpp
		$(CPP) -c $< -o $@

clean:
	rm -rf $(OBJECT_DIR) &> /dev/null