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

    public  void RGBPixel(YUVPixel pixel){
        int C = pixel.getY() - 16;
        int D = pixel.getU() - 128;
        int E = pixel.getV() - 128;

        this.red = (byte) clip((298 * C + 409 * E + 128)>>8);
        this.green = (byte) clip(298 * C - 100 * D - 208 * E + 128);
        this.blue = (byte) clip(298 * C + 516 * D + 128);

    }

//    Method from RGBPixel
    private short clip(int x) {
        if (x < 0)
            return 0;
        else if (x > 255)
            return 255;
        else
            return (short) x;
    }

    public short getRed() {
        return (short) (((short) this.red) + 128);
    }

    public short getGreen() {
        return (short) (((short) this.green) + 128);
    }

    public short getBlue() {
        return (short) (((short) this.blue) + 128);
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
        this.red = (byte) ((value >> 16) & 0xFF - 128);
        this.green = (byte) ((value >> 8) & 0xFF - 128);
        this.blue = (byte) (value & 0xFF - 128);
    }

    final void setRGB(short red, short green, short blue) {
        this.red = (byte) (red - 128);
        this.green = (byte) (green - 128);
        this.blue = (byte) (blue - 128);
    }

    @Override
    public String toString() {
        return ((this.red +128) +" "+ (this.green +128) +" "+ (this.blue +128));
    }

}
