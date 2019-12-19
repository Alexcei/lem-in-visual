import sys

def print_usage():
    print('''usage: python3 convert_res_noz_to_z map_with_z res_file
                map_with_z - map file of anthill, with z coord in rooms
                res_file - file with result of lem-in
            ''')

# if len(sys.argv) != 9:
#     print_usage()
#     exit()
def convert_res_noz_to_z(anthill_z, res_no_z):
    if (len(sys.argv) != 3):
        for i in sys.argv:
            print(i)
        #print(len(sys.argv))
        print_usage()
        exit()

    anthill_z = sys.argv[1]
    res_no_z = sys.argv[2]
    anthill_print = []

    with open(anthill_z, 'r') as fd:
        for line in fd:
            anthill_print.append(line)

    with open(res_no_z, 'r') as fd:
        for line in fd:
            if line[0] == "L":
                anthill_print.append(line)

    for line in anthill_print:
        print(line, end="")
