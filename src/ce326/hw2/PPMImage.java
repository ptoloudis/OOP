package ce326.hw2;

import java.io.*;
import java.util.Scanner;

public class PPMImage extends RGBImage {
    private File file;
    private StringBuffer photo = new StringBuffer();

//    Constructor
    public PPMImage(java.io.File fileName) throws FileNotFoundException, UnsupportedFileFormatException {
        super(width, height, sc.nextInt());
        if ( !fileName.exists() || !fileName.canRead()) {
            throw new FileNotFoundException();
        }

        Scanner sc = new Scanner(fileName);
        if( !sc.nextLine().equals("P3")) {
            throw new UnsupportedFileFormatException();
        }

        this.file = fileName;
        int width = sc.nextInt();
        int height = sc.nextInt();
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                super.setPixel(i, j, new RGBPixel(sc.nextShort(), sc.nextShort(), sc.nextShort()));
            }
        }

    }

    public PPMImage(RGBImage image)  {
        this.photo.append("P3\n");
        String str_image = image.toString();
        this.photo.append(str_image);
    }

    public PPMImage(YUVImage image){
        this.photo.append("P3\n");
        String str_image = image.toString();
        this.photo.append(str_image);
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
            fw.write(this.photo.toString());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
