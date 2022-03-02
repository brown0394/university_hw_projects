//import edu.pnu.admin.FootballClub;
//import edu.pnu.admin.Player;
//
//import java.util.Scanner;
//
//enum Command{ADD, FIND, CLEAR, LIST, QUIT, INVALID}
//public class FCTest {
//    private static Scanner scanner = new Scanner(System.in);
//    public static void main(String[] args){
//        FootballClub chelsea = new FootballClub("Chelsea");
//        while(true){
//            System.out.print("Enter Command String! ");
//            final Command cmd = getCommand(scanner);
//            if(cmd == Command.QUIT){
//                System.out.println("Bye");
//                break;
//            }
//            if(cmd == Command.INVALID){
//                System.out.println("Invalid Operation");
//                continue;
//            }
//            switch(cmd){
//                case ADD :{
//                    Player newPlayer = createPlayer();
//                    chelsea.addPlayer(newPlayer);
//                    break;
//                }
//                case FIND : {
//                    findPlayer(chelsea); break;
//                }
//                case CLEAR: {
//                    chelsea.removeALLPlayer(); break;
//                }
//                case LIST: {
//                    System.out.println(chelsea); break;
//                }
//                default: break;
//            }
//        }
//
//        scanner.close();
//    }
//
//    private static Command getCommand(Scanner scanner){
//        Command command = Command.INVALID;
//        String str = scanner.next().toUpperCase();
//        try {
//            command = Command.valueOf(str);
//        } catch (IllegalArgumentException e) {
//        }
//        return command;
//    }
//
//    private static void findPlayer(final FootballClub fc){
//        final String playerFirstName = scanner.next();
//        final int jerseyNumber = scanner.nextInt();
//        final Player foundPlayer = fc.findPlayer(playerFirstName, jerseyNumber);
//        if(foundPlayer != null){
//            System.out.println(foundPlayer);
//        }
//        else{
//            System.out.println("edu.pnu.admin.Player Not Found with name " +
//                    playerFirstName + " and number " + jerseyNumber);
//        }
//    }
//    private static Player createPlayer(){
//        final String playerFirstName = scanner.next();
//        final String playerLastName = scanner.next();
//        final int jerseyNumber = scanner.nextInt();
//        return new Player(playerFirstName, playerLastName, jerseyNumber);
//    }
//}
