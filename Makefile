#
# Makefile for a CS 101 lab or programming assignment.
# Do not modify this file!!!
#

SUBMIT_URL = https://cs.ycp.edu/marmoset/bluej/SubmitProjectViaBlueJSubmitter
COURSE_NAME = CS 101
SEMESTER = Spring 2016

INC = -Iinclude

# See if ncurses.h is in an "ncurses" subdirectory
NCURSES_DIR := $(shell if [ -r /usr/include/ncurses/ncurses.h ]; then echo "yes"; fi)
ifeq ($(NCURSES_DIR),yes)
CXXFLAGS_EXTRA := -DCONS_NCURSES_IS_IN_NCURSES_INCLUDE_DIR
endif
# Some unknown software on the KEC Windows load
# sets the GCC_EXEC_PREFIX environment variable, which
# prevents Cygwin's gcc/g++ from working correctly.
# Make sure it is unset when we invoke g++.
CXX = unset GCC_EXEC_PREFIX && g++

CXXFLAGS = -g -Wall $(CXXFLAGS_EXTRA) $(INC)

# If compiling on cygwin, need extra linker flag
UNAME := $(shell uname)
ifeq ($(UNAME),Cygwin)
LDFLAGS_EXTRA = -Wl,--enable-auto-import
endif

LDFLAGS = $(LDFLAGS_EXTRA) -lncurses

SRC = Chomp.cpp Player.cpp Scene.cpp
OBJ = $(SRC:.cpp=.o)
EXE = $(SRC:.cpp=.exe)

LIBOBJ = lib/Console.o

$(EXE) : clean $(OBJ) $(LIBOBJ)
	$(CXX) -o $@ $(OBJ) $(LIBOBJ) $(LDFLAGS)

submit :
	@echo "Please use one of the following commands:"
	@echo "  make submit_ms1"
	@echo "  make submit_ms2"
	@echo "  make submit_ms3"

submit_ms1 :
	PROJECT_NUMBER=assign05_ms1 make _submit

submit_ms2 :
	PROJECT_NUMBER=assign05_ms2 make _submit

_submit : submit.properties solution.zip
	perl submitToMarmoset.pl solution.zip submit.properties

solution.zip : collected-files.txt
	@echo "Creating a solution zip file"
	@zip -9 $@ `cat collected-files.txt`
	@rm -f collected-files.txt

# Create the submit.properties file that describes how
# the project should be uploaded to the Marmoset server.
submit.properties : nonexistent
	@echo "Creating submit.properties file"
	@rm -f $@
	@echo "submitURL = $(SUBMIT_URL)" >> $@
	@echo "courseName = $(COURSE_NAME)" >> $@
	@echo "semester = $(SEMESTER)" >> $@
	@echo "projectNumber = $(PROJECT_NUMBER)" >> $@

# Collect the names of all files that don't appear
# to be generated files.
collected-files.txt :
	@echo "Collecting the names of files to be submitted"
	@rm -f $@
	@find . -not \( \
				-name '*\.o' \
				-or -name '*\.exe' \
				-or -name '*~' \
				-or -name 'collected-files.txt' \
				-or -name 'submit.properties' \
				-or -type d \
			\) -print \
		| perl -ne 's,\./,,; print' \
		> $@

# This is just a dummy target to force other targets
# to always be out of date.
nonexistent :

# Remove generated files.
clean : 
	rm -f *.o lib/*.o *.exe collected-files.txt submit.properties solution.zip
