BUILD_DATE = $(shell date +"%Y%m%d")

.PHONY: help menuconfig all romfs update app

help:
	@echo "Usage:"
	@echo "		make menuconfig"
	@echo "     make all"
	@echo "     make app"
	@echo "     make romfs"
	@echo "     make update"

menuconfig:
	@./tools/mconf ./tools/rootconf

all: app
	@./pack.sh all

app:
	@./build.sh

romfs:
	@./pack.sh romfs

update:
	@./pack.sh update

rootfs:
	@./pack.sh rootfs

clean:
	@echo "clean"
	@rm -rf build output
