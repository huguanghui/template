add_rules("mode.debug", "mode.release")

-- 引入自定义工具链
includes("toolchains/*.lua")

option("nng_sdk")
   set_default("$(projectdir)/third_part/nng")
   set_showmenu(true)
   set_description("NNG SDK")

includes("demo")
