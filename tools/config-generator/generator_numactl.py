import json
import os

numa_styles = [('0,1,2,3', 'DIFF_SOCK'), ('0,4,8,12', 'SAME_SOCK')]

input_filename = 'list_of_benchmarks_numactl.txt'

with open(input_filename) as file:
    lines = [line.rstrip() for line in file if not line.startswith('#') and len(line.strip()) > 0]

output = []
for line in lines:
    for setting, name in numa_styles:
        bench_name = line.replace('/','_')
        output.append({
            "name": f"{bench_name}_{name}",
            "description": f"Running the {line} benchmarks with numactl constraints",
            "type": "NUMACTL",
            "params": {
                "cpu_binding": setting,
            },
            "regex_filter": f"{line}"
        })


print(json.dumps(output))
