package com.fm.repository;

import com.fm.unit.Player;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class PlayerFactory {
    private static List<String> getPosition(String[] fields, int idx) {
        List<String> positions = new ArrayList<>();
        if (fields[idx].startsWith("\"")) {
            for (int i = idx; i < fields.length; i++)
                positions.add(fields[i].replace("\"", "").trim());
        } else {
            positions.add(fields[idx]);
        }
        return positions;
    }
    public static Player createPlayersWithoutID(String[] fields){
        //your code here
        List<String> positionList = getPosition(fields, 5);
        Player newplayer = new Player(fields[0], Integer.parseInt(fields[1]), fields[2], fields[3],
                Integer.parseInt(fields[4]), positionList);
        return newplayer;
    }

    public static Player createPlayers(String[] fields){
        //your code here
        List<String> positionList = getPosition(fields, 6);
        Player newplayer = new Player(Integer.parseInt(fields[0]), fields[1], Integer.parseInt(fields[2]), fields[3],
                fields[4], Integer.parseInt(fields[5]),positionList);
        return newplayer;
    }
}