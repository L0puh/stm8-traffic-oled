CC         = sdcc
CFLAGS     = -mstm8 --std-c99 -Isrc
LDFLAGS    = -mstm8

FLASH      = stm8flash
FLASH_OPTS = -c stlinkv2 -p stm8s003f3

SRC_DIR    = src
SRCS       = $(SRC_DIR)/main.c \
             $(SRC_DIR)/i2c.c  \
             $(SRC_DIR)/oled.c \
             $(SRC_DIR)/timer.c\
             $(SRC_DIR)/traffic.c
OBJS       = $(SRCS:.c=.rel)

TARGET     = main.ihx

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS)

$(SRC_DIR)/%.rel: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

flash: $(TARGET)
	$(FLASH) $(FLASH_OPTS) -w $(TARGET)

rebuild: clean all

clean:
	rm -f $(TARGET)
	rm -f $(OBJS)
	rm -f $(SRC_DIR)/*.lst $(SRC_DIR)/*.sym $(SRC_DIR)/*.rst
	rm -f $(SRC_DIR)/*.map $(SRC_DIR)/*.lk $(SRC_DIR)/*.asm
	rm -f $(SRC_DIR)/*.cdb $(SRC_DIR)/*.adb $(SRC_DIR)/*.mem
	rm -f $(SRC_DIR)/*.ihx

info:
	@echo "SRCS = $(SRCS)"
	@echo "OBJS = $(OBJS)"

.PHONY: all flash rebuild clean info
