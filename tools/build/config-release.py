import os
import shutil

try:
    shutil.rmtree("./build/release")
except OSError as e:
    pass

os.makedirs("./build/release")

os.system(
    "cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=release -S./ -B./build/release -GNinja"
)
