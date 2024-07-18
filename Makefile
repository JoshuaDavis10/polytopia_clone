CC = gcc
CFLAGS = -O1 -Wall -std=c99 -Wno-missing-braces
LIBS = -lm -lraylib -lopengl32 -lgdi32 -lwinmm

SRC := src
OBJ := obj
BIN := demo.exe

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

$(BIN): $(OBJECTS)
	@echo linking...
	@$(CC) $^ -o $@ -I include/ -L lib/ $(LIBS)
	@echo compilation complete.

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	@echo compiling $<
	@$(CC) $(CFLAGS) -I$(SRC) -c $< -o $@

$(OBJ):
	@mkdir $(OBJ)

.PHONY: clean
clean:
	@if exist $(OBJ) echo deleting obj files...
	@if exist $(OBJ) rmdir /s /q $(OBJ)
	@if exist $(BIN) echo deleting demo.exe...
	@if exist $(BIN) del $(BIN)
	@echo clean complete.
