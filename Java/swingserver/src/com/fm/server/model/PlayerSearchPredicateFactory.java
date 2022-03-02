package com.fm.server.model;


import com.fm.search.SearchCondition;
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
                case CLUB: {
                    Predicate<Player> newpredic = (p) -> p.getClub().contains(s.getCondition());
                    condition.add(newpredic);
                    break;
                }
                case NATIONALITY:{
                    Predicate<Player> newpredic = (p) -> p.getNationality().contains(s.getCondition());
                    condition.add(newpredic);
                    break;
                }
                case NAME:{
                    Predicate<Player> newpredic = (p) -> p.getName().contains(s.getCondition());
                    condition.add(newpredic);
                    break;
                }
                case POSITION:{
                    Predicate<Player> newpredic = (p) -> p.getPositions().contains(s.getCondition());
                    condition.add(newpredic);
                    break;
                }
            }
        }

        return condition;
    }
}