CC = gcc

TARGET = bin/server
SOURCES = src/server.c src/httputils.c src/dirutils.c

$(TARGET): $(SOURCES)
	$(CC) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)
