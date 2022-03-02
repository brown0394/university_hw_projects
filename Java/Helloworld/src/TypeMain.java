import java.util.Arrays;
import java.util.List;
import java.util.Scanner;
public class TypeMain {
    public static void main(String[] args) {
//        /* Your code here!*/
//        // 스캐너로 입력 받기
        Scanner scanner = new Scanner(System.in);
        String input = scanner.nextLine();
        String []arr = input.split(" ");

        for (String s : arr) {
            System.out.println(s);
        }

        scanner.close();
//        // printType() 호출
//        printType(input);
//        // 형변환 ( String --> int)
//        printType(Integer.parseInt(input));
//        // 형변환 ( int --> float)
//        printType(Float.parseFloat(input));
    }
    private static void printType(String x) {
        System.out.println(x + " is a string");
    }
    private static void printType(int x) {
        System.out.println(x + " is an int");
    }
    private static void printType(float x) {
        System.out.println(x + " is a float");
    }
}
