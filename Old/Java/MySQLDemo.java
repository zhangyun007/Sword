import java.sql.*;

public class MySQLDemo {
 
    static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";  
    static final String DB_URL = "jdbc:mysql://localhost:3333/testdb";
 

    static final String USER = "root";
    static final String PASS = "root";
 
    public static void main(String[] args) {
        Connection conn = null;
        Statement stmt = null;
        try{
            Class.forName(JDBC_DRIVER);
        

            System.out.println("connect...");
            conn = DriverManager.getConnection(DB_URL,USER,PASS);
        

            System.out.println(" instance Statement object...");
            stmt = conn.createStatement();
            String sql;
            sql = "SELECT * FROM EMPLOYEE";
            ResultSet rs = stmt.executeQuery(sql);


            while(rs.next()){

                int id  = rs.getInt("id");
                String first_name = rs.getString("first_name");
				String last_name = rs.getString("first_name");
    
    
                System.out.print("ID: " + id);
                System.out.print(", site first_name: " + first_name);
                System.out.print(", site last_name: " + last_name);
                System.out.print("\n");
            }
     
            rs.close();
            stmt.close();
            conn.close();
        }catch(SQLException se){
          
            se.printStackTrace();
        }catch(Exception e){
           
            e.printStackTrace();
        }finally{
         
            try{
                if(stmt!=null) stmt.close();
            }catch(SQLException se2){
            }
            try{
                if(conn!=null) conn.close();
            }catch(SQLException se){
                se.printStackTrace();
            }
        }
        System.out.println("Goodbye!");
    }
}