package pc2.ex;

import java.io.*;
import java.net.*;
import java.rmi.*;
import java.rmi.registry.*;
import java.rmi.server.*;
import java.security.*;
import java.util.*;
import pc2.*;

import javax.swing.*;

/**
 * SampleGetRunsClient is a sample implmentation of the abstract {@link GetRunsClient}
 *
 * @author PC<sup>2</sup> Team, pc2@ecs.csus.edu
 */
public class SampleGetRunsClient extends GetRunsClient {
	
/**
 * 
 */
public SampleGetRunsClient() throws java.rmi.RemoteException {
	super();
}
/**
 * Handle New Run (Sample)
 * <P>
 * Outputs most information to the log <Br>
 * Unpacks the input files into the current directory
 * prepending RunXX onto the start of the filename.
 */
public void handleNewRun(RunInfoAndFiles run) {
	
	String nl = System.getProperty("line.separator");

	PC2Log.message("handleNewRun: "+
		run.getUserSiteId() + ":" + run.getRunId() );

	PC2Log.message("handleNewRun: "+
		nl + "Run Info " +
		nl + "site:id " + run.toString() +
		nl + "user id " + run.getUserId() +
		nl + "user name " + run.getUserTitle() +
		nl + "problem id " + run.getProblemId() +
		nl + "problem name " + run.getProblemTitle() +
		nl + "language id " + run.getLanguageId() +
		nl + "language name " + run.getLanguageTitle() +
		nl + "main file name " + run.getMainFileName() 
	);

	if (run.getNumUserFiles() == 0)
		PC2Log.message("handleNewRun: There are no files");
	else
	{
		PC2Log.message("handleNewRun: There are "+run.getNumUserFiles()+" files");
		for (int i = 0; i < run.getNumUserFiles();i ++)
		{
			String newfilename = "Run"+run.getRunId()+"."+run.getUserFileName(i);
			PC2Log.message("handleNewRun: File ["+i+"] "+run.getUserFileName(i)+" written to: "+newfilename);
			try {
				run.writeUserFile(i, newfilename);
			} catch (Exception ex)
			{
				System.err.println("Exception in handleNewRun "+ex.getMessage());
			}
		}
	}
}
/**
 * Starts the application.
 * @param args an array of command-line arguments
 */
public static void main(java.lang.String[] args) {

	SampleGetRunsClient  sc =null;
	try {
	   sc = new SampleGetRunsClient();
	} catch (Exception e){
		PC2Log.message("error in new SampleClient()",e);
		System.exit(12);
	}

	String loginId = "custom1";

	if (args.length > 0)
	{
		loginId = args[0];
		System.err.println("From Command line using login: "+loginId);
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

	try {	
		if (! sc.loginToPC2("127.0.0.1", PC2Constants.DEFAULT_PC2_PORT, 1, loginId, loginId))
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

	sc.showContestInfo(System.out);

	sc.waitAround(); // Wait for new runs, see the doc
	// for this method to find out why.
}
/**
 * Displays all contest info 
 */
public void showContestInfo(PrintStream ps) {

	try {

		// Problems

		ps.println("showContestInfo");
		ps.println("- - Problems - - ");
		for (int i = 1; i <= getNumProblems(); i ++)
		{
			ps.println("Problem "+i+" \""+getProblemTitle(new Long(i))+"\"");
		}
		ps.println(getNumProblems()+" problems defined");

		// Languages
		
		ps.println("- - Languages - - ");
		for (int i = 1; i <= getNumLanguages(); i ++)
		{
			ps.println("Language "+i+" \""+getLanguageTitle(new Long(i))+"\"");
		}
		ps.println(getNumLanguages()+" languages defined");

		// Team Names
		
		ps.println("- - Team Names - - ");
		for (int i = 1; i <= getNumTeamAccounts(); i ++)
		{
			ps.println("Team "+i+" \""+getTeamName (new Long(1), new Long (i))+"\"");
		}
		ps.println(getNumTeamAccounts()+" accounts defined");
		
		
	} catch (Exception ex) {
		PC2Log.message("Exception ",ex);
		
	}

}
/**
 * Wait around so that we can get incoming runs.
 * <P>
 * Wait around until a sentinel file 'stopcust' is
 * created.  When file is found in current directory
 * will stop waiting.
 * <P>
 * This functionality is done within PC<sup>2</sup> by
 * using JFrame to keep the JVM alive.
 */
public void waitAround() {

	long secs = 5;
	String filename = "stopcust";

	Thread th = new Thread();

	PC2Log.message("Create file named '"+filename+"' to exit client.");

	try {
		for (long i = 1; ; i ++)
		{
			PC2Log.message("["+i+"] waiting for "+secs+" secs...");
			th.sleep(secs * 1000);
			th.yield();

			File checkFile = new File(filename);
			if (checkFile.exists())
			{
				checkFile = null;
				PC2Log.message("Logging off...");
				if (logoffPC2())
				{
					PC2Log.message("Logged out.");
					th.yield();
					th.sleep (secs * 1000);
					System.exit(3);
				}
			}
		}
	} catch (Exception ex)
	{
		PC2Log.message("Exception ",ex);
	}
}
}
