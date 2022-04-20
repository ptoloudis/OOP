import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Sudoku implements ActionListener{
    private JButton[][] grind = new JButton[9][9];
    public JFrame frame = new JFrame("Sudoku");
    private JPanel panel = new JPanel();

    public Sudoku(int [][] table){
        frame.setLayout(new BoxLayout(frame.getContentPane(), BoxLayout.Y_AXIS));
        frame.setPreferredSize(new Dimension(500,600));
        frame.setDefaultCloseOperation(frame.EXIT_ON_CLOSE);
        JPanel buttonPanel = new JPanel();
        frame.add(buttonPanel);
        buttonPanel.setLayout(new GridLayout(9,9));
        String label=null;
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                label = table[i][j]==0?"":Integer.toString(table[i][j]);
                grind[i][j] = new JButton(label);
                grind[i][j].setFont( new Font("Arial", Font.BOLD, 20) );
                grind[i][j].setPreferredSize(new Dimension(30,30));
                buttonPanel.add(grind[i][j]);
            }

        }
    }

//    public static void main(String []args) {
//        Sudoku sg = new Sudoku();
//        sg.frame.pack();
//        sg.frame.setVisible(true);
//    }

    @Override
    public void actionPerformed(ActionEvent e) {
        System.out.println("Action performed");
    }
}