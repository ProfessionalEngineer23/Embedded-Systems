# === MCU settings ===
MCU = atmega328p
F_CPU = 16000000UL

# === Compiler and flags ===
CC = avr-gcc
CFLAGS = -mmcu=$(MCU) -Os -DF_CPU=$(F_CPU) -Iinclude

# === AVRDUDE settings ===
PROGRAMMER = arduino
PORT = COM23
BAUD = 115200

# === Directories ===
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = obj

# === Normal bot (harness project) files ===
SRC = $(SRC_DIR)/harness.c $(SRC_DIR)/usart.c $(SRC_DIR)/actions.c $(SRC_DIR)/config.c $(SRC_DIR)/pwm.c $(SRC_DIR)/ultrasonic.c
OBJ = $(OBJ_DIR)/millisMicrosDelay.o
TARGET = $(BUILD_DIR)/ExecutableFile

# === Autonomous bot files ===
AUTONOMOUS_SRC = $(SRC_DIR)/autonomous_bot.c $(SRC_DIR)/usart.c $(SRC_DIR)/config.c $(SRC_DIR)/pwm.c $(SRC_DIR)/ultrasonic.c
AUTONOMOUS_OBJ = $(OBJ)
AUTONOMOUS_TARGET = $(BUILD_DIR)/autonomous_bot

# === BUILD RULES ===

# Normal BOT (harness project) build
code: $(TARGET).hex

$(TARGET).elf: $(SRC) $(OBJ)
	mkdir -p $(BUILD_DIR) $(OBJ_DIR)
	$(CC) $(CFLAGS) $(SRC) $(OBJ) -o $@

$(TARGET).hex: $(TARGET).elf
	avr-objcopy -O ihex $< $@

# Autonomous BOT build
autonomous_bot: $(AUTONOMOUS_TARGET).hex

$(AUTONOMOUS_TARGET).elf: $(AUTONOMOUS_SRC) $(AUTONOMOUS_OBJ)
	mkdir -p $(BUILD_DIR) $(OBJ_DIR)
	$(CC) $(CFLAGS) $(AUTONOMOUS_SRC) $(AUTONOMOUS_OBJ) -o $@

$(AUTONOMOUS_TARGET).hex: $(AUTONOMOUS_TARGET).elf
	avr-objcopy -O ihex $< $@

# === UPLOAD RULES ===

upload: code
	avrdude -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$(TARGET).hex:i

upload_autonomous: autonomous_bot
	avrdude -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$(AUTONOMOUS_TARGET).hex:i

# === CLEAN ===
clean:
	rm -rf $(BUILD_DIR)/*.elf $(BUILD_DIR)/*.hex

.PHONY: code upload autonomous_bot upload_autonomous clean
