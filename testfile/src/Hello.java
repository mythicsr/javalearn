import java.util.Scanner;

import sun.print.resources.serviceui;

public class Hello {

	static char cNumCn[] = { '零', '壹', '貳', '叁', '肆', '伍', '陸', '柒', '捌', '玖' };
	static char unit[] = { '千','百','十','元' };
	public static void main(String[] args) {

		byte[] buf = new byte[1024];
		Scanner scanner = new Scanner(System.in);
		
		long Money;
		long zheng, xiao;
		System.out.print("请输入金额:");
		while (true) {
			Money = scanner.nextInt();
			System.out.println(getRMBstr(Money));
		}
	}
	
	
	public static String getRMBstr1(long num){
		String int2str = String.valueOf(num).trim();
		int length = int2str.length();
		char[] chrBuf = int2str.toCharArray();
		char[] outBuf = new char[128];
		int j = 4 - length;
		
		for(int i=0; i<length; i++){		
			outBuf[2*i] = cNumCn[Integer.valueOf(""+chrBuf[i])];
			outBuf[2*i+1] = unit[i+j];
		}
		return new String(outBuf).trim();
	}
	
	public static String getRMBstr2(String str1){
		char[] cbuf;
		cbuf = str1.trim().toCharArray();
		for(int i=0; i<cbuf.length/2; i++){
			if(cbuf[2*i]=='零')
				cbuf[2*i+1]='零';
		}
		
		
	}
}


