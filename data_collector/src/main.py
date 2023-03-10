import getopt
import sys
import logging
from typing import List, Tuple

from models import Config
from building import build_artifacts
from execptions import DataCollectorException
from executors import get_executor_for_type

logging.basicConfig(level=logging.NOTSET)

logger = logging.getLogger("data_collector")
logger.setLevel(logging.WARNING)


def read_arguments(argv) -> Tuple[str, List[str], bool]:
    configuration_file = ''
    selected_compilers = ['*']
    skipp_building = False

    opts, args = getopt.getopt(argv, "hc:vf", ["configuration=", "verbose", "compiler=", "no-build"])
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
        elif opt in "--no-build":
            skipp_building = True
        else:
            print("Wrong parameter! Could not find:", opt)
            sys.exit()
    return configuration_file, selected_compilers, skipp_building


def main(argv):
    configuration_file, selected_compilers, skipp_building = read_arguments(argv)
    no_compiler_found_message = "No compilers defined in configuration.json"

    logger.info(f'Configuration file using: {configuration_file}')

    # load the configuration
    configuration = Config.load_from_file(configuration_file)

    # removing compilers that should not be executed
    if selected_compilers != ['*']:
        no_compiler_found_message = f"No compilers names match the selection: {selected_compilers}"
        configuration.compiler = [x for x in configuration.compiler if x.name in selected_compilers]

    if len(configuration.compiler) == 0:
        logger.info(no_compiler_found_message)
        exit(0)

    # running building
    if not skipp_building:
        for compiler in configuration.compiler:
            build_artifacts(compiler, configuration)
    else:
        logger.info("Skipping building of the binaries for compilers!")

    # run the benchmarks for all the selected compilers
    for benchmark in configuration.benchmarks:
        for compiler in configuration.compiler:
            logger.info(f"Running the benchmark [{benchmark.name}] for compiler {compiler.name}")
            executor = get_executor_for_type(benchmark)
            executor.execute(benchmark, compiler, configuration)


if __name__ == "__main__":
    try:
        main(sys.argv[1:])
    except DataCollectorException as ex:
        error_msg = "Aborted due to an error"
        if ex.msg != '':
            error_msg += f": {ex.msg}"

        logger.error(error_msg)
        exit(1)
