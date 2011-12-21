import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

public class kequiv_mb implements Runnable {
    private Scanner in;
    private PrintWriter out;

    public static final int MAX_LENGTH = 20;
    public static final int NUM_DIGITS = 10;
    private DigitTrie trie;

    static class TrieNode {
        public int numLinks;
        public TrieNode parent;
        public TrieNode[] links;
        public boolean isLeaf;
    }

    static interface TrieNodeProcessor {
        boolean process(short[] digits, int length);
    }

    static class DigitTrie {
        private final TrieNode root = new TrieNode();

        public void insert(short[] digits, int length) {
            //System.out.print("insert: ");
            //dumpDigits(digits, length);
            //System.out.println();

            TrieNode node = root;
            for (int i = 0; i < length; i++) {
                if (node.isLeaf) {
                    return;
                }
                int digit = digits[i];
                if (node.links == null) {
                    node.links = new TrieNode[NUM_DIGITS];
                }
                if (node.links[digit] == null) {
                    final TrieNode newNode = new TrieNode();
                    newNode.parent = node;
                    node.links[digit] = newNode;
                    node.numLinks++;
                }
                node = node.links[digit];
            }
            makeLeaf(node);
            while (node != null) {
                optimize(node);
                node = node.parent;
            }
        }

        public boolean contains(short[] digits, int length) {
            TrieNode node = root;
            for (int i = 0; i < length; i++) {
                if (node.isLeaf) {
                    return true;
                }
                int digit = digits[i];
                node = node.links[digit];
                if (node == null) {
                    return false;
                }
            }
            return node.isLeaf;
        }

        public void enumerate(TrieNodeProcessor processor) {
            short[] digits = new short[MAX_LENGTH];
            enumerate(processor, root, digits, 0);
        }

        private boolean enumerate(TrieNodeProcessor processor, TrieNode node, short[] digits, int length) {
            if (node.isLeaf) {
                return processor.process(digits, length);
            }

            if (node.links == null) {
                return true;
            }

            for (int digit = 0; digit < 10; digit++) {
                if (node.links[digit] != null) {
                    digits[length] = (short) digit;
                    if (!enumerate(processor, node.links[digit], digits, length + 1)) {
                        return false;
                    }
                }
            }
            return true;
        }

        private void optimize(TrieNode node) {
            if (node.numLinks != NUM_DIGITS) {
                return;
            }
            int numLeafs = 0;
            for (int i = 0; i < NUM_DIGITS; i++) {
                if (node.links[i].isLeaf) {
                    numLeafs++;
                }
            }
            if (numLeafs == NUM_DIGITS) {
                makeLeaf(node);
            }
        }

        private void makeLeaf(TrieNode node) {
            node.isLeaf = true;
            node.links = null;
        }
    }

    public static void main(String[] args) {
        new Thread(new kequiv_mb()).start();
    }

    public void run() {
        try {
            in = new Scanner(new FileReader("kequiv.in"));
            out = new PrintWriter("kequiv.out");

            solve();

            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void dumpDigits(short[] digits, int length) {
        for (int i = 0; i < length; i++) {
            System.out.print(digits[i]);
        }
        for (int i = 0; i < MAX_LENGTH - length; i++) {
            System.out.print("?");
        }
    }

    private short[] toDigits(long value) {
        short[] result = new short[MAX_LENGTH];
        for (int i = 0; i < MAX_LENGTH; i++) {
            result[i] = (short) (value % 10);
            value /= 10;
        }
        for (int i = 0; i < MAX_LENGTH / 2; i++) {
            short tmp = result[i];
            result[i] = result[MAX_LENGTH - i - 1];
            result[MAX_LENGTH - i - 1] = tmp;
        }
        return result;
    }

    private void insertRange(DigitTrie trie, long lo, long hi) {
        final short[] loDigits = toDigits(lo);
        final short[] hiDigits = toDigits(hi);
        int i = 0;
        while (i < MAX_LENGTH && loDigits[i] == hiDigits[i]) {
            i++;
        }

        trie.insert(loDigits, MAX_LENGTH);
        trie.insert(hiDigits, MAX_LENGTH);

        if (i == MAX_LENGTH) {
            return;
        }

        for (int j = i + 1; j < MAX_LENGTH; j++) {
            short backup = loDigits[j];
            for (short digit = (short) (loDigits[j] + 1); digit < NUM_DIGITS; digit++) {
                loDigits[j] = digit;
                trie.insert(loDigits, j + 1);
            }
            loDigits[j] = backup;

            backup = hiDigits[j];
            for (short digit = (short) (hiDigits[j] - 1); digit >= 0; digit--) {
                hiDigits[j] = digit;
                trie.insert(hiDigits, j + 1);
            }
            hiDigits[j] = backup;
        }

        for (int digit = loDigits[i] + 1; digit <= hiDigits[i] - 1; digit++) {
            loDigits[i] = (short) digit;
            trie.insert(loDigits, i + 1);
        }
    }

    static class EquivalenceChecker implements TrieNodeProcessor {
        public boolean isOK = true;

        private final DigitTrie trie;
        private final short digit1;
        private final short digit2;

        public EquivalenceChecker(DigitTrie trie, short digit1, short digit2) {
            this.trie = trie;
            this.digit1 = digit1;
            this.digit2 = digit2;
        }

        public boolean process(short[] digits, int length) {
            for (int i = 0; i < length; i++) {
                if (digits[i] == digit1 || digits[i] == digit2) {
                    //System.out.print("check ");
                    //dumpDigits(digits, length);
                    //System.out.print(" to ");
                    final short backupDigit = digits[i];
                    digits[i] = (short) (digit1 + digit2 - digits[i]);
                    //dumpDigits(digits, length);
                    isOK &= trie.contains(digits, length);
                    //System.out.print(" -> ");
                    //System.out.println(isOK);
                    digits[i] = backupDigit;
                    if (!isOK) {
                        return false;
                    }
                }
            }
            return true;
        }
    }

    private boolean areEquivalent(final short digit1, final short digit2) {
        if (digit1 == digit2) {
            return true;
        }
        final EquivalenceChecker checker = new EquivalenceChecker(trie, digit1, digit2);
        trie.enumerate(checker);
        return checker.isOK;
    }

    private void solve() {
        trie = new DigitTrie();
        final int n = in.nextInt();
        for (int i = 0; i < n; i++) {
            final long lo = in.nextLong();
            final long hi = in.nextLong();
            insertRange(trie, lo, hi);
        }


        boolean[] usedDigits = new boolean[NUM_DIGITS];
        for (short i = 1; i < NUM_DIGITS; i++) {
            if (!usedDigits[i]) {
                for (short j = i; j < NUM_DIGITS; j++) {
                    if (!usedDigits[j] && areEquivalent(i, j)) {
                        out.print(j);
                        usedDigits[j] = true;
                    }
                }
                out.println();
            }
        }
    }
}
