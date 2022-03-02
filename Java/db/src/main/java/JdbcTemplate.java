//import java.sql.*;
//
//public class JdbcTemplate {
//    public <T> T execute (StatementCallback<T> action) {
//        T result = null;
//        try (Connection conn =
//                     DriverManager.getConnection("jdbc:h2:file:C:/Users/sungc/IdeaProjects/db/src/main/resources/db");
//             Statement stmt = conn.createStatement();){
//            result = action.doInStatement(stmt);
//        } catch (SQLException ex){}
//        return result;
//    }
//    public <T> T query (final String sql, RowMapper<T> mapper) {
//        class QueryStatementCallback implements StatementCallback<T> {
//            public T doInStatement(Statement stmt)
//                    throws SQLException {
//                T result = null;
//                try (ResultSet rs = stmt.executeQuery(sql);){
//                    result = mapper.mapRow(rs);
//                }
//                return result;
//            }
//        }
//        return execute(new QueryStatementCallback());
//    }
//
//
//    public interface RowMapper<T> {
//        T mapRow(ResultSet rs) throws SQLException;
//    }
//    public interface StatementCallback<T> {
//        T doInStatement(Statement stmt) throws SQLException;
//    }
//
//}