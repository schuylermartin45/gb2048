CC	= $(GBDK2020)/bin/lcc -Wa-l -Wl-m -Wl-j

BINS	= gb2048.gb
BIN_DIR	= bin

all:	$(BINS)

# Compile and link single file in one pass
%.gb:	%.c
	$(CC) -o $(BIN_DIR)/$@ $<

run:	gb2048.gb
	java -jar $(EMULICIOUS)/Emulicious.jar $(BIN_DIR)/gb2048.gb

clean:
	rm -f $(BIN_DIR)/*

