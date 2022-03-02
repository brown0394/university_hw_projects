package com.fm.view;

import com.fm.controller.SearchPlayerController;
import com.fm.model.SearchPlayerModel;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.Array;

public class SearchPlayerView  extends JFrame {
    private JTable table;

    private JButton buttonSearch;
    private JButton buttonCreate;
    private JButton buttonDelete;

    private JLabel labelName;
    private JLabel labelClub;
    private JLabel labelPosition;
    private JLabel labelNationality;

    private JTextField[] textField = new JTextField[4];
    private final int NAME = 0;
    private final int CLUB = 1;
    private final int POSITION = 2;
    private final int NATIONALITY = 3;

    // your code here
    public SearchPlayerView(SearchPlayerController controller, SearchPlayerModel model) {
        JScrollPane scrollPane = setTable(model);
        JPanel buttonPanel = setButtons(controller);
        JPanel inputPanel = setInputField();


        setLayout(new BorderLayout());
        add(inputPanel, BorderLayout.NORTH);
        add(buttonPanel, BorderLayout.CENTER);
        add(scrollPane, BorderLayout.SOUTH);
    }

    public SearchPlayerView(SearchPlayerController controller, JTable table) {
        JScrollPane scrollPane = new JScrollPane(table);
        JPanel buttonPanel = setButtons(controller);
        JPanel inputPanel = setInputField();


        setLayout(new BorderLayout());
        add(inputPanel, BorderLayout.NORTH);
        add(buttonPanel, BorderLayout.CENTER);
        add(scrollPane, BorderLayout.SOUTH);
    }


    final int columns = 80;
    int strutHeight = 3;
    private JPanel setTextFields() {
        JPanel panel = new JPanel();
        textField[NAME] = new JTextField(columns);
        textField[CLUB] = new JTextField(columns);
        textField[POSITION] = new JTextField(columns);
        textField[NATIONALITY] = new JTextField(columns);

        textField[NAME].setName("name");
        textField[CLUB].setName("club");
        textField[POSITION].setName("position");
        textField[NATIONALITY].setName("nationality");

        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
        panel.add(Box.createVerticalStrut(strutHeight));
        panel.add(textField[NAME]);
        panel.add(Box.createVerticalStrut(strutHeight));
        panel.add(textField[CLUB]);
        panel.add(Box.createVerticalStrut(strutHeight));
        panel.add(textField[POSITION]);
        panel.add(Box.createVerticalStrut(strutHeight));
        panel.add(textField[NATIONALITY]);

        return panel;
    }

    private JPanel setTexts() {
        Font font = new Font("Dialog", Font.PLAIN, 15);
        labelName = new JLabel("Name");
        labelClub = new JLabel("Club");
        labelPosition = new JLabel("Position");
        labelNationality = new JLabel("Nationality");
        labelName.setFont(font);
        labelClub.setFont(font);
        labelPosition.setFont(font);
        labelNationality.setFont(font);
        JPanel panel = new JPanel();
        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
        panel.add(labelName);
        panel.add(Box.createVerticalStrut(strutHeight));
        panel.add(labelClub);
        panel.add(Box.createVerticalStrut(strutHeight));
        panel.add(labelPosition);
        panel.add(Box.createVerticalStrut(strutHeight));
        panel.add(labelNationality);
        return panel;
    }

    private JPanel setInputField() {
        JPanel labels = setTexts();
        JPanel textFields = setTextFields();

        JPanel panel = new JPanel();
        panel.setLayout(new FlowLayout(FlowLayout.LEFT, 10, 2));
        panel.add(labels);
        panel.add(textFields);
        return panel;
    }

    private JPanel setButtons(SearchPlayerController controller) {
        buttonSearch = new JButton("Search");
        buttonCreate = new JButton("Create");
        buttonDelete = new JButton("Delete");
        Dimension dimension = new Dimension(264, 25);
        buttonSearch.setPreferredSize(dimension);
        buttonDelete.setPreferredSize(dimension);
        buttonCreate.setPreferredSize(dimension);

        buttonSearch.setName("Search");
        buttonSearch.addActionListener(new SearchPlayerActionListener(textField ,controller));

        JPanel buttonPanel = new JPanel();
        buttonPanel.setLayout(new FlowLayout());
        buttonPanel.add(Box.createHorizontalStrut(71));
        buttonPanel.add(buttonCreate);
        buttonPanel.add(buttonDelete);
        buttonPanel.add(buttonSearch);
        return buttonPanel;
    }

    private JScrollPane setTable(SearchPlayerModel model) {
       // Font font = new Font("Serif", Font.PLAIN, 15);
        table = new JTable();
      //  UIManager.put("Table.font", font);
        table.setModel(model);
        table.setRowHeight(24);
       // table.getTableHeader().setFont(font);
        table.setPreferredScrollableViewportSize(new Dimension(800, 500));
        return new JScrollPane(table);
    }
}