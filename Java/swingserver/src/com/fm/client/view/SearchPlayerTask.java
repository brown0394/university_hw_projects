package com.fm.client.view;

import com.fm.search.SearchCondition;
import com.fm.search.SearchField;

import javax.swing.*;
import java.util.ArrayList;
import java.util.List;

public class SearchPlayerTask extends SwingWorker<Void, Void> {
    private JTextField[] searchTermTextFields;
    private SearchPlayer controller;
    private final int NAME = 0;
    private final int CLUB = 1;
    private final int POSITION = 2;
    private final int NATIONALITY = 3;
    public SearchPlayerTask(JTextField[] searchTermTextFields, SearchPlayer controller) {
        this.searchTermTextFields = searchTermTextFields;
        this.controller = controller;
    }

    public Void doInBackground() { // executed in worker thread
        List<SearchCondition> condition = new ArrayList<SearchCondition>();
        String name = searchTermTextFields[NAME].getText();
        String club = searchTermTextFields[CLUB].getText();
        String pos = searchTermTextFields[POSITION].getText();
        String nation = searchTermTextFields[NATIONALITY].getText();

        if (!name.equals("")) {
            condition.add(new SearchCondition(SearchField.NAME, name));
        }
        if (!club.equals("")) {
            condition.add(new SearchCondition(SearchField.CLUB, club));
        }
        if (!pos.equals("")) {
            condition.add(new SearchCondition(SearchField.POSITION, pos));
        }
        if (!nation.equals("")) {
            condition.add(new SearchCondition(SearchField.NATIONALITY, nation));
        }
        controller.searchPlayer(condition);
        return null;
    }

    public void done() { // executed in Event Dispatch Thread
        System.out.println("search done\n");
    }
}
