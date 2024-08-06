import os
import toml
import pathlib
from code_edb_gen import update_db_and_c_files


def get_root_path():
    # for use in a variety of places below
    return pathlib.Path(__file__).resolve().parent.parent.parent


def get_config(root_path):
    config = toml.load(pathlib.Path.joinpath(root_path, "build.toml"))
    repo_config = config["repo"]
    gen_config = config["gen"]

    return repo_config, gen_config


def get_database_name(root_path, repo_config, gen_config):
    # create name of database
    database_version = gen_config["database_version"]
    if database_version == "":
        database_version = repo_config["version"]

        # remove the patch version (eg v1.2.3 -> v1.2)
        database_version = os.path.splitext(database_version)[0]

    database_name = repo_config["pid"] + "-" + database_version

    return os.path.join(root_path, "database", database_name)


def has_src_file_changed(root_path, gen_config):
    # make path to folder where timestamps are kept
    timestamp_record_path = os.path.join(root_path, "build", "timestamp.toml")
    os.makedirs(os.path.dirname(timestamp_record_path), exist_ok=True)

    # timestamp file exists?
    if os.path.isfile(timestamp_record_path):
        # load previous timestamps
        prev_timestamps = toml.load(timestamp_record_path)
        build_config_prev_timestamp = prev_timestamps["build config"]
        pimage_prev_timestamp = prev_timestamps["pimage"]
        config_prev_timestamp = prev_timestamps["config"]
        fault_prev_timestamp = prev_timestamps["fault"]
    else:
        build_config_prev_timestamp = None
        pimage_prev_timestamp = None
        config_prev_timestamp = None
        fault_prev_timestamp = None

    # get new timestamps
    build_config_path = os.path.join(root_path, "build.toml")
    pimage_csv_path = os.path.join(root_path, gen_config["pimage_csv_name"] + ".csv")
    config_csv_path = os.path.join(root_path, gen_config["config_csv_name"] + ".csv")
    fault_csv_path = os.path.join(root_path, gen_config["fault_csv_name"] + ".csv")
    build_config_timestamp = os.path.getmtime(build_config_path)
    pimage_timestamp = os.path.getmtime(pimage_csv_path)
    config_timestamp = os.path.getmtime(config_csv_path)
    fault_timestamp = os.path.getmtime(fault_csv_path)

    build_config_changed = build_config_prev_timestamp != build_config_timestamp
    pimage_changed = pimage_prev_timestamp != pimage_timestamp
    config_changed = config_prev_timestamp != config_timestamp
    fault_changed = fault_prev_timestamp != fault_timestamp

    # any timestamp changed?
    if (
        (build_config_changed)
        or (pimage_changed)
        or (config_changed)
        or (fault_changed)
    ):
        new_timestamps = {
            "build config": build_config_timestamp,
            "pimage": pimage_timestamp,
            "config": config_timestamp,
            "fault": fault_timestamp,
        }

        with open(timestamp_record_path, "w+") as f:
            toml.dump(new_timestamps, f)

    return build_config_changed, (pimage_changed or config_changed or fault_changed)


def generate_version_file(root_path, repo_config, gen_config):
    # read the toml to get the version
    version = repo_config["pid"] + "-" + repo_config["version"]

    # create a file with the version defined
    with open(
        os.path.join(root_path, gen_config["code_folder"], "gen_version.c"), "w"
    ) as f:
        f.write(
            'const unsigned char __attribute__( (section( ".firmwarePN" ) ) ) version[] = "'
            + version
            + '";'
        )


def generate_files(root_path, database_path, gen_config):
    update_db_and_c_files.update_db_and_c_files(
        runningDir=root_path,
        silent=True,
        database_path=database_path,
        pimage_c_subdir=None,
        BuildConfig=True,
        skipEOL=True,
        code_folder=gen_config["code_folder"],
        pimage_name=gen_config["pimage_name"],
        config_name=gen_config["config_name"],
        faults_name=gen_config["faults_name"],
        ext_src=gen_config["ext_src"],
        ext_head=gen_config["ext_head"],
        pimage_csv_name=gen_config["pimage_csv_name"],
        config_csv_name=gen_config["config_csv_name"],
        fault_csv_name=gen_config["fault_csv_name"],
        UpdateFaults=True,
    )


def write_edb(database_path, root_path):
    # move to the database folder
    bashCommand = "cd " + str(root_path) + "/database"
    os.system(bashCommand)
    # Convert xml to edb
    bashCommand = (
        str(root_path) + "/tools/build/edb-conv " + str(database_path) + ".xml"
    )
    os.system(bashCommand)


def main():
    root_path = get_root_path()
    repo_config, gen_config = get_config(root_path)
    build_cfg_changed, csv_files_changed = has_src_file_changed(root_path, gen_config)
    if build_cfg_changed:
        generate_version_file(root_path, repo_config, gen_config)
    if build_cfg_changed or csv_files_changed:
        print("Getting database path...")
        database_path = get_database_name(root_path, repo_config, gen_config)

        print("Generating files...")
        generate_files(root_path, database_path, gen_config)

        print("Converting xml to edb...")
        write_edb(database_path, root_path)


main()
