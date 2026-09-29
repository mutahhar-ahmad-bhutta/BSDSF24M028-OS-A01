# ---------- Macros (variables) ----------
CC       = gcc
CFLAGS   = -Wall -I../include
AR       = ar
ARFLAGS  = rc

OBJ_DIR  = ../obj
BIN_DIR  = ../bin
LIB_DIR  = ../lib

LIB_NAME   = myutils
STATIC_LIB = $(LIB_DIR)/lib$(LIB_NAME).a
TARGET     = $(BIN_DIR)/client_static

HEADERS  = ../include/mystrfunctions.h ../include/myfilefunctions.h
LIB_OBJS = $(OBJ_DIR)/mystrfunctions.o $(OBJ_DIR)/myfilefunctions.o
MAIN_OBJ = $(OBJ_DIR)/main.o

# ---------- Targets ----------
all: $(TARGET)

# Create the static library from the function object files
$(STATIC_LIB): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $^
	ranlib $@

# Link main.o with the static library to make the final program
$(TARGET): $(MAIN_OBJ) $(STATIC_LIB)
	$(CC) $(MAIN_OBJ) -L$(LIB_DIR) -l$(LIB_NAME) -o $@

# Compile: turn each .c file into a .o file
$(OBJ_DIR)/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Remove all generated files
clean:
	rm -f $(OBJ_DIR)/*.o $(STATIC_LIB) $(TARGET)

.PHONY: all clean
