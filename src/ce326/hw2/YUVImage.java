package ce326.hw2;

import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class YUVImage {
    int width;
    int height;
    public YUVPixel[][] image;

    public YUVImage(int height, int width) {
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

    public YUVImage(java.io.File file) throws FileNotFoundException, UnsupportedFileFormatException {
        if (!file.exists()){
            throw new FileNotFoundException();
        }

        Scanner sc = new Scanner(file);
        String line = sc.next();
        if (!line.equals("YUV3")) {
            throw new UnsupportedFileFormatException();
        }
        this.width = Integer.parseInt(sc.next());
        this.height = Integer.parseInt(sc.next());
        this.image = new YUVPixel[height][width];
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                this.image[i][j] = new YUVPixel((short) 0, (short) 0, (short) 0);
            }
        }

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                short y = Short.parseShort(sc.next());
                short u = Short.parseShort(sc.next());
                short v = Short.parseShort(sc.next());
                this.image[i][j].setY(y);
                this.image[i][j].setU(u);
                this.image[i][j].setV(v);

            }
        }
    }

    // Method
    public void equalize(){
        Histogram hist = new Histogram(this);
        hist.equalize();
    }

    public void toFile(java.io.File file) {
        if (file.exists()) {
            file.delete();
        }
        try {
            file.createNewFile();
            FileWriter fw = new FileWriter(file);
            fw.write("YUV3\n");
            fw.write(width + " " + height + "\n");
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    fw.write(image[i][j].toString() + "\n");
                }
            }
            fw.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append( width + " " + height + "\n");
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                sb.append(image[i][j].toString());
            }
            sb.append("\n");
        }
        return sb.toString();
    }

}
