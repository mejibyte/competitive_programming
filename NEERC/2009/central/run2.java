import java.util.Arrays;
import java.io.*;

/**
 * Simple tool to start two processes piped into each other.
 * 
 * @author Roman Elizarov
 */
public class run2 {
	public static void main(String[] args) throws IOException, InterruptedException {
		if (args.length < 2) {
			System.err.println("Usage: run2 <interaction-exe> <main-exe> [<main-process-args> ...]");
			return;
		}
		run2 instance = new run2(args);
		try {
			instance.go();
		} finally {
			instance.killThemAll();
		}
	}

	private final Process p1;
	private final Process p2;

	private run2(String[] args) throws IOException {
		ProcessBuilder pb1 = new ProcessBuilder(args[0]);
		ProcessBuilder pb2 = new ProcessBuilder(Arrays.asList(args).subList(1, args.length).toArray(new String[args.length - 1]));
		pb1.redirectErrorStream(true);
		pb2.redirectErrorStream(true);
		p1 = pb1.start();
		p2 = pb2.start();
	}

	private void go() throws InterruptedException {
		new Redirector(p1.getInputStream(), p2.getOutputStream()).start();
		new Redirector(p2.getInputStream(), p1.getOutputStream()).start();
		p2.waitFor();
		p1.destroy();
		p1.waitFor();
	}

	private void killThemAll() {
		p1.destroy();
		p2.destroy();
	}

	private class Redirector extends Thread {
		final InputStream in;
		final OutputStream out;

		private Redirector(InputStream in, OutputStream out) {
			this.in = in;
			this.out = out;
		}

		public void run() {
			byte[] buf = new byte[4096];
			int len;
			try {
				while ((len = in.read(buf)) > 0) {
					out.write(buf, 0, len);
					out.flush();
				}
			} catch (IOException e) {
				System.err.println(e.toString());
				killThemAll();
			}
		}
	}
}
