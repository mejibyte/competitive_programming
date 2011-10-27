import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.StringTokenizer;

public class exclusive_mb implements Runnable {
    private Scanner in;
    private PrintWriter out;

    private static final int NUM_NODES = 15;

    static class Node {
        public int color;
        public int edgesMask;
    }

    private final Node[] nodes = new Node[NUM_NODES];

    static class Edge {
        public int a, b;
    }

    private final ArrayList<Edge> edges = new ArrayList<Edge>();

    public static void main(String[] args) {
        new Thread(new exclusive_mb()).start();
    }

    public void run() {
        try {
            in = new Scanner(new FileReader("exclusive.in"));
            out = new PrintWriter("exclusive.out");

            solve();

            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private int nameToIndex(char ch) {
        return ch - 'L';
    }

    private char indexToName(int index) {
        return (char) ('L' + index);
    }

    private void solve() {
        for (int i = 0; i < NUM_NODES; i++) {
            nodes[i] = new Node();
        }
        
        final int numEdges = in.nextInt();
        in.nextLine();
        for (int i = 0; i < numEdges; i++) {
            StringTokenizer stringTokenizer = new StringTokenizer(in.nextLine());
            Edge edge = new Edge();
            edge.a = nameToIndex(stringTokenizer.nextToken().charAt(0));
            edge.b = nameToIndex(stringTokenizer.nextToken().charAt(0));
            edges.add(edge);
            if ((nodes[edge.a].edgesMask & (1 << edge.b)) == 0) {
                nodes[edge.a].edgesMask |= (1 << edge.b);
                nodes[edge.b].edgesMask |= (1 << edge.a);
            }
        }

        for (int i = 0; i < 1 << NUM_NODES; i++) {
            coloringSize[i] = Integer.MAX_VALUE;
        }

        final int allMask = (1 << NUM_NODES) - 1;
        final int waitChainLength = computeMinColoring(allMask) - 2;
        out.println(waitChainLength);

        int color = 0;
        int mask = allMask;
        while (mask != 0) {
            final int newMask = coloringBacktrack[mask];
            final int stableMask = mask & ~newMask;
            for (int i : unpackMask(stableMask)) {
                nodes[i].color = color;
            }
            mask = newMask;
            color++;
        }

        for (Edge edge : edges) {
            if (nodes[edge.a].color < nodes[edge.b].color) {
                out.printf("%c %c\n", indexToName(edge.a), indexToName(edge.b));
            } else {
                out.printf("%c %c\n", indexToName(edge.b), indexToName(edge.a));
            }
        }
    }

    private final int[] coloringSize = new int[1 << NUM_NODES];
    private final int[] coloringBacktrack = new int[1 << NUM_NODES];

    private int[] unpackMask(int mask) {
        int numNodes = 0;
        for (int i = 0; i < NUM_NODES; i++) {
            if ((mask & (1 << i)) != 0) {
                numNodes++;
            }
        }
        int[] result = new int[numNodes];
        int j = 0;
        for (int i = 0; i < NUM_NODES; i++) {
            if ((mask & (1 << i)) != 0) {
                result[j++] = i;
            }
        }
        return result;
    }

    private int computeMinColoring(int mask) {
        if (coloringSize[mask] != Integer.MAX_VALUE) {
            return coloringSize[mask];
        }
        
        if (mask == 0) {
            return 0;
        }

        final int[] list = unpackMask(mask);
        tryStableSet(list, 0, mask, 0, 0);

        return coloringSize[mask];
    }

    private void tryStableSet(int[] list, int listIndex, int totalMask, int stableMask, int neighborMask) {
        if (listIndex == list.length) {
            if (stableMask != 0) {
                final int newMask = totalMask & ~stableMask;
                final int size = computeMinColoring(newMask) + 1;
                if (coloringSize[totalMask] > size) {
                    coloringSize[totalMask] = size;
                    coloringBacktrack[totalMask] = newMask;
                }
            }
        } else {
            tryStableSet(list, listIndex + 1, totalMask, stableMask, neighborMask);

            final int j = list[listIndex];
            final int thisMask = 1 << j;
            if ((neighborMask & thisMask) == 0) {
                tryStableSet(list, listIndex + 1, totalMask, stableMask | thisMask, neighborMask | nodes[j].edgesMask);
            }
        }
    }
}
