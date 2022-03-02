package com.fm.unit;

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
    private static int MAXID = 0;

    public Player(int id, String name, int height, String nationality, String club, int overall, List<String> positions) {
        this.id = id;
        this.name = name;
        this.height = height;
        this.nationality = nationality;
        this.club = club;
        this.overall = overall;
        this.positions = positions;
        if (MAXID < id) MAXID = id;
    }

    public Player(String name, int height, String nationality, String club, int overall, List<String> positions) {
        this.id = ++MAXID;
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

    @Override
    public String toString() {
        return String.format("%d,%s,%d,%s,%s,%d,\"%s\"", id, name, height, nationality, club, overall, positions.toString().replaceAll("\\[|\\]", ""));
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Player player = (Player) o;
        return id == player.id;
    }

    @Override
    public int hashCode() {
        return Objects.hash(id);
    }
}