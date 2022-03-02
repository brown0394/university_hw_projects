package com.fm.model;

import com.fm.repository.PlayerRepository;

import javax.swing.table.DefaultTableModel;

public class SearchPlayerModel extends DefaultTableModel {
    public static final Object[] TABLE_HEADER = { "ID", "Player Name",
            "Height", "Nationality", "Club", "Overall", "positions" };

    static {
        PlayerRepository.getInstance().load();
    }

    public SearchPlayerModel() {
        super(PlayerRepository.getInstance().toArray(), TABLE_HEADER);
    }
}