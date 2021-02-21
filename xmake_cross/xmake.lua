add_rules("mode.debug", "mode.release")
set_policy("check.auto_ignore_flags", false)

-- 引入自定义工具链
includes("toolchains/*.lua")

option("build_type")
    set_default("3516DV300")
    set_showmenu(true)
    set_description("set build system type")
    set_values("3516DV300", "3516EV200")
option_end()

option("nng_sdk")
   set_default("$(projectdir)/third_part/nng")
   set_showmenu(true)
   set_description("NNG SDK")
option_end()

option("sdk_3516dv300")
   set_default("$(projectdir)/mpp/3516dv300")
   set_showmenu(true)
   set_description("3516DV300 SDK")
option_end()

option("sdk_3516ev200")
   set_default("$(projectdir)/mpp/3516ev200")
   set_showmenu(true)
   set_description("3516EV200 SDK")
option_end()

-- if is_config("build_type", "3516DV300") then
--    set_toolchains("arm-himix200-linux")
--    includes("mpp")
--    includes("src")
--end
--
--if is_config("build_type", "3516EV200") then
--    set_toolchains("arm-himix100-linux")
--    set_targetdir("$(projectdir)/build/$(build_type)/$(mode)")
--   includes("codec")
-- end
includes("src")
