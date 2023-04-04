# C++ compiler
CXX= g++
# additional flags provided to the compiler
CXXFLAGS= -Wall -Iinclude
# target name - from which we compile the program
TARGET=$(project_giray)

# automatic search of source files (in src and current folder)
SRCS := $(wildcard src/*.cpp *.cpp)
OBJS := $(SRCS:src/%.cpp=build/%.o)

# print out the information
$(info Compiler: $(CXX))
$(info Flags: $(CXXFLAGS))
$(info Target: $(TARGET))
$(info Source files: $(SRCS))
$(info Object files: $(OBJS))
$(info )

# target that compiles entire project
all: build/$(TARGET)

# target that compiles a program in debug mode
debug: CXXFLAGS:= -g -O0 $(CXXFLAGS)
debug: all

# target that compiles a program in release mode
release: CXXFLAGS:= -O3 $(CXXFLAGS)
release: all

# target to clean compiled files
clean:
	rm -rf build/*

# target that compiles a source code into object module
build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^ 

# target that links the object modules into a program
build/$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ 

