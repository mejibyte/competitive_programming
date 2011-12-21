import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Arrays;
import java.util.Scanner;

public class inspection_mb implements Runnable {
    private Scanner in;
    private PrintWriter out;

    private int numNodes;
    private int sourceNode;
    private int sinkNode;
    private boolean[][] hasArc;
    private int[][] resCap;
    private int[][] flow;
    private int[] visitedFrom;

    public static void main(String[] args) {
        new Thread(new inspection_mb()).start();
    }

    private static final int INFINITY = 1000000;

    public void run() {
        try {
            in = new Scanner(new FileReader("inspection.in"));
            out = new PrintWriter("inspection.out");

            solve();

            in.close();
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void solve() {
        numNodes = in.nextInt();
        sourceNode = numNodes;
        sinkNode = numNodes + 1;
        
        hasArc = new boolean[numNodes + 2][];
        flow = new int[numNodes + 2][numNodes + 2];
        resCap = new int[numNodes + 2][numNodes + 2];
        for (int i = 0; i < numNodes; i++) {
            hasArc[i] = new boolean[numNodes + 2];
            flow[i] = new int[numNodes + 2];
            resCap[i] = new int[numNodes + 2];

            resCap[sourceNode][i] = INFINITY;
            resCap[i][sinkNode] = INFINITY;
        }

        for (int from = 0; from < numNodes; from++) {
            final int numArcsFrom = in.nextInt();
            for (int j = 0; j < numArcsFrom; j++) {
                final int to = in.nextInt() - 1;
                hasArc[from][to] = true;
                if (hasArc[from][to]) {
                    flow[sourceNode][from]++;
                    resCap[sourceNode][from]--;
                    flow[from][sourceNode]--;
                    resCap[from][sourceNode]++;

                    flow[from][to] = 1;
                    resCap[from][to] = INFINITY;
                    flow[to][from] = -1;

                    flow[to][sinkNode]++;
                    resCap[to][sinkNode]--;
                    flow[sinkNode][to]--;
                    resCap[sinkNode][to]++;
                }
            }
        }

        visitedFrom = new int[numNodes + 2];
        while (tryAugment());

        int numPaths = 0;
        for (int i = 0; i < numNodes; i++) {
            numPaths += flow[sourceNode][i];
        }

        out.println(numPaths);

        for (;;) {
            int i = sourceNode;
            int j = traceFlowPath(i);
            if (j < 0) {
                break;
            }
            while (j != sinkNode) {
                out.printf("%d ", j + 1);
                flow[i][j]--;
                flow[j][i]++;
                i = j;
                j = traceFlowPath(i);
            }
            out.println();
        }
    }

    private int traceFlowPath(int from) {
        for (int to = 0; to < numNodes + 2; to++) {
            if (flow[from][to] > 0) {
                return to;
            }
        }
        return -1;
    }

    private boolean tryAugment() {
        Arrays.fill(visitedFrom, -1);
        augmentDfs(sinkNode, sinkNode);
        if (visitedFrom[sourceNode] < 0) {
            return false;
        }

        int i = sourceNode;
        while (i != sinkNode) {
            int j = visitedFrom[i];

            flow[j][i]++;
            resCap[j][i]--;

            flow[i][j]--;
            resCap[i][j]++;

            i = j;
        }

        return true;
    }

    private void augmentDfs(int where, int from) {
        if (visitedFrom[where] >= 0) {
            return;
        }
        visitedFrom[where] = from;
        if (where == sourceNode) {
            return;
        }
        for (int j = 0; j < numNodes + 2; j++) {
            if (resCap[where][j] > 0) {
                augmentDfs(j, where);
            }
        }
    }
}
