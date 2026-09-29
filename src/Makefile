# ---------- Macros (variables) ----------
CC       = gcc
CFLAGS   = -Wall -fPIC -I../include
AR       = ar
ARFLAGS  = rc

OBJ_DIR  = ../obj
BIN_DIR  = ../bin
LIB_DIR  = ../lib

LIB_NAME    = myutils
STATIC_LIB  = $(LIB_DIR)/lib$(LIB_NAME).a
DYNAMIC_LIB = $(LIB_DIR)/lib$(LIB_NAME).so

STATIC_TARGET  = $(BIN_DIR)/client_static
DYNAMIC_TARGET = $(BIN_DIR)/client_dynamic

HEADERS  = ../include/mystrfunctions.h ../include/myfilefunctions.h
LIB_OBJS = $(OBJ_DIR)/mystrfunctions.o $(OBJ_DIR)/myfilefunctions.o
MAIN_OBJ = $(OBJ_DIR)/main.o

# ---------- Targets ----------
all: $(STATIC_TARGET) $(DYNAMIC_TARGET)

# Static library: pack the object files into an archive
$(STATIC_LIB): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $^
	ranlib $@

# Dynamic library: build a shared object from position-independent objects
$(DYNAMIC_LIB): $(LIB_OBJS)
	$(CC) -shared -o $@ $^

# Static client: full path to the .a so the linker cannot pick the .so
$(STATIC_TARGET): $(MAIN_OBJ) $(STATIC_LIB)
	$(CC) $(MAIN_OBJ) $(STATIC_LIB) -o $@

# Dynamic client: -L and -l, the linker picks libmyutils.so
$(DYNAMIC_TARGET): $(MAIN_OBJ) $(DYNAMIC_LIB)
	$(CC) $(MAIN_OBJ) -L$(LIB_DIR) -l$(LIB_NAME) -o $@

# Compile: turn each .c file into a .o file
$(OBJ_DIR)/%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Remove all generated files
clean:
	rm -f $(OBJ_DIR)/*.o $(STATIC_LIB) $(DYNAMIC_LIB) $(STATIC_TARGET) $(DYNAMIC_TARGET)

.PHONY: all clean
