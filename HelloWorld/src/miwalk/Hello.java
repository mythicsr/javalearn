package miwalk;

import smartlock.HelloFoo2;

public class Hello {
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Hello.pri();
		Hello2.pri();
		HelloFoo1.pri();
		HelloFoo2.pri();
		smartlock.World.pri();
	}
	
	protected static void pri(){
		System.out.println("Hello");
	}
	
}
