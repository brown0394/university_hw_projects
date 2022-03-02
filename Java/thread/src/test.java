//import java.util.Scanner;
//
//public class test {
//    private static class SimpleRunnable implements Runnable {
//    public void run() {
//        String threadName =
//                Thread.currentThread().getName();
//        int i = 0 ;
//        while (!Thread.interrupted() ) {
//            System.out.printf("%s: %d%n", threadName, i) ;
//            i ++ ;
//        }
//    }
//}
//    public static void main(String[] args) {
//        Thread thread = new Thread(new SimpleRunnable()) ;
//        thread.start();
//        Scanner scanner = new Scanner(System.in) ;
//        scanner.next() ;
//        thread.interrupt() ; // The thread is now interrupted !
//    }
//}
