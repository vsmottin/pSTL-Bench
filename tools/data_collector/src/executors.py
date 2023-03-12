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
    return os.path.join(config.output_dir, compiler.name, benchmark.type.name, f'{prefix}{benchmark.name}.csv')


def generate_error_file(benchmark: Benchmark, compiler: Compiler, config: Config, prefix="") -> str:
    return os.path.join(config.output_dir, compiler.name, benchmark.type.name, 'stderr',
                        f'{prefix}{benchmark.name}.err')


def generate_benchmark_binary_call(benchmark: Benchmark, compiler: Compiler, config: Config) -> str:
    return ' '.join([
        get_binary_for_compiler(compiler, config),
        f'--benchmark_filter="{benchmark.regex_filter}"',
        f'--benchmark_repetitions={config.benchmark_repetitions}',
        '--benchmark_format="csv"',
    ])


class Executor(ABC):

    @abstractmethod
    def get_batch_output_filename(self, benchmark: Benchmark, compiler: Compiler, config: Config) -> str:
        """
        Generates the path to the output file for `SBATCH -o `
        :param benchmark:
        :param compiler:
        :param config:
        :return:
        """
        pass

    @abstractmethod
    def get_batch_error_filename(self, benchmark: Benchmark, compiler: Compiler, config: Config) -> str:
        """
        Generates the path to the error file for `SBATCH -e `
        :param benchmark:
        :param compiler:
        :param config:
        :return:
        """
        pass

    @abstractmethod
    def generate_batch_file_content(self, benchmark: Benchmark,
                                    compiler: Compiler,
                                    config: Config,
                                    batch_output_filename: str,
                                    batch_error_filename: str) -> str:
        """
        Generates the contents of the batch file to trigger the job.
        :param batch_error_filename:
        :param benchmark:
        :param compiler:
        :param config:
        :param batch_output_filename:
        :return:
        """
        pass

    @staticmethod
    def generate_batch_file_location(benchmark: Benchmark, compiler: Compiler, config: Config) -> str:
        return os.path.join(config.batch_file_location, compiler.name, benchmark.type.name, f'job_{benchmark.name}.job')

    def execute(self, benchmark: Benchmark, compiler: Compiler, config: Config) -> None:
        """
        Executes the logic to run the given benchmark for a given compiler under the provided configuration

        :param benchmark: the benchmark to run
        :param compiler: the compiler to use
        :param config: the configuration of the benchmark

        """
        batch_output_filename = self.get_batch_output_filename(benchmark, compiler, config)
        utils.ensure_file_existence(batch_output_filename)

        logger.info(f"{compiler.name}:{benchmark.name}: Using the batch output file [{batch_output_filename}]")

        batch_error_filename = self.get_batch_error_filename(benchmark, compiler, config)
        utils.ensure_file_existence(batch_error_filename)

        logger.info(f"{compiler.name}:{benchmark.name}: Using the batch error file [{batch_error_filename}]")

        batchfile_content = self.generate_batch_file_content(benchmark,
                                                             compiler,
                                                             config,
                                                             batch_output_filename,
                                                             batch_error_filename)

        batch_file_location = Executor.generate_batch_file_location(benchmark, compiler, config)
        utils.ensure_file_existence(batch_file_location)

        with open(batch_file_location, 'w+') as f:
            f.write(batchfile_content)

        logger.info(f"{compiler.name}:{benchmark.name}: Completed benchmark {compiler.name}:{benchmark.name}")


class DefaultExecutor(Executor):

    def get_batch_output_filename(self, benchmark: Benchmark, compiler: Compiler, config: Config) -> str:
        return generate_output_file(benchmark, compiler, config)

    def get_batch_error_filename(self, benchmark: Benchmark, compiler: Compiler, config: Config) -> str:
        return generate_error_file(benchmark, compiler, config)

    def generate_batch_file_content(self, benchmark: Benchmark,
                                    compiler: Compiler,
                                    config: Config,
                                    output_filename: str,
                                    batch_error_filename: str) -> str:
        binary_call = generate_benchmark_binary_call(benchmark, compiler, config)

        file_contents = f"""#! /bin/bash
#SBATCH -p {config.sbatch.partition}
#SBATCH -N 1
#SBATCH --cpu-freq=High
#SBATCH --time={config.sbatch.time}
#SBATCH -o {output_filename}
#SBATCH -e {batch_error_filename}

{binary_call}
"""

        return file_contents


class THREADSExecutor(Executor):

    def get_batch_output_filename(self, benchmark: Benchmark, compiler: Compiler, config: Config) -> str:
        number_of_threads = benchmark.params['threads']

        return generate_output_file(benchmark, compiler, config,
                                    prefix=f"[T{number_of_threads}]_")

    def get_batch_error_filename(self, benchmark: Benchmark, compiler: Compiler, config: Config) -> str:
        number_of_threads = benchmark.params['threads']

        return generate_error_file(benchmark, compiler, config,
                                   prefix=f"[T{number_of_threads}]_")

    def generate_batch_file_content(self, benchmark: Benchmark, compiler: Compiler, config: Config,
                                    batch_output_filename: str, batch_error_filename: str) -> str:
        number_of_threads = benchmark.params['threads']

        binary_call = generate_benchmark_binary_call(benchmark, compiler, config)

        file_contents = f"""#! /bin/bash
#SBATCH -p {config.sbatch.partition}
#SBATCH -N 1
#SBATCH --cpu-freq=High
#SBATCH --time={config.sbatch.time}
#SBATCH -o {batch_output_filename}
#SBATCH -e {batch_error_filename}

export OMP_NUM_THREADS={number_of_threads}

{binary_call}
"""

        return file_contents


class NUMACTLExecutor(Executor):

    def get_batch_output_filename(self, benchmark: Benchmark, compiler: Compiler, config: Config) -> str:
        numactl_cpu_binding = benchmark.params['cpu_binding']

        return generate_output_file(benchmark, compiler, config,
                                    prefix=f"[{numactl_cpu_binding}]_")

    def get_batch_error_filename(self, benchmark: Benchmark, compiler: Compiler, config: Config) -> str:
        numactl_cpu_binding = benchmark.params['cpu_binding']

        return generate_error_file(benchmark, compiler, config,
                                   prefix=f"[{numactl_cpu_binding}]_")

    def generate_batch_file_content(self, benchmark: Benchmark,
                                    compiler: Compiler,
                                    config: Config,
                                    output_filename: str,
                                    batch_error_filename: str) -> str:
        numactl_cpu_binding = benchmark.params['cpu_binding']
        binary_call = generate_benchmark_binary_call(benchmark, compiler, config)

        file_contents = f"""#! /bin/bash
#SBATCH -p {config.sbatch.partition}
#SBATCH -N 1
#SBATCH --cpu-freq=High
#SBATCH --time={config.sbatch.time}
#SBATCH -o {output_filename}
#SBATCH -e {batch_error_filename}

numactl --physcpubind={numactl_cpu_binding} {binary_call}
        """

        return file_contents


def get_executor_for_type(benchmark: Benchmark) -> Executor:
    logger.info(f"Retrieving executor for benchmark ({benchmark.name}) of type: {benchmark.type.name}")

    if benchmark.type.value is BenchmarkType.DEFAULT.value:
        return DefaultExecutor()
    elif benchmark.type.value is BenchmarkType.NUMACTL.value:
        return NUMACTLExecutor()
    elif benchmark.type.value is BenchmarkType.THREADS.value:
        return THREADSExecutor()
    else:
        raise DataCollectorException(f"No executor found for type {benchmark.type.name}")
