package pc2.ex;

/**
 * Sample Team Client Abstract Class, extends {@link TeamClient}. 
 */
public class SampleTeamClent extends TeamClient {
/*
 *
 * @see BaseClient#handleClarAnswered (ClarInfoAndFiles) */
public void handleClarAnswered(ClarInfoAndFiles clar) {}
/**
 * handleClientRefresh method comment.
 */
public void handleClientRefresh() {}
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
/*
 *
 * @see BaseClient#handleSettingsUpdated() */
public void handleSettingsUpdated() {}
}
