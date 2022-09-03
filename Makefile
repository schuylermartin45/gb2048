CFLAGS	= -Wa-l -Wl-m -Wl-j
CC	= $(GBDK2020)/bin/lcc $(CFLAGS) 

BIN	= bin/
SRC	= src/
BINS	= $(BIN)gb2048.gb

SRCS	= $(wildcard $(SRC)*.c) 
OBJS	= $(patsubst %.c,$(BIN)%.o,$(notdir $(SRCS)))

all:	$(OBJS) $(BINS)

$(BIN)%.o:	$(SRC)%.c
	$(CC) -c -o $@ $<

$(BIN)%.s:	$(SRC)%.c
	$(CC) -S -o $@ $<

$(BIN)%.o:	$(SRC)%.s
	$(CC) -c -o $@ $<

$(BIN)%.gb: $(OBJS)	
	$(CC) -o $@ $(OBJS)

run:	all
	java -jar $(EMULICIOUS)/Emulicious.jar $(BINS)

clean:
	rm -f $(BIN)*
 