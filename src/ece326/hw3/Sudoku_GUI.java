package ece326.hw3;

import java.awt.*;
import java.awt.event.*;
import java.util.Stack;
import javax.swing.*;
import javax.swing.text.*;


public class Sudoku_GUI extends JFrame implements Cloneable{
    SudokuGenerator gen =  new SudokuGenerator("Easy");
    Container container = getContentPane();
    boolean isSolved = false;
    public static final int GRID_SIZE = 9;
    public static final int SUB_GRID_SIZE = 9;

    Stack<Input_Undo> undo_stack = new Stack<>();
    Stack<R_Color> input_color = new Stack<>();
    // GUI
    public static final int CELL_SIZE = 60;
    public static final int CANVAS_SIZE = GRID_SIZE * CELL_SIZE;
    public static final Font FONT_NUMBERS = new Font("Comicsans", Font.BOLD, 20);
    private JTextField[][] cells = new JTextField[GRID_SIZE][GRID_SIZE];
    private JTextField[][] sub_cells = new JTextField[GRID_SIZE][GRID_SIZE];

    private static final Color FG_CLOSE = Color.BLACK;
    private static final Color BG_CLOSE = Color.gray;
    private static final Color BG_WRONG = Color.red;
    private static final Color BG_OPEN = Color.white;
    private static final Color BG_INPUT = Color.yellow;
    private static final Color BG_DIF_SOL = Color.BLUE;

    private int sel_row = -1;
    private int sel_col = -1;

    private int[][] board = gen.getBoard();

    private boolean[][] mask = gen.getMask();

    JCheckBox checkSol = new JCheckBox("Check against solution");


    class JTextFieldLimit extends PlainDocument {
        private int limit;
        JTextFieldLimit(int limit) {
            super();
            this.limit = limit;
        }
        JTextFieldLimit(int limit, boolean upper) {
            super();
            this.limit = limit;
        }
        public void insertString(int offset, String str, AttributeSet attr) throws BadLocationException {
            if (str == null)
                return;
            if ((getLength() + str.length()) <= limit) {
                super.insertString(offset, str, attr);
            }
        }
    }

    // ToDo: make the Button work
    public void actionPerformed(ActionEvent e){
        String command =e.getActionCommand();
        int selectedRow = -1;
        int selectedCol = -1;
        JTextField actionSource = (JTextField)e.getSource();
        boolean found = false;
        for(int row = 0; row < GRID_SIZE && !found; ++row){
            for(int col = 0; col < GRID_SIZE && !found; ++col){
                if(cells[row][col] == actionSource){
                    selectedRow = row;
                    selectedCol = col;
                    found = true;
                }

            }
        }
        int value = 0;

        try{
            try {
                value = Integer.parseInt(command);
            }
            catch (NumberFormatException z)
            {
                value = 0;
            }
            cells[selectedRow][selectedCol].setBackground(BG_INPUT);
            if(board[selectedRow][selectedCol] == value) {
                mask[selectedRow][selectedCol] = true;
                if (gen.checkMask(mask)) {
                    winner();
                }
            }
            else{
                for (int row = 0; row < GRID_SIZE; ++row) {
                    if (board[row][selectedCol] == value && mask[row][selectedCol]) {
                        cells[row][selectedCol].setBackground(BG_WRONG);
                    }
                }
                for (int col = 0; col < GRID_SIZE; ++col) {
                    if (board[selectedRow][col] == value && mask[selectedRow][col]) {
                        cells[selectedRow][col].setBackground(BG_WRONG);
                    }
                }

            }
            cells[selectedRow][selectedCol].setForeground(FG_CLOSE);
        }
        catch (Exception except){
            cells[selectedRow][selectedCol].setText("");

        }
    }

    private class InputListener implements KeyListener{
        @Override
        public void keyPressed(KeyEvent e){

        }
        @Override
        public void keyTyped(KeyEvent e){

        }
        @Override
        public void keyReleased(KeyEvent e){
            int selectedRow = -1;
            int selectedCol = -1;

            if (isSolved) {
                return;
            }

            while(input_color.size() > 0){
                R_Color in = input_color.pop();
                cells[in.getRow()][in.getCol()].setBackground(in.getColor());
            }

            String command = null;
            JTextField actionSource = (JTextField)e.getSource();
            boolean found = false;
            for(int row = 0; row < GRID_SIZE && !found; ++row){
                for(int col = 0; col < GRID_SIZE && !found; ++col){
                    if(cells[row][col] == actionSource){
                        selectedRow = row;
                        selectedCol = col;
                        command = sub_cells[row][col].getText();
                        found = true;
                    }

                }
            }
            int value = 0;

            String input = cells[selectedRow][selectedCol].getText();

            try{
                value = Integer.parseInt(input);

                if(sel_col != -1 && sel_row != -1){
                    cells[sel_row][sel_col].setBackground(BG_OPEN);
                }

                cells[selectedRow][selectedCol].setBackground(BG_INPUT);
                if(board[selectedRow][selectedCol] == value) {
                    for (int row = 0; row < GRID_SIZE; ++row) {
                        for (int col = 0; col < GRID_SIZE; ++col) {
                            if (cells[row][col].getText().equals(input)) {
                                R_Color in = new R_Color(row, col, cells[row][col].getBackground());
                                input_color.push(in);
                                cells[row][col].setBackground(BG_INPUT);
                            }
                        }
                    }
                    mask[selectedRow][selectedCol] = true;
                    if (gen.checkMask(mask)) {
                        isSolved = true;
                        winner();
                    }
                }
                else{
                    for (int row = 0; row < GRID_SIZE; ++row) {
                        for (int col = 0; col < GRID_SIZE; ++col) {
                            if (cells[row][col].getText().equals(input)) {
                                R_Color in = new R_Color(row, col, cells[row][col].getBackground());
                                input_color.push(in);
                                cells[row][col].setBackground(BG_INPUT);
                            }
                        }
                    }

                    for (int row = 0; row < GRID_SIZE; ++row) {

                        if (board[row][selectedCol] == value && mask[row][selectedCol]) {
                            cells[row][selectedCol].setBackground(BG_WRONG);
                        }
                    }
                    for (int col = 0; col < GRID_SIZE; ++col) {

                        if (board[selectedRow][col] == value && mask[selectedRow][col]) {
                            cells[selectedRow][col].setBackground(BG_WRONG);
                        }
                    }

                    check3_3(selectedRow, selectedCol, value);

                }
            }
            catch (Exception except){
                cells[selectedRow][selectedCol].setText("");

            }
            sel_col = selectedCol;
            sel_row = selectedRow;

            sub_cells[selectedRow][selectedCol].setText(cells[selectedRow][selectedCol].getText());
            Input_Undo x = new Input_Undo(selectedRow, selectedCol, command);
            undo_stack.push(x);
        }
    }

    private void check3_3(int row, int col, int k){
        boolean found = false;
        switch (row/3){
            case 0:
                switch (col/3){
                    case 0:

                        for (int i = 0; i < 3; i++) {
                            for (int j = 0; j < 3; j++) {
                                if(i == row && j == col){
                                    continue;
                                }

                                if (cells[i][j].getText().equals(Integer.toString(k))) {
                                    if (found = true) {
                                        R_Color in = new R_Color(row, col, cells[row][col].getBackground());
                                        input_color.push(in);
                                        cells[i][j].setBackground(BG_WRONG);
                                    }
                                    found = true;
                                }
                            }
                        }

                        break;
                    case 1:
                        for (int i = 0; i < 3; i++) {
                            for (int j = 3; j < 6; j++) {
                                if(i == row && j == col){
                                    continue;
                                }

                                if (cells[i][j].getText().equals(Integer.toString(k))) {
                                    if (found = true) {
                                        R_Color in = new R_Color(row, col, cells[row][col].getBackground());
                                        input_color.push(in);
                                        cells[i][j].setBackground(BG_WRONG);
                                    }
                                    found = true;
                                }
                            }
                        }
                        break;
                    case 2:
                        for (int i = 0; i < 3; i++) {
                            for (int j = 6; j < 9; j++) {
                                if(i == row && j == col){
                                    continue;
                                }

                                if (cells[i][j].getText().equals(Integer.toString(k))) {
                                    if (found = true) {
                                        R_Color in = new R_Color(row, col, cells[row][col].getBackground());
                                        input_color.push(in);
                                        cells[i][j].setBackground(BG_WRONG);
                                    }
                                    found = true;
                                }
                            }
                        }
                        break;
                }
                    break;
            case 1:
                switch (col/3){
                    case 0:
                       for (int i = 3; i < 6; i++) {
                           for (int j = 0; j < 3; j++) {
                               if(i == row && j == col){
                                   continue;
                               }

                               if (cells[i][j].getText().equals(Integer.toString(k))) {
                                   if (found = true) {
                                       R_Color in = new R_Color(row, col, cells[row][col].getBackground());
                                       input_color.push(in);
                                       cells[i][j].setBackground(BG_WRONG);
                                   }
                                   found = true;
                               }
                           }
                       }
                       break;
                    case 1:
                        for (int i = 3; i < 6; i++) {
                            for (int j = 3; j < 6; j++) {
                                if(i == row && j == col){
                                    continue;
                                }

                                if (cells[i][j].getText().equals(Integer.toString(k))) {
                                    if (found = true) {
                                        R_Color in = new R_Color(row, col, cells[row][col].getBackground());
                                        input_color.push(in);
                                        cells[i][j].setBackground(BG_WRONG);
                                    }
                                    found = true;
                                }
                            }
                        }
                        break;
                    case 2:
                        for (int i = 3; i < 6; i++) {
                            for (int j = 6; j < 9; j++) {
                                if(i == row && j == col){
                                    continue;
                                }

                                if (cells[i][j].getText().equals(Integer.toString(k))) {
                                    if (found = true) {
                                        R_Color in = new R_Color(row, col, cells[row][col].getBackground());
                                        input_color.push(in);
                                        cells[i][j].setBackground(BG_WRONG);
                                    }
                                    found = true;
                                }
                            }
                        }
                        break;
                }
                break;
            case 2:
                switch (col/3){
                    case 0:
                        for (int i = 6; i < 9; i++) {
                            for (int j = 0; j < 3; j++) {
                                if(i == row && j == col){
                                    continue;
                                }

                                if (cells[i][j].getText().equals(Integer.toString(k))) {
                                    if (found = true) {
                                        R_Color in = new R_Color(row, col, cells[row][col].getBackground());
                                        input_color.push(in);
                                        cells[i][j].setBackground(BG_WRONG);
                                    }
                                    found = true;
                                }
                            }
                        }
                        break;
                    case 1:
                        for (int i = 6; i < 9; i++) {
                            for (int j = 3; j < 6; j++) {
                                if(i == row && j == col){
                                    continue;
                                }

                                if (cells[i][j].getText().equals(Integer.toString(k))) {
                                    if (found = true) {
                                        R_Color in = new R_Color(row, col, cells[row][col].getBackground());
                                        input_color.push(in);
                                        cells[i][j].setBackground(BG_WRONG);
                                    }
                                    found = true;
                                }
                            }
                        }
                        break;
                    case 2:
                        for (int i = 6; i < 9; i++) {
                            for (int j = 6; j < 9; j++) {
                                if(i == row && j == col){
                                    continue;
                                }

                                if (cells[i][j].getText().equals(Integer.toString(k))) {
                                    if (found = true) {
                                        R_Color in = new R_Color(row, col, cells[row][col].getBackground());
                                        input_color.push(in);
                                        cells[i][j].setBackground(BG_WRONG);
                                    }
                                    found = true;
                                }
                            }
                        }
                        break;
                }
                break;
        }
    }

    private void winner(){
        for (int row = 0; row < GRID_SIZE; ++row) {
            for (int col = 0; col < GRID_SIZE; ++col) {
                cells[row][col].setEditable(false);
            }
        }

        JOptionPane.showMessageDialog(null, "Congratulation!");
    }

    private JMenuBar buildMenu() {
        JMenuBar bar = new JMenuBar();
        JMenu menu = new JMenu("New Game");

        JMenuItem easy  = new JMenuItem("Easy");
        JMenuItem intermediate  = new JMenuItem("Intermediate");
        JMenuItem expert = new JMenuItem("Expert");

        menu.add(easy);
        menu.add(intermediate);
        menu.add(expert);

        bar.add(menu);

        easy.addActionListener((ActionEvent e) -> {
            dispose();
            isSolved = false;
            new Sudoku_GUI("Easy");
        });

        intermediate.addActionListener((ActionEvent e)-> {
            dispose();
            isSolved = false;
            new Sudoku_GUI("Intermediate");
        });

        expert.addActionListener((ActionEvent e)-> {
            dispose();
            isSolved = false;
            new Sudoku_GUI("Expert");
        });

        return bar;
    }

    private void undo() {
        if(isSolved){
            return;
        }

        if(sel_col != -1 && sel_row != -1){
            cells[sel_row][sel_col].setBackground(BG_OPEN);
        }

        while(input_color.size() > 0){
            R_Color in = input_color.pop();
            cells[in.getRow()][in.getCol()].setBackground(in.getColor());
        }

        if(!undo_stack.isEmpty()){
            Input_Undo x = undo_stack.pop();
            cells[x.getRow()][x.getCol()].setText(x.getInput());
            cells[x.getRow()][x.getCol()].setBackground(BG_OPEN);
        }
    }

    private void solve(){
        if(isSolved){
            return;
        }

        if(sel_col != -1 && sel_row != -1){
            cells[sel_row][sel_col].setBackground(BG_OPEN);
        }

        while(input_color.size() > 0){
            R_Color in = input_color.pop();
            cells[in.getRow()][in.getCol()].setBackground(in.getColor());
        }

        for(int i = 0; i < GRID_SIZE; ++i){
            for(int j = 0; j < GRID_SIZE; ++j) {
                if (!mask[i][j]) {
                    cells[i][j].setForeground(FG_CLOSE);
                    cells[i][j].setText("" + board[i][j]);
                }
            }
        }

        isSolved = true;
        for (int row = 0; row < GRID_SIZE; ++row) {
            for (int col = 0; col < GRID_SIZE; ++col) {
                cells[row][col].setBackground(BG_OPEN);
                cells[row][col].setEditable(false);
            }
        }
    }

    private void checkSolution(){
        if(isSolved){
            return;
        }

        if(sel_col != -1 && sel_row != -1){
            cells[sel_row][sel_col].setBackground(BG_OPEN);
        }

        while(input_color.size() > 0){
            R_Color in = input_color.pop();
            cells[in.getRow()][in.getCol()].setBackground(in.getColor());
        }

        for (int row = 0; row < GRID_SIZE; ++row) {
            for (int col = 0; col < GRID_SIZE; ++col) {
                if(!cells[row][col].getText().equals("")) {
                    if (!cells[row][col].getText().equals("" + board[row][col])) {
                        R_Color in = new R_Color(row, col, cells[row][col].getBackground());
                        input_color.add(in);
                        cells[row][col].setBackground(BG_DIF_SOL);
                    }
                }
            }
        }
    }

    public Sudoku_GUI(String difficulty){
        gen = new SudokuGenerator(difficulty);
        container.setLayout(new BorderLayout());
        JPanel grid = new JPanel();
        grid.setLayout(new GridLayout(GRID_SIZE, GRID_SIZE));
        InputListener listener = new InputListener();
        for(int row = 0; row < GRID_SIZE; ++row){
            for(int col = 0; col < GRID_SIZE; ++col){
                cells[row][col] = new JTextField();
                sub_cells[row][col] = new JTextField();
                cells[row][col].setDocument(new JTextFieldLimit(1));
                grid.add(cells[row][col]);
                if(!mask[row][col]){
                    sub_cells[row][col].setText("");
                    cells[row][col].setText("");
                    cells[row][col].setEditable(true);
                    cells[row][col].setBackground(BG_OPEN);
                    cells[row][col].addKeyListener(listener);
                }
                else{
                    sub_cells[row][col].setText(board[row][col] + "");
                    cells[row][col].setText(board[row][col] + "");
                    cells[row][col].setEditable(false);
                    cells[row][col].setBackground(BG_CLOSE);
                    cells[row][col].setForeground(FG_CLOSE);
                }
                cells[row][col].setHorizontalAlignment(JTextField.CENTER);
                cells[row][col].setFont(FONT_NUMBERS);
            }
        }

        container.setPreferredSize(new Dimension(CANVAS_SIZE, CANVAS_SIZE));

        JButton undoButton = new JButton("Undo");
        undoButton.setMaximumSize(new Dimension(10, 10));
        JButton clearButton = new JButton("clear");
        clearButton.setMaximumSize(new Dimension(10, 10));
        JButton solveButton = new JButton("Solve");
        solveButton.setMaximumSize(new Dimension(10, 10));

        JPanel buttonPanel = new JPanel();
        buttonPanel.setLayout(new GridLayout(3, 9));
        JButton[] Button = new JButton[9];
        for (int i = 0; i < 9; i++) {
            Button[i] = new JButton(i + 1 + "");
            Button[i].setPreferredSize(new Dimension(10,10));
            Button[i].setFont(FONT_NUMBERS);
            Button[i].setBackground(new Color(15, 200, 255));
            Button[i].setForeground(Color.BLACK);
            Button[i].addActionListener(this::actionPerformed);
            buttonPanel.add(Button[i]);
        }
        buttonPanel.add(clearButton);
        buttonPanel.add(undoButton);
        buttonPanel.add(solveButton);
        buttonPanel.add(checkSol);

        JMenuBar menu = buildMenu();
        setJMenuBar(menu);
        container.add(grid,   BorderLayout.CENTER);
        container.add(buttonPanel, BorderLayout.SOUTH);

        undoButton.addActionListener((ActionEvent e) -> {
            undo();
        });

        solveButton.addActionListener((ActionEvent e) -> {
            solve();
        });

        clearButton.addActionListener((ActionEvent e) -> {
            ;
        });

        checkSol.addActionListener((ActionEvent e) -> {
            checkSolution();
        });

        pack();

        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);  // Handle window closing
        setTitle("Sudoku");
        setVisible(true);
    }

}
