# #
# make shortcut
# #
a : all
f : config

all:
	@echo "all"

config:
	@echo "config"
	#$(MAKE_UPPER) aabb.txt

# # 
# config
# #

# host
HOST :=$(if $(HOST),$(HOST),$(if ${shell uname | egrep -i linux}, linux,))
HOST :=$(if $(HOST),$(HOST),$(if ${shell uname | egrep -i darwin}, macosx,))
HOST :=$(if $(HOST),$(HOST),$(if ${shell uname | egrep -i cygwin}, cygwin,))
HOST :=$(if $(HOST),$(HOST),$(if ${shell uname | egrep -i mingw}, msys,))
HOST :=$(if $(HOST),$(HOST),$(if ${shell uname | egrep -i windows}, msys,))

# platform
PLAT :=$(if $(PLAT),$(PLAT),$(if ${shell uname | egrep -i linux}, linux,))
PLAT :=$(if $(PLAT),$(PLAT),$(if ${shell uname | egrep -i darwin}, macosx,))
PLAT :=$(if $(PLAT),$(PLAT),$(if ${shell uname | egrep -i cygwin}, cygwin,))
PLAT :=$(if $(PLAT),$(PLAT),$(if ${shell uname | egrep -i mingw}, mingw,))
PLAT :=$(if $(PLAT),$(PLAT),$(if ${shell uname | egrep -i windows}, windows,))
PLAT :=$(if $(PLAT),$(PLAT),linux)

PRO_DIR :=$(abspath .)
$(info $(PRO_DIR))

define MAKE_UPPER
${shell echo $(1) | sed "s/\(.*\)/\U\1/g"}
endef

test_upper := $(call MAKE_UPPER, test)
$(info $(test_upper))
