package ce326.hw1;

// Class definition for TrieNode
public class TrieNode {
    TrieNode[] children = new TrieNode[26];
    StringBuffer[] edge= new StringBuffer[26];
    boolean isEndOfWord;


    public TrieNode(boolean isEndOfWord) {
        this.isEndOfWord = isEndOfWord;
    }

    public void setIsEnd(boolean isEndOfWord) {
        this.isEndOfWord = isEndOfWord;
    }

    public boolean isFinal() {
        for (int i = 0; i < 26; i++) {
            if (children[i] != null) {
                return false;
            }
        }
        return true;
    }

    public int totalChildren() {
        int count = 0;
        for (int i = 0; i < 26; i++) {
            if (children[i] != null) {
                count++;
            }
        }
        return count;
    }

    public int position_edge() {
        for (int i = 0; i < 26; i++) {
            if (edge[i] != null) {
                return i;
            }
        }
        return -1;
    }

}
