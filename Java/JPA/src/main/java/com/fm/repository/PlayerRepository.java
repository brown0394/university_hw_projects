package com.fm.repository;


import com.fm.entity.Player;
import com.sun.xml.bind.v2.model.core.ID;

import javax.persistence.EntityManager;
import javax.persistence.EntityTransaction;
import java.util.List;
import java.util.Optional;

public class PlayerRepository implements IRepository{
    private final EntityManager em;

    public static final String SELECT_ALL_QUERY_STRING = "select x from %s x";


    public PlayerRepository(EntityManager entityManager) {
        this.em = entityManager;
    }

    public void save(Player entity) {
        EntityTransaction tx = em.getTransaction();
        tx.begin();
        try{
            em.persist(entity);
            tx.commit();
        } catch (Exception ex){
            ex.printStackTrace();
            tx.rollback();
        }
    }

    private String getSelectAllQueryString() {
        return String.format(SELECT_ALL_QUERY_STRING, Player.class.getSimpleName());
    }

    public List<Player> findAll() {
        //EntityTransaction tx = em.getTransaction();
        return em.createQuery(getSelectAllQueryString(), Player.class).getResultList();
    }

    public void deleteById(int id) {
        Optional<Player> entity = findById(id);
        EntityTransaction tx = em.getTransaction();
        tx.begin();
        try {
            em.remove(entity.orElseThrow(()
                    -> new RuntimeException(String.format("No %s entity with id %s exists!", Player.class, id))));
            tx.commit();
        } catch (Exception ex){
            ex.printStackTrace();
            tx.rollback();
        }
    }

    public Optional<Player> findById(int id){
        return Optional.ofNullable(em.find(Player.class, id));
    };
}