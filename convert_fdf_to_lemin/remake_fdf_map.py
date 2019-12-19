import sys
# print("hello world!")
if len(sys.argv) > 0:
    # print(sys.argv[1])
    with open(sys.argv[1], 'r') as fd:
        matrix = []
        i = 0
        for line in fd:
            print(line)
            matrix.append([])
            for num in line.split(" "):
                matrix[i].append(int(num))
            i += 1

# print(matrix)

print("#rooms:")
room = 0
rooms = []
for i in range(len(matrix)):
    rooms.append([])
    for j in range(len(matrix[i])):
        print(room, " ", i, " ", j, " ", matrix[i][j])
        rooms[i].append(room)
        room += 1

directions0 = ((-1, 0), (0, 1), (1, 0), (0, -1))

links = []
for i in range(len(rooms)):
    for j in range(len(rooms[i])):
        for r, c in directions0:
            y = i + r
            x = j + c
            if 0 <= y < len(rooms) and 0 <= x < len(rooms[i]):
                room1 = min(rooms[i][j], rooms[y][x])
                room2 = max(rooms[i][j], rooms[y][x])
                links.append((room1, room2))
links = set(links)
# print(rooms)
# print(links)

for link in links:
    print("{}-{}".format(link[0], link[1]))
