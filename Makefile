BINARY:=human4b
OBJECTS:=main.o cipher.o

$(BINARY): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(BINARY)
	rm -f $(OBJECTS)
