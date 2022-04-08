package ce326.hw2;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class Histogram {
    private int[] histogram = new int[236];
    private float size;
    private YUVImage image;

    public Histogram(YUVImage image) {
        this.size = (float) (image.height * image.width);
        this.image = image;
        short x;
        for (int i = 0; i < image.height; i++) {
            for (int j = 0; j < image.width; j++) {
                x = image.image[i][j].getY();
                this.histogram[x]++;
            }
        }
    }

    public String toString() {
        int thousand, hundred, ten, one, tmp;
        StringBuilder s = new StringBuilder();

        for (int i = 0; i < 236; i++) {
            s.append( String.format("\n%3d.(%4d)\t", i, histogram[i]));
            tmp = histogram[i];
            thousand = tmp / 1000;
            hundred = (tmp % 1000) / 100;
            ten = (tmp % 100) / 10;
            one = tmp % 10;
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
            String tmp = toString();
            writer.write(tmp);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public short getEqualizedLuminocity(int luminocity){
        return (short) histogram[luminocity];
    }

    public void equalize(){
        float[] pdf = new float[236];
        float[] cdf = new float[236];
        int x;
        float z = 0;

        for (int i = 0; i < 236; i++) {
            z = (float) histogram[i];
            pdf[i] = ( z / size);
        }

        cdf[0] = pdf[0];
        for (int i = 1; i < 236; i++) {
            cdf[i] = cdf[i-1] + pdf[i];
        }

        for (int i = 0; i < 236; i++) {
            histogram[i]= (int) (235 * cdf[i]);
        }

        for (int i = 0; i < image.height; i++) {
            for (int j = 0; j < image.width; j++) {
                x = image.image[i][j].getY();
                image.image[i][j].setY((short) histogram[x]);
            }
        }
    }

}
