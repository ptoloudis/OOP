package ce326.hw2;

public class RGBPixel {
    byte red;
    byte green;
    byte blue;

//    Constructor for RGBPixel
    public RGBPixel(short red, short green, short blue) {
        this.red = (byte) (red - 128);
        this.green = (byte) (green - 128);
        this.blue = (byte) (blue - 128);
    }

    public RGBPixel(RGBPixel pixel){
        this.red = pixel.red;
        this.green = pixel.green;
        this.blue = pixel.blue;
    }

//    public  void RGBPixel(YUVPixel pixel){
//        System.out.println("YUVPixel");
//    }

//    Method from RGBPixel
    public short getRed() {
        return (short) this.red;
    }

    public short getGreen() {
        return (short) this.green;
    }

    public short getBlue() {
        return (short) this.blue;
    }

    public void setRed(short red) {
        this.red = (byte) (red - 128);
    }

    public void setGreen(short green) {
        this.green = (byte) (green - 128);
    }

    public void setBlue(short blue) {
        this.blue = (byte) (blue - 128);
    }

    public int getRGB() {
        return (this.red << 16) | (this.green << 8) | this.blue;
    }

    void setRGB(int value) {
        this.red = (byte) ((value >> 16) & 0xFF);
        this.green = (byte) ((value >> 8) & 0xFF);
        this.blue = (byte) (value & 0xFF);
    }

    final void setRGB(short red, short green, short blue) {
        this.red = (byte) (red - 128);
        this.green = (byte) (green - 128);
        this.blue = (byte) (blue - 128);
    }

    @Override
    public String toString() {
        return (this.red +" "+ this.green +" "+this.blue
        );
    }

}
