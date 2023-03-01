import logging
from abc import ABC, abstractmethod

from Models import Compiler, Config, Benchmark, BenchmarkType
from execptions import DataCollectorException

logger = logging.getLogger("data_collector")


# def generate_
# ./master_benchmarks --benchmark_format=csv --benchmark_filter="gcc_b1_1_for_each_linear_seq" --benchmark_repetitions=3

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
        pass


def get_executor_for_type(benchmark: Benchmark) -> Executor:
    logger.info(f"Retrieving executor for benchmark ({benchmark.name}) of type: {benchmark.type.name}")

    if benchmark.type.value is BenchmarkType.DEFAULT.value:
        return DefaultExecutor()
    else:
        raise DataCollectorException(f"No executor found for type {benchmark.type.name}")
