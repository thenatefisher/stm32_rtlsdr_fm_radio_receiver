###################################################
# Build Options
###################################################

# select architecture
ARCH 	+= -mcpu=cortex-m7 -mthumb
ASFLAGS += $(ARCH)
CFLAGS  += $(ARCH)

# compile using c11, all warnings, output listing
C_APP_FLAGS += -std=c11
C_APP_FLAGS += -Wall -Wextra
C_APP_FLAGS += -Wa,-ashld=$(LST_DIR)/$(@F:.o=.lst)

# ST HAL settings
CFLAGS += -DSTM32F746xx
CFLAGS += -DUSE_HAL_DRIVER
CFLAGS += -DUSE_USB_HS

# enable link time optimization
# and compile time optimizations
# CFLAGS += -flto # TODO: fix this- currently invokes hardfault on reset
CFLAGS += -O3
CFLAGS += -g

# we are using custom startup file
CFLAGS += -nostartfiles

# break individual compilation units out into
# data and function sections, then eliminate unused
# sections in linker phase
CFLAGS  += -fdata-sections -ffunction-sections
LDFLAGS += -Wl,--gc-sections

# generate a map file
LDFLAGS += -Wl,-Map=$(ANA_DIR)/$(BIN_NAME).map

include builder/opts/fpu_hard.mk
