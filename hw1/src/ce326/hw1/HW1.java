package ce326.hw1;

//  Library imports
import java.util.Scanner;

public class HW1 {
    public static void main(String[] args) {
        Trie tmp = new Trie(); // Create a new Trie
        boolean flag; // flag for checking if the word is in the dictionary
        Scanner sc = new Scanner(System.in); // Create a scanner for user input
        String input,word;
        int size;

        while (true) {
            System.out.println("?: "); // Prompt user for input

            input = sc.next(); // Get user input
            switch (input) { // Check user input
                case "-i" -> { // Insert a word into the Trie
                    word = sc.next();
                    tmp.insert(word);
                }
                case "-r" -> { // Remove a word from the Trie
                    word = sc.next();
                    tmp.delete(word);
                }
                case "-f" -> { // Find a word in the Trie
                    word = sc.next();
                    flag = tmp.search(word);
                    if (flag) { // If the word is in the dictionary
                        System.out.println("FND "+word.toLowerCase()+" OK");
                    } else { // If the word is not in the dictionary
                        System.out.println("FND "+word.toLowerCase()+" NOK");
                    }
                }
                case "-p" -> tmp.print_preOrder(); // Print the Trie in pre-order
                case "-d" -> tmp.print_dictionary(); // Print the dictionary
                case "-w" -> { // Print the words same length and different in n characters
                    word = sc.next();
                    size = sc.nextInt();
                    tmp.distant(word, size);
                }
                case "-s" -> { // Print the words in the dictionary with a given prefix
                    word = sc.next();
                    tmp.suffix_all(word);
                }
                case "-q" -> { // Quit the program
                    System.out.println("Bye bye!");
                    System.exit(0);
                }
            }
        }
    }
}
