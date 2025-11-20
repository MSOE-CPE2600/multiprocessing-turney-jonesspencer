CC=gcc
CFLAGS=-c -Wall -g
LDFLAGS=-ljpeg
SOURCES= mandel.c jpegrw.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=mandel

all: $(SOURCES) $(EXECUTABLE) mandelmovie

# pull in dependency info for *existing* .o files
-include $(OBJECTS:.o=.d) mandelmovie.d

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

mandelmovie: mandelmovie.o
	$(CC) mandelmovie.o -lm -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM $< > $*.d

clean:
	rm -rf $(OBJECTS) mandelmovie.o $(EXECUTABLE) mandelmovie *.d
	rm *.jpg