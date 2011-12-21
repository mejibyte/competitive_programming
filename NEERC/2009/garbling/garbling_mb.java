import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;

public class garbling_mb implements Runnable {
    private Scanner in;
    private PrintWriter out;
    private char[][] map;
    private int[][] table;
    private int numRows;
    private int numCols;

    public static void main(String[] args) {
        new Thread(new garbling_mb()).start();
    }

    public void run() {
        try {
            in = new Scanner(new FileReader("garbling.in"));
            out = new PrintWriter("garbling.out");

            solve();

            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void rotateClockwise(int row, int col) {
        int a = table[row][col];
        int b = table[row][col + 1];
        int c = table[row + 1][col];
        int d = table[row + 1][col + 1];
        table[row][col] = c;
        table[row][col + 1] = a;
        table[row + 1][col] = d;
        table[row + 1][col + 1] = b;
    }

    private void rotateCounterclockwise(int row, int col) {
        int a = table[row][col];
        int b = table[row][col + 1];
        int c = table[row + 1][col];
        int d = table[row + 1][col + 1];
        table[row][col] = b;
        table[row][col + 1] = d;
        table[row + 1][col] = a;
        table[row + 1][col + 1] = c;
    }

    private void applyMap(int row, int col) {
        if (map[row][col] == 'R') {
            rotateClockwise(row, col);
        } else if (map[row][col] == 'L') {
            rotateCounterclockwise(row, col);
        }
    }

    private void solve() {
        numRows = in.nextInt();
        numCols = in.nextInt();
        long numMoves = in.nextLong();
        in.nextLine();

        map = new char[numRows - 1][];
        for (int row = 0; row < numRows - 1; row++) {
            map[row] = new char[numCols - 1];
            final String line = in.nextLine();
            for (int col = 0; col < numCols - 1; col++) {
                map[row][col] = line.charAt(col);
            }
        }

        initTable();

        final long turnLength = (numRows - 1) * (numCols - 1);
        final long numTurns = numMoves / turnLength;
        final int remMoves = (int) (numMoves % turnLength);

        long[] cycleDeltas = new long[numRows * numCols];
        simulate(turnLength, cycleDeltas);
//        dumpTable();

        long[] counters = new long[numRows * numCols];
        boolean[] used = new boolean[numRows * numCols];
        for (int i = 0; i < numRows * numCols; i++) {
            if (!used[i]) {
                final ArrayList<Integer> permCycle = new ArrayList<Integer>();
                int j = i;
                do {
                    permCycle.add(j);
                    used[j] = true;
                    j = table[j / numCols][j % numCols]; 
                } while (j != i);

                for (int k = 0; k < permCycle.size(); k++) {
                    final int from = permCycle.get(k);
                    final int to = permCycle.get((int) ((k + numTurns) % permCycle.size()));
                    table[from / numCols][from % numCols] = to;
                }

                long totalDelta = 0;
                for (int value : permCycle) {
                    totalDelta += cycleDeltas[value];
                }

                final long numCycles = numTurns / permCycle.size();
                for (int value: permCycle) {
                    counters[value] += totalDelta * numCycles;
                }

                final int remCycles = (int) (numTurns % permCycle.size());
                for (int k = 0; k < remCycles; k++) {
                    for (int l = 0; l < permCycle.size(); l++) {
                        final int pos = permCycle.get(((l + k) % permCycle.size()));
                        counters[pos] += cycleDeltas[permCycle.get(l)];
                    }
                }
            }
        }

//        dumpTable();
        simulate(remMoves, counters);

        for (long value : counters) {
            out.println(value);
        }
    }

    private void simulate(long numMoves, long[] counters) {
        int row = 0;
        int col = 0;
        for (int i = 0; i < numMoves; i++) {
            counters[table[row][col]]++;
            applyMap(row, col);
            col++;
            if (col == numCols - 1) {
                row++;
                col = 0;
            }
            if (row == numRows - 1) {
                row = 0;
            }
        }
    }

    private void initTable() {
        table = new int[numRows][];
        int counter = 0;
        for (int row = 0; row < numRows; row++) {
            table[row] = new int[numCols];
            for (int col = 0; col < numCols; col++) {
                table[row][col] = counter++;
            }
        }
    }

    private void dumpTable() {
        for (int row = 0; row < numRows; row++) {
            for (int col = 0; col < numCols; col++) {
                System.out.printf("%3d ", table[row][col]);
            }
            System.out.println();
        }
    }

}
