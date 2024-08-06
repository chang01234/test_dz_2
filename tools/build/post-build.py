import os
import sys
import toml
from pathlib import Path
import shutil


def parse_inputs():
    # expected arguments:
    # 0: file path
    # 1: build output directory
    # 2: compiler tools path + one level
    # 3: workspace path
    build_output_path = Path(sys.argv[1]).resolve()
    ide_path = Path(sys.argv[2]).parent
    workspace_path = Path(sys.argv[3]).resolve()
    return build_output_path, ide_path, workspace_path


# make paths to various tools
def get_tool_paths(ide_path, workspace_path):
    compiler_tools_path = ide_path.joinpath("ide", "tools", "bin")
    proj_tools_path = Path(workspace_path).joinpath("tools", "build")
    return compiler_tools_path, proj_tools_path


# make paths to various build artifacts
def get_artifact_paths(workspace_path, build_output_path, proj_tools_path):
    # grab the toml for version & pid information
    config = toml.load(Path.joinpath(workspace_path, "build.toml"))
    repo = config["repo"]

    # prepare build artifact paths
    build_artifact_path = Path(build_output_path).joinpath(
        repo["project_name"] + ".elf"
    )
    app_name = Path(repo["pid"] + "-" + repo["version"] + "-" + repo["suffix"] + ".s19")
    app_path = build_output_path.joinpath(app_name)
    boot_name = Path(repo["boot_pid"] + "-" + repo["boot_version"] + ".s19")
    boot_path = proj_tools_path.joinpath(boot_name)
    app_wBoot_name = Path(str(app_name.with_suffix("")) + "_wBoot_" + str(boot_name))
    app_wBoot_path = build_output_path.joinpath(app_wBoot_name)
    image_cfg_path = proj_tools_path.joinpath(
        repo["pid"] + "_wBoot_" + repo["boot_pid"] + ".cfg"
    )

    return build_artifact_path, app_path, boot_path, app_wBoot_path, image_cfg_path


# print size statistics
def print_size_stats(compiler_tools_path, build_artifact_path):
    print_size_cmd = ["arm-none-eabi-size"]
    print_size_cmd.append(str(build_artifact_path))
    os.system(" ".join(print_size_cmd))


# make an s19 mapped directly to runtime memory
def make_runtime_s19(compiler_tools_path, app_path, build_artifact_path):
    s19_runtime_path = Path(str(app_path.with_suffix("")) + "-runtime.s19")
    make_runtime_cmd = ["arm-none-eabi-objcopy"]
    make_runtime_cmd.extend(
        ["-O", "srec", str(build_artifact_path), str(s19_runtime_path)]
    )
    os.system(" ".join(make_runtime_cmd))


# make a copy of the s19 for field flashing
def make_field_s19(workspace_path, app_path):
    # grab the toml to get the offset that will need to be applied to the s19
    config = toml.load(Path.joinpath(workspace_path, "build.toml"))
    repo = config["repo"]
    memory = config["memory"]
    offset = memory["field_flashing_app_start_addr"] - memory["app_start_addr"]

    s19_runtime_path = Path(str(app_path.with_suffix("")) + "-runtime.s19")
    s19_fieldflashing_path = Path(str(app_path.with_suffix("")) + ".s19")

    make_field_s19_command = ["srec_cat"]
    make_field_s19_command.extend(
        [
            "-execution_start_address",
            "0",
            "-disable",
            "data-count",
            "-address-length",
            "3",
        ]
    )
    # set the header to pid-version-suffix
    make_field_s19_command.extend(
        ["-header", repo["pid"] + "-" + repo["version"] + "-" + repo["suffix"]]
    )
    # add the input file with its offset filter
    make_field_s19_command.extend([str(s19_runtime_path), "-offset", str(offset)])
    # add the output file
    make_field_s19_command.extend(["-O", str(s19_fieldflashing_path)])

    print(" ".join(make_field_s19_command))
    os.system(" ".join(make_field_s19_command))


# combine the s/w and bootloader into a single s19
def make_combined_s19(proj_tools_path, boot_path, app_path, app_wBoot_path):
    s19_with_boot_cmd = ["srec_cat"]
    s19_with_boot_cmd.append(str(boot_path))
    s19_with_boot_cmd.append(str(app_path.with_suffix("")) + "-runtime.s19")
    s19_with_boot_cmd.append("-O")
    s19_with_boot_cmd.append(str(app_wBoot_path))
    os.system(" ".join(s19_with_boot_cmd))


# create sap file from combined s19
def make_sap(image_cfg_path, app_wBoot_path):
    # set up the sap image creation config file
    cfg_dest = str(app_wBoot_path.with_suffix("")) + "_Image.cfg"
    shutil.copyfile(image_cfg_path, cfg_dest)

    with open(cfg_dest, "w") as outfile, open(image_cfg_path, "r") as infile:
        for line in infile:
            new_line = line.replace(
                "%APP_WITH_BOOT_PATH%", str(app_wBoot_path.with_suffix(""))
            )
            new_line = new_line.replace(
                "%IMAGE_NAME%", str(app_wBoot_path.with_suffix("").name)
            )
            outfile.write(new_line)

    # create sap image using cyclone tool
    img_cmd = [
        "C:\PEMicro\cyclone\imageCreation\ImageCreationSupportFiles\csapacmpz.exe"
    ]
    img_cmd.extend(["!", cfg_dest])
    img_cmd.extend(["imagefile", str(app_wBoot_path.with_suffix(".sap"))])
    img_cmd.extend(["imagecontent", str(app_wBoot_path)])
    os.system(" ".join(img_cmd))


def main():
    # build up a series of paths
    build_output_path, ide_path, workspace_path = parse_inputs()
    compiler_tools_path, proj_tools_path = get_tool_paths(ide_path, workspace_path)
    (
        build_artifact_path,
        app_path,
        boot_path,
        app_wBoot_path,
        image_cfg_path,
    ) = get_artifact_paths(workspace_path, build_output_path, proj_tools_path)

    # make all the output files
    print_size_stats(compiler_tools_path, build_artifact_path)
    make_runtime_s19(compiler_tools_path, app_path, build_artifact_path)
    make_field_s19(workspace_path, app_path)
    make_combined_s19(proj_tools_path, boot_path, app_path, app_wBoot_path)

    # SAP file generation is currently not supported on Linux by PEMicro: https://www.pemicro.com/blog/index.cfm?post_id=253
    # make_sap(image_cfg_path, app_wBoot_path)

    # for a bit of visual space before the next output
    print("")


main()
