project('GamifyLife',
        ['cpp', 'c'],
        default_options : [
            'warning_level=3',
            'cpp_std=c++20'
        ],
)

incdirs = [
    include_directories('include'),
]

yaml = dependency('yaml-cpp')
curses = dependency('notcurses', required: true)
glm = dependency('glm', fallback : ['glm', 'glm_dep'], version: ['>=0.9.9.8'])

project_root = meson.current_source_dir()

py = import('python').find_installation('python3')
run_command(py, 'scripts/generate_meson_files.py', 'src', check: true)

src = []
subdir('src')

exe = executable(
    'GamifyLife',
    sources: src,
    dependencies: [
        yaml,
        curses,
        glm,
    ],
    include_directories: incdirs,
    install : true,
)