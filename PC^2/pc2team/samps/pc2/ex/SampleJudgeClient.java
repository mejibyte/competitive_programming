package pc2.ex;

import pc2.*;

/**
 * Sample Judge Client Abstract Class, extends {@link JudgeClient}.
 */
public class SampleJudgeClient extends JudgeClient {
/**
 * SampleJudgeClient constructor comment.
 */
public SampleJudgeClient() {
	super();
}
/*
 *
 * @see BaseClient#handleCheckedOutRun (RunInfoAndFiles) */
public void handleCheckedOutRun(RunInfoAndFiles run) {}
/*
 *
 * @see BaseClient#handleClarAnswered (ClarInfoAndFiles) */
public void handleClarAnswered(ClarInfoAndFiles clar) {}
/*
 *
 * @see BaseClient#handleClarSelected(ClarInfoAndFiles) */
public void handleClarSelected(ClarInfoAndFiles clar) {}
/**
 * handleClientRefresh method comment.
 */
public void handleClientRefresh() {}
/**
 * HandleJudgedRun method comment.
 */
public void HandleJudgedRun(RunInfoAndFiles run) {

	String nl = System.getProperty("line.separator");

	PC2Log.message("HandleJudgedRun: "+
		run.getUserSiteId() + ":" + run.getRunId() );
}
/*
 *
 * @see BaseClient#handleNewClar(ClarInfoAndFiles) */
public void handleNewClar(ClarInfoAndFiles clar)
{
}
/* 
 *
 * @see BaseClient#handleNewRun(RunInfoAndFiles) */
public void handleNewRun(RunInfoAndFiles run)
{
}
/**
 * HandleNewRun method comment.
 */
public void HandleNewRun(RunInfoAndFiles run) {
	String nl = System.getProperty("line.separator");

	PC2Log.message("HandleNewRun: "+
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
/*
 *
 * @see BaseClient#handleRunJudged (RunInfoAndFiles, boolean, String) */
public void handleRunJudged(RunInfoAndFiles run, boolean isSolved, java.lang.String judgement) {}
/*
 *
 * @see BaseClient#handleRunStatusUpdated (RunInfoAndFiles) */
public void handleRunStatusUpdated(RunInfoAndFiles run) {}
/*
 *
 * @see BaseClient#handleRunUpdated (RunInfoAndFiles) */
public void handleRunUpdated(RunInfoAndFiles run) {}
/**
 * HandleSelectedRun method comment.
 */
public void HandleSelectedRun(RunInfoAndFiles run) {

	String nl = System.getProperty("line.separator");

	PC2Log.message("HandleJudgedRun: "+
		run.getUserSiteId() + ":" + run.getRunId() );
		
}
/*
 *
 * @see BaseClient#handleSettingsUpdated() */
public void handleSettingsUpdated() {}
/*
 *
 * @see BaseClient#handleUNCheckedOutRun (RunInfoAndFiles) */
public void handleUNCheckedOutRun(RunInfoAndFiles run) {}
}
