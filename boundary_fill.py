#!/usr/bin/env python
from sys import setrecursionlimit

# Python implementation for a variation of the Boundary Filling Algorithm

# For tracking
mtrack = []

matrix1 = [ 
	[ 1, 2, 3 ],
	[ 4, 1, 6 ], 
	[ 4, 5, 1 ]
]
# Should be 2 (of 4s)

matrix2 = [ 
	[ 1, 1, 1, 2, 4 ],
	[ 5, 1, 5, 3, 1 ],
	[ 3, 4, 2, 1, 1 ] 
]
# Should be 4 (of 1s)

matrix3 = [ 
	[ 3, 3, 3, 3, 3, 1 ],
	[ 3, 4, 4, 4, 3, 4 ],
	[ 2, 4, 3, 3, 3, 4 ],
	[ 2, 4, 4, 4, 4, 4 ] 
]
# Should be 11 (of 4s)

matrix4 = [ 
	[ 1, 1, 1, 1, 1 ],
	[ 1, 1, 1, 1, 1 ],
	[ 1, 1, 0, 1, 1 ],
	[ 1, 1, 1, 1, 1 ],
	[ 1, 1, 1, 1, 1 ] 
]
# Should be 24 (of 1s)

# Chose matrix to evaluate:
matrix = matrix4

# Function for 4 connected Pixels
def boundaryFillFour(matrix, x, y, lx, ly, color):
    track = 0
    if y < ly and y >= 0:
        if x < lx and x >= 0:
            if mtrack[x][y] != 0:
                return 0 # Skip
            if matrix[x][y] == color: 
                track += 1
                mtrack[x][y] = 1 # Mark
                
                track+=boundaryFillFour(matrix, x + 1, y, lx, ly, color)
                track+=boundaryFillFour(matrix, x, y + 1, lx, ly, color)
                track+=boundaryFillFour(matrix, x - 1, y, lx, ly, color)
                track+=boundaryFillFour(matrix, x, y - 1, lx, ly, color)
    return track

# NOTE: Python's recursion capabilities are very limited.
# On a 15x15 mattrix the script gives
# "Maximum recursion depth exceeded while calling a python object"
# On the other hand, on my machine, increasing the below limit to just
# 20.000 produces a core dump/abort due to the segmentation violation
# (SIGSEGV), apparently consuming all the memory.
# My configuration:
# OSX Mojave, 24Gb of RAM.
setrecursionlimit(10000)

count = 0
max_count = 0
ly = len(matrix[0])
lx = len(matrix) 
for x in range(lx):
    mtrack.append([0] * ly)

for y in range(ly):
    for x in range(lx):
        count = boundaryFillFour(matrix, x, y, lx, ly, matrix[x][y])
        if max_count < count:
            max_count = count
print(max_count)
