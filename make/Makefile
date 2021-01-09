THIS_DIR=$(shell pwd)
filter-false = $(strip $(filter-out 0 off OFF false FALSE, $1))
filter-true = $(strip $(filter-out 1 on ON true TRUE, $1))

all: nvim

CMAKE_PRG ?= $(shell (command -v cmake3 || echo cmake))

BUILD_TYPE ?= $(shell (type ninja  > /dev/null 2>&1 && echo "Ninja") || \
							echo "Unix Makefiles"	) 
DEPS_BUILD_DIR ?= .deps
ifneq (1, $(words [$(DEPS_BUILD_DIR)]))
	$(error DEPS_BUILD_DIR  must not contain whitespace)
endif

ifeq (,$(BUILD_TOOL))
	ifeq (Ninja,$(BUILD_TYPE))
		ifneq ($(shell $(CMAKE_PRG) --help 2>/dev/null | grep Ninja),)
			BUILD_TOOL := ninja	
		else
			BUILD_TOOL = $(MAKE)
			BUILD_TYPE := Unix Makefiles
		endif
	else
		BUILD_TOOL = $(MAKE)
	endif
endif

BUILD_CMD = $(BUILD_TOOL)

USE_BUNDLED=
aa=$(call filter-true, $(USE_BUNDLED))

$(info CMAKE_PRG is $(CMAKE_PRG))
$(info BUILD_TYPE is $(BUILD_TYPE))
$(info BUILD_TOOL is $(BUILD_TOOL))

nvim: build/.ran-cmake deps
	@echo "nvim $@"
	@echo "nvim $<"
	@echo "aa: $(aa)"

build/.ran-cmake: | deps
	@echo $@

deps: | build/.ran-third-party-cmake
ifeq ($(call filter-true, $(USE_BUNDLED)),)
	@echo $@
endif

ifeq ($(call filter-true, $(USE_BUNDLED)),)
$(DEPS_BUILD_DIR):
	# mkdir -p "$@"
	echo "DIR $@"

build/.ran-third-party-cmake:: $(DEPS_BUILD_DIR)
	@echo "AA: $@"
endif

build/.ran-third-party-cmake::
	@echo "BB: $@"

abc:
	@echo $@
