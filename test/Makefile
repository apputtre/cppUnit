INCLUDE_DIRS=../include include
BIN_PATH=bin
SRC_PATH=src test
OBJ_PATH=obj

OBJ_FILES=main.o

VPATH = $(BIN_PATH) $(OBJ_PATH) $(SRC_PATH) $(INCLUDE_DIRS)

CXXFLAGS = -Wall -Wextra -Werror -g -std=c++20 $(foreach dir,$(INCLUDE_DIRS),$(patsubst %,-I%,$(dir)))
CFLAGS = -g $(foreach dir,$(INCLUDE_DIRS),$(patsubst %,-I%,$(dir)))

main.exe: main.cpp ../include/* test_outputs/* include/*
	mkdir -p $(BIN_PATH)
	$(CXX) $(CXXFLAGS) src/main.cpp -o $(BIN_PATH)/main.exe $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(BIN_PATH)/*