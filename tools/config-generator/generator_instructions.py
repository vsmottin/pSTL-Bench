import json
import os

input_filename = 'list_of_benchmarks_instructions.txt'

with open(input_filename) as file:
    lines = [line.rstrip() for line in file if not line.startswith('#') and len(line.strip()) > 0]

output = []
for line in lines:
    bench_name = line.replace('/','_')
    output.append({
        "name": f"{bench_name}_Instructions",
        "description": f"Running the {line} benchmarks without any constraints and collecting the instructions",
        "type": "INSTRUCTIONS",
        "regex_filter": f"{line}"
    })

print(json.dumps(output))
