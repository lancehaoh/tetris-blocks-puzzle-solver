# tetris-blocks-puzzle-solver

Solver for Cluefinders 4th grade adventure tetris-blocks-puzzle challenge (see "puzzle.jpg").

Rules for challenge:

1. Fit all 12 blocks into the grid with no overlaps.

2. Each block can be rotated up to 180 degrees in any direction.

3. No reflection allowed on the blocks. (i.e. |__ cannot be transformed to __| )


Input file format is as follows:

___________________________________________________________________________________________________________
height_of_grid width_of_grid

number_of_blocks

height_of_first_block width_of_first_block

5x5 matrix representing the block (use 'x' if the cell is part of the shape's outline. 'o' otherwise.)

.

.

.

height_of_last_block width_of_last_block

5x5 matrix representing the block

___________________________________________________________________________________________________________

The input for this puzzle is defined in the file "in"

The solver outputs the solution to the puzzle as a character matrix, representing different blocks as different characters. See "solution.png" for the actual colored solution.

To run the solver, a C++ compiler is required to compile the code.
Then put "solver.cpp" and "in" into the same directory and perform the following command:

./solver < in

Runtime: the solver solves the given puzzle in 42 seconds on a 2015 Macbook Air with a 1.6 Ghz Intel Core i5 processor.
