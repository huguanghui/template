
sinclude test

aabb:
	echo "hello world"

%_config:
	echo $(@:_config)

test: boards.cfg
	@echo $<
	@echo $@
	@awk '(NF && $$1 !~ /^#/) { print $$1 ": " $$1 "_config; $$(MAKE)" }' $< > $@ 
