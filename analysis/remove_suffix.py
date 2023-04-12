import os
from pathlib import Path
import getopt
import sys
import subprocess
from typing import List, Tuple
from fnmatch import fnmatch


target_dir = '/Users/diego/Desktop/BENCHMARK_NEBULAC_ALL_67M_WITH_BYTES'

suffix = '/manual_time'



def inplace_change(filename, old_string, new_string):
    # Safely read the input filename using 'with'
    with open(filename) as f:
        s = f.read()
        if old_string not in s:
            print('"{old_string}" not found in {filename}.'.format(**locals()))
            return

    # Safely write the changed content, if found in the file
    with open(filename, 'w') as f:
        print('Changing "{old_string}" to "{new_string}" in {filename}'.format(**locals()))
        s = s.replace(old_string, new_string)
        f.write(s)





if __name__ == '__main__':

    files_to_trigger = []

    for path, subdirs, files in os.walk(target_dir):
        for name in files:
            if fnmatch(name, '*.csv'):
                file = os.path.join(path, name)
                inplace_change(file,suffix,'')
