#!python3
import sys
import os

directions0 = ((-1, 0), (0, 1), (1, 0), (0, -1))
directions1 = ((-1, -1), (-1, 1), (1, -1), (1, 1))
directions2 = ((-2, -1), (-2, 1), (-1, 2), (1, 2), (2, -1), (2, 1), (-1, -2), (1, -2))
directions3 = ((-3, -2), (-3, 2), (-2, 3), (2, 3), (3, -2), (3, 2), (-2, -3), (2, -3))
directions4 = ((-4, -3), (-4, -2), (-4, -1), (-4, 1), (-4, 2), (-4, 3),
               (4, -3), (4, -2), (4, -1), (4, 1), (4, 2), (4, 3),
               (-3, 4), (-2, 4), (-1, 4), (1, 4), (2, 4), (3, 4),
               (-3, -4), (-2, -4), (-1, -4), (1, -4), (2, -4), (3, -4),
               (-4, -4), (-4, 4), (4, 4), (4, -4))

def print_usage():
    print(
'''usage: python3 convert_fdf_to_lemin.py arg1
    arg1: map_name

    then enter parameters of anthill
    this script convert map fdf to lemin anthill. it create two files in folder of fdf file:
        file with z coordinate
        and file with no z
        ''')

def addlinks(links, rooms, i, j, directions):
    for r, c in directions:
        y = i + r
        x = j + c
        if 0 <= y < len(rooms) and 0 <= x < len(rooms[i]):
            try:
                room1 = min(rooms[i][j], rooms[y][x])
                room2 = max(rooms[i][j], rooms[y][x])
                links.append((room1, room2))
            except:
                pass

if len(sys.argv) < 2:
    print_usage()
    exit()

filename = sys.argv[1]

# create matrix of vertex (matrix[][]) from file
if len(sys.argv) > 0:
    with open(filename, 'r') as fd:
        matrix = []
        i = 0
        for line in fd:
            matrix.append([])
            for num in line.rstrip().split(" "):
                try:
                    matrix[i].append(int(num))
                except:
                    pass
            i += 1
print("#size map: height {} x width {}".format(len(matrix), len(matrix[0])))

number_of_ants = int(input("Enter number of ants: "))
start_room_i = int(input("Enter row of start room: "))
start_room_j = int(input("Enter col of start room: "))
end_room_i = int(input("Enter row of end room: "))
end_room_j = int(input("Enter col of end room: "))
print(
    '''type of connections:
    0 - ortogonal connections
    1 - (0) connections + start/end diagonal connections
    2 - (1) connections + start/end radius 2 connections
    3 - (2) connections + start/end radius 3 connections
    4 - (0) connections + start/wnd radius 4 connections
    5 - (0) connections + every room radius 1-4 connections'''
)
type_connections = int(input("Enter type of connections rooms (1..5): "))

# print_rooms - make list with info for printing anthill
print_rooms = []
print_rooms_no_z = []
print_rooms.append(str(number_of_ants))
print_rooms_no_z.append(str(number_of_ants))
print_rooms.append("#rooms:")
print_rooms_no_z.append("#rooms:")
room = 0 # counter of rooms
# rooms[][] - matrix of rooms, where rooms[i[j] == number of room.
rooms = []
for i in range(len(matrix)):
    rooms.append([])
    for j in range(len(matrix[i])):
        if i == start_room_i and j == start_room_j:
            print_rooms.append("##start")
            print_rooms_no_z.append("##start")
        if i == end_room_i and j == end_room_j:
            print_rooms_no_z.append("##end")
            print_rooms.append("##end")
        print_rooms_no_z.append(str(room) + " " + str(j) + " " + str(i))
        print_rooms.append(str(room) + " " + str(j) + " " + str(i) + " " + str(matrix[i][j]))
        rooms[i].append(room)
        room += 1

#base directions (ortogonal)
links = []
for i in range(len(rooms)):
    for j in range(len(rooms[i])):
        addlinks(links, rooms, i, j, directions0)

# additional links (1) (diagonal near start/end)
links1 = []
if int(type_connections) >= 1 and int(type_connections) != 4:
    addlinks(links1, rooms, start_room_i, start_room_j, directions1)
    addlinks(links1, rooms, end_room_i, end_room_j, directions1)

# additional links (2) (edges on distanse 2)
if int(type_connections) >= 2 and int(type_connections) != 4:
    addlinks(links1, rooms, start_room_i, start_room_j, directions2)
    addlinks(links1, rooms, end_room_i, end_room_j, directions2)

# additional links (3) (feel +-2 boxes with diagonal edges)
links2 = []
if int(type_connections) >= 3 and int(type_connections) != 4:
    for i in range(-2, 3):
        for j in range(-2, 3):
            s_i = start_room_i + i
            s_j = start_room_j + j
            e_i = end_room_i + i
            e_j = end_room_j + j
            addlinks(links2, rooms, s_i, s_j, directions1)
            addlinks(links2, rooms, e_i, e_j, directions1)

# add links (4) (24 edges on distanse 4)
if int(type_connections) >= 4:
    addlinks(links1, rooms, start_room_i, start_room_j, directions4)
    addlinks(links1, rooms, end_room_i, end_room_j, directions4)

if int(type_connections) >= 5:
    for i in range(len(rooms)):
        for j in range(len(rooms[i])):
            addlinks(links, rooms, i, j, directions1)
            addlinks(links, rooms, i, j, directions2)
            addlinks(links, rooms, i, j, directions3)
            addlinks(links, rooms, i, j, directions4)


# remove duplicates of links
links = set(links)
links1 = set(links1)
links2 = set(links2)

# union links
links = links.union(links1)
links = links.union(links2)

filename1 = []
filename1.append(os.path.splitext(filename)[0])
filename1.append(str(number_of_ants))
filename1.append(str(start_room_i))
filename1.append(str(start_room_j))
filename1.append(str(end_room_i))
filename1.append(str(end_room_j))
filename1.append(str(type_connections))
filename1 = "_".join(filename1)
filename_z = filename1 + "_z"
filename_no_z = filename1 + "_no_z"

with open(filename_z, "w") as fd, open(filename_no_z, "w") as fd_no_z:
    for line in print_rooms:
        fd.write(line + "\n")
    for line in print_rooms_no_z:
        fd_no_z.write(line + "\n")
    for link in links:
        fd.write("{}-{}".format(link[0], link[1]) + "\n")
        fd_no_z.write("{}-{}".format(link[0], link[1]) + "\n")
    fd.write("#size map: height {} x width {}".format(len(matrix), len(matrix[0])) + "\n")
    fd_no_z.write("#size map: height {} x width {}".format(len(matrix), len(matrix[0])) + "\n")

