
#!/bin/bash
# this is a template for script of the command activate
#--------------------------------------------
#HELP COMMAND
case $1 in
    help)
	
	case $2 in
		$var)
		echo -e "New: Creates a new project with the given name in the current location.\n
		Activate: Activates an existing project and within this:\n
		Add: In the case of a given path, the project is created on the specified path.\n
		Run: Runs the program. Forwards any parameters to the program.\n
		Test: Runs tests inside the project."
		;;
	
		new)
		echo -e "New: Creates a new project with the given name in the current location."
		;;
		activate)
		echo -e "Activate: Activates an existing project and within this:"
		;;
		add)
		echo -e "Add: In the case of a given path, the project is created on the specified path." 
		;;
		build)
		echo -e "Build: Builds the program inside the project. "
		;;
		run)
		echo -e "Run: Runs the program. Forwards any parameters to the program."
		;;
		test)
		echo -e "Test: Runs tests inside the project."
		;;
		
	esac
;;
esac
#--------------------------------------------
#NEW COMMAND
case $1 in
	new)
	case $3 in
    		-d)
    		mkdir -p $4/$2/{src,include,build,tests} && touch $4/$2/src/main.c && touch $4/$2/Makefile && echo "# C++ compiler
CXX= g++
# additional flags provided to the compiler
CXXFLAGS= -Wall -Iinclude
# target name - from which we compile the program
TARGET=$'('$2')'

# automatic search of source files (in src and current folder)
SRCS := $'(wildcard src/*.cpp *.cpp)'
OBJS := $'(SRCS:src/%.cpp=build/%.o)'

# print out the information
$'(info Compiler: $'(CXX)')'
$'(info Flags: $'(CXXFLAGS)')'
$'(info Target: $'(TARGET)')'
$'(info Source files: $'(SRCS)')'
$'(info Object files: $'(OBJS)')'
$'(info )'

# target that compiles entire project
all: build/$'(TARGET)'

# target that compiles a program in debug mode
debug: CXXFLAGS:= -g -O0 $'(CXXFLAGS)'
debug: all

# target that compiles a program in release mode
release: CXXFLAGS:= -O3 $'(CXXFLAGS)'
release: all

# target to clean compiled files
clean:
	rm -rf build/*

# target that compiles a source code into object module
build/%.o: src/%.cpp
	$'(CXX)' $'(CXXFLAGS)' -c -o $@ $^ 

# target that links the object modules into a program
build/$'(TARGET)': $'(OBJS)'
	$'(CXX)' $'(CXXFLAGS)' -o $@ $^ 
"> $4/$2/Makefile && echo "// Your First C++ Program

#include <iostream>

int main() {
    std::cout << "Hello World!";
    return 0;
}">$4/$2/src/main.c
    	
;;
esac
#--------------------------------------------
#ACTIVATE COMMAND
case $1 in
	activate)
	
	bash --rcfile $(dirname $0)/my_bashrc

;;
esac
#--------------------------------------------
#ADD COMMAND
case $1 in
	add)

	function add(){
	
	
cd src	
 touch "$1.c"
 touch "$1.h"
 echo '#ifndef '$1'_H_
#define '$1'_H_

// Class declaration goes here

#endif // '$1'_H_'>$1.h
 
 
 echo '#include' '"'$1.h'"'>$1.c
 }

add $2
;;
esac
#--------------------------------------------
#BUILD COMMAND
case $1 in
	build)
	
	#CODE HERE
;;
esac
#--------------------------------------------
#RUN COMMAND
case $1 in
	run)
       
        make
        ./run
;;
esac
#--------------------------------------------
#TEST COMMAND
case $1 in
	test)
	while getopts "l:" arg; do
	echo "Exist" "Equal" "GT" "..."
	done
	while test $# -gt 0; do
  	case "$1" in
    	   -h|--help)
      	echo "$package - attempt to capture frames"
      	echo " "
      	echo "$package [options] application [arguments]"
      	echo " "
      	echo "options:"
      	echo "-h, --help                show brief help"
      	echo "-a, --action=ACTION       specify an action to use"
      	echo "-o, --output-dir=DIR      specify a directory to store output in"
      	exit 0
      	;;
    	-a)
      	shift
      	if test $# -gt 0; then
        	export PROCESS=$1
      	else
        	echo "no process specified"
        	exit 1
      	fi
      	shift
      	;;
    	--action*)
      	export PROCESS=`echo $1 | sed -e 's/^[^=]*=//g'`
      	shift
      	;;
    	-o)
      	shift
      	if test $# -gt 0; then
        	export OUTPUT=$1
      	else
        	echo "no output dir specified"
        	exit 1
      	fi
      	shift
      	;;
    	--output-dir*)
      	export OUTPUT=`echo $1 | sed -e 's/^[^=]*=//g'`
      	shift
      	;;
    	*)
      	break
      	;;
  	esac
	done
#--------------------------------------------
#

;;
esac
#--------------------------------------------






