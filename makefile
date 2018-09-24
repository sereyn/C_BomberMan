# Declare variables

CC=gcc
FLAGS=-W -Wall -std=c89 -pedantic -O3 `pkg-config --cflags MLV`
POSTFLAGS=`pkg-config --libs-only-l MLV`
SRC_DIR=./source
OBJ_DIR=./build
RELEASE_DIR=./release
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
	$(EXEC)

rebuild:
	@make clean --no-print-directory
	@make build --no-print-directory

clean:
	@echo "Cleaning project..."
	@rm -f $(OBJ_DIR)/*.o $(EXEC)
	@echo "Project cleaned"

.PHONY: build_and_run build run rebuild clean


# Compilation

$(EXEC): $(OBJ)
	$(CC) $(FLAGS) -o $@ $^ $(POSTFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(FLAGS) -o $@ -c $< $(POSTFLAGS)


# Dependencies

$(OBJ_DIR)/main.o: $(SRC_DIR)/editor.h $(SRC_DIR)/bomberman.h

$(OBJ_DIR)/player.o: $(SRC_DIR)/player.h $(SRC_DIR)/utils.h

$(OBJ_DIR)/blocks.o: $(SRC_DIR)/blocks.h $(SRC_DIR)/utils.h

$(OBJ_DIR)/floors.o: $(SRC_DIR)/floors.h $(SRC_DIR)/utils.h

$(OBJ_DIR)/editor.o: $(SRC_DIR)/editor.h $(SRC_DIR)/bomberman.h $(SRC_DIR)/blocks.h $(SRC_DIR)/floors.h $(SRC_DIR)/files.h

$(OBJ_DIR)/bomberman.o: $(SRC_DIR)/bomberman.h $(SRC_DIR)/floors.h $(SRC_DIR)/blocks.h $(SRC_DIR)/sprites.h $(SRC_DIR)/player.h

$(OBJ_DIR)/files.o: $(SRC_DIR)/files.h

$(OBJ_DIR)/sprites.o: $(SRC_DIR)/sprites.h
