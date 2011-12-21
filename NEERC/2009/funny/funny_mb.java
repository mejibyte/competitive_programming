import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashSet;
import java.util.PriorityQueue;
import java.util.Scanner;

public class funny_mb implements Runnable {
    private Scanner in;
    private PrintWriter out;
    private short[][] playCounters;
    private PriorityQueue<Item> queue = new PriorityQueue<Item>();
    private HashSet<String> queued = new HashSet<String>();
    private HashSet<String> playWords = new HashSet<String>();

    class Item implements Comparable<Item> {
        public final String word;
        public final short[] counters;
        public final int bonus;

        public Item(String word, short[] counters, int bonus) {

            this.word = word;
            this.counters = counters;
            this.bonus = bonus;
        }

        public int compareTo(Item o) {
            return o.bonus - bonus;
        }
    }

    public static void main(String[] args) {
        new Thread(new funny_mb()).start();
    }

    public void run() {
        try {
            in = new Scanner(new FileReader("funny.in"));
            out = new PrintWriter("funny.out");

            solve();

            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private short[] countLetters(String word) {
        short[] counters = new short[26];
        for (int i = 0; i < word.length(); ++i) {
            char ch = word.charAt(i);
            counters[ch - 'A']++;
        }
        return counters;
    }

    private boolean isLeq(short[] lhsCounters, short[] rhsCounters) {
        for (int i = 0; i < 26; i++) {
            if (lhsCounters[i] > rhsCounters[i]) {
                return false;
            }
        }
        return true;
    }

    private int calcBonus(short[] candidateCounters) {
        int bonus = 0;
        for (short[] counters : playCounters) {
            if (isLeq(candidateCounters, counters)) {
                bonus++;
            }
        }
        return bonus;
    }

    private void tryEnqueue(String word, short[] counters) {
        if (queued.add(word)) {
            final int bonus = calcBonus(counters);
            final Item item = new Item(word, counters, bonus);
            queue.add(item);
        }
    }

    private void solve() {
        final int n = in.nextInt();
        final int m = in.nextInt();
        in.nextLine();

        playCounters = new short[m][];
        for (int i = 0; i < m; i++) {
            String word = in.nextLine();
            playWords.add(word);
            playCounters[i] = countLetters(word);
        }

        for (int i = 0; i < 26; i++) {
            String word = Character.toString((char) ('A' + i));
            final short[] counters = countLetters(word);
            tryEnqueue(word, counters);
        }

        int numOut = 0;
        while (numOut < n) {
            final Item item = queue.remove();
            if (!playWords.contains(item.word)) {
                out.println(item.word);
                numOut++;
            }
            for (int i = 0; i < 26; i++) {
                String newWord = item.word + (char)('A' + i);
                short[] newCounters = item.counters.clone();
                newCounters[i]++;
                tryEnqueue(newWord, newCounters);
            }
        }
    }
}
