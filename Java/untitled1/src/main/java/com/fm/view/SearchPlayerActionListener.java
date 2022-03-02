package com.fm.view;

import com.fm.controller.SearchPlayerController;

import javax.print.attribute.standard.MediaSize;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;

public class SearchPlayerActionListener implements ActionListener {
    private JTextField[] searchTermTextFields;
    private SearchPlayerController controller;
    private final int NAME = 0;
    private final int CLUB = 1;
    private final int POSITION = 2;
    private final int NATIONALITY = 3;

    public SearchPlayerActionListener(JTextField[] searchTermTextFields, SearchPlayerController controller) {
        super();
        this.searchTermTextFields = searchTermTextFields;
        this.controller = controller;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        // your code here

        List<SearchCondition> condition = new ArrayList<SearchCondition>();
        String name = searchTermTextFields[NAME].getText();
        String club = searchTermTextFields[CLUB].getText();
        String pos = searchTermTextFields[POSITION].getText();
        String nation = searchTermTextFields[NATIONALITY].getText();

        if (!name.equals("")) {
            condition.add(new SearchCondition("name", name));
        }
        if (!club.equals("")) {
            condition.add(new SearchCondition("club", club));
        }
        if (!pos.equals("")) {
            condition.add(new SearchCondition("position", pos));
        }
        if (!nation.equals("")) {
            condition.add(new SearchCondition("nationality", nation));
        }
        controller.searchPlayer(condition);
    }
}