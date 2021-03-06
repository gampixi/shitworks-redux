TARGET_EXEC ?= a.out

BUILD_DIR ?= ./build
SRC_DIRS ?= ./shitworks-redux

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := include
INC_FLAGS := $(addprefix -I,$(INC_DIRS)) 

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -std=c++17
CXXFLAGS ?= -std=c++17
LDFLAGS ?= -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lstdc++ -lm

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS`) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)/shitworks-redux
	$(RM) $(BUILD_DIR)/a.out

-include $(DEPS)

MKDIR_P ?= mkdir -p