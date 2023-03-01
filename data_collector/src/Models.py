import json
from dataclasses import dataclass, field
from typing import List

from dataclass_wizard import fromdict


@dataclass
class Compiler:
    name: str
    CXX_COMPILER: str
    CXX_FLAGS: str
    build_location: str
    description: str


@dataclass
class Config:
    output_dir: str
    benchmark_repetitions: str
    cmake_location: str
    compiler: List['Compiler']

    @staticmethod
    def load_from_file(configuration_file: str):
        file = open(configuration_file)
        json_content = json.load(file)

        return fromdict(Config, json_content)
