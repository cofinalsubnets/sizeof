BINNAME = sizeof
HEADER = $(BINNAME)types.h
CC = gcc
CCFLAGS = -Os -s -D HEADER=\"$(HEADER)\"
PREFIX = /usr/local

$(BINNAME): $(BINNAME).c $(HEADER)
	@$(CC) $(CCFLAGS) -o $(BINNAME) $<

$(HEADER): types
	@echo "const struct sizeentry sizes[] = {" > $@
	@cat $< | sed -ne '/[^ ]/ {s/.*/  {"&", sizeof(&)},/p}' >> $@
	@echo "};" >> $@

install: $(BINNAME)
	@mv $(BINNAME) $(PREFIX)/bin

clean:
	@rm -f $(HEADER)

.PHONY: install clean
