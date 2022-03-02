import java.util.List;
import java.util.Optional;

public interface IRepository {
    void save(Player t);
    void deleteById(int id);
    List<Player> findAll();
    Optional<Player> findById(int id);
}