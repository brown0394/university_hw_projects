//import java.sql.ResultSet;
//import java.sql.SQLException;
//import java.util.ArrayList;
//import java.util.Arrays;
//import java.util.List;
//
//public class ClubRowMapper implements
//    JdbcTemplate.RowMapper<List<Club>>{
//        public List<Club> mapRow (ResultSet rs) throws SQLException {
//        List<Club> clubs = new ArrayList<>();
//        while (rs.next()) {
//            int id = rs.getInt("ID");
//            String name = rs.getString("CLUB_NAME");
//            Club club = new Club(id, name);
//            clubs.add(club);a
//        }
//        return clubs;
//    }
//}
