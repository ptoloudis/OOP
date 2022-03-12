package ce326.hw1;

//  Library imports
import java.util.Scanner;

public class HW1 {

    public static void main(String[] args) {
        Trie tmp = new Trie();
        boolean flag;
        Scanner sc = new Scanner(System.in);
        String input,word;

        while (true) {
            System.out.print("?:");

            input = sc.next();
            switch (input) {
                case "-i":
                    word = sc.next();
                    tmp.insert(word);
                    break;
                case "-r":
                    word = sc.next();
                    tmp.delete(word);
                    break;
                case "-f":
                    word = sc.next();
                    flag = tmp.search(word);
                    if (flag) {
                        System.out.println("FND word OK");
                    }
                    else {
                        System.out.println("FND word NOK");
                    }
                    break;
                case "-p":
                    tmp.print_preOrder();
                    break;
                case "-d":
                    tmp.print_dictionary();
                    break;
                case "-w":
//                        TODO: -w command
                    break;
                case "-s":
                    word = sc.next();
                    tmp.suffix_all(word);
                    break;
                case "-t":

                case "-q":
                    System.out.println("Bye bye!");
                    System.exit(0);
            }
        }
    }

}
