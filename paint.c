// This program was written on 21 Oct 2019
//
// Version 2.0 - 27.10.2019

#include <stdio.h>
#include <math.h>

// The dimensions of the canvas (20 rows x 36 columns).
#define N_ROWS 20
#define N_COLS 36

// Shades (assuming your terminal has a black background).
#define BLACK 0
#define DARK 1
#define GREY 2
#define LIGHT 3
#define WHITE 4

// Provided helper functions:
// Display the canvas.
void displayCanvas(int canvas[N_ROWS][N_COLS]);

// Clear the canvas by setting every pixel to be white.
void clearCanvas(int canvas[N_ROWS][N_COLS]);

// Calculate the distance between two points.
double distance(int row1, int col1, int row2, int col2);

// ----------------------------------------------------------------------
// functions for drawing lines

int drawLine (
int start_row, int start_col, int length, int direction,
int canvas[N_ROWS][N_COLS], int shade
);

void verticalLine (
int start_row, int start_col, int length, int direction,
int canvas[N_ROWS][N_COLS], int shade
);
    
void horizontalLine (
int start_row, int start_col, int length, int direction,
int canvas[N_ROWS][N_COLS], int shade
);

void diagonalLine (
int start_row, int start_col, int length, int direction,
int canvas[N_ROWS][N_COLS], int shade
);

// -----------------------------------------------------------------------
// functions for drawing square

int drawSquare (
int start_row, int start_col, int length, int direction,
int canvas[N_ROWS][N_COLS], int shade
);
    
void diagonal (
int start_row, int start_col, int length, int direction,
int canvas[N_ROWS][N_COLS], int shade
);

// -----------------------------------------------------------------------
// function for copy & paste

int copyPaste (
int start_row, int start_col, int length, int direction,
int canvas[N_ROWS][N_COLS], int target_row, int target_col
);
// ------------------------------------------------------------------------
// function for drawing ellipse

int ellipse (
int focus_1_row, int focus_1_col, int focus_2_row, int focus_2_col,
double radius, int fill, int canvas[N_ROWS][N_COLS], int shade
);
// -------------------------------------------------------------------------
// the main function

int main(void) {
    
    // 2D array for the canvas background
    int canvas[N_ROWS][N_COLS] = {0};
    clearCanvas(canvas);

    // declare variables
    int command;
    int start_row, start_col, length, direction;
    int shade = 0;
    int new_shade;
    int target_row, target_col;
    int focus_1_row, focus_1_col, focus_2_row, focus_2_col, fill;
    double radius;

    // scan in the instruction number
    while (scanf ("%d", &command) == 1) { 
    
        // draw line while command = 1
        if (command == 1) {
            scanf (
            "%d %d %d %d", 
            &start_row, &start_col, &length, &direction
            );
            drawLine (start_row, start_col, length, direction, canvas, shade);
            
            // draw square while command = 2
        } else if (command == 2) {
            scanf (
            "%d %d %d %d", 
            &start_row, &start_col, &length, &direction
            );
            drawSquare (
            start_row, start_col, length, direction, canvas, shade
            );  
            
            // change shade colour while command = 3     
        } else if (command == 3) {
            scanf ("%d", &new_shade);
            if (new_shade + shade >= 0 && new_shade + shade <= 4) {
                shade += new_shade;
            }
            
            // copy the previous commands and paste while command = 4
        } else if (command == 4) {
            scanf (
            "%d %d %d %d %d %d", 
            &start_row, &start_col, &length, &direction,
            &target_row, &target_col
            );
            copyPaste (
            start_row, start_col, length, direction, canvas, 
            target_row, target_col
            );
            
            // draw ellipse while command = 0
        } else if (command == 0) {
            scanf (
            "%d %d %d %d %lf %d",
            &focus_1_row, &focus_1_col, &focus_2_row, &focus_2_col, 
            &radius, &fill
            );
            ellipse (
            focus_1_row, focus_1_col, focus_2_row, focus_2_col, 
            radius, fill, canvas, shade
            );
        }
    }

    displayCanvas(canvas);

    return 0;
}

// --------------------------------------------------------------------------
// function of drawing straight lines

int drawLine (
int start_row, int start_col, int length, int direction,
int canvas[N_ROWS][N_COLS], int shade
) {
    
    // make sure degree of direction is < 360
    if (direction >= 360) {
        direction = direction % 360;
    }
    
    // if length = 0, nothing is to be draw
    if (length == 0) {
        return 0;
        
        // if command start point outside canvas, draw nothing
    } else if 
    (
    start_row > (N_ROWS - 1) || start_col > (N_COLS - 1) || 
    start_row < 0 || start_col < 0
    ) {
        start_row = start_col = 0;

        // if length > 1, draw vertical line
        // if length = 1, draw a dot at the start points
        // if length < 0, make it positive, reverse direction, draw line
    } else if (direction == 0 || direction == 180) {
        if (length > 1) {
            verticalLine (
            start_row, start_col, length, direction, canvas, shade
            );
        } else if (length == 1) {
            canvas[start_row][start_col] = shade;
        } else if (length < 0) {
            length = - length;
            if (direction == 0) {
                direction += 180;
                verticalLine (
                start_row, start_col, length, direction, canvas, shade
                );
            } else if (direction == 180) {
                direction -= 180;
                verticalLine (
                start_row, start_col, length, direction, canvas, shade
                );
            }
        }
        
        // if length > 1, draw horizontal line
        // if length = 1, draw a dot at the start points
        // if length < 0, make it positive, reverse direction, draw line
    } else if (direction == 90 || direction == 270) {
        if (length > 1) {
            horizontalLine (
            start_row, start_col, length, direction, canvas, shade
            );
        } else if (length == 1) {
            canvas[start_row][start_col] = shade;
        } else if  (length < 0) {
            length = - length;
            if (direction == 90) {
                direction += 180;
                horizontalLine (
                start_row, start_col, length, direction, canvas, shade
                );
            } else if (direction == 270) {
                direction -= 180;
                horizontalLine (
                start_row, start_col, length, direction, canvas, shade
                );
            }
        }
        
        // if length > 1, draw diagonal line
        // if length = 1, draw a dot at the start points
        // if length < 0, make it positive, reverse direction,
        // draw diagonal lines
    } else if (
        direction == 45 || direction == 135 || 
        direction == 225 || direction == 315
    ) {
        if (length > 1) {
            diagonalLine (
            start_row, start_col, length, direction, canvas, shade
            );
        } else if (length == 1) {
            canvas[start_row][start_col] = shade;
        } else if (length < 0) {
            length = - length;
            if (direction == 45) {
                direction += 180;
                diagonalLine (
                start_row, start_col, length, direction, canvas, shade
                );
            } else if (direction == 135) {
                direction += 180;
                diagonalLine (
                start_row, start_col, length, direction, canvas, shade
                );
            } else if (direction == 225) {
                direction -= 180;
                diagonalLine (
                start_row, start_col, length, direction, canvas, shade
                );
            } else if (direction == 315) {
                direction -= 180;
                diagonalLine (
                start_row, start_col, length, direction, canvas, shade
                );
            }
        }
    }
    
    return canvas[start_row][start_col];
}

// degree = 0 & 180 are verticalLine, increase or decrease row numbers
void verticalLine (
int start_row, int start_col, int length, int direction,
int canvas[N_ROWS][N_COLS], int shade
) {
    
    int i;
    int end_row = 0;

    // calculate end_row 
    if (direction == 0) {
        end_row = start_row - length;
    } else if (direction == 180) {
        end_row = start_row + length;
    }

    // draw nothing if the end_row out of bound
    if (end_row > (N_ROWS) || end_row < -1) {

        // direction = 0, move up   
    } else if (direction == 0) {
        i = 0;
        while (i < length) {
            canvas[start_row][start_col] = shade;
            start_row --;
            i ++;
        }       
        // direction = 180, move down
    } else if (direction == 180) {
        i = 0;
        while (i < length) {
            canvas[start_row][start_col] = shade;
            start_row ++;
            i ++;
        }  
    }
}

// degree = 90 & 270 are horizontalLine, increase or decreas column numbers
void horizontalLine (
int start_row, int start_col, int length, int direction,
int canvas[N_ROWS][N_COLS], int shade
) {
    
    int i;
    int end_col = 0;
    
    // calculate end_col
    if (direction == 90) {
        end_col = start_col + length;    
    } else if (direction == 270) {
        end_col = start_col - length;
    } 

    // draw nothing if the end_col out of bound
    if (end_col > (N_COLS) || end_col < -1) {
    
        // direction = 90, move right
    } else if (direction == 90) {
        i = 0;
        while (i < length) {
            canvas[start_row][start_col] = shade;
            start_col ++;
            i ++;
        }
        // direction = 270, move left
    } else if (direction == 270) {
        i = 0;
        while (i < length) {
            canvas[start_row][start_col] = shade;
            start_col --;
            i ++;
        }  
    }
}

void diagonalLine (
int start_row, int start_col, int length, int direction,
int canvas[N_ROWS][N_COLS], int shade
) {
    
    int i = 0;
    
    // draw nothing if the end_col out of bound
    if (start_row - length < 0 || start_col + length > (N_COLS - 1)) {
    }
        
    // direction = 45, move northeast    
    if (direction == 45) {
        if (start_row - length < 0 || start_col + length > (N_COLS - 1)) {
        } else {
            i = 0;
            while (i < length) {
                canvas[start_row][start_col] = shade;
                start_row --;
                start_col ++;
                i ++;
            }
        }
        
        // direction = 135, move southeast
    } else if (direction == 135) {
        if (
        start_row + length > (N_ROWS - 1) || 
        start_col + length > (N_COLS - 1)
        ) {
        
        } else {
            i = 0;
            while (i < length) {
                canvas[start_row][start_col] = shade;
                start_row ++;
                start_col ++;
                i ++;
            }  
        }
        
        // direction = 225, move southwest
    } else if (direction == 225) {
        if (start_row + length > (N_ROWS - 1) || start_col - length < 0) {
        
        } else {
            i = 0;
            while (i < length) {
                canvas[start_row][start_col] = shade;
                start_row ++;
                start_col --;
                i ++;
            }  
        }
        
        // direction = 315, move northwest
    } else if (direction == 315) {
        if (start_row - length < 0 || start_col - length < 0) {
        } else {
            i = 0;
            while (i < length) {
                canvas[start_row][start_col] = shade;
                start_row --;
                start_col --;
                i ++;
            }
        }  
    } 
}

// --------------------------------------------------------------------------
// functions for drawing square

int drawSquare (
int start_row, int start_col, int length, int direction,
int canvas[N_ROWS][N_COLS], int shade
) {
    
    // make sure degree of direction is < 360
    if (direction >= 360) {
        direction = direction % 360;
    } 
       
    // length = 0, draw nothing
    if (length == 0) {
    
        // if start_row / start_col out of bound, draw nothing
    } else if 
    (
    start_row > (N_ROWS - 1) || start_col > (N_COLS - 1) || 
    start_row < 0 || start_col < 0
    ) {
        start_row = start_col = 0;
        
    } else {
        // drawSquare = drawLine, if direction = 0, 90, 180, 270
        if (
        direction == 0 || direction == 90 || 
        direction == 180 || direction == 270
        ) {
            drawLine (start_row, start_col, length, direction, canvas, shade);
            
            // length > 1, draw diagonal
            // length < 0, make it positive, reverse direction,
            // draw square across the diagonal
        } else if (
        direction == 45 || direction == 225 || 
        direction == 135 || direction == 315
        ) {
            if (length >= 1) {
                diagonal (
                start_row, start_col, length, direction, canvas, shade
                );
            } else if (length < 0) {
                length = - length;
                if (direction == 45) {
                    direction += 180;
                    diagonal (
                    start_row, start_col, length, direction, 
                    canvas, shade
                    );
                } else if (direction == 135) {
                    direction += 180;
                    diagonal (
                    start_row, start_col, length, direction, 
                    canvas, shade
                    );
                } else if (direction == 225) {
                    direction -= 180;
                    diagonal (
                    start_row, start_col, length, direction, 
                    canvas, shade
                    );
                } else if (direction == 315) {
                    direction -= 180;
                    diagonal (
                    start_row, start_col, length, direction, 
                    canvas, shade);
                }
            } else {
            } 
            
            // if direction invalid, draw nothing
        } else {
        }
    }
    return canvas[start_row][start_col];
}

void diagonal (
int start_row, int start_col, int length, int direction,
int canvas[N_ROWS][N_COLS], int shade
) {
    
    // i = row numbers, j = column numbers
    int i = 0;
    int j = 0;
    
    // direction = 45, move northeast
    if (direction == 45) {
        if (start_row - length < 0 || start_col + length > (N_COLS - 1)) {
            canvas[start_row][start_col] = WHITE;
        } else {
            while (i < length) {
                j = 0;
                while (j < length) {
                    canvas[start_row][start_col] = shade;
                    j ++;
                    start_col ++;
                }
                i ++;
                start_row --;
                start_col = start_col - length;
            }   
        }  
        
        // direction = 225, move southwest
    } else if (direction == 225) {
        if (start_row + length > (N_ROWS - 1) || start_col - length < 0) {
        
        } else {
            while (i < length) {
                j = 0;
                while (j < length) {
                    canvas[start_row][start_col] = shade;
                    j ++;
                    start_col --;
                }
                i ++;
                start_row ++;
                start_col = start_col + length;
            } 
        } 
        
        // direction = 135, move southeast      
    } else if (direction == 135) {
        if (
        start_row + length > (N_ROWS - 1) || 
        start_col + length > (N_COLS - 1)
        ) {
        
        } else {
            while (i < length) {
                j = 0;
                while (j < length) {
                    canvas[start_row][start_col] = shade;
                    j ++;
                    start_col ++;
                }
                i ++;
                start_row ++;
                start_col = start_col - length;
            }    
        } 
        
        // direction = 315, move northwest   
    } else if (direction == 315) {
        if (start_row - length < 0 || start_col - length < 0) {
        } else {        
            while (i < length) {
                j = 0;
                while (j < length) {
                    canvas[start_row][start_col] = shade;
                    j ++;
                    start_col --;
                }
                i ++;
                start_row --;
                start_col = start_col + length;
            } 
        }       
    }        
}

// ---------------------------------------------------------------------------
// function for copy & paste

int copyPaste (
int start_row, int start_col, int length, int direction,
int canvas[N_ROWS][N_COLS], int target_row, int target_col
) {
    
    // copy everything into the new 2D array
    int copy[N_ROWS][N_COLS] = {0};
    
    // i = row numbers, j = column numbers
    int i = 0;
    int j = 0;
    
    // if out of bound, draw nothing
    if (
    (target_row + length) > (N_ROWS - 1) || 
    (target_col + length) > (N_COLS -1)
    ) {
        
        // else, copy shades from canvas[i][j] into copy [i][j]
    } else {
        while (i < N_ROWS) {
            j = 0;
            while (j < N_COLS) {
                copy[i][j] = canvas[i][j];
                j ++;
            }
            i ++;
        }
        
        i = 0;
        j = 0;
        
        // paste shades from copy into canvas[target_row][target_col]
        while (i < length) {
            j = 0;
            while (j < length) {
                canvas[target_row][target_col] = copy[start_row][start_col];
                j ++;
                target_col ++;
                start_col ++;
            }
            i ++;
            target_row ++;
            start_row ++;
            target_col -= length;
            start_col -= length;
        }
    }
    
    return canvas[target_row][target_col];
}

// ---------------------------------------------------------------------------
// function for drawing ellipse

int ellipse (
int focus_1_row, int focus_1_col, int focus_2_row, int focus_2_col,
double radius, int fill, int canvas[N_ROWS][N_COLS], int shade
) {

    int i = 0;
    int j = 0;
    
    // solid ellipse
    if (fill != 0) {
        while (i < N_ROWS) {
            j = 0;
            while (j < N_COLS) {
                if (
                distance (i, j, focus_1_row, focus_1_col) + 
                distance (i, j, focus_2_row, focus_2_col) <= (2 * radius)
                ) {
                    canvas[i][j] = shade;
                } else {
                }
                j ++;
            }
            i ++;
        }
        
        // draw hollow ellipse if fill = 0
    } else {
        i = 0;
        j = 0;
        while (i < N_ROWS) {
            j = 0;
            while (j < N_COLS) {
                
                // i + 1, down
                // i - 1, up
                // j + 1, right
                // j - 1, left
                if (
                distance (i, j, focus_1_row, focus_1_col) + 
                distance (i, j, focus_2_row, focus_2_col) <= (2 * radius) &&
                (
                distance (i + 1, j, focus_1_row, focus_1_col) + 
                distance (i + 1, j, focus_2_row, focus_2_col) > (2 * radius) ||
                distance (i - 1, j, focus_1_row, focus_1_col) + 
                distance (i - 1, j, focus_2_row, focus_2_col) > (2 * radius) ||
                distance (i, j + 1, focus_1_row, focus_1_col) + 
                distance (i, j + 1, focus_2_row, focus_2_col) > (2 * radius) ||
                distance (i, j - 1, focus_1_row, focus_1_col) + 
                distance (i, j - 1, focus_2_row, focus_2_col) > (2 * radius)
                )
                ) {
                    canvas[i][j] = shade;
                } else {
                }
                j ++;
            }
            i ++;
        }
    }
    return 0;
}


// ---------------------------------------------------------------------------
// given functions

// Displays the canvas, by printing the integer value stored in
// each element of the 2-dimensional canvas array.
void displayCanvas(int canvas[N_ROWS][N_COLS]) {
    int row = 0;
    while (row < N_ROWS) {
        int col = 0;
        while (col < N_COLS) {
            printf("%d ", canvas[row][col]);
            col++;
        }
        row++;
        printf("\n");
    }
}


// Sets the entire canvas to be blank, by setting each element in the
// 2-dimensional canvas array to be WHITE (which is #defined at the top
// of the file).
void clearCanvas(int canvas[N_ROWS][N_COLS]) {
    int row = 0;
    while (row < N_ROWS) {
        int col = 0;
        while (col < N_COLS) {
            canvas[row][col] = WHITE;
            col++;
        }
        row++;
    }
}

// Calculate the distance between two points (row1, col1) and (row2, col2).
double distance(int row1, int col1, int row2, int col2) {
    int row_dist = row2 - row1;
    int col_dist = col2 - col1;
    return sqrt((row_dist * row_dist) + (col_dist * col_dist));
}
