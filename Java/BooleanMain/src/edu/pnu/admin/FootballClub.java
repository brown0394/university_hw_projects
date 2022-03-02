//package edu.pnu.admin;
//
//import edu.pnu.collection.GenericList;
//
//import java.util.Objects;
//
//public class FootballClub {
//    private String name;
//    private final int maxSquadSize = 25;
//
//    private GenericList<Player> squad = new GenericList<Player>();
//
//    public String toString(){
//        String msg = "FootballClub Name: " + name + " Player Count: " + squad.size() + "\n";
//        for(int i = 0; i < squad.size(); ++i){
//            msg += "\t" + squad.get(i) + "\n";
//        }
//        return msg;
//    }
//
//    public FootballClub(String clubname){
//        name = clubname;
//    }
//
//    public void addPlayer(Player newplayer){
//        squad.add(newplayer);
//    }
//
//    public Player findPlayer(String firstname, int jersey){
//        if(!squad.isEmpty()){
//            for(int i = 0; i < squad.size(); ++i){
//                if(squad.get(i).equals(firstname, jersey)){
//                    return squad.get(i);
//                }
//            }
//        }
//        return null;
//    }
//
//    public void removeAllPlayer(){
//        if(!squad.isEmpty()){
//            squad.clear();
//        }
//    }
//
//    @Override
//    public boolean equals(Object o) {
//        if (this == o) return true;
//        if (o == null || getClass() != o.getClass()) return false;
//        FootballClub that = (FootballClub) o;
//        return Objects.equals(name, that.name) && Objects.equals(squad, that.squad);
//    }
//
//    @Override
//    public int hashCode() {
//        return Objects.hash(name, maxSquadSize, squad);
//    }
//}
