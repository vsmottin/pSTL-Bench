import numpy as np
import os
import sys
import getopt

DEFAULT_NUMBER_OF_ENTRIES = 1_000_000
DEFAULT_MU = 1_000
DEFAULT_SIGMA = 30
DEFAULT_OUTPUT_FILE = 'output.txt'
DEFAULT_FLOATING_FORMAT = False

if __name__ == '__main__':
    mu = DEFAULT_MU
    sigma = DEFAULT_SIGMA
    nr_of_entries = DEFAULT_NUMBER_OF_ENTRIES
    output_file = DEFAULT_OUTPUT_FILE
    floating_format = DEFAULT_FLOATING_FORMAT

    opts, args = getopt.getopt(sys.argv[1:], "fhn:m:s:o", ["entries=", "mu=", "sigma=", "output="])
    for opt, arg in opts:
        if opt == "-h":
            print("random_input_numbers.py -n <nr_of_entries> -m <value_of_mu> -s <value_of_sigma> [-f]")
            sys.exit()
        elif opt in ("-n", "--entries"):
            nr_of_entries = int(arg)
        elif opt in ("-m", "--mu"):
            mu = float(arg)
        elif opt in ("-s", "--sigma"):
            sigma = float(arg)
        elif opt in ("-o", "--output"):
            output_file = arg
        elif opt == "-f":
            floating_format = True

    print("Generation parameters")
    print("Entries:", nr_of_entries)
    print("Mu", mu)
    print("Sigma", sigma)
    print("Output file", output_file)

    header = f"{nr_of_entries}"

    s = np.random.normal(mu, sigma, nr_of_entries)
    if floating_format:
        np.savetxt(output_file, s, header=header, comments="")
    else:
        np.savetxt(output_file, s, fmt="%+1i", header=header, comments="")
