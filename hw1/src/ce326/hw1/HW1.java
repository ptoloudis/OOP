package ce326.hw1;

//  Library imports
import java.util.Scanner;

public class HW1 {

    public static void main(String[] args) {
        Trie tmp = new Trie();
        boolean flag;
        Scanner sc = new Scanner(System.in);
        String input,word;
        int size;

        while (true) {
            System.out.print("?:");

            input = sc.next();
            switch (input) {
                case "-i" -> {
                    word = sc.next();
                    tmp.insert(word);
                }
                case "-r" -> {
                    word = sc.next();
                    tmp.delete(word);
                }
                case "-f" -> {
                    word = sc.next();
                    flag = tmp.search(word);
                    if (flag) {
                        System.out.println("FND word OK");
                    } else {
                        System.out.println("FND word NOK");
                    }
                }
                case "-p" -> tmp.print_preOrder();
                case "-d" -> tmp.print_dictionary();
                case "-w" -> {
                    word = sc.next();
                    size = sc.nextInt();
                    tmp.distant(word, size);
                }
                case "-s" -> {
                    word = sc.next();
                    tmp.suffix_all(word);
                }
                case "-t", "-q" -> {
                    System.out.println("Bye bye!");
                    System.exit(0);
                }
            }
        }
    }

}
