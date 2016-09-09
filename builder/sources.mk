###################################################
# Project Source Selection
###################################################

# Project
CFLAGS_I += -I$(APP_DIR) -I$(APP_DIR)/target_config -I$(APP_DIR)/usb
APP_SRCS += $(shell find $(APP_DIR) -type f -name '*.c')

# Startup assembly file (required)
STARTUP_FILE = $(APP_DIR)/target_config/startup_stm32f746xx.s

# add link placement (aka 'scatter') file
LDFLAGS += -T$(APP_DIR)/target_config/STM32F746NGHx_FLASH.ld

# For semihosting
CFLAGS += --specs=rdimon.specs
LDFLAGS += -lrdimon

# both required; nano specs required to define _fini
CFLAGS += --specs=nosys.specs --specs=nano.specs
LDFLAGS += -lc_nano -lm

###################################################
# Resource Selection
###################################################

# rtl-sdr project
CFLAGS_I += -I$(RES_DIR)/librtlsdr
RES_SRCS += $(shell find $(RES_DIR)/librtlsdr -type f -name '*.c')

# CMSIS
CFLAGS_I += -I$(RES_DIR)/CMSIS/Device/ST/STM32F7xx/Include
CFLAGS_I += -I$(RES_DIR)/CMSIS/Include

# HAL
CFLAGS_I += -I$(RES_DIR)/STM32F7xx_HAL_Driver/Inc
RES_SRCS += $(shell find $(RES_DIR)/STM32F7xx_HAL_Driver/Src -type f -name '*.c')

# BSP
CFLAGS_I += -I$(RES_DIR)/STM32746G-BSP
RES_SRCS += $(shell find $(RES_DIR)/STM32746G-BSP -type f -name '*.c')

# USB Host
CFLAGS_I += -I$(RES_DIR)/STM32_USB_Host_Library/Core/Inc
RES_SRCS += $(shell find $(RES_DIR)/STM32_USB_Host_Library/Core/Src -type f -name '*.c')

###################################################
# Reformat source vars for directives
###################################################

# reformating OBJS arrays to not include template
# files or directory information
FILTERED_RSRCS    = $(patsubst %template.c, ,$(RES_SRCS))
ROBJ_FILES        = $(notdir $(FILTERED_RSRCS:.c=.o))
RBUILD_OBJS       = $(patsubst %.o, $(RBUILD_DIR)/%.o, $(ROBJ_FILES))

AOBJ_FILES        = $(notdir $(APP_SRCS:.c=.o))
ABUILD_OBJS       = $(patsubst %.o, $(ABUILD_DIR)/%.o, $(AOBJ_FILES))

vpath %.c $(sort $(dir $(RES_SRCS)))
vpath %.c $(sort $(dir $(APP_SRCS)))
