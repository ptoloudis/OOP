package ce326.hw2;

import java.io.*;
import java.util.Scanner;

public class PPMImage extends RGBImage {
    private File file;
    private StringBuffer photo = new StringBuffer();

//    Constructor
    public PPMImage(java.io.File fileName) throws FileNotFoundException, UnsupportedFileFormatException {
        super();
        if ( !fileName.exists() || !fileName.canRead()) {
            throw new FileNotFoundException();
        }

        Scanner sc = new Scanner(fileName);
        if( !sc.nextLine().equals("P3")) {
            throw new UnsupportedFileFormatException();
        }

        this.file = fileName;
        super.width = sc.nextInt();
        super.height = sc.nextInt();
        super.colordepth = sc.nextInt();
        super.image = new RGBPixel[super.height][super.width];
        for (int i = 0; i < super.height; i++) {
            for (int j = 0; j < super.width; j++) {
                super.image[i][j] = new RGBPixel(sc.nextShort(), sc.nextShort(), sc.nextShort());
            }
        }

    }

    public PPMImage(RGBImage image)  {
        super(image);
    }

    public PPMImage(YUVImage image){
       super(image);
    }

//  Method

    public String toString() {
        String str = "";
        try {
            Scanner sc = new Scanner(this.file);
            sc.nextLine();
            while(sc.hasNextLine()) {
                str += sc.nextLine() + "\n";
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        return str;
    }

    public void toFile(java.io.File file) {
        if (file.exists()) {
            file.delete();
        }
        try {
            file.createNewFile();
            FileWriter fw = new FileWriter(file);
            fw.write("P3\n");
            StringBuilder sb = new StringBuilder();
            sb.append(super.width + " " + super.height + " " + super.colordepth + "\n");
            for (int i = 0; i < super.height; i++) {
                for (int j = 0; j < super.width; j++) {
                    sb.append(super.image[i][j].toString()+"\n");
                }
            }
            fw.write(sb.toString());
            fw.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
