#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Indexing for row i, column j
#define B(b,i,j) (b[(i)*9+(j)])
// Indexing for block row ii, block col jj, row i, col j
#define BB(b,ii,jj,i,j) (B(b,(ii)*3+(i),(jj)*3+(j)))
// Row within grid from index
#define ROW(ix) ((ix)/9)
// Column within grid from index
#define COL(ix) ((ix)%9)

// Char representing empty position
#define EMPTY '.'

bool rows_ok(const char *b)
{
    // For each row
    for (int i=0; i<9; i++) {
	// Reset histogram
	int hist9[9];
	memset(hist9,0,sizeof(hist9));

	// For each column
	for (int j=0; j<9; j++) {
	    // For each non-empty position
	    if (B(b,i,j)!=EMPTY) {
		// Update histogram and check for duplicates
		hist9[B(b,i,j) - '0']++;
		if (hist9[B(b,i,j) - '0']>1)
		    return false;
	    }
	}
    }
    return true;
}

bool cols_ok(const char *b)
{
    // For each column
    for (int j=0; j<9; j++) {
	// Reset histogram
	int hist9[9];
	memset(hist9,0,sizeof(hist9));

	// For each row
	for (int i=0; i<9; i++) {
	    // For each non-empty position
	    if (B(b,i,j)!=EMPTY) {
		// Update histogram and check for duplicates
		hist9[B(b,i,j) - '0']++;
		if (hist9[B(b,i,j) - '0']>1)
		    return false;
	    }
	}
    }
    return true;
}

bool squares_ok(const char *b)
{
    // For each block row
    for (int ii=0; ii<3; ii++) {
	// For each block column
	for (int jj=0; jj<3; jj++) {
	    // Reset histogram
	    int hist9[9];
	    memset(hist9,0,sizeof(hist9));

	    // For each row and col
	    for (int i=0; i<3; i++)
		for (int j=0; j<3; j++)
		    if (BB(b,ii,jj,i,j)!=EMPTY) {
			// Update histogram and check for duplicates
			hist9[BB(b,ii,jj,i,j) - '0']++;
			if (hist9[BB(b,ii,jj,i,j) - '0']>1)
			    return false;
		    }
	}
    }
    return true;
}

bool board_ok(const char *b)
{
    return rows_ok(b) && cols_ok(b) && squares_ok(b);
}

bool board_filled(const char *b)
{
    return !strchr(b, EMPTY);
}

bool board_done(const char *b)
{
    return board_filled(b) && board_ok(b);
}

// Return index of an unassigned pos
void find_unassigned(const char *b,int *i, int *j)
{
    int ix = strchr(b, EMPTY) - b;
    *i = ROW(ix);
    *j = COL(ix);
}

void print_sudoku(const char *b)
{
    for (int i=0; i<9; i++) {
	for (int j=0; j<9; j++) {
	    if (B(b,i,j)==EMPTY) {
		printf(" .");
	    } else {
		printf(" %c", B(b,i,j) + 1);
	    }
	    if (j<8 && j%3==2)
		printf(" |");
	}
	printf("\n");
	if (i<8 && i%3==2)
	    printf("-------+-------+-------\n");
    }
    printf("\n");
    getchar();
}

bool is_safe(char *b, int i, int j, char d)
{
    // Set position...
    B(b,i,j) = d;
    // ...check board...
    bool ok = board_ok(b);
    // ...and reset position.
    B(b,i,j) = EMPTY;

    return ok;
}

char *solve(char *b)
{
    print_sudoku(b);

    // Done already?
    if (board_done(b))
	return b;

    // Find a free position
    int i,j;
    find_unassigned(b, &i, &j);

    // Try each digit at free position
    for (char d='0'; d<'9'; d++) {
	// Safe at the posn?
	if (is_safe(b, i, j, d)) {
	    // Set it...
	    B(b,i,j) = d;
	    // ...and try to solve remainder
	    char *solved = solve(b);
	    if (solved) {
		return solved;
	    } else {
		// Reset position
		B(b,i,j) = EMPTY;
	    }
	}
    }
    return NULL;
}

int main(void)
{
    char board[82];

    memset(board, 0, sizeof(board));
    memset(board, EMPTY, 81);

    const char *src = ".32..9........7.9.1..5....294..2.....2.7..1...7......3......8.....961.7.5....89.1";

    for (int i=0; src[i]; i++) {
	if (src[i] != EMPTY) {
	    board[i] = src[i] - 1;
	}
    }

    char *s = solve(board);

    if (s) {
	print_sudoku(s);
    } else {
	printf("Failed\n");
    }

    return 0;
}
