import logging
import os
import subprocess
from abc import ABC, abstractmethod
from pathlib import Path
from typing import List

from Models import Compiler, Config, Benchmark, BenchmarkType, get_binary_for_compiler
from execptions import DataCollectorException

logger = logging.getLogger("data_collector")


def generate_output_file(benchmark: Benchmark, compiler: Compiler, config: Config) -> str:
    return os.path.join(config.output_dir, benchmark.type.name, f'{compiler.name}_{benchmark.name}.csv')


def generate_benchmark_binary_call(benchmark: Benchmark, compiler: Compiler, config: Config, output_file: str) -> List[
    str]:
    return [
        get_binary_for_compiler(compiler, config),
        f'--benchmark_filter={benchmark.regex_filter}',
        f'--benchmark_repetitions={config.benchmark_repetitions}',
        '--benchmark_out_format=csv',
        f'--benchmark_out={output_file}'
    ]


class Executor(ABC):

    @abstractmethod
    def execute(self, benchmark: Benchmark, compiler: Compiler, config: Config) -> None:
        """
        Executes the logic to run the given benchmark for a given compiler under the provided configuration

        :param benchmark: the benchmark to run
        :param compiler: the compiler to use
        :param config: the configuration of the benchmark

        """
        pass


class DefaultExecutor(Executor):

    def execute(self, benchmark: Benchmark, compiler: Compiler, config: Config) -> None:
        output_filename = generate_output_file(benchmark, compiler, config)
        logger.info(f"{compiler.name}:{benchmark.name}: Using the output file [{output_filename}]")

        call_args = generate_benchmark_binary_call(benchmark, compiler, config, output_filename)
        logger.debug(f"{compiler.name}:{benchmark.name}: Generated call args for benchmark: {(' '.join(call_args))}")

        # creates dirs etc if they do not exists
        output_path = Path(output_filename)
        if not os.path.exists(output_path.parent):
            os.makedirs(output_path.parent)
        output_path.touch(exist_ok=True)  # will create file, if it exists will do nothing

        process = subprocess.run(call_args)

        if process.returncode != 0:
            raise DataCollectorException(f"Error when executing the benchmark {compiler.name}:{benchmark.name}")

        logger.info(f"{compiler.name}:{benchmark.name}: Completed benchmark {compiler.name}:{benchmark.name}")


def get_executor_for_type(benchmark: Benchmark) -> Executor:
    logger.info(f"Retrieving executor for benchmark ({benchmark.name}) of type: {benchmark.type.name}")

    if benchmark.type.value is BenchmarkType.DEFAULT.value:
        return DefaultExecutor()
    else:
        raise DataCollectorException(f"No executor found for type {benchmark.type.name}")
