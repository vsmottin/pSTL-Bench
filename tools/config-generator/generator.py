import json
import os

input_filename = 'list_of_benchmarks.txt'

with open(input_filename) as file:
    lines = [line.rstrip() for line in file if not line.startswith('#') and len(line.strip()) > 0]

output = []
for line in lines:
    output.append({
        "name": f"{line}_Default",
        "description": f"Running the {line} benchmarks without any constraints",
        "type": "DEFAULT",
        "regex_filter": f"{line}/"
    })

print(json.dumps(output))
