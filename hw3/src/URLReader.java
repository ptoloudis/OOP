import java.net.*;
import java.io.*;

public class URLReader {
    int[][] table = new int[9][9];

    public URLReader( int difficulty ){

        int x = 0;
        URL url=null;
        try {
            switch (difficulty) {
                case 0: url = new URL("http://gthanos.inf.uth.gr/~gthanos/sudoku/exec.php?difficulty=easy");
                    break;
                case 1: url = new URL("http://gthanos.inf.uth.gr/~gthanos/sudoku/exec.php?difficulty=intermediate");
                    break;
                case 2: url = new URL("http://gthanos.inf.uth.gr/~gthanos/sudoku/exec.php?difficulty=expert");
                    break;
            }

            BufferedReader in = new BufferedReader(new InputStreamReader(url.openStream()) );

            System.out.println("Reading from URL...");


            for(int i =0; i<9; i++){
                for(int j=0; j<9; j++){
                    x = in.read();
                    if (x == 46){
                        x = 0;
                    }
                    else{
                        x = x - '0';
                    }
                    table[i][j] = x;
                }
                x = in.read();
            }
            in.close();
        }
        catch(IOException ex) {
            System.out.println("Error while reading or writing from URL: "+url.toString() );
        }
    }

    public int[][] getTable(){
        return table;
    }
}
