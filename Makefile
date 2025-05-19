# Directories
SRC_DIR := src
OBJ_DIR := build

# Find all .c files under src/ recursively
SRCS := $(shell find $(SRC_DIR) -name '*.c')

# Create corresponding object files in build/, maintaining structure
OBJS := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
DEPS := $(OBJS:.o=.d)

# Output binary
OBJ_NAME = main

# Compiler and flags
CC = gcc
CFLAGS = -std=c11 -Wall -MMD -MP $(addprefix -I, $(shell find $(SRC_DIR) -type d))
LDFLAGS = `sdl2-config --libs` -lSDL2_image

# Targets
all: $(OBJ_NAME)
	@echo "Running program..."
	./$(OBJ_NAME)

# Link object files into final executable
$(OBJ_NAME): $(OBJS)
	@echo "Linking..."
	$(CC) $^ -o $@ $(LDFLAGS)

# Compile each .c to matching .o in build/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build and binary
clean:
	rm -rf $(OBJ_NAME) $(OBJ_DIR)

# Include dependency files
-include $(DEPS)

