# [Makefile]

# Author   : William Hsiao
# Descript :  
# 1.[make Sample]: Generate Sample Executable File.
# 2.[make Slib]: Generate the Static Library.  (Make Sure the Lib Folder Already Exists)
# 3.[make Dlib]: Generate the Dynamic Library. (Make Sure the Lib Folder Already Exists)
# * In the Furture,The Lib Folder will be Detected and will be Automaticlly Generated if it does not Exist.
# 4.[make clean]: Remove Current Executable File Folder and Lib Folder Library
# 5.[make all]: Conduct all Functions above and Execute Sample.exe.(Except Delete the File)

# [Option]
CC = gcc
AR = ar -rcs
RM = rm -f
SHARED = -shared -fpic

CFLAGS = -std=c99 -Wall -Wextra
CDEF += -DLEAKCHECK

LIB_FOLDER = ./Lib/
LIB = XsLeakCheck
SRC = XsLeakCheck.c
OBJ = XsLeakCheck.o

COLOR_BLACK  = "\e[30;1m"
COLOR_RED    = "\e[31;1m"
COLOR_GREEN  = "\e[32;1m"
COLOR_YELLOW = "\e[33;1m"
COLOR_BLUE   = "\e[34;1m"
COLOR_PURPLE = "\e[35;1m"
COLOR_CYAN   = "\e[36;1m"
COLOR_WHITE  = "\e[37;1m"

TITLE_COLOR = $(COLOR_GREEN)
RESET_COLOR = $(COLOR_WHITE)


# [Content]
.PHONY:all clean

all:Slib Dlib Sample run-coverage
	./Sample

# Sample Code Tag
Sample:$(OBJ)
	@echo -e $(TITLE_COLOR) "@@Start to Build XsLeakCheck Sample" $(RESET_COLOR)
	$(CC) $(CFLAGS) $(CDEF) $(OBJ) $@.c -o $@

# Static Library Tag
Slib:$(OBJ)
	@echo -e $(TITLE_COLOR) "@@Start to Build XsLeakCheck Static Library" $(RESET_COLOR)
	$(AR) $(LIB_FOLDER)Lib$(LIB).a $(OBJ)

# Dynamic Library Tag
Dlib:$(OBJ)
	@echo -e $(TITLE_COLOR) "@@Start to Build XsLeakCheck Dynamic Library" $(RESET_COLOR)
	$(CC) $(SHARED) $(OBJ) -o $(LIB_FOLDER)Lib$(LIB).so
	$(CC) $(SHARED) $(OBJ) -o $(LIB_FOLDER)Lib$(LIB).dll

coverage:$(OBJ)
	$(CC) $(CFLAGS) $(CDEF) $(OBJ) -fprofile-arcs -ftest-coverage Sample.c -o $@

run-coverage:coverage
	./coverage && gcov Sample

$(OBJ):$(SRC)
	$(CC) $(CFLAGS) $(CDEF) $(SRC) -c -o $(OBJ)

# Remove File
clean:
	@echo -e $(TITLE_COLOR) "@@Remove ./ [*.o] [*.exe] [*.stackdump] File" $(RESET_COLOR)
	$(RM) $(OBJ) *.exe *.stackdump *.gcov *.gcda *.gcno
	@echo -e $(TITLE_COLOR) "@@Remove ./Lib [*.dll] [*.so] [*.a] File" $(RESET_COLOR)
	$(RM) $(LIB_FOLDER)*.dll $(LIB_FOLDER)*.so $(LIB_FOLDER)*.a
