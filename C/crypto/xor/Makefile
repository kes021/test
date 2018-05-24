


#C = clang-4.0
CFLAGS += -ggdb -Wall  -pedantic-errors -pedantic -MT $@ -MMD -MP -flto -O2
LDFLAGS += -ggdb -flto -O2

targets = xorcrypt xorbreak

#target-binmv-source = binmv.c bmanip.c
#target-binmv-out = binmv
#target-binmv-lib = m

#target-aescrypt-source = aescrypt.c binrep.c aes128.c
#target-aescrypt-out = aescrypt
#target-aescrypt-lib =


target-aestest-source = aestest.c binrep.c aes128.c
target-aestest-out = aestest
target-aestest-lib =

#target-xenc-source = xenc.c bmanip.c
#target-xenc-out = xenc

target-xorcrypt-source = xorcrypt.c binrep.c binmanip.c file-utils.c
target-xorcrypt-out = xorcrypt

target-xorbreak-source = xorbreak.c binrep.c binmanip.c textscore.c binrep-util.c
target-xorbreak-out = xorbreak



.PHONY: all clean zip

all: $(targets)

clean:
	$(RM) *.o *.d *.s
	$(RM) $(targets)


%.o: %.c
%.o: %.c %.d
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $<

%.d: ;


.SECONDEXPANSION:

#$(targets): $$(patsubst %.c,%.o,$$(target-$$@-source))
$(targets): $$(patsubst %.c,%.o,$(filter-out %.c, $$(target-$$@-source)))
	$(CC) $(LDFLAGS) $^ $(LOADLIBES) $(LDLIBS) -o $@

.PRECIOUS: %.d

-include $(all-source:.c=.d)
