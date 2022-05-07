OUTDIR = build
TARGET = firmware
CCPRINT = ★ \e[32mCOMPILE\e[0m
LDPRINT = ★ \e[32mLINK\e[0m
OBJCOPYPRINT = ★ \e[32mOBJCOPY\e[0m
CLEANPRINT = ★ \e[32mCLEAN\e[0m
SIZEPRINT = ★ \e[32mSIZE\e[0m


# ################################################################# #
# AVR OPTIONS
# ################################################################# #
MCU = atmega4809
F_CPU = 16000000L


# ################################################################# #
# Set compiler flags & command
# ################################################################# #
AVR_FLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU)
WARNING_FLAGS = -std=c++17 -Wall -Wextra -Wpedantic -Weffc++ \
				-Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused \
				-Woverloaded-virtual -Wconversion -Wsign-conversion \
				-Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches \
				-Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion \
				-Wfloat-equal -Wfloat-conversion \
				-Warith-conversion -Wno-non-virtual-dtor
COMPILE_FLAGS = -g -Os -flto
INCLUDE_FLAGS = #-isystem /home/remi/.platformio/packages/framework-arduino-megaavr/cores/arduino/ -isystem /home/remi/.platformio/packages/framework-arduino-megaavr/variants/nona4809/
OPTIONS_FLAGS =

CC = avr-g++ $(OPTIONS_FLAGS) $(COMPILE_FLAGS) $(AVR_FLAGS) $(INCLUDE_FLAGS) $(if $(findstring lib/,$<),,$(WARNING_FLAGS))  # no extra warning flags for libraries
OBJCOPY = avr-objcopy
SIZE = avr-objdump -Pmem-usage


# ################################################################# #
# Set source code directories
# ################################################################# #
SRC_SRC = $(shell find ./src -name "*.cpp" | cut -sd / -f 2-)


# ################################################################# #
# Set libraries code directories
# ################################################################# #
# SRC_USBSerial = lib/avr-simple-usb-serial/src/usb_serial.cpp lib/avr-simple-usb-serial/src/usb_utils.cpp
SRC_LIB =  #/home/remi/.platformio/packages/framework-arduino-megaavr/cores/arduino/wiring.c


# ################################################################# #
# Group source codes by language
# ################################################################# #
SRC = $(SRC_SRC) $(SRC_LIB)
SRC_CPP = $(filter %.cpp, $(SRC))
SRC_C = $(filter %.c, $(SRC))
SRC_S = $(filter %.S, $(SRC))


# ################################################################# #
# Configure phony & default targets
# ################################################################# #
.SUFFIXES:
.PHONY: all size clean
all: $(OUTDIR)/$(TARGET).hex


# ################################################################# #
# Define object file targets, and rules by language
# ################################################################# #
OBJECTS_CPP = $(addprefix $(OUTDIR)/,$(SRC_CPP:.cpp=.o))
OBJECTS_C = $(addprefix $(OUTDIR)/,$(SRC_C:.c=.o))
OBJECTS_S = $(addprefix $(OUTDIR)/,$(SRC_S:.S=.o))
OBJECTS = $(OBJECTS_CPP) $(OBJECTS_C) $(OBJECTS_S)

$(OBJECTS_CPP): $(OUTDIR)/%.o: %.cpp
	@echo -e "$(CCPRINT)" $@ "<-" $<
	@mkdir -p $(@D)
	@$(CC) -MMD -MP -c $< -o $@
-include $(OBJECTS_CPP:.o=.d)

$(OBJECTS_C): $(OUTDIR)/%.o: %.c
	@echo -e "$(CCPRINT)" $@ "<-" $<
	@mkdir -p $(@D)
	@$(CC) -MMD -MP -c -x c $< -o $@
-include $(OBJECTS_C:.o=.d)

$(OBJECTS_S): $(OUTDIR)/%.o: %.S
	@echo -e "$(CCPRINT)" $@ "<-" $<
	@mkdir -p $(@D)
	@$(CC) -MMD -MP -c -x assembler-with-cpp $< -o $@
-include $(OBJECTS_S:.o=.d)


# ################################################################# #
# Define binary/hex targets
# ################################################################# #
$(OUTDIR)/$(TARGET).elf: $(OBJECTS)
	@echo -e "$(LDPRINT)" $@ "<-" $^
	@$(CC) $^ -o $@

$(OUTDIR)/$(TARGET).hex: $(OUTDIR)/$(TARGET).elf
	@echo -e "$(OBJCOPYPRINT)" $@ "<-" $^
	@$(OBJCOPY) -R .eeprom -O ihex $^ $@


# ################################################################# #
# Define size target
# ################################################################# #
size: $(OUTDIR)/$(TARGET).elf
	@echo -e "$(SIZEPRINT)"
	@$(SIZE) $<


# ################################################################# #
# Define cleanup target
# ################################################################# #
clean:
	@echo -e "$(CLEANPRINT) $(OUTDIR)"
	@rm -fr $(OUTDIR)
