import json
import os
from dataclasses import dataclass
from enum import Enum
from typing import List, Any, Dict, Optional

from dataclass_wizard import fromdict


class BenchmarkType(Enum):
    THREADS = "THREADS"
    DEFAULT = "DEFAULT"
    NUMACTL = 'NUMACTL'
    INSTRUCTIONS = 'INSTRUCTIONS'


@dataclass
class Compiler:
    name: str
    CXX_COMPILER: str
    CXX_FLAGS: str
    build_location: str
    description: Optional[str]


@dataclass
class Benchmark:
    name: str
    description: Optional[str]
    type: BenchmarkType
    regex_filter: str
    params: Optional[Dict[Any, Any]] = None


@dataclass
class SbatchConfig:
    partition: str
    time: str


@dataclass
class Config:
    output_dir: str
    benchmark_repetitions: str
    build_artifacts_dir: str
    cmake_location: str
    binary_target: str
    batch_file_location: str
    sbatch: SbatchConfig
    compiler: List[Compiler]
    benchmarks: List[Benchmark]

    @staticmethod
    def load_from_file(configuration_file: str):
        file = open(configuration_file)
        json_content = json.load(file)

        return fromdict(Config, json_content)


def get_build_artifact_folder_for_compiler(compiler: Compiler, config: Config) -> str:
    """
    Gets the build artifact location for a compiler under the given configuration
    :param compiler:
    :param config:
    :return:
    """
    return os.path.join(config.build_artifacts_dir, compiler.build_location)


def get_binary_for_compiler(compiler: Compiler, config: Config) -> str:
    """
    Gets the build artifact location for a compiler under the given configuration
    :param compiler:
    :param config:
    :return:
    """
    return os.path.join(get_build_artifact_folder_for_compiler(compiler, config), config.binary_target)
