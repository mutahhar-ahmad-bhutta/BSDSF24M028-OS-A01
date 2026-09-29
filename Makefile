# Top-level Makefile: passes the work to src/Makefile

all:
	$(MAKE) -C src

clean:
	$(MAKE) -C src clean

.PHONY: all clean
