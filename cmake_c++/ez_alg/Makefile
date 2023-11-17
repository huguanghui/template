BUILD_DATE = $(shell date +"%Y%m%d")

SDK_ROOT := $(PWD)

.PHONY: help menuconfig all update app system rom configtftp config build

help:
	@echo "Usage:"
	@echo "		make menuconfig"
	@echo "     make all"

menuconfig:
	@./tools/mconf ./tools/rootconf

all:
	@echo "all"

clean:
	@echo "clean"
	@rm -rf build output
