//import java.util.Scanner;
//
//public class MathMain {
//    public static void main(String[] args){
//        System.out.print("Enter a begin number: ");
//        Scanner scanner = new Scanner(System.in);
//        int num1 = scanner.nextInt();
//        System.out.print("Enter an end number: ");
//        int num2 = scanner.nextInt();
//        scanner.close();
//
//        long sum = getSumBetween(num1, num2);
//        System.out.printf("Sum between %d and %d : %,d%n", num1, num2, sum);
//
//        long product = getProductBetween(num1, num2);
//        System.out.printf("Product between %d and %d : %,d%n", num1, num2, product);
//    }
//
//    private static long getSumBetween(int begin, int end){
//        long result = 0;
//        for(int i = begin; i < end+1; ++i){
//            result += i;
//        }
//        return result;
//    }
//    private static long getProductBetween(int begin, int end){
//        long result = 1;
//        for(int i = begin; i < end+1; ++i){
//            result *= i;
//        }
//        return result;
//    }
//}
