import json
from dataclasses import dataclass
from enum import Enum
from typing import List, Any, Dict, Optional

from dataclass_wizard import fromdict


class BenchmarkType(Enum):
    DEFAULT = "DEFAULT"
    NUMACTL = 'NUMACTL'


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
class Config:
    output_dir: str
    benchmark_repetitions: str
    cmake_location: str
    compiler: List['Compiler']
    benchmarks: List['Benchmark']

    @staticmethod
    def load_from_file(configuration_file: str):
        file = open(configuration_file)
        json_content = json.load(file)

        return fromdict(Config, json_content)
