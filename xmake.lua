add_rules("mode.debug", "mode.release")

add_requires("libsdl 2.26.*")

target("tetris")
    set_kind("binary")
    add_headerfiles("src/*.h")
    add_files("src/*.c")
    add_packages("libsdl")
