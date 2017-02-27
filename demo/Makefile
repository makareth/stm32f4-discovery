TARGET		= demo
BOARD		= STM32F4_Discovery

BOARD_UC	= STM32F4-Discovery
BOARD_LC   	= stm32f4_discovery
BSP_BASE	= $(BOARD_LC)

OCDFLAGS	= -f board/stm32f4discovery.cfg
GDBFLAGS	=

EXAMPLE		= Examples/GPIO/GPIO_IOToggle
	
MCU_FAMILY 	= stm32f4xx
MCU_LC     	= stm32f407xx
MCU_MC     	= STM32F407xx
MCU_UC     	= STM32F407VG

LDFILE		= STM32F407VG_FLASH.ld

#SRCS       	= main.c syscalls.c stm32f4xx_hal_msp.c console.c
SRCS       	= main.c syscalls.c usart.c console.c spi.c error.c lis3dsh.c
# stm32f4_discovery_lis302dl.c
SRCS      	+= system_$(MCU_FAMILY).c
SRCS      	+= stm32f4xx_it.c
SRCS      	+= stm32f4xx_hal_rcc.c stm32f4xx_hal_rcc_ex.c stm32f4xx_hal.c stm32f4xx_hal_cortex.c stm32f4xx_hal_gpio.c stm32f4xx_hal_spi.c stm32f4xx_hal_dma.c stm32f4xx_hal_pwr_ex.c stm32f4xx_hal_uart.c $(BSP_BASE).c


OCD_DIR    	= /usr/share/openocd/scripts

CUBE_DIR	= cube

BSP_DIR         = $(CUBE_DIR)/Drivers/BSP/$(BOARD_UC)
HAL_DIR		= $(CUBE_DIR)/Drivers/STM32F4xx_HAL_Driver
CMSIS_DIR	= $(CUBE_DIR)/Drivers/CMSIS

DEV_DIR    	= $(CMSIS_DIR)/Device/ST/STM32F4xx

CUBE_URL   	= http://www.st.com/st-web-ui/static/active/en/st_prod_software_internet/resource/technical/software/firmware/stm32cubef4.zip


######################################################################################
# GNU GCC ARM Embeded Toolchain base directories and binaries 
######################################################################################
PREFIX		= arm-none-eabi
GCC_BASE = /usr/
GCC_BIN  = $(GCC_BASE)bin/
GCC_LIB  = $(GCC_BASE)$(PREFIX)/lib/
GCC_INC  = $(GCC_BASE)$(PREFIX)/include/
AS       = $(GCC_BIN)$(PREFIX)-as
CC       = $(GCC_BIN)$(PREFIX)-gcc
CPP      = $(GCC_BIN)$(PREFIX)-g++
LD       = $(GCC_BIN)$(PREFIX)-gcc
OBJCOPY  = $(GCC_BIN)$(PREFIX)-objcopy
OBJDUMP  = $(GCC_BIN)$(PREFIX)-objdump
SIZE     = $(GCC_BIN)$(PREFIX)-size
GDB      = $(GCC_BIN)$(PREFIX)-gdb

DEFS		= -D$(MCU_MC) -DUSE_HAL_DRIVER

INCS       = -Iinc
INCS      += -I$(BSP_DIR)
INCS      += -I$(CMSIS_DIR)/Include
INCS      += -I$(DEV_DIR)/Include
INCS      += -I$(HAL_DIR)/Inc

LIBS       = -L$(CMSIS_DIR)/Lib

# Compiler flags
CFLAGS     = -Wall -g -std=gnu99 -Os
CFLAGS    += -mlittle-endian -mcpu=cortex-m4 -march=armv7e-m -mthumb
CFLAGS    += -mfpu=fpv4-sp-d16 -mfloat-abi=hard
CFLAGS    += -ffunction-sections -fdata-sections
CFLAGS    += $(INCS) $(DEFS)

LDFLAGS    =  -fno-exceptions -Wl,--gc-sections -Wl,-Map=$(TARGET).map $(LIBS) -T$(MCU_LC).ld

VPATH      = ./src
VPATH     += $(BSP_DIR)
VPATH     += $(HAL_DIR)/Src
VPATH     += $(DEV_DIR)/Source/

#scoulibaly@K93SV:~/stmf4-discovery/demo/cube/Drivers/BSP/STM32F4-Discovery

OBJS       = $(addprefix obj/,$(SRCS:.c=.o))
DEPS       = $(addprefix dep/,$(SRCS:.c=.d))

# Prettify output
V = 0
ifeq ($V, 0)
	Q = @
	P = > /dev/null
endif

.PHONY: all dirs program debug template clean

all: $(TARGET).bin

-include $(DEPS)

dirs: dep obj cube
dep obj src:
	@echo "[MKDIR]   $@"
	$Qmkdir -p $@

obj/%.o : %.c | dirs
	@echo "[CC]      $(notdir $<)"
	$Q$(CC) $(CFLAGS) -c -o $@ $< -MMD -MF dep/$(*F).d

$(TARGET).elf: $(OBJS)
	@echo "CFLAGS= $(CFLAGS)"
	@echo "[LD]      $(TARGET).elf"
	$Q$(CC) $(CFLAGS) $(LDFLAGS) src/startup_$(MCU_LC).s $^ -o $@
	@echo "[OBJDUMP] $(TARGET).lst"
	$Q$(OBJDUMP) -St $(TARGET).elf >$(TARGET).lst
	@echo "[SIZE]    $(TARGET).elf"
	$(SIZE) $(TARGET).elf

$(TARGET).bin: $(TARGET).elf
	@echo "CFLAGS= $(CFLAGS)"
	@echo "[OBJCOPY] $(TARGET).bin"
	$Q$(OBJCOPY) -O binary $< $@

openocd:
	$(OCD) -s $(OCD_DIR) $(OCDFLAGS)

program: all
	$(OCD) -s $(OCD_DIR) $(OCDFLAGS) -c "program $(TARGET).elf verify reset"

debug:
	@if ! nc -z localhost 3333; then \
		echo "\n\t[Error] OpenOCD is not running! Start it with: 'make openocd'\n"; exit 1; \
	else \
		$(GDB)  -ex "target extended localhost:3333" \
			-ex "monitor arm semihosting enable" \
			-ex "monitor reset halt" \
			-ex "load" \
			-ex "monitor reset init" \
			$(GDBFLAGS) $(TARGET).elf; \
	fi

cube:
	rm -fr $(CUBE_DIR)
	wget -O /tmp/cube.zip $(CUBE_URL)
	unzip /tmp/cube.zip
	mv STM32Cube* $(CUBE_DIR)
	chmod -R u+w $(CUBE_DIR)
	rm -f /tmp/cube.zip

template: cube src
	cp -ri $(CUBE_DIR)/Projects/$(BOARD)/$(EXAMPLE)/Src/* src
	cp -ri $(CUBE_DIR)/Projects/$(BOARD)/$(EXAMPLE)/Inc/* src
	cp -i $(DEV_DIR)/Source/Templates/gcc/startup_$(MCU_LC).s src
	cp -i $(CUBE_DIR)/Projects/$(BOARD)/$(LDFILE) $(MCU_LC).ld

clean:
	@echo "[RM]      $(TARGET).bin"; rm -f $(TARGET).bin
	@echo "[RM]      $(TARGET).elf"; rm -f $(TARGET).elf
	@echo "[RM]      $(TARGET).map"; rm -f $(TARGET).map
	@echo "[RM]      $(TARGET).lst"; rm -f $(TARGET).lst
	@echo "[RMDIR]   dep"          ; rm -fr dep
	@echo "[RMDIR]   obj"          ; rm -fr obj

flags:
	@echo "CFLAGS= $(CFLAGS)"
	@echo "DEFS= $(DEFS)"
	@echo "BSP_DIR  = $(BSP_DIR)"
	@echo "HAL_DIR  = $(HAL_DIR)"
	@echo "DEV_DIR  = $(DEV_DIR)"
	@echo "Startup = startup_$(MCU_LC).s"
