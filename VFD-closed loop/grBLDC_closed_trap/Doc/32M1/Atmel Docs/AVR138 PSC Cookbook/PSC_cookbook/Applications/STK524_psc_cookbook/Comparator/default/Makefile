###############################################################################
# Makefile for the project Comparator
###############################################################################

## General Flags
PROJECT = Comparator
MCU = atmega324p
TARGET = Comparator.elf
CC = avr-gcc.exe

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -std=gnu99 -O0 -funsigned-char -funsigned-bitfields
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=Comparator.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Include Directories
INCLUDES = -I"D:\Work_SVN\Applications\STK524_psc_cookbook\Comparator\..\..\..\Drivers\comparator" -I"D:\Work_SVN\Applications\STK524_psc_cookbook\Comparator\..\..\..\Utils\GCC" -I"D:\Work_SVN\Applications\STK524_psc_cookbook\Comparator\..\..\..\Drivers\psc" -I"D:\Work_SVN\Applications\STK524_psc_cookbook\Comparator\..\..\..\Drivers\pll" -I"D:\Work_SVN\Applications\STK524_psc_cookbook\Comparator\." 

## Objects that must be built in order to link
OBJECTS = test_with_comparator.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) Comparator.hex Comparator.eep Comparator.lss size

## Compile
test_with_comparator.o: ../test_with_comparator.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) Comparator.elf dep/* Comparator.hex Comparator.eep Comparator.lss Comparator.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

