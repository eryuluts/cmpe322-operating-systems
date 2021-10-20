build-dir = $(CURDIR)/build
CC = cl
ALG ?= PP_FCFS
export ALG CC

all:
	$(MAKE) -C $(build-dir) SRCDIR=$(CURDIR) driver.exe

clean:
	$(MAKE) -C $(build-dir) clean
