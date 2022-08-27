CC	= $(GBDK2020)/bin/lcc -Wa-l -Wl-m -Wl-j

BINS	= gb2048.gb

all:	$(BINS)

# Compile and link single file in one pass
%.gb:	%.c
	$(CC) -o $@ $<

run:	gb2048.gb
	java -jar $(EMULICIOUS)/Emulicious.jar ./gb2048.gb

clean:
	rm -f *.o *.lst *.map *.gb *~ *.rel *.cdb *.ihx *.lnk *.sym *.asm *.noi

