import getopt
import sys
import logging
from typing import List, Tuple

from Models import Config
from src.Building import build_artifacts

logging.basicConfig(level=logging.NOTSET)

logger = logging.getLogger("data_collector")
logger.setLevel(logging.WARNING)


def read_arguments(argv) -> Tuple[str, List[str]]:
    configuration_file = ''
    selected_compilers = ['*']

    opts, args = getopt.getopt(argv, "hc:vf", ["configuration=", "verbose", "compiler="])
    for opt, arg in opts:
        if opt == '-h':
            print('main.py -i <inputfile> -o <outputfile>')
            sys.exit()
        elif opt in ("-c", "--configuration"):
            configuration_file = arg
        elif opt in ("-v", "--verbose"):
            logger.setLevel(logging.DEBUG)
        elif opt in ("-f", "--compiler"):
            selected_compilers = arg.split(',')
        else:
            print("Wrong parameter! Could not find:", opt)
            sys.exit()
    return configuration_file, selected_compilers


def main(argv):
    configuration_file, selected_compilers = read_arguments(argv)

    logger.info(f'Configuration file using: {configuration_file}')

    configuration = Config.load_from_file(configuration_file)

    # removing compilers that should not be executed
    if selected_compilers != ['*']:
        configuration.compiler = [x for x in configuration.compiler if x.name in selected_compilers]

    # running building
    for compiler in configuration.compiler:
        build_artifacts(compiler, configuration.cmake_location)


if __name__ == "__main__":
    main(sys.argv[1:])
