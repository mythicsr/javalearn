package chen;

public class Test {
	String name = "Test";
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		Computer computer = new Computer();
		computer.loadOutPutDevice(OutputFactory.getOutputDevice());
		computer.print();
		new Inner().name = "hello";
	}  
	
	
	public void test(){
		new Inner().name = "hello";
	}
	
	public class Inner{
		private String name = "InnerName";
		private void Inshow(){
			System.out.println(Test.this.name);
		}
	}

}
