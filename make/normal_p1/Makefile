# HOME := $(shell echo ${GSF_HOME})
# CC := $(shell echo ${GSF_CC})
# AR := $(shell echo ${GSF_AR})
# CFLAGS := $(shell echo ${GSF_CFLAGS})
# LDFLAGS := -g $(shell echo ${GSF_LDFLAGS})
HOME := $(PWD)
TARG := demo.exe

include $(HOME)/toolchains/toolchain-params.mk
#=============================================================

INCS := -I$(HOME) -Isrc -Iinc

SRCS := $(shell find src -type f -name "*.c" -o -name "*.cpp")
OBJS := $(patsubst %.c, %.o, $(SRCS))

# LIBS += -L$(HOME)/lib/$(GSF_CPU_ARCH) -lm -lpthread
LIBS += -Llib -lm -lpthread

$(TARG): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)
	# cp $(TARG) $(HOME)/bin/$(GSF_CPU_ARCH)/ -v

DEPS := $(patsubst %.o, %.d, $(OBJS))
-include $(DEPS)
.c.o:
	$(CC) $(CFLAGS) -c -MMD $< $(INCS) -o $@

.Phony: clean
clean:
	-rm $(TARG) $(OBJS) $(DEPS) src/*.bak -rf

