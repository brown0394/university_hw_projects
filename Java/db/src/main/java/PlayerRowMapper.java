//import java.sql.ResultSet;
//import java.sql.SQLException;
//import java.util.ArrayList;
//import java.util.Arrays;
//import java.util.List;
//
//class PlayerRowMapper implements
//        JdbcTemplate.RowMapper<List<Player>> {
//    public List<Player> mapRow(ResultSet rs) throws SQLException {
//        List<Player> players = new ArrayList<>();
//        while(rs.next()) {
//            int id = rs.getInt("ID");
//            String name = rs.getString("SHORT_NAME");
//            int heightCM = rs.getInt("HEIGHT_CM");
//            String countryName = rs.getString("COUNTRY_NAME");
//            String clubName = rs.getString("CLUB_NAME");
//            int overall = rs.getInt("OVERALL");
//            String positions = rs.getString("PLAYER_POSITIONS");
//            Player player = new Player(id, name, heightCM, countryName,
//                    clubName, overall, Arrays.asList(positions.split(",")));
//            players.add(player);}
//        return players;}}