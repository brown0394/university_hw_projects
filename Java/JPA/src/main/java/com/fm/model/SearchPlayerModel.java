package com.fm.model;

import com.fm.repository.PlayerRepository;

import javax.swing.table.DefaultTableModel;

public class SearchPlayerModel extends DefaultTableModel {
    public static final Object[] TABLE_HEADER = { "ID", "Player Name",
            "Height", "Nationality", "Club", "Overall", "positions" };

    public SearchPlayerModel() {
        super(null, TABLE_HEADER);
    }
}