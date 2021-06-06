#*******************************************************************************
# File name        : makefile
# File description : 
# Author           : ronyett
#*******************************************************************************

SRC_DIR				= 	.
OBJECT_DIR		= 	$(SRC_DIR)/object
MAKE_DIR_CMD	= 	mkdir $(OBJECT_DIR)

CC  					= 	gcc
LINK  				= 	gcc
AR						= 	ar
CHK   				= 	
CHECK_FOR_CHK	:= 	$(shell command -v $(CHK) 2> /dev/null)

#*******************************************************************************
# Build options
#*******************************************************************************

# gcov and gprof build options
COVPFLAGS			= 	-fprofile-arcs -ftest-coverage
PROFLAGS			= 	-pg
#PFLAGS				= 	$(COVFLAGS)

# Main CC and Link build strings
DEBUG					= 	-g
CFLAGS				= 	-c -std=c99 -Wall -pedantic $(PFLAGS)
LFLAGS				= 	$(PFLAGS) -static -L.

# -DDEBUG_TRACE	Will turn on deep trace per function
# -DEXCEPTION	Will use the real exceptions with the 'try' that's in the test harness

# Code checking with splint
CODE_CHECK       	= 	splint
CODE_CHECK_ARGS	 	= 	-showfunc -mustfreefresh -nullpass -nullret -noeffect

# codespell
CODE_SPELL		= 	codespell
CODE_SPELL_ARGS		= 	--skip "*.a,*.o,*.exe,./.git"
CHECK_FOR_CODESPELL	:=	$(shell command -v $(CODE_SPELL) 2> /dev/null)

#
# Libs, objs targets
# libstack library is built from trap handling and the stack implementation. 
#
OBJS  		     	=	$(OBJECT_DIR)/main.o 		
LIBS  		     	= 

#*******************************************************************************
# Build targets:
# all		Creates object directory, builds executable and runs checker
# lib		Build only the list library, no test harness
# splint-it	run the Syntax checker
# clean		Delete object and library files
#*******************************************************************************

all:	$(OBJECT_DIR) main.exe 

lib:	$(LIBS)

main.exe:	$(OBJS) $(LIBS)
	$(LINK) $(OBJS) $(LFLAGS) -o main.exe

$(OBJECT_DIR):
	-$(MAKE_DIR_CMD)

$(OBJECT_DIR)/main.o:		main.c
	$(CC) $(CFLAGS) $(DEBUG) main.c -o $(OBJECT_DIR)/main.o

# Code checking target
#
splint-it:
	$(CODE_CHECK) $(CODE_CHECK_ARGS) main.c

spelling-bee:
ifndef CHECK_FOR_CODESPELL
	@echo "** codespell was not found"
else
	$(CODE_SPELL) $(CODE_SPELL_ARGS)
endif

clean:
	rm -f main.exe
	rm -f $(OBJECT_DIR)/trap.o
	rm -f *.gcno
	rm -f *.gcda
	rm -f gmon.out
	rm -f core

#
# Fin
#

