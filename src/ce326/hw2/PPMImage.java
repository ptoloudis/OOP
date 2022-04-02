package ce326.hw2;

import java.io.*;
import java.util.Scanner;

public class PPMImage {
    private StringBuffer header;

//    Constructor
    public PPMImage(String Name) throws FileNotFoundException, UnsupporedFileFormatExtesion {
        File fileName = new File(Name);
        if ( !fileName.exists() || !fileName.canRead()) {
            throw new FileNotFoundException();
        }

        Scanner sc = new Scanner(fileName);
        if( !sc.nextLine().equals("P3")) {
            throw new UnsupporedFileFormatExtesion();
        }

    }

    public PPMImage(RGBImage image) {
//        this.fileName = new File(image.getFileName());
    }

    public String toString() {
        return this.header.toString();
    }

    public void toFile(java.io.File file) {
        try {
            PrintWriter pw = new PrintWriter(file);
            pw.print(this.header.toString());
            pw.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }

}
