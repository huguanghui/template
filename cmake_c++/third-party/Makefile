THIS_DIR = $(shell pwd)

DEPS_BUILD_DIR ?= .dep

CMAKE_PRG ?= $(shell (command -v cmake3 || echo cmake))
BUILD_CMD := make

all: deps
	@echo "hello"

# 测试 $(BUILD_CMD) -C $(DEPS_BUILD_DIR)
deps: | build/.ran-third-party-cmake
	@echo "aabb"

$(DEPS_BUILD_DIR):
	mkdir -p "$@"

# cd $(DEPS_BUILD_DIR) && $(CMAKE_PRG) -G $(THIS_DIR)/third-party
build/.ran-third-party-cmake:: $(DEPS_BUILD_DIR)
	@echo "DEPS_BUILD_DIR"

build/.ran-third-party-cmake::
	mkdir -p build
	touch $@

clean:
	@echo "clean..."

distclean:
	rm -rf ${DEPS_BUILD_DIR} build
	$(MAKE) clean
