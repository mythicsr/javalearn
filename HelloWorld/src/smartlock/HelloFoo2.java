package smartlock;
import miwalk.*;

public class HelloFoo2 extends Hello{
	public static void pri(){
		
		System.out.println("override HelloFoo2");
	}
	public void spri(){
		super.pri();
	}
}