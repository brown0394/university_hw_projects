//import entity.Club;
//import entity.Player;
//
//import javax.persistence.EntityManager;
//import javax.persistence.EntityManagerFactory;
//import javax.persistence.EntityTransaction;
//import javax.persistence.Persistence;
//
//public class JpaEntityTest {
//    public static void main(String[] args) {
//        EntityManagerFactory emf =
//                Persistence.createEntityManagerFactory("pnu.cse");
//        EntityManager em = emf.createEntityManager();
//        Club club = new Club();
//        club.setName("PNU");
//        EntityTransaction tx = em.getTransaction();
//        try{
//            tx.begin();
//            Player player = em.find(Player.class, 2L);
//            player.setClub(club);
//            club.getPlayers().add(player);
//            em.persist(club);
//            tx.commit();
//        } catch (Exception ex){
//            ex.printStackTrace();
//            tx.rollback();
//        }
//        System.out.printf("%d, %s, %s\n", club.getId(), club.getName(), club.getPlayers());
//    }
//}