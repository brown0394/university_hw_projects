package com.fm.controller;

import com.fm.model.SearchPlayerModel;
import com.fm.repository.PlayerRepository;
import com.fm.repository.PlayerSearchPredicateFactory;
import com.fm.view.SearchCondition;

import javax.swing.table.DefaultTableModel;
import java.util.List;

public class SearchPlayerController {
    DefaultTableModel model;

    public SearchPlayerController(DefaultTableModel model){
        this.model = model;
    }

    public void searchPlayer(List<SearchCondition> conditions){
        Object[][] newData = PlayerRepository.toArray(
                PlayerRepository.getInstance().query(
                        PlayerSearchPredicateFactory.makeConditions(conditions)));
        model.setDataVector(newData, SearchPlayerModel.TABLE_HEADER);
    }
}