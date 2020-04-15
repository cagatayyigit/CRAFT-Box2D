
# Takes 1 input that is the output of the simulation.
# Produces variations of it (number of object + 1)

import sys
import argparse
import json
import subprocess
import os
import glob
import copy
from autorun import run_simulation

parser = argparse.ArgumentParser()
parser.add_argument('--path', action='store', dest='path', required=True,
                    help='Simulation\'s output JSON path.')
parser.add_argument('--controller-path', action='store', dest='controller_path', required=True,
                    help='Simulation\'s controller JSON path.') 
parser.add_argument('--executable-path', action='store', dest='exec_path', required=True,
                    help='Testbed executable path.')
args = parser.parse_args()



def new_output_json(output: json, i: int):
    output = copy.deepcopy(output)
    del output["scene_states"][0]["scene"]["objects"][i]
    return output


def create_variations(controller: json, output: json) -> list:
    start_scene_state = output["scene_states"][0]
    objects = start_scene_state["scene"]["objects"]
    variations = [new_output_json(output, i) for i in range(len(objects)) if objects[i]["shape"] not in ["wall","wall_r", "wall_l", "ground"]]
    controller_paths = []
    for i in range(len(variations)):
        output = variations[i]
        name = f"{os.path.splitext(args.path)[0]}_var_{i}"
        json.dump(output, open(f"{name}.json", "w"))
        controller_paths.append(create_controller_variations(controller, name))
        
        return controller_paths



def create_controller_variations(controller: json, name: str) -> str:
    controller = copy.deepcopy(controller)
    controller["outputVideoPath"] = f"{name}_out.mpg"
    controller["outputJSONPath"] =  f"{name}_out.json"
    controller["inputScenePath"] = f"{name}.json" 

    name = f"{name}_controller.json"
    json.dump(controller, open(name, "w"))
    return name


if __name__ == '__main__':
    controller_paths = create_variations(json.load(open(args.controller_path, "r")), json.load(open(args.path, "r")))
    for c in controller_paths:
        run_simulation(args.exec_path, c)
