package chen;

public class OutputFactory {
	private static Output output;
	public static Output getOutputDevice(){
		return new BetterPrinter();
	}
}
