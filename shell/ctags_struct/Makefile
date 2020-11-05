ATM=0

V_RUN = $(V_RUN_$(V))
V_RUN_ = $(V_RUN_$(ATM))
V_RUN_0 = @echo "  RUN       $@";

units:
	$(V_RUN) \
	echo ${ZSH_VERSION+set}; \
	if test x$(VG) = x1; then \
		VALGRIND=-with-valgrind; \
  fi;    \
	if ! test x$(TRAVIS)$(APPVEYOR)$(CIRCLECI) = x; then \
		SHOW_DIFF_OUTPUT=--show-diff-output; \
	fi;      \
	builddir=$$(pwd); \
	echo $(builddir)
