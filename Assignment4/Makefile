EXECUTABLE := prodCon

SOURCES := *.c

INCLUDES := -I .
EXT := out
CC := gcc

# -Wall checks for any warnings
CFLAGS  := -g -Wall

# typing 'make' will invoke the first target entry in the file
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
default: $(EXECUTABLE)

# To create the executable file count we need the object files
# prodCon.o:
$(EXECUTABLE):  prodCon.o 
	$(CC) $(CFLAGS) -o $(EXECUTABLE) prodCon.o

# To create the object file recfile.o, we need the source files
# prodCon.c
prodCon.o:  prodCon.c
	$(CC) $(CFLAGS) -c prodCon.c -lpthread


# Removes any files that end in .o to clean the folder
clean:
	rm $(EXECUTABLE) *.o
# this line required by make - don't delete