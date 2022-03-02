//import javax.persistence.EntityManager;
//import javax.persistence.EntityTransaction;
//import java.util.List;
//import java.util.Optional;
//
//public class JpaRepository<T, ID> {
//    private final Class<T> domainType;
//    private final EntityManager em;
//
//    public static final String SELECT_ALL_QUERY_STRING = "select x from %s x";
//
//    public JpaRepository(Class<T> domainType, EntityManager entityManager) {
//        this.domainType = domainType;
//        this.em = entityManager;
//    }
//
//    public T save(T entity) {
//        EntityTransaction tx = em.getTransaction();
//        tx.begin();
//        try{
//            em.persist(entity);
//            tx.commit();
//        } catch (Exception ex){
//            ex.printStackTrace();
//            tx.rollback();
//        }
//        return entity;
//    }
//
//    private String getSelectAllQueryString() {
//        return String.format(SELECT_ALL_QUERY_STRING, domainType.getSimpleName());
//    }
//
//    public List<T> findAll() {
//        //EntityTransaction tx = em.getTransaction();
//        return em.createQuery(getSelectAllQueryString(), domainType).getResultList();
//    }
//
//    public void deleteById(ID id) {
//        Optional<T> entity = findById(id);
//        EntityTransaction tx = em.getTransaction();
//        tx.begin();
//        try {
//            em.remove(entity.orElseThrow(()
//                    -> new RuntimeException(String.format("No %s entity with id %s exists!", domainType, id))));
//            tx.commit();
//        } catch (Exception ex){
//            ex.printStackTrace();
//            tx.rollback();
//        }
//    }
//
//    Optional<T> findById(ID id){
//        return Optional.ofNullable(em.find(domainType, id));
//    };
//}