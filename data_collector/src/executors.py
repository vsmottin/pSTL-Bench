import logging
import os
import subprocess
from abc import ABC, abstractmethod
from pathlib import Path
from typing import List

import utils
from models import Compiler, Config, Benchmark, BenchmarkType, get_binary_for_compiler
from execptions import DataCollectorException

logger = logging.getLogger("data_collector")


def generate_output_file(benchmark: Benchmark, compiler: Compiler, config: Config, prefix="") -> str:
    return os.path.join(config.output_dir, benchmark.type.name, f'{prefix}{compiler.name}_{benchmark.name}.csv')


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
    def get_output_filename(self, benchmark: Benchmark, compiler: Compiler, config: Config) -> str:
        """
        Generate the relative filename (name of the file and the path to it)
        :param benchmark:
        :param compiler:
        :param config:
        :return:
        """
        pass

    @abstractmethod
    def generate_call_args(self, benchmark: Benchmark, compiler: Compiler, config: Config, output_filename: str) -> \
            List[str]:
        """
        Generate the process call args that are then provided to the subprocess call.
        :param benchmark:
        :param compiler:
        :param config:
        :param output_filename:
        :return:
        """
        pass

    def execute(self, benchmark: Benchmark, compiler: Compiler, config: Config) -> None:
        """
        Executes the logic to run the given benchmark for a given compiler under the provided configuration

        :param benchmark: the benchmark to run
        :param compiler: the compiler to use
        :param config: the configuration of the benchmark

        """
        output_filename = self.get_output_filename(benchmark, compiler, config)
        utils.ensure_file_existence(output_filename)

        logger.info(f"{compiler.name}:{benchmark.name}: Using the output file [{output_filename}]")

        call_args = self.generate_call_args(benchmark, compiler, config, output_filename)
        logger.debug(f"{compiler.name}:{benchmark.name}: Generated call args for benchmark: {(' '.join(call_args))}")

        process = subprocess.run(call_args)

        if process.returncode != 0:
            raise DataCollectorException(f"Error when executing the benchmark {compiler.name}:{benchmark.name}")

        logger.info(f"{compiler.name}:{benchmark.name}: Completed benchmark {compiler.name}:{benchmark.name}")


class DefaultExecutor(Executor):

    def get_output_filename(self, benchmark: Benchmark, compiler: Compiler, config: Config) -> str:
        return generate_output_file(benchmark, compiler, config)

    def generate_call_args(self, benchmark: Benchmark, compiler: Compiler, config: Config, output_filename: str) -> \
            List[str]:
        return generate_benchmark_binary_call(benchmark, compiler, config, output_filename)


class NUMACTLExecutor(Executor):

    def get_output_filename(self, benchmark: Benchmark, compiler: Compiler, config: Config) -> str:
        numactl_cpu_binding = benchmark.params['cpu_binding']

        return generate_output_file(benchmark, compiler, config,
                                    prefix=f"[{numactl_cpu_binding}]_")

    def generate_call_args(self, benchmark: Benchmark, compiler: Compiler, config: Config, output_filename: str) -> \
            List[str]:
        numactl_cpu_binding = benchmark.params['cpu_binding']
        call_args = generate_benchmark_binary_call(benchmark, compiler, config, output_filename)
        return ['numactl', f'--physcpubind={numactl_cpu_binding}'] + call_args


def get_executor_for_type(benchmark: Benchmark) -> Executor:
    logger.info(f"Retrieving executor for benchmark ({benchmark.name}) of type: {benchmark.type.name}")

    if benchmark.type.value is BenchmarkType.DEFAULT.value:
        return DefaultExecutor()
    elif benchmark.type.value is BenchmarkType.DEFAULT.value:
        return NUMACTLExecutor()
    else:
        raise DataCollectorException(f"No executor found for type {benchmark.type.name}")
