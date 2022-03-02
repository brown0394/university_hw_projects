package com.fm.server.model;

import com.fm.unit.Player;

import java.util.ArrayList;
import java.util.List;
import java.util.function.Predicate;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class PlayerQuery {
    public static List<Player> query(List<Player> players, List<Predicate<Player>> conditions){
        //your code here
        List<Player> plist = null;
        Stream<Player> pstream = players.stream();
        for (Predicate<Player> p : conditions) {
            pstream = pstream.filter(p);
        }
        if(!conditions.isEmpty()) {
            plist = pstream.collect(Collectors.toList());
        }
        return plist;
    }
}