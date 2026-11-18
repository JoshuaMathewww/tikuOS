# make test: build and run the energy tests. make clean: delete the build.

REPO   := ../..
CC     ?= cc
CFLAGS := -Wall -Ifake -I$(REPO) -I$(REPO)/kernel

SRCS := test_energy.c host_stubs.c \
        $(REPO)/kernel/energy/tiku_energy.c \
        $(REPO)/kernel/process/tiku_process.c

test_energy: $(SRCS) $(REPO)/kernel/energy/tiku_energy.h
	$(CC) $(CFLAGS) $(SRCS) -o $@

test: test_energy
	./test_energy

clean:
	rm -f test_energy
