add_rules("mode.debug", "mode.release")

-- 引入自定义工具链
includes("toolchains/arm-himix200-linux.lua")

target("cpu_test")
    set_kind("binary")
    add_files("src/*.c")
    -- set_toolchains("arm-himix200-linux")

