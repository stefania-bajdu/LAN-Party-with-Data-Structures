CXX = g++
CXXFLAGS = -g -Wall
ifeq ($(OS), Windows_NT)
    SHARED-LIB = libs.dll
else
    SHARED-LIB = libs.so
endif
EXECUTABLE = lanParty
BUILD_FOLDER_PATH = ../build/
LIBS_PATH = ./libs

all: build-lib build-exe clean

build-lib:
	@$(CXX) *.c -I$(LIBS_PATH) -shared -fPIC $(CXXFLAGS) -o $(BUILD_FOLDER_PATH)$(SHARED-LIB)

build-exe:
	@$(CXX) *.c -I$(LIBS_PATH) $(CXXFLAGS) -o $(EXECUTABLE)

.PHONY: clean 
clean: 	
	@rm -f *.o 
