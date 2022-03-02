package com.fm.repository;

import com.fm.game.SearchCondition;
import com.fm.unit.Player;

import java.util.ArrayList;
import java.util.List;
import java.util.function.Predicate;

public class PlayerSearchPredicateFactory {
    public static List<Predicate<Player>> makeConditions(List<SearchCondition> searchConditions){
        // your code here
        List<Predicate<Player>> condition = new ArrayList<>();

        for(SearchCondition s : searchConditions) {
            switch(s.getField()) {
                case "club": {
                    Predicate<Player> newpredic = (p) -> p.getClub().contains(s.getCondition());
                    condition.add(newpredic);
                    break;
                }
                case "nationality":{
                    Predicate<Player> newpredic = (p) -> p.getNationality().contains(s.getCondition());
                    condition.add(newpredic);
                    break;
                }
                case "name":{
                    Predicate<Player> newpredic = (p) -> p.getName().contains(s.getCondition());
                    condition.add(newpredic);
                    break;
                }
                case "position":{
                    Predicate<Player> newpredic = (p) -> p.getPositions().equals(s.getCondition());
                    condition.add(newpredic);
                    break;
                }
            }
        }

        return condition;
    }
}