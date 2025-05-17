# Directories
SRC_DIR = src
OBJ_DIR = build

# Files
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
DEPS := $(OBJS:.o=.d)
OBJ_NAME = main

# Compiler
CC = gcc
CFLAGS = -std=c11 -Wall -I$(SRC_DIR) -MMD -MP
LDFLAGS = `sdl2-config --libs` -lSDL2_image

# Targets
all: $(OBJ_NAME)
	@echo "Running program..."
	./$(OBJ_NAME)

$(OBJ_NAME): $(OBJS)
	@echo "Linking..."
	$(CC) $^ -o $@ $(LDFLAGS)

# Compile .c to .o and generate .d dependency files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(OBJ_NAME) $(OBJ_DIR)

# Include auto-generated dependency files
-include $(DEPS)

