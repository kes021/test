


C = gcc -c
CFLAGS = -std=c11 -O2
INCL =

LD = gcc

RM = rm -f


targets = aescrypt aestest

#target-binmv-source = binmv.c bmanip.c
#target-binmv-out = binmv
#target-binmv-lib = m

target-aescrypt-source = aescrypt.c binrep.c aes128.c
target-aescrypt-out = aescrypt
target-aescrypt-lib =


target-aestest-source = aestest.c binrep.c aes128.c
target-aestest-out = aestest
target-aestest-lib =

#target-xenc-source = xenc.c bmanip.c
#target-xenc-out = xenc






all-source = $(foreach target,$(targets),$(target-$(target)-source))

.PHONY: all clean

all: $(targets)

clean:
	$(RM) *.o *.d *.s
	$(RM) $(targets)

-include $(all-source:.c=.d)

%.d: %.c
	$(C) -MM $^ > $@

%.o: %.c %.d
	$(C) $(CFLAGS) $(addprefix -I, $(INCL)) $< -o $@

.SECONDEXPANSION:

$(targets): $$(patsubst %.c,%.o,$$(target-$$@-source))
	$(LD) $(addprefix -l, $(target-$@-lib)) $^ -o $@

