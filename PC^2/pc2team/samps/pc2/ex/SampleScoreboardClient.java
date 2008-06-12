package pc2.ex;

import javax.swing.*;
import java.io.*;
import pc2.PC2Log;
import pc2.PC2ini;
/**
 * Sample Scoreboard Client Abstract Class, extends {@link ScoreboardClient}. 
 */
public class SampleScoreboardClient extends ScoreboardClient {
	// used by printRow to print out all the problem statistics
	private long numProblems=0;
	// 
	private String fileName=null;
	private Object printingLock=new Object();
/**
 * SampleScoreboardClient constructor comment.
 * @exception java.rmi.RemoteException The exception description.
 */
public SampleScoreboardClient() throws java.rmi.RemoteException {
	super();
}
/**
 * handleClientRefresh method comment.
 */
public void handleClientRefresh() {}
/**
 * Each time a new run is submitted to a PC<SUP>2</SUP> Server
 * this method is called passing run information and files to this
 * method.
 * <P>
 * Note: one can extract the files from {@link RunInfoAndFiles} using
 * {@link RunInfoAndFiles#writeUserFile(int,String)}
 *.
 */
public void handleNewRun(RunInfoAndFiles run) {}
/**
 * Each time a run is judged this method will be invoked with
 * the run and judgement info.
 *
 */
public void handleRunJudged(RunInfoAndFiles run, boolean isSolved, String judgement) {
	printHTML();	
}
/**
 * Invoked when run is judged
 *
 * @param run pc2.ex.RunInfoAndFiles
 */
public void handleRunStatusUpdated(RunInfoAndFiles run) {}
/**
 * Indicates when contest settings have changed
 */
public void handleSettingsUpdated() {
	printHTML();
}
/**
 * When a judge un checks out (returns a run without judging) this is invoked
 *
 * @see RunInfoAndFiles
 * @param run pc2.ex.RunInfoAndFiles
 */
public void handleUNCheckedOutRun(RunInfoAndFiles run) {}
/**
 * Starts the application.
 * @param args java.lang.String[]
 */
public static void main(String[] args) {
	SampleScoreboardClient sc = null;
	try {
	   sc = new SampleScoreboardClient();
	} catch (Exception e){
		PC2Log.message("error in new SampleClient()",e);
		System.exit(12);
	}
	// This sets the debug level for the log according to pc2v8.ini
	if (new PC2ini().containsKey("client.debugLevel")) {
		String temp=PC2ini.getKey("client.debugLevel");
		try {
			int value=new Integer(temp).intValue();
			PC2Log.setDebugLevel(value);
		} catch (NumberFormatException nfe) {
			;
		}
	}

	if (args != null && args.length > 0) {
		sc.fileName=args[0];
	}
	String loginId = "board1";
	// siteId of 0 means any site

	try {
		if (! sc.loginToPC2("127.0.0.1", pc2.PC2Constants.DEFAULT_PC2_PORT, 0, loginId, loginId))
		{
			PC2Log.message("Could not login as "+loginId);
			JFrame frame = new JFrame("Invisible JFrame... ooh");
			JOptionPane.showMessageDialog
				(
				frame, 
				"Could not login as "+loginId,
				"Login failure",
				JOptionPane.INFORMATION_MESSAGE
				);
			System.exit(5);
		}
		
	} catch (Exception exc) {
		PC2Log.message("Exception ",exc);
	}
	

	// print scoreboard at start
	sc.printHTML();
	String sentinel = "stopboard";
	PC2Log.message("Create file named '"+sentinel+"' to exit client.");
	Thread loopy = new Thread ();
	try {

		for (;;)
		{
//			PC2Log.message("remaining "+(max-count));
			loopy.sleep(1000);
			loopy.yield();
			java.io.File f = new java.io.File(sentinel);
			if (f.exists())
			{
				f.deleteOnExit();
				System.out.println("found "+sentinel+", exiting ");
				sc.logoff();
				System.exit(4);
			}
		}
		
	} catch (Exception ex) {
		PC2Log.message("Funny bugger aren't you ",ex);
	}

	if (sc.logoffPC2())
	{
		PC2Log.message("Logged out.");
		System.exit(0);
	}
}
/**
 * Insert the method's description here.
 * Creation date: (8/14/2002 3:29:52 PM)
 * @param os java.io.PrintWriter
 */
private void printHeader(PrintWriter os) {
	if (os == null) {
		os=new PrintWriter(System.out,true);
	}
	os.println("<html>");
	os.println("<head><title>"+this.getClass().getName()+"</title><head>");
	os.println("<body>");
	os.println("<table>");
		os.print("<tr>");
		os.print("<th><strong><u>Rank</u></strong></th>");
		os.print("<th><strong><u>Name</u></strong></th>");
		os.print("<th><strong><u>Solved</u></strong></th>");
		os.print("<th><strong><u>Score</u></strong></th>");
		// now all per problem stuff
		String alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		for(int j=0;j < numProblems;j++) {
			os.print("<th>&nbsp;&nbsp;&nbsp;&nbsp;<u><strong>"+alphabet.charAt(j % 26)+"</u></strong>&nbsp;&nbsp;&nbsp;&nbsp;</th>");
		}
		os.print("</tr>");
		os.println();
}
/**
 * Insert the method's description here.
 * Creation date: (8/20/02 5:53:33 PM)
 */
private void printHTML() {
	try {
		synchronized (printingLock) {
			PC2Log.message("print scoreboard begin");
			ClientScoreData[] sd = null;
			ProblemScoreData psd = null;
			PrintWriter pout = null;
			if (fileName != null) {
				pout = new PrintWriter(new FileOutputStream(fileName), true);
			} else {
				pout = new PrintWriter(System.out, true);
			}
			numProblems = getNumProblems();
			printHeader(pout);

			if (getNumTeamAccounts() > 0) {
				sd = getStandings();
				if (sd == null) {
					// no standings
					PC2Log.message("no standings ?!?");
				}
				for (int i = 0; i < sd.length; i++) {
					printRow(pout, sd[i]);
				}
			} else {
				PC2Log.message("No teams defined");
			}
			printTrailer(pout);
			PC2Log.message("print scoreboard end");
		}
	} catch (Exception e) {
		PC2Log.message("printHTML()", e);
	}
}
/**
 * Insert the method's description here.
 * Creation date: (8/14/2002 3:29:52 PM)
 * @param os java.io.PrintWriter
 * @param csd pc2.ex.ClientScoreData
 */
private void printRow(PrintWriter os, ClientScoreData csd) {
	if (os == null) {
		os=new PrintWriter(System.out,true);
	}
	if (csd == null) {
		PC2Log.message("printRow no ClientScoreData to print");
	} else {
		os.print("<tr>");
		os.print("<td>"+csd.getRank()+"</td>");
		os.print("<td>"+csd.getTeamName()+"</td>");
		os.print("<td>"+csd.getNumberOfSolvedProblems()+"</td>");
		os.print("<td>"+csd.getScore()+"</td>");
		// now all per problem stuff
		String stats="";
		ProblemScoreData psd=null;
		for(int j=1;j <= numProblems;j++) {
			psd=csd.getProblemScoreData(j);
			if (psd.isSolved()) {
				stats=psd.getAttempts()+"/"+psd.getSolutionTime();
			} else {
				stats=psd.getAttempts()+"/--";
			}
			os.print("<td>"+stats+"</td>");
		}
		os.print("</tr>");
		os.println();
	}
}
/**
 * Insert the method's description here.
 * Creation date: (8/14/2002 3:29:52 PM)
 * @param os java.io.PrintWriter
 */
private void printTrailer(PrintWriter os) {
	if (os == null) {
		os=new PrintWriter(System.out,true);
	}
	os.println("</table>");
	os.println("</body>");
	os.println("</html>");
}
}
