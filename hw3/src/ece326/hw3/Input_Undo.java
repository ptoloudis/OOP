package ece326.hw3;

public class Input_Undo {
    private int row, col;
    private String input;

    public Input_Undo(int row, int col, String input) {
        this.row = row;
        this.col = col;
        this.input = input;
    }

    public int getRow() {
        return row;
    }

    public int getCol() {
        return col;
    }

    public String getInput() {
        return input;
    }

}
