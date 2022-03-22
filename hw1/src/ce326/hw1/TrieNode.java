package ce326.hw1;

// Class definition for TrieNode
public class TrieNode {
    TrieNode[] children = new TrieNode[26]; // 26 children
    StringBuffer[] edge= new StringBuffer[26]; // 26 strings
    boolean isEndOfWord; // true if the node is the end of a word


    public TrieNode(boolean isEndOfWord) {
        this.isEndOfWord = isEndOfWord;
    }  // initializes the node with no children and no edges

    public void setIsEnd(boolean isEndOfWord) {
        this.isEndOfWord = isEndOfWord;
    } // sets the isEndOfWord field of the node

    public boolean isFinal() {
        for (int i = 0; i < 26; i++) {
            if (children[i] != null) {
                return false;
            }
        }
        return true;
    } // returns true if the node have no children

    public int totalChildren() {
        int count = 0;
        for (int i = 0; i < 26; i++) {
            if (children[i] != null) {
                count++;
            }
        }
        return count;
    } // returns the number of children of the node

}
