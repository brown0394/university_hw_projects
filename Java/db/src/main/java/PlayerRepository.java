import java.sql.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;

public class PlayerRepository implements IRepository{

    public void save(Player t) {
        String country_sql = "SELECT * FROM COUNTRY " +
                "WHERE COUNTRY_NAME = \'" + t.getNationality() + "\'";
        Country country = query(country_sql, new CountryRowMapper());
        if (country == null) {
            String cinsql = "INSERT INTO COUNTRY (COUNTRY_NAME)\n" +
                    "VALUES ( \'" + t.getNationality() + "\' )";
            update(cinsql);
            country = query(country_sql, new CountryRowMapper());
        }

        String club_sql = "SELECT * FROM CLUB\n" +
                "WHERE CLUB_NAME = \'" + t.getClub() + "\'";
        Club club = query(club_sql, new ClubRowMapper());
        if (club == null) {
            String cinsql = "INSERT INTO CLUB (CLUB_NAME)\n" +
                    "VALUES ( \'" + t.getClub() + "\')";
            update(cinsql);
            club = query(club_sql, new ClubRowMapper());
        }

        StringBuilder positions = new StringBuilder();
        boolean first = true;
        for (String s : t.getPositions()) {
            if (first) {
                first = false;
                positions.append(s);
            }
            else positions.append(", " + s);
        }

        String sql = "INSERT INTO PLAYER ( SOFIFA_ID, " +
                "SHORT_NAME, HEIGHT_CM, COUNTRY_ID, " +
                "CLUB_ID, OVERALL, PLAYER_POSITIONS) " +
                "VALUES ( " + Integer.toString(t.getId()) + ", \'" + t.getName() +
                "\', " + Integer.toString(t.getHeight()) + ", " +
                Integer.toString(country.getId()) + ", " +
                Integer.toString(club.getId()) + ", " + Integer.toString(t.getOverall()) +
                ", \'" + positions.toString() + "\' )";
        if (update(sql) > 0) {
            sql = "SELECT * FROM PLAYER_VIEW WHERE OVERALL = " + Integer.toString(t.getOverall()) +
                    " AND SHORT_NAME = \'" + t.getName() + "\'";
            Player idp = query(sql, new PlayerRowMapper2()).get(0);
            System.out.println(idp.getId());
            for (String s : t.getPositions()) {
                String posql = "SELECT * FROM POSITION WHERE POSITION_NAME = \'" + s + "\'";
                Integer id = query(posql, new PositionRowMapper());
                String posupdate = "INSERT INTO PLAYER_POSITION (PLAYER_ID, POSITION_ID)\n" +
                        "VALUES ( " + idp.getId() + ", " + id.toString() + " )";
                update(posupdate);
            }
        }
    }
    public void deleteById(int id) {
        String sql = "DELETE FROM PLAYER\n" +
                "WHERE ID = " + Integer.toString(id);
        update(sql);
    }
    public List<Player> findAll() {
        return query("SELECT * FROM PLAYER_VIEW", new PlayerRowMapper());
    }
    public Optional<Player> findById(int id) {
        String sql = "SELECT * FROM PLAYER_VIEW WHERE ID = " + Integer.toString(id);
        Optional<Player> player = Optional.empty();
        List<Player> p = query(sql, new PlayerRowMapper());
        if(p.size() > 0)
            player = Optional.ofNullable(p.get(0));
        return player;
    }

    public Optional<List<Player>> findClub(String clubName) {
        String sql = "SELECT * FROM PLAYER_VIEW\n" +
                "WHERE CLUB_NAME = \'" + clubName + "\'";
        List<Player> players = query(sql, new PlayerRowMapper());
        return Optional.ofNullable(players);
    }


    public <T> T execute (StatementCallback<T> action) {
        T result = null;
        try (Connection conn =
                     DriverManager.getConnection("jdbc:h2:file:C:/Users/sungc/IdeaProjects/db/src/main/resources/db");
             Statement stmt = conn.createStatement();){
            result = action.doInStatement(stmt);
        } catch (SQLException ex){}
        return result;
    }
    public <T> T query (final String sql, RowMapper<T> mapper) {
        class QueryStatementCallback implements StatementCallback<T> {
            public T doInStatement(Statement stmt)
                    throws SQLException {
                T result = null;
                try (ResultSet rs = stmt.executeQuery(sql);){
                    result = mapper.mapRow(rs);
                }
                return result;
            }
        }
        return execute(new QueryStatementCallback());
    }

    public int update (final String sql) {
        int result = 0;
        try (Connection conn =
                     DriverManager.getConnection("jdbc:h2:file:C:/Users/sungc/IdeaProjects/db/src/main/resources/db");
             Statement stmt = conn.createStatement();){
            result = stmt.executeUpdate(sql);
        } catch (SQLException ex){}
        return result;
    }

    public interface RowMapper<T> {
        T mapRow(ResultSet rs) throws SQLException;
    }
    public interface StatementCallback<T> {
        T doInStatement(Statement stmt) throws SQLException;
    }


    private class PlayerRowMapper implements RowMapper<List<Player>> {
    public List<Player> mapRow(ResultSet rs) throws SQLException {
        List<Player> players = new ArrayList<>();
        while(rs.next()) {
            int id = rs.getInt("ID");
            String name = rs.getString("SHORT_NAME");
            int heightCM = rs.getInt("HEIGHT_CM");
            String countryName = rs.getString("COUNTRY_NAME");
            String clubName = rs.getString("CLUB_NAME");
            int overall = rs.getInt("OVERALL");
            String positions = rs.getString("PLAYER_POSITIONS");
            Player player = new Player(id, name, heightCM, countryName,
                    clubName, overall, Arrays.asList(positions.split(",")));
            players.add(player);}
        return players;}}

    private class PlayerRowMapper2 implements RowMapper<List<Player>> {
        public List<Player> mapRow(ResultSet rs) throws SQLException {
            List<Player> players = new ArrayList<>();
            while(rs.next()) {
                int id = rs.getInt("ID");
                String name = rs.getString("SHORT_NAME");
                int heightCM = rs.getInt("HEIGHT_CM");
                String countryName = rs.getString("COUNTRY_NAME");
                String clubName = rs.getString("CLUB_NAME");
                int overall = rs.getInt("OVERALL");
                String positions = "no, info";
                Player player = new Player(id, name, heightCM, countryName,
                        clubName, overall, Arrays.asList(positions.split(",")));
                players.add(player);}
            return players;}}

    private class CountryRowMapper implements RowMapper<Country> {
        public Country mapRow(ResultSet rs) throws SQLException {
            Country country = null;
            while(rs.next()) {
                int id = rs.getInt("ID");
                String name = rs.getString("COUNTRY_NAME");
                country = new Country(id, name);
            }
            return country;
        }
    }

    private class Country {
        public int getId() {
            return id;
        }

        private int id;

        public String getName() {
            return name;
        }

        private String name;
        public Country(int id, String name) {
            this.id = id;
            this.name = name;
        }
    }

public class ClubRowMapper implements RowMapper<Club>{
        public Club mapRow (ResultSet rs) throws SQLException {
            Club club = null;
            while(rs.next()) {
                int id = rs.getInt("ID");
                String name = rs.getString("CLUB_NAME");
                club = new Club(id, name);
            }
            return club;
        }
}


    private class Club {
        private int id;
        private String name;


        public Club() {}
        public Club(int id, String name) {
            this.id = id;
            this.name = name;
        }

        public int getId() {
            return id;
        }

        public String getName() {
            return name;
        }
    }
    public class PositionRowMapper implements RowMapper<Integer>{
        public Integer mapRow (ResultSet rs) throws SQLException {
            Integer idp = null;
            while(rs.next()) {
                int id = rs.getInt("ID");
                idp = id;
            }
            return idp;
        }
    }
}
