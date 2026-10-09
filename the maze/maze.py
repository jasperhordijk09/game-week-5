from random import shuffle
import matplotlib.pyplot as pyplot

# Symbolische constanten
UNVISITED = 0
NORTH = 1
EAST = 2
SOUTH = 4
WEST = 8

WIDTH = 11
HEIGHT = 11

directions = [NORTH, EAST, SOUTH, WEST]

# Geeft nieuwe coördinaten en True terug als het hokje binnen het raster ligt en nog onbezocht is, anders False
def try_direction(x, y, direction):
    if direction == NORTH:
        y = y + 1
    elif direction == EAST:
        x = x + 1
    elif direction == SOUTH:
        y = y - 1
    elif direction == WEST:
        x = x - 1
    return x, y, x != -1 and x != WIDTH and y != -1 and y != HEIGHT and maze[y][x] == UNVISITED

# Kijkt vanaf de opgegeven coördinaten welke richtingen nog kunnen en zet een stap in al die richtingen
def tunnel(x, y):
    shuffle(directions) # Maak de volgorde willekeurig
    for direction in directions: # Probeer ze een voor een
        xn, yn, ok = try_direction(x, y, direction)
        if ok: # Als een richting kan,
            maze[y][x] += direction # maak dan een opening in die richting
            if direction == NORTH:
                maze[yn][xn] += SOUTH # en een opening in het naburige hokje
            elif direction == EAST:
                maze[yn][xn] += WEST
            elif direction == SOUTH:
                maze[yn][xn] += NORTH
            elif direction == WEST:
                maze[yn][xn] += EAST
            tunnel(xn, yn)
      
maze = []
for i in range(HEIGHT):
    maze.append([UNVISITED] * WIDTH) # Maak een raster volledig gevuld met UNVISITED
tunnel(HEIGHT // 2, WIDTH // 2) # Begin (ongeveer) in het midden met graven

# Schrijf doolhof naar binair bestand
file = open('maze.bin', 'wb')
file.write(bytearray([WIDTH, HEIGHT]))
for row in maze:
    file.write(bytearray(row))
file.close()

# Toon doolhof op scherm
data = [(WIDTH, 0, 0), (0, 0, HEIGHT), '-k', 0.5, 0.5, 'og', WIDTH - 0.5, HEIGHT - 0.5, 'or'] # Lijnen voor de rand en stippen voor start en finish
for y, row in enumerate(maze):
    for x, cell in enumerate(row):
        if cell & EAST == 0:
            data.extend([(x + 1, x + 1), (y, y + 1), '-k'])
        if cell & NORTH == 0:
            data.extend([(x, x + 1), (y + 1, y + 1), '-k'])
pyplot.figure(figsize = (8, 8)) # grootte in inches, 11x16 is ongeveer A3
pyplot.plot(*data)
pyplot.xticks([]) # geen merktekens aan de assen
pyplot.yticks([])
pyplot.tight_layout() # smalle kantlijnen
pyplot.savefig("maze.pdf", format = "pdf")
pyplot.show()
