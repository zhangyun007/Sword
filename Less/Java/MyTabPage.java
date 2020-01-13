
import javax.swing.*;

import java.awt.*;

public class MyTabPage  extends JTabbedPane

{

private static final long serialVersionUID = 1L;

static final int WIDTH=600;

    static final int HEIGHT=400;

    public MyTabPage()

    {

      JFrame f=new JFrame("JTabbedPane test");

      JPanel p=new JPanel();

      f.setContentPane(p);

      f.setVisible(true);

         setLayout(new BorderLayout());

         JPanel panel1 = new JPanel ();
		 
		 JTextField name = new JTextField(30);
		 
		 panel1.add(name);
		 
		 panel1.setVisible(true);
		 

         JPanel panel2 = new JPanel ();

         JPanel panel3 = new JPanel ();

         JPanel panel4 = new JPanel ();

         JPanel panel5 = new JPanel ();

         panel1.setLayout(new BorderLayout());

         addTab("Tab1", panel1);

         setEnabledAt(0,true);

         setTitleAt(0,"JTabbedPane1 test");

         addTab ("Tab2", panel2);

         setEnabledAt (1, true);

         setTitleAt (1,"JTabbedPane2 hello");

         addTab ("Tab3", panel3);

         setEnabledAt (2, true);

         setTitleAt (2,"JTabbedPane3 aaa");

         addTab ("Tab4", panel4);

         setEnabledAt(0,true);

         setTitleAt(3,"JTabbedPane bbb");

         addTab ("Tab5", panel5);

         setEnabledAt(4,true);

         setTitleAt(4,"JTabbedPane5 ccc");

         setPreferredSize (new Dimension (800,600));

         setTabPlacement (JTabbedPane.TOP);

         setTabLayoutPolicy (JTabbedPane.SCROLL_TAB_LAYOUT);

         p.add("Center",this);

         setVisible(true);

 }

 public static void main(String[] args)

 {

     new MyTabPage();

 }

}