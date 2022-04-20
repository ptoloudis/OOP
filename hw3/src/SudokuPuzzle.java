import java.util.Scanner;

public class SudokuPuzzle {
    // Java program for above approach


    // N is the size of the 2D matrix N*N
    static int N = 9;

    /* Takes a partially filled-in grid and attempts
    to assign values to all unassigned locations in
    such a way to meet the requirements for
    Sudoku solution (non-duplication across rows,
    columns, and boxes) */
    static boolean solveSudoku(int grid[][], int row,
                               int col) {

    /*if we have reached the 8th
    row and 9th column (0
    indexed matrix) ,
    we are returning true to avoid further
    backtracking	 */
        if (row == N - 1 && col == N)
            return true;

        // Check if column value becomes 9 ,
        // we move to next row
        // and column start from 0
        if (col == N) {
            row++;
            col = 0;
        }

        // Check if the current position
        // of the grid already
        // contains value >0, we iterate
        // for next column
        if (grid[row][col] != 0)
            return solveSudoku(grid, row, col + 1);

        for (int num = 1; num < 10; num++) {

            // Check if it is safe to place
            // the num (1-9) in the
            // given row ,col ->we move to next column
            if (isSafe(grid, row, col, num)) {

            /* assigning the num in the current
            (row,col) position of the grid and
            assuming our assigned num in the position
            is correct */
                grid[row][col] = num;

                // Checking for next
                // possibility with next column
                if (solveSudoku(grid, row, col + 1))
                    return true;
            }
        /* removing the assigned num , since our
        assumption was wrong , and we go for next
        assumption with diff num value */
            grid[row][col] = 0;
        }
        return false;
    }

    /* A utility function to print grid */
    static void print(int[][] grid) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                System.out.print(grid[i][j] + " ");
            System.out.println();
        }
    }

    // Check whether it will be legal
    // to assign num to the
    // given row, col
    static boolean isSafe(int[][] grid, int row, int col,
                          int num) {

        // Check if we find the same num
        // in the similar row , we
        // return false
        for (int x = 0; x <= 8; x++)
            if (grid[row][x] == num)
                return false;

        // Check if we find the same num
        // in the similar column ,
        // we return false
        for (int x = 0; x <= 8; x++)
            if (grid[x][col] == num)
                return false;

        // Check if we find the same num
        // in the particular 3*3
        // matrix, we return false
        int startRow = row - row % 3, startCol
                = col - col % 3;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (grid[i + startRow][j + startCol] == num)
                    return false;

        return true;
    }


    // main method
    public static void main(String[] args) {

        System.out.println("Enter the sudoku puzzle");
        Scanner sc = new Scanner(System.in);
        URLReader urlReader = new URLReader(sc.nextInt());
        int[][] b = urlReader.getTable();

        // Printing the grid
        int size = b.length;

        System.out.println("The grid is: ");
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                System.out.print(b[i][j] + " ");
            }
            System.out.println();
        }

        Sudoku sg = new Sudoku(b);
        sg.frame.pack();
        sg.frame.setVisible(true);


// creating an object of the class SudokuPuzzle
        SudokuPuzzle obj = new SudokuPuzzle();

// computing the size of the grid

        System.out.println();
        if (solveSudoku(b, 0, 0))
            print(b);
        else
            System.out.println("No Solution exists");
    }
}
