package ece326.hw3;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.URLConnection;


public class Network {

    private static final String Easy = "http://gthanos.inf.uth.gr/~gthanos/sudoku/exec.php?difficulty=easy";
    private static final String Intermediate = "http://gthanos.inf.uth.gr/~gthanos/sudoku/exec.php?difficulty=intermediate";
    private static final String Expert = "http://gthanos.inf.uth.gr/~gthanos/sudoku/exec.php?difficulty=expert";

    int[][] board = new int[9][9];

    public Network(String difficulty) {
        URL url=null;

        if ( difficulty.equals("Default" )){ //For Start the Game
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    board[i][j] = 0;
                }
            }
            return;
        }

        try {
            switch (difficulty) {
                case "Easy" -> url = new URL(Easy);
                case "Intermediate" -> url = new URL(Intermediate);
                case "Expert" -> url = new URL(Expert);
            }
            assert url != null;
            URLConnection urlcon = url.openConnection();
            BufferedReader in = new BufferedReader( new InputStreamReader(urlcon.getInputStream()) );

            int k;
            for (int i = 0; i < 9; i++) {
                String line = in.readLine();
                for (int j = 0; j < 9; j++) {
                    k = line.charAt(j) - '0';
                    if (k < 0)
                        k = 0;
                    board[i][j] = k;
                }
            }
            in.close();

            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    System.out.print(board[i][j] + " ");
                }
                System.out.println();
            }
        }
        catch(MalformedURLException ex) {
            switch (difficulty) {
                case "Easy" -> System.out.println("Invalid URL: " + Easy);
                case "Intermediate" -> System.out.println("Invalid URL: " + Intermediate);
                case "Expert" -> System.out.println("Invalid URL: " + Expert);
            }
            ex.printStackTrace();
        }
        catch(IOException ex) {
            System.out.println("Error while reading or writing from URL: "+url);
        }
    }

    public int[][] getBoard() {
        return board;
    }
}
