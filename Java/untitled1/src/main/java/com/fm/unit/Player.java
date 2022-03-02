package com.fm.unit;

import java.lang.reflect.Field;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;

public class Player {
    public static int ID = 0;
    public static int NAME = 1;
    public static int HEIGHT = 2;
    public static int NATIONALITY = 3;
    public static int CLUB = 4;
    public static int OVERALL = 5;
    public static int POSITION = 6;

    private final int id;
    private final String name;
    private final int height;
    private final String nationality;
    private final String club;
    private final int overall;
    private final List<String> positions;

    public Player(int id, String name, int height, String nationality, String club, int overall, List<String> positions){
        this.id = id;
        this.name = name;
        this.height = height;
        this.nationality = nationality;
        this.club = club;
        this.overall = overall;
        this.positions = positions;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public int getHeight() {
        return height;
    }

    public String getNationality() {
        return nationality;
    }

    public String getClub() {
        return club;
    }

    public int getOverall() {
        return overall;
    }

    public List<String> getPositions() {
        return positions;
    }

    public Object[] toArray(){
        Field[] fields = Player.class.getDeclaredFields();
        fields = Arrays.stream(fields).filter(f->f.getModifiers()==18).toArray(Field[]::new);
        Object[] result = new Object[fields.length];
        try {
            for (int i = 0; i < fields.length; i++)
                if(fields[i].getModifiers()==18)
                    result[i] = fields[i].get(this);
        } catch (Exception e){
            System.err.println(e);
            System.exit(1);
        }
        return result;
    }

    @Override
    public String toString() {
        return String.valueOf(id);
    }

}
