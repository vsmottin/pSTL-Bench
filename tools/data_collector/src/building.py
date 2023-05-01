import logging
import subprocess
from typing import List

from models import Compiler, Config, get_build_artifact_folder_for_compiler

logger = logging.getLogger("data_collector")


def log_subprocess_output(pipe, prefix='') -> None:
    for line in iter(pipe.readline, b''):  # b'\n'-separated lines
        logger.info(f'{prefix} %r', line)


def start_subprocess_and_log(args: List[str], prefix: str = "",
                             error_msg: str = "Error when calling a subprocess") -> None:
    process = subprocess.Popen(args, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)

    with process.stdout:
        log_subprocess_output(process.stdout, prefix)
    exitcode = process.wait()  # 0 means success

    if exitcode != 0:
        logger.critical(error_msg)
        exit(1)


def build_artifacts(compiler: Compiler, configuration: Config) -> None:
    logger.info(f"Building artifacts for compiler: {compiler.name}")

    generate_ninja_cmake(compiler, configuration)

    build_binary(compiler, configuration)


def build_binary(compiler: Compiler, configuration: Config) -> None:
    """
    Generate the binary using all the cmake configs
    :param configuration:
    :param compiler:
    :return:
    """
    logger.info("Starting binary build")
    build_artifact_folder = get_build_artifact_folder_for_compiler(compiler, configuration)

    logger.info(f"Binary build location: {build_artifact_folder}")

    binary_build_args = ['cmake',
                         '--build', build_artifact_folder,
                         '--target', configuration.binary_target,
                         ]

    start_subprocess_and_log(binary_build_args, prefix=f"{compiler.name}-binary_build",
                             error_msg=f"Could not build binary for: {compiler.name}")
    logger.info("Successfully completed binary build")


def generate_ninja_cmake(compiler: Compiler, configuration: Config) -> None:
    """
    Runs the command to convert the cmake file into a ninja build process
    :param configuration:
    :param compiler:
    :return:
    """
    logger.info("Starting cmake ninja build")

    cmake_ninja_build_args = ['cmake',
                              '-DCMAKE_MAKE_PROGRAM=ninja',
                              f'-DCMAKE_CXX_COMPILER={compiler.CXX_COMPILER}',
                              '-G', 'Ninja',
                              f'{" ".join(compiler.CMAKE_OPTIONS if compiler.CMAKE_OPTIONS else [])}',
                              '-DCMAKE_BUILD_TYPE=Release',
                              f'-DBENCHMARK_PREFIX={compiler.name}',
                              f'-DCMAKE_CXX_FLAGS="{compiler.CXX_FLAGS}"',
                              '-S', configuration.cmake_location,
                              '-B', get_build_artifact_folder_for_compiler(compiler, configuration)
                              ]

    logger.debug(f"Using the cmake ninja command: {(' '.join(cmake_ninja_build_args))}")

    start_subprocess_and_log(cmake_ninja_build_args, prefix=f"{compiler.name}-cmake-ninja",
                             error_msg=f"Could not build: {compiler.name}")

    logger.info("Successfully completed cmake ninja build")
