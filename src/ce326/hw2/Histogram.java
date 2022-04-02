package ce326.hw2;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class Histogram {
    private int[] histogram;
    private int size;
    private YUVImage image;

    public Histogram(YUVImage image) {
        this.image = image;
        size = image.height * image.width;
        histogram = new int[256];
        short x;
        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                x = image.image[i][j].getY();
                histogram[x]++;
            }
        }
    }

    public String toString() {
        int thousand, hundred, ten, one;
        StringBuffer s = new StringBuffer();

        for (int i = 0; i < 256; i++) {
            s.append( String.format("\n%.3f\t(%.4f)\t", (double) i, (double) histogram[i]));
            thousand = histogram[i] / 1000;
            hundred = (histogram[i] % 1000) / 100;
            ten = (histogram[i] % 100) / 10;
            one = histogram[i] % 10;
            for (int j = 0; j < thousand; j++) {
                s.append("#");
            }
            for (int j = 0; j < hundred; j++) {
                s.append("$");
            }
            for (int j = 0; j < ten; j++) {
                s.append("@");
            }
            for (int j = 0; j < one; j++) {
                s.append("*");
            }

        }
        s.append("\n");
        return s.toString();
    }

    public void toFile(File file)  {
        try (FileWriter writer = new FileWriter(file)) {
            writer.write(toString());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public short getEqualizedLuminocity(int luminocity){
        return (short) histogram[luminocity];
    }

    public void equalize(){
        float pdf[] = new float[256];
        float cdf[] = new float[256];
        int x;

        for (int i = 0; i < 256; i++) {
            pdf[i] = histogram[i]/size;
        }
        cdf[0] = pdf[0];
        for (int i = 1; i < 256; i++) {
            cdf[i] = cdf[i-1] + pdf[i];
        }
        for (int i = 0; i < 256; i++) {
            histogram[i]= (int) (235 *cdf[i]);
        }

        for (int i = 0; i < image.width; i++) {
            for (int j = 0; j < image.height; j++) {
                x = image.image[i][j].getY();
                image.image[i][j].setY((short) histogram[x]);
            }
        }
    }

}
