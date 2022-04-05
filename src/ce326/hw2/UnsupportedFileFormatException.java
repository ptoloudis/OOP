package ce326.hw2;

import java.lang.Exception;

public class UnsupportedFileFormatException extends Exception {

    public UnsupportedFileFormatException() {
        System.out.println("Unsupported file format!");
    }

    public UnsupportedFileFormatException(String message) {
        System.out.println(message);
    }


}
