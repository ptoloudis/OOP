package ce326.hw1;

//  Library imports
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;


// Class definition for Trie
class Trie {
    private TrieNode root ;
    private char Case ;

    public Trie() {
        root = new TrieNode(false);
        this.Case = 'a';
    }

    public void insert(String word) {
        word = word.toLowerCase();

        if (search(word) == true) {
            System.out.println("ADD word NOK");
            return;
        }

        TrieNode current = root;
        int i =0, j =0, pos =0;

        while (word.length() > i && current.edge[word.charAt(i)- Case] != null) {
            pos = word.charAt(i) - Case;
            j = 0;

            StringBuffer label = current.edge[pos];
            while (j < label.length() && label.charAt(j) == word.charAt(i)) {
                j++;
                i++;
            }

            if (j == label.length()) {
                current = current.children[pos];
            }
            else {
                if(i == word.length()) {
                    TrieNode existingNode = current.children[pos];
                    TrieNode newNode = new TrieNode(true);
                    StringBuffer remaining = strCopy(label, j);
                    current.children[pos] = newNode;
                    newNode.children[remaining.charAt(0) - Case] = existingNode;
                    newNode.edge[word.charAt(i) - Case] = remaining;
                }
                else {
                    StringBuffer remaining = strCopy(label, j);
                    TrieNode newNode = new TrieNode(false);
                    StringBuffer remainingWord = strCopy(word, j);

                    TrieNode  temp = current.children[pos];
                    label.setLength(j);
                    current.children[pos] = newNode;

                    newNode.edge[remaining.charAt(0) - Case] = remainingWord;
                    newNode.edge[remainingWord.charAt(0) - Case] = remaining;

                    newNode.children[remaining.charAt(0) - Case] = new TrieNode(true);
                    newNode.children[remainingWord.charAt(0) - Case] = temp;

                }
                System.out.println("ADD word OK");
                return;
            }

        }
        if (i < word.length()) {
            current.edge[word.charAt(i) - Case] = strCopy(word, i);
            current.children[word.charAt(i) - Case] = new TrieNode(true);
        }
        else {
            current.setIsEnd(true);
        }
        System.out.println("ADD word OK");
    }

    private StringBuffer strCopy(CharSequence str, int pos) {
        StringBuffer temp = new StringBuffer(100);
        for (int i = pos; i < str.length(); i++) {
            temp.append(str.charAt(i));
        }
        return temp;
    }

    public void print_dictionary(){
        printUtil(root, new  StringBuffer());
    }

    private void printUtil(TrieNode current, StringBuffer str) {
        if (current.isEndOfWord) {
            System.out.println(str);
        }
        for (int i = 0; i < root.edge.length; ++i) {
            if (current.children[i] != null) {
                int length = str.length();

                str = str.append(current.edge[i]);
                printUtil(current.children[i], str);
                str = str.delete(length, str.length());

            }
        }
    }

    public boolean search(String word) {
        word = word.toLowerCase();
        TrieNode current = root;
        int i =0, j =0, pos =0;

        while (word.length() > i && current.edge[word.charAt(i)- Case] != null) {
            pos = word.charAt(i) - Case;
            StringBuffer label = current.edge[pos];
            j = 0;

            while (j < word.length() && j < label.length()) {
                if (word.charAt(j) != label.charAt(i)) {
                    return false;
                }
                j++;
                i++;
            }

            if (j == label.length() && i <= word.length()) {
                current = current.children[pos];
            }
            else {
                return false;
            }
        }
        return i == word.length() && current.isEndOfWord;
    }

    public void delete(String word) {
        word = word.toLowerCase();
        TrieNode current = root;
        int i =0, j =0, pos =0;

        while (word.length() > i && current.edge[word.charAt(i)- Case] != null) {
            pos = word.charAt(i) - Case;
            j = 0;

            while (j < word.length() && word.charAt(j) == word.charAt(i)) {
                if (word.charAt(j) != word.charAt(i)) {
                    System.out.println("DEL word NOK");
                }
                j++;
                i++;
            }

            if (j == word.length() && i <= word.length()) {
                current = current.children[pos];
            }
            else {
                System.out.println("DEL word NOK");
            }

        }

        if((i == word.length() && current.isEndOfWord) == true) {
            current.isEndOfWord = false;
            System.out.println("DEL word OK");
        }
        else {
            System.out.println("DEL word NOK");
        }
    }

    public void print_preOrder() {
        System.out.println("PreOrder: ");
        printPreOrder(root);
        System.out.println();
    }

    private void printPreOrder(TrieNode current){
        if(current.isEndOfWord){
            if(current.isFinal() == true){
                System.out.print("(T)");
            }
            System.out.println(current.edge+" ");
        }
        for(int i = 0; i < root.edge.length; ++i){
            if(current.children[i] != null){
                printPreOrder(current.children[i]);
            }
        }
    }

    public void suffix_all(String word) {
        suffix(word);
        System.out.println();
    }

    private void suffix(String word) {
        word = word.toLowerCase();
        TrieNode current = root;
        int i =0, j =0, pos =0;

        while (word.length() > i && current.edge[word.charAt(i)- Case] != null) {
            pos = word.charAt(i) - Case;
            j = 0;

            while (j < word.length() && word.charAt(j) == word.charAt(i)) {
                if (word.charAt(j) == word.charAt(i)) {
                    return;
                }
                j++;
                i++;
            }

            if (j == word.length() && i <= word.length()) {
                current = current.children[pos];
            }
            else {
                return;
            }

        }

        if((i == word.length() && current.isEndOfWord) == true) {
            System.out.println();
            System.out.println("Word is a suffix " + word + ":");
            System.out.println(current.edge);
        }
        else {
            return;
        }
    }

    public void printDot( ) throws FileNotFoundException {
        PrintWriter wr = new PrintWriter(new File("trie.dot"));
        System.out.println("digraph G {");
        print_dot(wr, root, new  StringBuffer());
        System.out.println("}");
    }

    private void print_dot(PrintWriter wr, TrieNode current, StringBuffer str){
        if (current.isEndOfWord) {
            wr.print(str);
        }
        for (int i = 0; i < root.edge.length; ++i) {
            if (current.children[i] != null) {
                int length = str.length();

                str = str.append(current.edge[i]);
                printUtil(current.children[i], str);
                str = str.delete(length, str.length());
            }
        }
    }

//    TODO: make -w word X
}