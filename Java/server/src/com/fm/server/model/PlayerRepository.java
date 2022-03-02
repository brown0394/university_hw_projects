package com.fm.server.model;

import com.fm.server.resource.ResourceFile;
import com.fm.unit.Player;

import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;
import java.util.function.Predicate;

public class PlayerRepository {
    private static PlayerRepository instance = new PlayerRepository();
    boolean loaded = false;
    private List<Player> players;

    private PlayerRepository(){}

    public static PlayerRepository getInstance() {
        return instance;
    }

    public List<Player> load() {
        if (!isLoaded()) {
            List<Player> players = new ArrayList<>();
            String resourceFileName = Thread.currentThread().getContextClassLoader().getResource("players_20_short.csv").getFile();
            try (Scanner scanner = new Scanner(new File(resourceFileName))) {
                if (scanner.hasNext()) scanner.nextLine();
                while (scanner.hasNext()) {
                    String line = scanner.nextLine();
                    Player p = createPlayer(line.split(","));
                    players.add(p);
                }
            } catch (Exception e) {
                System.out.println(e);
            }
            this.players = players;
        }
        return players;
    }

    public boolean isLoaded() {
        return loaded;
    }

    public List<Player> query(List<Predicate<Player>> conditions){
        if (0 < conditions.size() && 0 < players.size())
            return PlayerQuery.query(players, conditions);
        else
            return new ArrayList<>();
    }

    private Player createPlayer(String[] fields) {
        Player player = new Player(ResourceFile.getId(fields), ResourceFile.getName(fields), ResourceFile.getHeight(fields),
                ResourceFile.getNationality(fields), ResourceFile.getClub(fields), ResourceFile.getOverall(fields), ResourceFile.getPosition(fields));
        return player;
    }

//    private List<String> getPosition(String[] fields) {
//        List<String> positions = new ArrayList<>();
//        if (fields[Player.POSITION].startsWith("\"")) {
//            for (int i = Player.POSITION; i < fields.length; i++)
//                positions.add(fields[i].replace("\"", "").trim());
//        } else {
//            positions.add(fields[Player.POSITION]);
//        }
//        return positions;
//    }
//
//    private int getOverall(String[] arr) {
//        return Integer.parseInt(arr[Player.OVERALL]);
//    }
//
//    private String getClub(String[] fields) {
//        return fields[Player.CLUB];
//    }
//
//    private String getNationality(String[] fields) {
//        return fields[Player.NATIONALITY];
//    }
//
//    private int getHeight(String[] fields) {
//        return Integer.parseInt(fields[Player.HEIGHT]);
//    }
//
//    private String getName(String[] fields) {
//        return fields[Player.NAME];
//    }
//
//    private int getId(String[] fields) {
//        return Integer.parseInt(fields[Player.ID]);
//    }
    public Object[][] toArray(){
        Object[][] result = new Object[players.size()][Player.class.getDeclaredFields().length];
        for(int i=0; i < players.size(); i++)
            result[i] = players.get(i).toArray();
        return result;
    }

    public static Object[][] toArray(List<Player> players){
        Object[][] result = new Object[players.size()][Player.class.getDeclaredFields().length];
        for(int i=0; i < players.size(); i++)
            result[i] = players.get(i).toArray();
        return result;
    }
}



//getResource("players_20_short.csv").getFile(); String resourceFileName = Thread.currentThread().getContextClassLoader().getResource("com/fm/repository/players_20_short.csv").getPath();