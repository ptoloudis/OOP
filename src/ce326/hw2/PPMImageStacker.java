package ce326.hw2;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.List;
import java.util.Scanner;

public class PPMImageStacker {
    private List <RGBImage> images;
    private RGBImage output;
    private int length;

    // Constructor
    public PPMImageStacker(java.io.File dir) throws FileNotFoundException, UnsupportedFileFormatException {
        boolean z = dir.exists();
        if (!z) {
            throw new FileNotFoundException("[ERROR] Directory "+ dir.getName() +" does not exist!");
        }
        if (!dir.isDirectory()) {
            throw new FileNotFoundException("[ERROR] " + dir.getName() + " is not a directory!");
        }

        int i;
        Scanner scanner;
        java.io.File[] files = dir.listFiles();
        for ( i = 0; i < files.length; i++) {
            if (files[i].isFile()) {
                scanner = new Scanner(files[i]);
                if (scanner.hasNext()) {
                    if (!scanner.next().equals("P3")) {
                        throw new UnsupportedFileFormatException();
                    }
                }
                scanner.close();
            }
        }

        int width, height, max, R, G, B;
        RGBPixel pixel;
        RGBImage image = null;
        images = new java.util.ArrayList<RGBImage>(files.length);
        this.length = files.length;

        for (i = 0; i < files.length; i++) {
            scanner = new Scanner(files[i]);
            if (scanner.hasNext()) {
                if (scanner.next().equals("P3")) {
                    width = Integer.parseInt( scanner.next());
                    height = Integer.parseInt( scanner.next());
                    max = Integer.parseInt( scanner.next());
                    image = new RGBImage(height, width, max);
                    for (int x = 0; x < height; x++) {
                        for (int y = 0; y < width; y++) {
                            R = Integer.parseInt( scanner.next());
                            G = Integer.parseInt( scanner.next());
                            B = Integer.parseInt( scanner.next());
                            pixel = new RGBPixel((short) R, (short) G, (short) B);
                            image.setPixel(x, y, pixel);
                        }
                    }
                }
            }
            scanner.close();
            images.add(image);
        }
    }

    // Method: stack
    public void stack() {
        int width = images.get(0).getWidth();
        int height = images.get(0).getHeight();
        int countR = 0, countG = 0, countB = 0;
        RGBPixel pixel;
        output = new RGBImage(height, width, output.MAX_COLORDEPTH);

        for (int x = 0; x < height; x++) {
            for (int y = 0; y < width; y++) {
                countB = 0;
                countG = 0;
                countR = 0;
                for (int i = 0; i < length; i++) {
                    countB += images.get(i).getPixel(x, y).getBlue();
                    countG += images.get(i).getPixel(x, y).getGreen();
                    countR += images.get(i).getPixel(x, y).getRed();
                }
                countB /= length;
                countG /= length;
                countR /= length;
                pixel = new RGBPixel((short) countR, (short) countG, (short) countB);
                output.setPixel(x, y, pixel);
            }
        }
    }

    // Method: PPMImage
    public PPMImage getStackedImage() {
        return new PPMImage(output);
    }

}
