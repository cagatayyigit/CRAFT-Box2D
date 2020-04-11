
# Takes 1 input that is the output of the simulation.
# Produces variations of it (number of object + 1)

import sys
import argparse
import json
import subprocess
import os
import glob
import copy


parser = argparse.ArgumentParser()
parser.add_argument('--path', action='store', dest='path', required=True,
                    help='Simulation\'s output JSON path.')
args = parser.parse_args()



def new_output_json(output: json, i: int):
    output = copy.deepcopy(output)
    del output["scene_states"][0]["scene"]["objects"][i]
    return output


def create_variations(output: json):
    start_scene_state = output["scene_states"][0]
    objects = start_scene_state["scene"]["objects"]
    variations = [new_output_json(output, i) for i in range(len(objects)) if objects[i]["shape"] not in ["wall", "ground"]]
    
    for i in range(len(variations)):
        output = variations[i]
        json.dump(output, open(f"{os.path.splitext(args.path)[0]}_var_{i}.json", "w"))


if __name__ == '__main__':
    create_variations(json.loads(open(args.path, "r").read()))

