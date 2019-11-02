#include <stdio.h>

/* C implementation for a variation of the Boundary Filling Algorithm */

/* Chose a particular matrix to evaluate: */
#define M2

#ifdef M1
const int LX = 3;
const int LY = 3;
const int matrix[][LX] = {
	{ 1, 2, 3 },
	{ 4, 1, 6 }, 
	{ 4, 5, 1 }
};
/* Should be 2 (of 4s) */
#endif

#ifdef M2
const int LX = 5;
const int LY = 3;
const int matrix[][LX] = {
	{ 1, 1, 1, 2, 4 },
	{ 5, 1, 5, 3, 1 },
	{ 3, 4, 2, 1, 1 } 
};
/* Should be 4 (of 1s) */
#endif

#ifdef M3
const int LX = 6;
const int LY = 4;
const int matrix[][LX] = { 
	{ 3, 3, 3, 3, 3, 1 },
	{ 3, 4, 4, 4, 3, 4 },
	{ 2, 4, 3, 3, 3, 4 },
	{ 2, 4, 4, 4, 4, 4 } 
};
/* Should be 11 (of 4s) */
#endif

#ifdef M4
const int LX = 5;
const int LY = 5;
const int matrix[][LX] = {
	{ 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1 },
	{ 1, 1, 0, 1, 1 },
	{ 1, 1, 1, 1, 1 },
	{ 1, 1, 1, 1, 1 } 
};
/* Should be 24 (of 1s) */
#endif

/* For tracking */
int mtrack[LY][LX] = { 0 };

/* Function for 4 connected Pixels */
int boundaryFillFour(const int matrix[][LX], int x, int y, int color)
{
    int track = 0;
    if (y < LY && y >= 0)
        if (x < sizeof(matrix[0])/sizeof(int) && x >= 0) {
            if (mtrack[y][x] != 0)
		return 0; /* Skip */
            if (matrix[y][x] == color) {
                track += 1;
		mtrack[y][x] = 1; /* Mark */
                track+=boundaryFillFour(matrix, x + 1, y, color);
                track+=boundaryFillFour(matrix, x, y + 1, color);
                track+=boundaryFillFour(matrix, x - 1, y, color);
                track+=boundaryFillFour(matrix, x, y - 1, color);
	    }
	}
    return track;
}

int main()
{
int count = 0;
int max_count = 0;
for (int y = 0; y < sizeof(matrix)/sizeof(matrix[0]); y++)
    for (int x = 0; x < sizeof(matrix[0])/sizeof(int); x++) {
        count = boundaryFillFour(matrix, x, y, matrix[y][x]);
	if (max_count < count)
		max_count = count;
    }
printf("%d\n", max_count);
}
