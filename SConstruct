#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")

# For reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

def recursive_glob(src_dir, extensions=[".cpp"]):
    source_files = []
    for root, _, files in os.walk(src_dir):
        for file in files:
            if os.path.splitext(file)[1] in extensions:
                source_files.append(os.path.join(root, file))
    return source_files

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/"])
# sources = Glob("src/*.cpp")
sources = recursive_glob("src")

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "tic_tac_toe/bin/libtic_tac_toe.{}.{}.framework/libtic_tac_toe.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
elif env["platform"] == "ios":
    if env["ios_simulator"]:
        library = env.StaticLibrary(
            "tic_tac_toe/bin/libtic_tac_toe.{}.{}.simulator.a".format(env["platform"], env["target"]),
            source=sources,
        )
    else:
        library = env.StaticLibrary(
            "tic_tac_toe/bin/libtic_tac_toe.{}.{}.a".format(env["platform"], env["target"]),
            source=sources,
        )
else:
    library = env.SharedLibrary(
        "tic_tac_toe/bin/libtic_tac_toe{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
