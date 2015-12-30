import java.util.Scanner;
import java.lang.*;
import java.math.BigDecimal;

import com.sun.javafx.print.Units;
import com.sun.prism.Image;

public class Hello {
	final static String[] fanTi = { "��", "Ҽ", "��", "��", "��", "��", "½", "��",
			"��", "��", "ʰ" };
	final static String[] strUnit = { "��", "ǧ", "��", "ʮ", "Ԫ", "��", "��" };

	/**
	 * @param args
	 */
	@SuppressWarnings("resource")
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner scanner = new Scanner(System.in);

		double iMoney;
		long zheng;
		long xiao;
		String strZheng;
		String strXiao;

		String strMoney;
		String strOut = "";
		char[] chrBuf = new char[128];
		System.out.println("�������");

		iMoney = scanner.nextDouble();

		zheng = (long) iMoney;
		xiao = (long) (Arith.mul(Arith.sub(iMoney, zheng), 100));

		strMoney = String.valueOf(zheng) + String.valueOf(xiao);
		for (int i = 0; i < 5; i++) {
			strOut += getFan(String.valueOf((int) (zheng
					/ Math.pow(10.0, 5 - i - 1) % 10.0)))
					+ strUnit[i];
		}
		for (int i = 0; i < 2; i++) {
			strOut += getFan(String.valueOf((int) (xiao
					/ Math.pow(10.0, 2 - i - 1) % 10.0)))
					+ strUnit[5 + i];
		}

		chrBuf = strOut.toCharArray();
		for (int i = 0; i < 7; i++) {
			if (chrBuf[2 * i] == '��')
				chrBuf[2 * i + 1] = '��';
		}
		strOut = String.valueOf(chrBuf).trim();
		System.out.println(strOut);

		strOut = strOut.replace("������������", "��");
		strOut = strOut.replace("��������", "��");
		strOut = strOut.replace("����", "��");

		
		System.out.println(strOut);

	}

	static void syslog(String str) {
		System.out.print(str);
	}

	static void syslogln(String str) {
		System.out.println(str);
	}

	static String getFan(String str) {
		return fanTi[Integer.parseInt(str)];
	}
}
