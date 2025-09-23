MCU = atmega328p
F_CPU = 16000000UL
BAUD = 9600
PROGRAMMER = arduino
PORT = COM23
BAUDRATE = 115200

CC = avr-gcc
OBJCOPY = avr-objcopy

# Enable float support in printf and math functions
CFLAGS = -Wall -Os -mmcu=$(MCU) -DF_CPU=$(F_CPU)
LDFLAGS = -mmcu=$(MCU) -Wl,-u,vfprintf -lprintf_flt -lm

TARGET = adc
SRC = adc.c usart.c

all: $(TARGET).hex

$(TARGET).elf: $(SRC)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(TARGET).hex: $(TARGET).elf
	$(OBJCOPY) -O ihex -R .eeprom $< $@

upload: $(TARGET).hex
	avrdude -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUDRATE) -U flash:w:$<

clean:
	rm -f *.hex *.elf *.o
