import toml
import sys

# grab the toml for version & pid information
config = toml.load("./build.toml")
repo = config["repo"]

if len(sys.argv) < 2:
    print("No valid argument for the script: can be 'project-name', 'jlink-micro', ...")
elif sys.argv[1] == "project-name":
    print(repo["project_name"])
elif sys.argv[1] == "jlink-micro":
    print(repo["jlink_micro"])
else:
    print(f"Invalid argument for the script: can be 'project-name', 'jlink-micro', ... Is {sys.argv[1]}")
    