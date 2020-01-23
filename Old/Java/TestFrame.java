import java.awt.Container;
import javax.swing.*;

public class TestFrame extends JFrame{
    
    private static final long serialVersionUID = 1L;
    
    public TestFrame(){
        this.setTitle("test");
        Container con = this.getContentPane();
        JScrollPane jp = new JScrollPane(new JTextArea(50,20));
        con.add(jp);
        this.setVisible(true);
        this.setBounds(50, 50, 200, 200);
        this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
    }
    public static void main(String[] args) {
        new TestFrame();
    }
}