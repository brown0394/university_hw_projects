package com.fm.repository;

import com.fm.unit.Player;

import java.util.List;
import java.util.Optional;
import java.util.function.Predicate;

public interface IRepository {
    int count();
    void save(Player t);
    void delete(Player t);
    void deleteById(int id);
    boolean existsById(int id);
    Iterable<Player> findAll();
    Optional<Player> findById(int id);
    List<Player> findByConditions(List<Predicate<Player>> conditions);
}