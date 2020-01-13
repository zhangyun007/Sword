import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;



public class Russian
{
    public static void main(String[] agrs)
    {
        JFrame frame=new JFrame("Chinese to Russian");  
        JPanel jp=new JPanel(); 
		
		JLabel label = new JLabel("请输入想要查询的中文或者俄文单词：");
        JTextField txtfield1=new JTextField(); 
        txtfield1.setText("Input Chinese or Russian");    
		JButton button = new JButton("查询");

		jp.add(label);
        jp.add(txtfield1);
		jp.add(button);
		
		// 为按钮绑定监听器
        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // 对话框
                JOptionPane.showMessageDialog(null, "保存成功！");
            }
        });
     
        frame.add(jp);
        frame.setBounds(300,200,400,100);
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}
