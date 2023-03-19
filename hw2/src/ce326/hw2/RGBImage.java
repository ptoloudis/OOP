package ce326.hw2;

public class RGBImage implements Image {
    int width;
    int height;
    int colordepth;
    static final int MAX_COLORDEPTH = 255;
    RGBPixel[][] image;

//    Constructor for RGBImage
    public RGBImage(){}

    public RGBImage(int height , int width , int colordepth) {
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

    public RGBImage(YUVImage yuvImage) {
        RGBPixel rgbPixel;
        YUVPixel yuvPixel;
        width = yuvImage.width;
        height = yuvImage.height;
        colordepth = MAX_COLORDEPTH;
        image = new RGBPixel[height][width];
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                yuvPixel = yuvImage.image[i][j];
                rgbPixel = new RGBPixel(yuvPixel);
                image[i][j] = rgbPixel;

            }
        }
    }

//    Method from RGBImage
    public int getWidth() {
        return this.width;
    }

    public int getHeight() {
        return this.height;
    }

    public int getColorDepth() {
        return colordepth;
    }

    public RGBPixel getPixel(int row, int col) {
        return this.image[row][col];
    }

    public void setPixel(int row, int col, RGBPixel pixel) {
        image[row][col] = pixel;
    }

    public void grayscale(){
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                short gray = (short) ((image[i][j].getRed() * 0.3 )+ (image[i][j].getGreen() * 0.59) + (image[i][j].getBlue() * 0.11));
                this.image[i][j].setRed(gray);
                this.image[i][j].setGreen(gray);
                this.image[i][j].setBlue(gray);
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
        int newHeight = this.width;
        int newWidth = this.height;
        RGBPixel[][] newImage = new RGBPixel[newHeight][newWidth];
        for (int k = 0; k < this.height; k++) {
            for (int l = 0; l < this.width; l++) {
                newImage[l][k] = image[this.height-1-k][l];
            }
        }
        this.height = newHeight;
        this.width = newWidth;
        this.image = newImage;
    }

    //   Method Override Image
    @Override
    public String toString(){
        StringBuilder sb = new StringBuilder();
        sb.append(width + " " + height + " " + colordepth + "\n");
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                sb.append(image[i][j].toString()+"\n");
            }
            sb.append("\n");
        }
        return sb.toString();
    }

}
