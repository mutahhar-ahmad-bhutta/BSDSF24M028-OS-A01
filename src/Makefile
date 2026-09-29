# ---------- Macros (variables) ----------
CC      = gcc
CFLAGS  = -Wall -I../include
OBJ_DIR = ../obj
BIN_DIR = ../bin
TARGET  = $(BIN_DIR)/client

HEADERS = ../include/mystrfunctions.h ../include/myfilefunctions.h
OBJECTS = $(OBJ_DIR)/main.o $(OBJ_DIR)/mystrfunctions.o $(OBJ_DIR)/myfilefunctions.o

# ---------- Targets ----------
all: $(TARGET)

# Link: combine all object files into the final program
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET)

# Compile: turn each .c file into a .o file
$(OBJ_DIR)/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Remove all generated files
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)

.PHONY: all clean
