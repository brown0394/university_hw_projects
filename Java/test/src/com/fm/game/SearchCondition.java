package com.fm.game;

public class SearchCondition {
    private final String field;
    private final String condition;

    public SearchCondition(String field, String condition){
        this.field = field;
        this.condition = condition;
    }

    public String getField() {
        return field;
    }

    public String getCondition() {
        return condition;
    }
}