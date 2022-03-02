package com.fm.controller;

import com.fm.entity.Player;
import com.fm.model.SearchPlayerModel;
import com.fm.repository.PlayerRepository;
import com.fm.repository.PlayerSearchPredicateFactory;
import com.fm.view.SearchCondition;

import javax.persistence.EntityManager;
import javax.persistence.EntityManagerFactory;
import javax.persistence.Persistence;
import javax.swing.table.DefaultTableModel;
import java.util.List;
import java.util.Optional;

public class SearchPlayerController {
    DefaultTableModel model;
    EntityManagerFactory emf;
    EntityManager em;


    public SearchPlayerController(DefaultTableModel model){
        this.model = model;
        emf = Persistence.createEntityManagerFactory("pnu.cse");
        em = emf.createEntityManager();
    }

    public void searchPlayer(List<SearchCondition> conditions){
        PlayerRepository playerRepository = new PlayerRepository(em);
        Optional<Player> player = playerRepository.findById(18203);
       // club.get().getPlayers().stream().forEach(System.out::println);
        em.close(); emf.close();
        Object[][] newData =
//                PlayerRepository.toArray(
//                PlayerRepository.getInstance().query(
//                        PlayerSearchPredicateFactory.makeConditions(conditions)));
        model.setDataVector(newData, SearchPlayerModel.TABLE_HEADER);
    }
}