project('tetris', 'c',
    default_options: [
        'default_library=static',
        'warning_level=2'
    ])

cc = meson.get_compiler('c')
sdl2_dep = dependency('sdl2')

sourceFiles = []
subdir('src')

executable('tetris', sourceFiles,
    dependencies: sdl2_dep,
    win_subsystem: 'windows')