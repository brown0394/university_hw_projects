//import java.util.List;
//
//public class JDBCTemplateTest {
//    public static void main(String[] args) {
//        String sql = "SELECT * FROM CLUB";
//        JdbcTemplate template = new JdbcTemplate();
//        List<Club> clubs = template.query(sql, new ClubRowMapper());
//        clubs.stream().forEach(System.out::println);
//    }
//}