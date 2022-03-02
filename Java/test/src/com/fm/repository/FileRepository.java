package com.fm.repository;

import com.fm.unit.Player;

import java.io.*;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;
import java.util.function.Predicate;

import static java.nio.file.StandardOpenOption.APPEND;

public class FileRepository implements IRepository {
    public static final String[] FILE_HEADER =
            { "sofifa_id", "short_name", "height_cm", "nationality", "club", "overall", "player_positions", "\n" };
    private static FileRepository instance = new FileRepository();
    public final String FILENAME =
            Thread.currentThread().getContextClassLoader().getResource("com/fm/repository/players_20_short.csv").getPath().replaceFirst("/", "");//getResource("players_20_short.csv").getFile();
    private boolean loaded = false;
    private List<Player> players;

    private FileRepository(){
        load();
    }

    public static FileRepository getInstance() {return instance;}

    private Player create(String[] fields) {
        return PlayerFactory.createPlayers(fields);
    }
    //your code here

    public void load() {//이걸르 수정? dd
        if(!isLoaded()) {
            List<Player> players = new ArrayList<>();
            Path path = Paths.get(FILENAME);
            Charset charset = Charset.forName("UTF-8");
            if(Files.exists(path)){
                try(BufferedReader reader = Files.newBufferedReader(path, charset)){
                    loaded = true;
                    String line;
                    while ((line=reader.readLine())!=null) {
                        if (line.contains(FILE_HEADER[0])) {
                            continue;
                        }
                        Player p = createPlayer(line.split(","));
                        players.add(p);
                    }
                }catch(IOException e){
                    e.printStackTrace();
                    System.out.println(e);
                }finally{
                    this.players = players;
                    loaded = false;
                }
            }
        }
 //String resourceFileName = Thread.currentThread().getContextClassLoader().getResource("com/fm/repository/players_20_short.csv").getPath();

    }

    public int count() {
        return players.size();
    }

    public void save(Player t) {
        if(!isLoaded()) {
            Path path = Paths.get(FILENAME);
            Charset charset = Charset.forName("UTF-8");
            if(Files.exists(path)){
                try(BufferedWriter writer = Files.newBufferedWriter(path, charset, APPEND)){
                    loaded = true;
                    writer.write(t.toString()+"\n");
                }catch(IOException e){
                    e.printStackTrace();
                    System.out.println(e);
                }finally{
                    this.players.add(t);
                    loaded = false;
                }
            }
        }
    }

    public void delete(Player t) {
        for (int i = 0; i < players.size(); ++i) {
            if(t.equals(players.get(i))){
                players.remove(i);
                break;
            }
        }
        if(!isLoaded()) {
            Path path = Paths.get(FILENAME);
            Charset charset = Charset.forName("UTF-8");
            if(Files.exists(path)){
                try(BufferedWriter writer = Files.newBufferedWriter(path, charset)){
                    loaded = true;
                    for(String s : FILE_HEADER) {
                        writer.write(s);
                        if(!s.equals("\n")) {
                            writer.write(',');
                        }
                    }
                    for(Player p : players) {
                        writer.write(p.toString()+"\n");
                    }
                }catch(IOException e){
                    e.printStackTrace();
                    System.out.println(e);
                }finally{
                    loaded = false;
                }
            }
        }
    }

    public void deleteById(int id) {
        for (int i = 0; i < players.size(); ++i) {
            if(players.get(i).getId() == id){
                players.remove(i);
                break;
            }
        }
        if(!isLoaded()) {
            Path path = Paths.get(FILENAME);
            Charset charset = Charset.forName("UTF-8");
            if(Files.exists(path)){
                try(BufferedWriter writer = Files.newBufferedWriter(path, charset)){
                    loaded = true;
                    for(String s : FILE_HEADER) {
                        writer.write(s);
                        if(!s.equals("\n")) {
                            writer.write(',');
                        }
                    }
                    for(Player p : players) {
                        writer.write(p.toString()+"\n");
                    }
                }catch(IOException e){
                    e.printStackTrace();
                    System.out.println(e);
                }finally{
                    loaded = false;
                }
            }
        }
    }
    public boolean existsById(int id) {
        for (int i = 0; i < players.size(); ++i) {
            if(players.get(i).getId() == id){
                return true;
            }
        }
        return false;
    }

    public Iterable<Player> findAll(){
        Iterable<Player> p = new Iterable<Player>() {
            @Override
            public Iterator<Player> iterator() {
                return null;
            }
        };
        return p;
    }

    public Optional<Player> findById(int id) {
        Optional<Player> op = players.stream().filter((p)->p.getId()==id).findAny();
        return op;
    }
    public List<Player> findByConditions(List<Predicate<Player>> conditions) {
        if (0 < conditions.size() && 0 < players.size())
            return PlayerQuery.query(players, conditions);
        else
            return new ArrayList<>();
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
        Player player = new Player(getId(fields), getName(fields), getHeight(fields),
                getNationality(fields), getClub(fields), getOverall(fields), getPosition(fields));
        return player;
    }

    private List<String> getPosition(String[] fields) {
        List<String> positions = new ArrayList<>();
        if (fields[Player.POSITION].startsWith("\"")) {
            for (int i = Player.POSITION; i < fields.length; i++)
                positions.add(fields[i].replace("\"", "").trim());
        } else {
            positions.add(fields[Player.POSITION]);
        }
        return positions;
    }

    private int getOverall(String[] arr) {
        return Integer.parseInt(arr[Player.OVERALL]);
    }

    private String getClub(String[] fields) {
        return fields[Player.CLUB];
    }

    private String getNationality(String[] fields) {
        return fields[Player.NATIONALITY];
    }

    private int getHeight(String[] fields) {
        return Integer.parseInt(fields[Player.HEIGHT]);
    }

    private String getName(String[] fields) {
        return fields[Player.NAME];
    }

    private int getId(String[] fields) {
        return Integer.parseInt(fields[Player.ID]);
    }
}
