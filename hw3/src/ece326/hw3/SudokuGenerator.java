package ece326.hw3;

public class SudokuGenerator {
    public static final int SIZE = 9;
    private int[][] board, board2;
    Network network;
    private boolean[][] mask = {
            { true, true, true, true, true, true, true, true, true },
            { true, true, true, true, true, true, true, true, true },
            { true, true, true, true, true, true, true, true, true },
            { true, true, true, true, true, true, true, true, true },
            { true, true, true, true, true, true, true, true, true },
            { true, true, true, true, true, true, true, true, true },
            { true, true, true, true, true, true, true, true, true },
            { true, true, true, true, true, true, true, true, true },
            { true, true, true, true, true, true, true, true, true }
    };

    int[][] start;

    public SudokuGenerator(String difficulty){
        network = new Network(difficulty);
        board2 = network.getBoard();
        start = board2;
        generateBoard();
        generateMask();

    }

    public int[][] getBoard(){
        return board;
    }

    public boolean[][] getMask(){
        return mask;
    }

    public void generateBoard(){
        SudokuPuzzle solver = new SudokuPuzzle(start);
        solver.solve();
        board = solver.getBoard();
    }
    public void generateMask(){
        for(int i = 0; i < mask.length; ++i){
            for(int j = 0; j < mask.length; ++j){
                if(board2[i][j] == 0){
                    mask[i][j] = false;
                }
            }
        }

    }
    boolean checkMask(boolean[][] mask){
        for(int i = 0; i < mask.length; ++i){
            for(int j = 0; j < mask.length; ++j){
                if(!mask[i][j]){
                    return false;
                }
            }
        }
        return true;
    }
}
