//package edu.pnu.admin;
//
//import java.util.Objects;
//
//public class Player {
//    private String firstName;
//    private String lastName;
//    private int jerseyNumber;
//
//    public String toString(){
//        return "[" + lastName + ", " + firstName + " " + String.valueOf(jerseyNumber) + "]";
//    }
//
//    public Player(String FirstName, String LastName, int jNumber){
//        firstName = FirstName;
//        lastName = LastName;
//        jerseyNumber = jNumber;
//    }
//
//    public boolean equals(String fn, int jn) {
//        return jerseyNumber == jn && firstName.equals(fn);
//    }
//
//    @Override
//    public int hashCode() {
//        return Objects.hash(firstName, lastName, jerseyNumber);
//    }
//}
