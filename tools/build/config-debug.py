import os
import shutil

try:
    shutil.rmtree("./build/debug")
except OSError as e:
    pass

os.makedirs("./build/debug")

os.system(
    "cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=debug -S./ -B./build/debug -GNinja"
)
