EXECUTABLE := recfile

SOURCES := *.cpp

INCLUDES := -I .
EXT := out
CC := g++

# -Wall checks for any warnings
CFLAGS  := -g -Wall

# typing 'make' will invoke the first target entry in the file
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
default: $(EXECUTABLE)

# To create the executable file count we need the object files
# recfile.o and main.o:
$(EXECUTABLE):  recfile.o 
	$(CC) $(CFLAGS) -o $(EXECUTABLE) recfile.o

# To create the object file recfile.o, we need the source files
# recfile.cpp
recfile.o:  recfile.cpp
	$(CC) $(CFLAGS) -c recfile.cpp


# Removes any files that end in .o to clean the folder
clean:
	rm $(EXECUTABLE) *.o
# this line required by make - don't delete