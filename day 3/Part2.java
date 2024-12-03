package advent;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.function.Consumer;
import java.util.regex.MatchResult;
import java.util.regex.Pattern;

public class Part2 {

	public static void main(String[] args) {
		try {
			Scanner reader = new Scanner(new FileInputStream(new File("input.txt")));
			String txt = "";
			while (reader.hasNextLine()) {
				txt += reader.nextLine();
			}
			int sum = 0;
			String [] active = txt.split("do\\(\\)");
			for (String a : active) {
				ArrayList<Integer> mults = new ArrayList<Integer>();
				Pattern.compile("mul\\((?<a>\\d{1,3})\\,(?<b>\\d{1,3})\\)").matcher(a.replaceFirst("don't\\(\\).*", "")).results().iterator().forEachRemaining(new Consumer<MatchResult>() {
	
					@Override
					public void accept(MatchResult t) {
						mults.add(Integer.parseInt(t.group("a")) * Integer.parseInt(t.group("b")));
					}
					
				});
				for (int x : mults) {
					sum += x;
				}
			}
			System.out.println(sum);
			reader.close();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}

}
