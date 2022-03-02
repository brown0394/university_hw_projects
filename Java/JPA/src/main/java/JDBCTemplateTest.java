//import entity.Club;
//import entity.Player;
//
//import javax.persistence.EntityManager;
//import javax.persistence.EntityManagerFactory;
//import javax.persistence.Persistence;
//import java.util.Optional;
//
//public class JDBCTemplateTest {
//    public static void main(String[] args) {
//        EntityManagerFactory emf = Persistence.createEntityManagerFactory("pnu.cse");
//        EntityManager em = emf.createEntityManager();
//        JpaRepository<Club, Long> playerRepository = new JpaRepository<>(Club.class, em);
//        Optional<Club> club = playerRepository.findById(18503L);
//        club.get().getPlayers().stream().forEach(System.out::println);
//        em.close(); emf.close();
//    }
//}
