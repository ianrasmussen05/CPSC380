EXECUTABLE := prodcon

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
# prodcon.o:
$(EXECUTABLE):  checksum.o prodcon.o
	$(CC) $(CFLAGS) checksum.o prodcon.o -o $(EXECUTABLE) -lpthread

checksum.o: checksum.c 
	$(CC) $(CFLAGS) -c checksum.c

prodcon.o: prodcon.c 
	$(CC) $(CFLAGS) -c prodcon.c checksum.o


# Removes any files that end in .o to clean the folder
clean:
	rm $(EXECUTABLE) *.o
# this line required by make - don't delete