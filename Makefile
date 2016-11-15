#makefile from  https://spin.atomicobject.com/2016/08/26/makefile-c-projects/
CC = avr-gcc
CFLAGS=-Os -DF_CPU=16000000UL 
LDFLAGS=-mmcu=atmega328p

TARGET_EXEC ?= a.elf

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

SRCS := $(shell LC_ALL=C find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell LC_ALL=C find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

upload:
	cd $(BUILD_DIR); \
	avr-objcopy -O ihex -R .eeprom $(TARGET_EXEC) out.hex; \
	avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:out.hex;

$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
