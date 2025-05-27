# Verilator executable
VERILATOR = verilator

# Source directories
SRC_DIR = src
SIM_DIR = sim

# Output directory
BUILD_DIR = build

# Top-level testbenches
TOPS = tb_top_0 tb_top_1 tb_top_2

# Verilog source files (add more if needed)
SRC_FILES = $(wildcard $(SRC_DIR)/**/*.v)

# C++ testbench
CPP_FILE = main.cpp

# Compilation flags
VERILATOR_FLAGS = --cc --exe --build -Wall -Wno-fatal --timing -Mdir $(BUILD_DIR)

# Default target
all: $(TOPS)

# Build each top-level testbench
$(TOPS): %: $(BUILD_DIR)/%
	@echo "Built $@"

$(BUILD_DIR)/%: $(SIM_DIR)/%.v $(SRC_FILES) $(CPP_FILE)
	@mkdir -p $(BUILD_DIR)
	$(VERILATOR) $(VERILATOR_FLAGS) -o $(notdir $@) $^

# Run simulation for each top-level testbench
run_%: $(BUILD_DIR)/%
	./$<

# Clean build files
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean $(TOPS) run_%