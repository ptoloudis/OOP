package ece326.hw3;

import java.awt.*;

public class R_Color {

    private int row, col;
    private Color input;

    public R_Color(int row, int col, Color input) {
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

    public Color getColor() {
        return input;
    }
}
