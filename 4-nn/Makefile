testName=nn
$(if $(testName),,$(error 'testName' must be defined before Makefile.simple is used))
CILPATH=../../obliv-c
REMOTE_HOST=localhost
CFLAGS=-DREMOTE_HOST=$(REMOTE_HOST) -O3
./a.out: $(testName).oc $(testName).c ../../obliv-c/test/oblivc/common/util.c $(CILPATH)/_build/libobliv.a
	$(CILPATH)/bin/oblivcc $(CFLAGS) -I . $(testName).oc $(testName).c ../../obliv-c/test/oblivc/common/util.c
clean:
	rm -f a.out
