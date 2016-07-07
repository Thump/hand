############################################################################
#
# Hand makefile
# Denis McLaughlin
# February 24, 1999
#
###########################################################################

# runtime default configuration values

# the base directory for all config files
#BASE=/usr/local
BASE=.

# default location for binary
BINDIR=$(BASE)/bin

# default configuration file
CONFDIR=$(BASE)/lib/hand
CONFIG=$(CONFDIR)/hand.ini

# default log file
LOGDIR=$(BASE)/lib/hand
LOGFILE=$(LOGDIR)/hand.log

# default listen port
PORT=1499

# default verbosity level: requires DF=1 (see debug.h for values)
VL=0

# version number
VERSION="1.01"


###########################################################################

# general compile flags 'n stuff

# The compiler to use
CC=gcc

# these are for general use
CFLAGS= -Wall -O2 -DBASE=\"$(BASE)\" -DCONFIG=\"$(CONFIG)\" -DLOGFILE=\"$(LOGFILE)\" -DPORT=$(PORT) -DDF=$(DF) -DVL=$(VL) -DVERSION=\"$(VERSION)\"

LDFLAGS=

# command to generate tag files
#CTAGS=ctags -tvS
CTAGS=ctags 

# tags file
CTAGSFILE=./tags


###########################################################################

SOURCE=hand.c print.c config.c log.c socket.c

OBJ=hand.o print.o config.o log.o socket.o

AUX=$(CTAGSFILE)

BIN=hand

CLEAN=$(OBJ) $(AUX)

REALCLEAN=$(CLEAN) $(BIN)

#*******************************#

$(BIN): $(OBJ) tags
	$(CC) $(OBJ) -o $(BIN) $(LDFLAGS) 

all : $(OBJ) 
	$(CC) $(OBJ) -o $(BIN) $(LDFLAGS) 

tags: $(SRC) $(HEADERS)
	rm -f $(CTAGSFILE)
	$(CTAGS) -f $(CTAGSFILE) *.h *.c

install: $(BIN)
	install -d -m 755 -o 0 -g 0 $(BINDIR)
	install -m 755 -o 0 -g 0 hand $(BINDIR)
	install -d -m 755 -o 0 -g 0 $(CONFDIR)
	install -m 644 -o 0 -g 0 hand.ini $(CONFDIR)

uninstall: $(BIN)
	rm -f $(BINDIR)/hand
	rm -f $(CONFDIR)/hand.ini
	rm -f $(CONFDIR)/hand.log
	rmdir $(CONFDIR)

clean:
	rm -f $(CLEAN)

realclean:
	rm -f $(REALCLEAN)

%.o : %.c 
	$(CC) $(CFLAGS) -c $< -o $@
