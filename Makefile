# ---------- Macros (variables) ----------
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin
MANDIR = $(PREFIX)/share/man/man3

# ---------- Targets ----------
all:
	$(MAKE) -C src

# Copy the program and man pages into the system folders (needs sudo)
install:
	install -d $(BINDIR) $(MANDIR)
	install -m 755 bin/client_static $(BINDIR)/client
	install -m 644 man/man3/*.3 $(MANDIR)

# Remove everything that install copied
uninstall:
	rm -f $(BINDIR)/client
	rm -f $(MANDIR)/mystrlen.3 $(MANDIR)/mystrcpy.3 $(MANDIR)/mystrncpy.3
	rm -f $(MANDIR)/mystrcat.3 $(MANDIR)/wordCount.3 $(MANDIR)/mygrep.3

clean:
	$(MAKE) -C src clean

.PHONY: all install uninstall clean
