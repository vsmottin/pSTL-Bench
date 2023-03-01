import logging
import subprocess
from typing import List

from Models import Compiler

logger = logging.getLogger("data_collector")

ARTIFACTS_FOLDER = 'build-artifacts'
BINARY_TARGET = 'master_benchmarks'


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


def build_artifacts(compiler: Compiler, cmake_location: str) -> None:
    logger.info(f"Building artifacts for compiler: {compiler.name}")

    generate_ninja_cmake(cmake_location, compiler)

    build_binary(compiler)


def build_binary(compiler) -> None:
    """
    Generate the binary using all the cmake configs
    :param compiler:
    :return:
    """
    logger.info("Starting binary build")
    binary_build_args = ['cmake',
                         '--build', f'./{ARTIFACTS_FOLDER}/{compiler.build_location}',
                         '--target', BINARY_TARGET,
                         '-j', '8'
                         ]

    start_subprocess_and_log(binary_build_args, prefix=f"{compiler.name}-binary_build",
                             error_msg=f"Could not build binary for: {compiler.name}")
    logger.info("Successfully completed binary build")


def generate_ninja_cmake(cmake_location, compiler) -> None:
    """
    Runs the command to convert the cmake file into a ninja build process
    :param cmake_location:
    :param compiler:
    :return:
    """
    logger.info("Starting cmake ninja build")
    cmake_ninja_build_args = ['cmake',
                              '-DCMAKE_MAKE_PROGRAM=ninja',
                              f'-DCMAKE_CXX_COMPILER={compiler.CXX_COMPILER}',
                              '-G', 'Ninja',
                              f'-DBENCHMARK_PREFIX={compiler.name}',
                              # f'-DCMAKE_CXX_FLAGS="{compiler.CXX_FLAGS}"',
                              '-S', cmake_location,
                              '-B', f'./{ARTIFACTS_FOLDER}/{compiler.build_location}'
                              ]
    start_subprocess_and_log(cmake_ninja_build_args, prefix=f"{compiler.name}-cmake-ninja",
                             error_msg=f"Could not build: {compiler.name}")
    logger.info("Successfully completed cmake ninja build")
