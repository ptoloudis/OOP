package ce326.hw2;

import java.lang.Exception;

public class UnsupporedFileFormatExtesion extends Exception {

    public UnsupporedFileFormatExtesion() {
        System.out.println("Unsupported file format!");
    }

    public UnsupporedFileFormatExtesion(String message) {
        System.out.println(message);
    }


}
