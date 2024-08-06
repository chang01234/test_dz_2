# script to build an MCUExpresso project from the command line

import os
import sys
import pathlib

# path to GNU tools and compiler: arm-none-eabi-gcc.exe, ....
IDE_VERSION = "MCUXpressoIDE_11.6.1_8255"
IDE_PATH = os.path.join("C:", os.sep, "nxp", IDE_VERSION)
TOOLCHAIN_PATH = os.path.join(IDE_PATH, "ide", "tools", "bin")
IDE = os.path.join(IDE_PATH, "ide", "mcuxpressoidec.exe")
PROJECT_NAME = "sw0000_folder_template/release"

# workspace to use
WORKSPACE = os.path.join(
    "C:", os.sep, "Users", os.getlogin(), "Documents", IDE_VERSION, "tmp", "workspace"
)

print("Extending PATH if not already present")
sys.path.append(TOOLCHAIN_PATH)

# build the command with desired args
cmd = [IDE]
cmd.append("-nosplash")
cmd.append("--launcher.suppressErrors")
cmd.append("-application org.eclipse.cdt.managedbuilder.core.headlessbuild")
cmd.extend(["-data", WORKSPACE])
cmd.extend(["-import", str(pathlib.Path(__file__).parent.parent.parent.resolve())])

if len(sys.argv) > 1:
    arg = sys.argv[1]
else:
    arg = None

# run mcuexpresso builder
if arg == "clean":
    print("Clean build...")
    cmd.append("-cleanBuild")
else:
    print("Incremental build...")
    cmd.append("-build")

cmd.append(PROJECT_NAME)
os.system(" ".join(cmd))
