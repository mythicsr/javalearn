package chen;

public class Computer {
	private Output output;
	
	public void loadOutPutDevice(Output op){
		output = op;
	}
	
	public void print(){
		output.out();
	}
}
