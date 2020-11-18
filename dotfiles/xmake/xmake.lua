add_rules("mode.debug", "mode.release")

target("xmake")
    set_kind("binary")
    add_files("src/*.c")

