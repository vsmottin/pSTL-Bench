import os
from pathlib import Path
import getopt
import sys
import subprocess
from typing import List, Tuple


def get_params_from_argv(argv) -> Tuple[str, bool]:
    target_dir = ""
    only_count = False

    opts, args = getopt.getopt(argv, "hct:", ["target-dir="])
    for opt, arg in opts:
        if opt == '-h':
            print('main.py -i <inputfile> -o <outputfile>')
            sys.exit()
        elif opt in ["-t", "--target-dir"]:
            target_dir = arg
        elif opt in ["-c"]:
            only_count = True
        else:
            print("Wrong parameter! Could not find:", opt)
            sys.exit()
    return target_dir, only_count


if __name__ == "__main__":
    target_dir, only_count = get_params_from_argv(sys.argv[1:])

    files_to_trigger = []

    for dirpath, dirnames, filenames in os.walk(target_dir):
        if not dirnames:
            if only_count:
                print(f"{dirpath} has {(len(filenames))} files")

            files_to_trigger.extend([os.path.join(dirpath, x) for x in filenames])

    print(f"Total number of batch files: {len(files_to_trigger)} ")

    if only_count:
        exit(0)

    for filename in files_to_trigger:
        args = ["sbatch", filename]
        process = subprocess.Popen(args, stdout=subprocess.STDOUT, stderr=subprocess.STDOUT)

        exitcode = process.wait()  # 0 means success

        if exitcode != 0:
            print(f"Error triggering: {(' '.join(args))}")
            exit(1)
