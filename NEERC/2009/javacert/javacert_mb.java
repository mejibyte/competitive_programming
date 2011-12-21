import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Scanner;

public class javacert_mb implements Runnable {
    private Scanner in;
    private PrintWriter out;
    private int totalCorrect;
    private int totalQuest;
    private int numCateg;
    private int[] correctPercentage;
    private int bestDiff;
    private int[] bestCorrect;
    private int[] bestQuest;
    private int lowerBound[][];
    private int upperBound[][];

    public static void main(String[] args) {
        new Thread(new javacert_mb()).start();
    }

    private static final int INFINITY = 1000000;

    public void run() {
        try {
            in = new Scanner(new FileReader("javacert.in"));
            out = new PrintWriter("javacert.out");

            solve();

            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private int getPercentage(int part, int total) {
        int quot = (100 * part) / total;
        int rem = (100 * part) % total;
        if (2 * rem == total) {
            return quot % 2 == 0 ? quot : quot + 1;
        } else if (2 * rem < total) {
            return quot;
        } else {
            return quot + 1;
        }
    }

    private int getLowerBound(int total, int percentage) {
        int guess = total * (percentage - 1) / 100;
        while (getPercentage(guess, total) < percentage) {
            guess++;
        }
        return guess;
    }

    private int getUpperBound(int total, int percentage) {
        int guess = total * (percentage + 1) / 100;
        while (getPercentage(guess, total) > percentage) {
            guess--;
        }
        return guess;
    }

    private void solve() {
        totalCorrect = in.nextInt();
        totalQuest = in.nextInt();
        numCateg = in.nextInt();
        correctPercentage = new int[numCateg];
        for (int i = 0; i < numCateg; i++) {
            correctPercentage[i] = in.nextInt();
        }

        int[][][] opt = new int[numCateg + 1][totalQuest + 1][totalCorrect + 1];
        int[][][] backQuest = new int[numCateg + 1][totalQuest + 1][totalCorrect + 1];
        int[][][] backCorrect = new int[numCateg + 1][totalQuest + 1][totalCorrect + 1];
        for (int i = 0; i <= totalQuest; i++) {
            Arrays.fill(opt[0][i], INFINITY);
        }
        opt[0][0][0] = 0;

        lowerBound = new int[totalQuest + 1][101];
        upperBound = new int[totalQuest + 1][101];
        for (int i = 1; i <= totalQuest; i++) {
            for (int j = 0; j <= 100; j++) {
                lowerBound[i][j] = getLowerBound(i, j);
                upperBound[i][j] = getUpperBound(i, j);
            }
        }

        bestDiff = INFINITY;
        bestQuest = new int[numCateg];
        bestCorrect = new int[numCateg];
        for (int low = 1; low <= totalQuest / numCateg + 1; low++) {
            for (int categ = 0; categ < numCateg; categ++) {
                for (int curQuest = 0; curQuest <= totalQuest; curQuest++) {
                    for (int curCorrect = 0; curCorrect <= totalCorrect; curCorrect++) {
                        int bestDiff = INFINITY;
                        int bestQuest = -1;
                        int bestCorrect = -1;
                        for (int thisQuest = low; thisQuest <= curQuest; thisQuest++) {
                            final int lowCorrect = lowerBound[thisQuest][correctPercentage[categ]];
                            final int upperCorrect = Math.min(upperBound[thisQuest][correctPercentage[categ]], curCorrect);
                            for (int thisCorrect = lowCorrect; thisCorrect <= upperCorrect; thisCorrect++) {
                                int thisDiff = Math.max(
                                        opt[categ][curQuest - thisQuest][curCorrect - thisCorrect],
                                        thisQuest - low);
                                if (thisDiff < bestDiff) {
                                    bestDiff = thisDiff;
                                    bestQuest = thisQuest;
                                    bestCorrect = thisCorrect;
                                }
                            }
                        }
                        opt[categ + 1][curQuest][curCorrect] = bestDiff;
                        backQuest[categ + 1][curQuest][curCorrect] = bestQuest;
                        backCorrect[categ + 1][curQuest][curCorrect] = bestCorrect;
                    }
                }
            }

            if (opt[numCateg][totalQuest][totalCorrect] < bestDiff) {
                bestDiff = opt[numCateg][totalQuest][totalCorrect];
                
                int curQuest = totalQuest;
                int curCorrect = totalCorrect;
                for (int categ = numCateg - 1; categ >= 0; categ--) {
                    bestQuest[categ] = backQuest[categ + 1][curQuest][curCorrect];
                    bestCorrect[categ] = backCorrect[categ + 1][curQuest][curCorrect];
                    curQuest -= bestQuest[categ];
                    curCorrect -= bestCorrect[categ];
                }

                assert curQuest == 0;
                assert curCorrect == 0;
            }
        }

        for (int i = 0; i < numCateg; i++) {
            out.printf("%d %d\n", bestQuest[i] - bestCorrect[i], bestQuest[i]);
        }
    }

}
