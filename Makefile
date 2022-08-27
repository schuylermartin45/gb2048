CC	= $(GBDK2020)/bin/lcc -Wa-l -Wl-m -Wl-j

BIN_DIR	= bin
SRC_DIR = src
BINS	= gb2048.gb

all:	$(BINS)

# Compile and link single file in one pass
%.gb:	$(SRC_DIR)/%.c
	$(CC) -o $(BIN_DIR)/$@ $<

run:	gb2048.gb
	java -jar $(EMULICIOUS)/Emulicious.jar $(BIN_DIR)/gb2048.gb

clean:
	rm -f $(BIN_DIR)/*

