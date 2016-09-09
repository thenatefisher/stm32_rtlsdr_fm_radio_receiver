# enable floating point hardware
CFLAGS += -mfloat-abi=hard -mfpu=fpv5-sp-d16
CFLAGS += -DARM_MATH_CM7 -D__FPU_PRESENT
