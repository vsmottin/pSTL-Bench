import json
import os

threads = [1, 2, 4, 8, 16, 32]

input_filename = 'list_of_benchmarks_strong_scaling.txt'

with open(input_filename) as file:
    lines = [line.rstrip() for line in file if not line.startswith('#') and len(line.strip()) > 0]

output = []
for line in lines:
    bench_name = line.replace('/', '_')
    for t in threads:
        output.append({
            "name": f"{bench_name}_T{t}",
            "description": f"Running the {line} benchmarks with threading constraints",
            "type": "THREADS",
            "params": {
                "threads": t,
            },
            "regex_filter": f"{line}"
        })

print(json.dumps(output))
