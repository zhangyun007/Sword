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
		
		JLabel label = new JLabel("��������Ҫ��ѯ�����Ļ��߶��ĵ��ʣ�");
        JTextField txtfield1=new JTextField(); 
        txtfield1.setText("Input Chinese or Russian");    
		JButton button = new JButton("��ѯ");

		jp.add(label);
        jp.add(txtfield1);
		jp.add(button);
		
		// Ϊ��ť�󶨼�����
        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // �Ի���
                JOptionPane.showMessageDialog(null, "����ɹ���");
            }
        });
     
        frame.add(jp);
        frame.setBounds(300,200,400,100);
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}
