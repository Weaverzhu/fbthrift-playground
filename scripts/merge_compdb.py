import json
import os

DB_NAME = "compile_commands.json"

cwd = os.path.dirname(os.path.abspath(__file__)) + "/.."
build_dirs = [f for f in os.listdir(cwd) if os.path.isdir(f) and DB_NAME in os.listdir(f)]

print(build_dirs)
input("continue?")

content = []

for d in build_dirs:
    with open(os.path.join(d, DB_NAME)) as f:
        content += json.load(f)
    
    
with open(os.path.join(cwd, DB_NAME), "w") as f:
    json.dump(content, f)