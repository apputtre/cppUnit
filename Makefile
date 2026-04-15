INCLUDE_DIRS=include
BIN_PATH=test/bin
SRC_PATH=src test
OBJ_PATH=obj

OBJ_FILES=main.o

VPATH = $(BIN_PATH) $(OBJ_PATH) $(SRC_PATH) $(INCLUDE_DIRS)

# Variables used for implicit rules
CXXFLAGS = -Wall -Wextra -Werror -g -std=c++20 $(foreach dir,$(INCLUDE_DIRS),$(patsubst %,-I%,$(dir)))
CFLAGS = -g $(foreach dir,$(INCLUDE_DIRS),$(patsubst %,-I%,$(dir)))
LDFLAGS = 

main.exe: main.cpp TestCase.h TestEnvironment.h TestReport.h TestSuite.h TestSuiteReport.h
	mkdir -p $(BIN_PATH)
	$(CXX) $(CXXFLAGS) test/main.cpp -o $(BIN_PATH)/main.exe $(LDFLAGS)

.PHONY: clean
clean:
	rm -f $(BIN_PATH)/*