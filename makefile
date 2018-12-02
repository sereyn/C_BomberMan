# Declare variables

CC=gcc
FLAGS=-W -Wall -Wextra -g -std=c89 -pedantic -O3 `pkg-config --cflags MLV`
POSTFLAGS=`pkg-config --libs-only-l MLV`
SRC_DIR=./source
OBJ_DIR=./build
RELEASE_DIR=./bin
EXEC=$(RELEASE_DIR)/bomberman
SRC=$(shell find $(SRC_DIR) -name "*.c")
OBJ=$(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))


# makefile functions

build_and_run:
	@make build --no-print-directory
	@make run --no-print-directory

build:
	@mkdir -p $(OBJ_DIR) $(RELEASE_DIR)
	@echo "Building project..."
	@make $(EXEC)
	@echo "Project built"

run:
	@echo "Running project..."
	@$(EXEC)

debug:
	@echo "Debugging project... (type run)"
	@gdb $(EXEC)

rebuild:
	@make clean --no-print-directory
	@make build --no-print-directory

clean:
	@echo "Cleaning project..."
	@rm -f $(OBJ_DIR)/*.o $(EXEC)
	@echo "Project cleaned"

.PHONY: build_and_run build run debug rebuild clean


# Compilation

$(EXEC): $(OBJ)
	@echo "Linking..."
	@$(CC) $(FLAGS) -o $@ $^ $(POSTFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(SRC_DIR)/%.h
	@echo "Compiling \"$(notdir $<)\""
	@$(CC) $(FLAGS) -o $@ -c $< $(POSTFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/objects/%.c $(SRC_DIR)/objects/%.h
	@echo "Compiling \"objects/$(notdir $<)\""
	@$(CC) $(FLAGS) -o $@ -c $< $(POSTFLAGS)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.c
	@echo "Compiling \"$(notdir $<)\""
	@$(CC) $(FLAGS) -o $@ -c $< $(POSTFLAGS)


# Dependencies

$(OBJ_DIR)/main.o: $(SRC_DIR)/game.h $(SRC_DIR)/menu.h $(SRC_DIR)/bomberman.h $(SRC_DIR)/utils.h $(SRC_DIR)/grid.h $(SRC_DIR)/inputs.h $(SRC_DIR)/editor.h

$(OBJ_DIR)/editor.o: $(SRC_DIR)/bomberman.h $(SRC_DIR)/objects.h $(SRC_DIR)/files.h $(SRC_DIR)/utils.h $(SRC_DIR)/inputs.h

$(OBJ_DIR)/bomberman.o: $(SRC_DIR)/objects.h $(SRC_DIR)/utils.h $(SRC_DIR)/grid.h $(SRC_DIR)/inputs.h $(SRC_DIR)/sprites.h $(SRC_DIR)/objects/player.h $(SRC_DIR)/objects/bomb.h $(SRC_DIR)/objects/flame.h $(SRC_DIR)/objects/bonus.h

$(OBJ_DIR)/files.o: $(SRC_DIR)/utils.h $(SRC_DIR)/bomberman.h $(SRC_DIR)/objects.h $(SRC_DIR)/objects/bomb.h $(SRC_DIR)/objects/flame.h $(SRC_DIR)/objects/bonus.h $(SRC_DIR)/objects/player.h

$(OBJ_DIR)/objects.o: $(SRC_DIR)/bomberman.h $(SRC_DIR)/utils.h $(SRC_DIR)/grid.h $(SRC_DIR)/sprites.h

$(OBJ_DIR)/grid.o: $(SRC_DIR)/utils.h

$(OBJ_DIR)/game.o: $(SRC_DIR)/utils.h $(SRC_DIR)/files.h $(SRC_DIR)/objects.h $(SRC_DIR)/sprites.h $(SRC_DIR)/objects/player.h $(SRC_DIR)/inputs.h

$(OBJ_DIR)/sprites.o: $(SRC_DIR)/utils.h

$(OBJ_DIR)/menu.o: $(SRC_DIR)/utils.h $(SRC_DIR)/bomberman.h $(SRC_DIR)/files.h $(SRC_DIR)/inputs.h

$(OBJ_DIR)/player.o: $(SRC_DIR)/bomberman.h $(SRC_DIR)/objects.h $(SRC_DIR)/sprites.h $(SRC_DIR)/inputs.h $(SRC_DIR)/objects/bomb.h $(SRC_DIR)/objects/flame.h

$(OBJ_DIR)/bomb.o: $(SRC_DIR)/bomberman.h $(SRC_DIR)/objects.h $(SRC_DIR)/sprites.h $(SRC_DIR)/objects/player.h

$(OBJ_DIR)/flame.o: $(SRC_DIR)/bomberman.h $(SRC_DIR)/objects.h $(SRC_DIR)/sprites.h

$(OBJ_DIR)/bonus.o: $(SRC_DIR)/bomberman.h $(SRC_DIR)/objects.h $(SRC_DIR)/sprites.h $(SRC_DIR)/objects/player.h $(SRC_DIR)/utils.h
