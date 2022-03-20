package ce326.hw1;

// Class definition for Trie
class Trie {
    private TrieNode root ;
    final private char Case ;

    public Trie() {
        root = new TrieNode(false);
        this.Case = 'a';
    }

    public void insert(String word) {
        word = word.toLowerCase();

        if (search(word)) {
            System.out.println("ADD "+word+" NOK");
            return;
        }

        TrieNode current = root;
        int i = 0, j, index;
        while (i < word.length() && current.edge[word.charAt(i) - Case] != null) {

            index = word.charAt(i) - Case;
            j = 0;
            StringBuffer label = current.edge[index];

            while (j < label.length() && i < word.length() && label.charAt(j) == word.charAt(i)) {
                i++;
                j++;
            }

            // If is the same as the
            // label length
            if (j == label.length()) {
                current = current.children[index];
            }
            else {

                if (i == word.length()) {
                    TrieNode existingChild = current.children[index];
                    TrieNode newChild = new TrieNode(true);
                    StringBuffer remaining = strCopy(label, j);

                    label.setLength(j);

                    current.children[index] = newChild;
                    newChild.children[remaining.charAt(0) - Case] = existingChild;
                    newChild.edge[remaining.charAt(0) - Case] = remaining;

                }
                else {


                    StringBuffer remaining  = strCopy(label, j);
                    TrieNode newChild = new TrieNode(false);
                    StringBuffer remainingWord = strCopy(word, i);
                    TrieNode temp = current.children[index];

                    label.setLength(j);
                    current.children[index] = newChild;
                    newChild.edge[remaining.charAt(0) - Case] = remaining;
                    newChild.children[remaining.charAt(0) - Case] = temp;
                    newChild.edge[remainingWord.charAt(0)- Case] = remainingWord;
                    newChild.children[remainingWord.charAt(0)- Case] = new TrieNode(true);
                }
                System.out.println("ADD "+word+" OK");
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
        System.out.println("ADD "+word+" OK");
}

    private StringBuffer strCopy(CharSequence str, int pos) {
        StringBuffer temp = new StringBuffer(100);
        for (int i = pos; i < str.length(); i++) {
            temp.append(str.charAt(i));
        }
        return temp;
    }

    public void print_dictionary(){
        System.out.println();
        System.out.println("***** Dictionary *****");
        printUtil(root, new  StringBuffer());
        System.out.println();
    }

    private void printUtil(TrieNode current, StringBuffer str) {
        if (current.isEndOfWord) {
            System.out.println(str);
        }
        for (int i = 0; i < root.edge.length; ++i) {
            if (current.edge[i] != null) {
                int length = str.length();

                str.append(current.edge[i]);
                printUtil(current.children[i], str);
                str.delete(length, str.length());

            }
        }
    }

    public boolean search(String word) {
        word = word.toLowerCase();
        TrieNode current = root;
        int i =0, j , pos ;

        while (word.length() > i && current.edge[word.charAt(i)- Case] != null) {
            pos = word.charAt(i) - Case;
            StringBuffer label = current.edge[pos];
            j = 0;

            while (i < word.length() && j < label.length()) {
                if (word.charAt(i) != label.charAt(j)) {
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
        return (i == word.length() && current.isEndOfWord);
    }

    public void delete(String word) {
        word = word.toLowerCase();
        if (!search(word)) {
            System.out.println("RMV "+word+" NOK");
            return;
        }

        TrieNode current = root;
        boolean delete = true;
        int i =0, j , pos ;

        while (word.length() > i && current.edge[word.charAt(i)- Case] != null) {
            pos = word.charAt(i) - Case;
            StringBuffer label = current.edge[pos];
            j = 0;

            while (i < word.length() && j < label.length()) {
                j++;
                i++;
            }

            if (j == label.length() && i == word.length() && current.children[pos].isFinal()) {
                current.edge[pos] = null;
                current.children[pos] = null;
            }

            if (j == label.length() && i <= word.length()) {
                current = current.children[pos];
            }
            else {
                delete = false;
                System.out.println("RMV "+word+" NOK");
            }
        }
        if (current != null){
            if (i == word.length() && current.isEndOfWord) {
                current.isEndOfWord = false;
            }
        }

        if (root != null) {
            compress_dictionary(root, root, 0);
        }

        if (delete)
            System.out.println("RMV "+word+" OK");

    }

    private void compress_dictionary(TrieNode current,TrieNode parent, int pos) {
        if (current.isFinal()){
            return;
        }
        for (int i = 0; i < 26; ++i) {
            if (current.children[i] != null) {
                TrieNode tmp = current.children[i];
                compress_dictionary(tmp, current, i);
                if (current.totalChildren() == 1 && !current.isEndOfWord &&  current != root) {
                    parent.edge[pos].append(current.edge[i]);
                    current.children = tmp.children;
                    current.edge = tmp.edge;
                    current.isEndOfWord = tmp.isEndOfWord;
                }
            }
        }
    }

    public void print_preOrder() {
        System.out.print("PreOrder: ");
        printPreOrder(root);
        System.out.println();
    }

    private void printPreOrder(TrieNode current) {
        for (int i = 0; i < root.edge.length; ++i) {
            if (current.children[i] != null) {
                if (current.children[i].isEndOfWord) {
                    System.out.print(current.edge[i]+"# ");
                }
                else {
                    System.out.print(current.edge[i]+" ");
                }

                printPreOrder(current.children[i]);
            }
        }
    }

    public void suffix_all(String word) {
        word = word.toLowerCase();
        System.out.println();
        System.out.println("Words with suffix "+word+":");
        suffix(word, root, new StringBuffer());
        System.out.println();
    }

    private void suffix(String word, TrieNode current ,StringBuffer str) {
        if (current.isEndOfWord && (str.lastIndexOf(word) != -1)) {
            System.out.println(str);
        }
        for (int i = 0; i < root.edge.length; ++i) {
            if (current.edge[i] != null) {
                int length = str.length();

                str.append(current.edge[i]);
                suffix(word, current.children[i], str);
                str.delete(length, str.length());

            }
        }

    }

    public void distant(String word, int x) {
        word = word.toLowerCase();
        System.out.println();
        System.out.println("Distant words of "+word+" ("+x +"):");
        print_distant(root, word, new StringBuffer(), x);
        System.out.println();
    }

    private void print_distant(TrieNode current, String str, StringBuffer str_d, int x) {
        if(current.isEndOfWord && str_d.length() == str.length()){
            if(stringCompare(str, str_d.toString()) == x ){
                System.out.println(str_d);
            }

        }
        for (int i = 0; i < root.edge.length; ++i) {
            if (current.children[i] != null) {
                int length = str_d.length();

                str_d.append(current.edge[i]);
                print_distant(current.children[i], str, str_d, x);
                str_d.delete(length, str_d.length());

            }
        }
    }

    private int stringCompare(String str1, String str2){
        int count = 0;
        int l1 = str1.length();
        int l2 = str2.length();
        int min = Math.min(l1, l2);

        for (int i = 0; i < min; i++) {
            int str1_ch = str1.charAt(i);
            int str2_ch = str2.charAt(i);

            if (str1_ch != str2_ch) {
                count++;
            }
        }

        return count;
    }

}

