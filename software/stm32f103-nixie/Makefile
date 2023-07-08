PROJECT = stm32f103-nixie
BUILD_DIR = bin

CFLAGS += -Wno-unused-parameter -g -O0 -DDEBUG

SHARED_DIR = ../my-common-code ../PD_Micro/src
CFILES = main.c  \
		 usart_irq_printf.c \
		 PD_UFP_Protocol.c \
		 FUSB302_UFP.c \
		 PD_UFP.c

CFILES += api.c
AFILES += api-asm.S

# TODO - you will need to edit these two lines!
DEVICE=stm32f103cb
OOCD_FILE = board/stm32f103c8_blue_pill.cfg

# You shouldn't have to edit anything below here.
VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))
OPENCM3_DIR=../libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ../rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
