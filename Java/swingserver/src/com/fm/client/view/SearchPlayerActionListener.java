package com.fm.client.view;



import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;


public class SearchPlayerActionListener implements ActionListener {
    private JTextField[] searchTermTextFields;
    private SearchPlayer controller;
    private SearchPlayerTask task;


    public SearchPlayerActionListener(JTextField[] searchTermTextFields, SearchPlayer controller) {
        super();
        this.searchTermTextFields = searchTermTextFields;
        this.controller = controller;
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        // your code here
        task = new SearchPlayerTask(searchTermTextFields, controller);
        task.execute();
    }
}