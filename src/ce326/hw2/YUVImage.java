package ce326.hw2;

import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class YUVImage {
    int width;
    int height;
    public YUVPixel[][] image;

    public YUVImage(int width, int height) {
        this.width = width;
        this.height = height;
        image = new YUVPixel[height][width];
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                image[i][j] = new YUVPixel((short) 16, (short) 128, (short) 128);
            }
        }
    }

    public YUVImage(YUVImage image){
        this.width = image.width;
        this.height = image.height;
        this.image = new YUVPixel[height][width];
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                this.image[i][j] = new YUVPixel(image.image[i][j].getY(), image.image[i][j].getU(), image.image[i][j].getV());
            }
        }
    }

    public YUVImage(RGBImage image) {
        this.width = image.getWidth();
        this.height = image.getHeight();
        this.image = new YUVPixel[height][width];
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                this.image[i][j] = new YUVPixel(image.getPixel(i, j));
            }
        }
    }

    // Method
    public void egualize(){
        Histogram hist = new Histogram(this);
        hist.equalize();
    }

    public void toFile(java.io.File file) throws FileNotFoundException, UnsupporedFileFormatExtesion {
        Scanner sc = new Scanner(file);
        String line = sc.next();
        if (line.equals("YUV")) {
            throw new UnsupporedFileFormatExtesion();
        }
        this.width = sc.nextInt();
        this.height = sc.nextInt();
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                short y = sc.nextShort();
                short u = sc.nextShort();
                short v = sc.nextShort();
                image[i][j] = new YUVPixel(y, u, v);
            }
        }
    }

    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append( width + "x  " + height + "\n");
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                sb.append(image[i][j].toString());
            }
            sb.append("\n");
        }
        return sb.toString();
    }

}
