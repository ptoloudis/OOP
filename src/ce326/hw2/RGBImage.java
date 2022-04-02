package ce326.hw2;

public class RGBImage implements Image {
    private int width;
    private int height;
    private int colordepth;
    final int MAX_COLORDEPTH = 255;
    private RGBPixel[][] image;

//    Constructor for RGBImage
    public RGBImage(){
        width = 0;
        height = 0;
        colordepth = 0;
    }

    public RGBImage(int width, int height, int colordepth) {
        this.width = width;
        this.height = height;
        this.colordepth = colordepth;
        image = new RGBPixel[height][width];
    }

    public RGBImage(RGBImage copyImage){
        width = copyImage.getWidth();
        height = copyImage.getHeight();
        colordepth = copyImage.getColorDepth();
        image = new RGBPixel[height][width];
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                image[i][j] = copyImage.getPixel(i, j);
            }
        }
    }

//    Method from RGBImage
    public int getWidth() {
        return width;
    }

    public int getHeight() {
        return height;
    }

    public int getColorDepth() {
        return colordepth;
    }

    public RGBPixel getPixel(int row, int col) {
        return image[row][col];
    }

    public void setPixel(int row, int col, RGBPixel pixel) {
        image[row][col] = pixel;
    }

    public void grayscale(){
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                int gray = (int) ((image[i][j].getRed() * 0.3 )+ (image[i][j].getGreen() * 0.59) + (image[i][j].getBlue() * 0.11));
                this.image[i][j].setRGB(gray);
            }
        }
    }

//    Method from Interface Image
    public void doublesize(){
        int newHeight = height * 2;
        int newWidth = width * 2;
        RGBPixel[][] newImage = new RGBPixel[newHeight][newWidth];
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                newImage[2*i][2*j] = image[i][j];
                newImage[2*i + 1][2*j] = image[i][j];
                newImage[2*i][2*j + 1] = image[i][j];
                newImage[2*i + 1][2*j + 1] = image[i][j];
            }
        }
        this.image = newImage;
        this.height = newHeight;
        this.width = newWidth;
    }

    public void halfsize(){
        int newHeight = height / 2;
        int newWidth = width / 2;
        short red, green, blue;
        RGBPixel[][] newImage = new RGBPixel[newHeight][newWidth];
        for (int i = 0; i < newHeight; i++) {
            for (int j = 0; j < newWidth; j++) {
                red = (short) ((image[2*i][2*j].getRed() + image[2*i + 1][2*j].getRed() + image[2*i][2*j + 1].getRed() + image[2*i + 1][2*j + 1].getRed()) / 4);
                green = (short) ((image[2*i][2*j].getGreen() + image[2*i + 1][2*j].getGreen() + image[2*i][2*j + 1].getGreen() + image[2*i + 1][2*j + 1].getGreen()) / 4);
                blue = (short) ((image[2*i][2*j].getBlue() + image[2*i + 1][2*j].getBlue() + image[2*i][2*j + 1].getBlue() + image[2*i + 1][2*j + 1].getBlue()) / 4);
                newImage[i][j] = new RGBPixel(red, green, blue);
            }
        }

        this.image = newImage;
        this.height = newHeight;
        this.width = newWidth;
    }

    public void rotateClockwise(){
        int newHeight = width;
        int newWidth = height;
        RGBPixel[][] newImage = new RGBPixel[newHeight][newWidth];
        for (int i = 0; i < newHeight; i++) {
            for (int j = 0; j < newWidth; j++) {
                newImage[i][j] = image[j][newHeight - i - 1];
            }
        }
        for (int i = 0; i < newHeight; i++) {
            for (int j = 0; j < newWidth; j++) {
                image[height - i -1][height - j -1] = newImage[i][j];
            }
        }
    }

    //   Method Override Image
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append(width + " " + height + " " + colordepth + "\n");
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                sb.append(image[i][j].toString()+" ");
            }
            sb.append("\n");
        }
        return sb.toString();
    }

}
