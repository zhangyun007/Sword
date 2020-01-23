import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.*;
import java.awt.*;

import java.io.*; 



public class FlowChart
{
    public static void main(String[] agrs)
    {
        JFrame frame = new JFrame("Chinese to Russian");  
		frame.setLayout(null);//��������Ϊnull
		
        MyPanel jp = new MyPanel(); 
		jp.setBounds(90, 60, 1200, 1000);		//λ�úͳ���
		jp.setBorder(BorderFactory.createLineBorder(Color.red, 3));	//�߱߿�
       
		JLabel label = new JLabel("��������Ҫ��ѯ�����Ļ��߶��ĵ��ʣ�");
		JButton button = new JButton("��ѯ");
		jp.add(label);
		jp.add(button);
		
		// Ϊ��ť�󶨼�����
        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // �Ի���
                JOptionPane.showMessageDialog(null, "����ɹ���");
            }
        });
		
		MyPanel jp_a = new MyPanel(); 
		jp_a.setBounds(120, 120, 240, 240);
		jp_a.setBorder(BorderFactory.createLineBorder(Color.blue, 3));	//�߱߿�


		JTextField txtfield1 = new JTextField(); 
        txtfield1.setText("Input Chinese or Russian");    
		
		jp_a.add(txtfield1);
     
        frame.add(jp);
		frame.add(jp_a);
		
        frame.setBounds(300,200,800,600);
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
	
	/**
     * �������
     */
    public static class MyPanel extends JPanel {
        /**
         * ������������: ���� JPanel ������һ�θ÷�����������,
         * ֮��������ݸı���Ҫ���»���, �ɵ��� updateUI() ��������
         * ϵͳ�ٴε��ø÷������Ƹ��� JPanel �����ݡ�
         */
        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);

            // ���µ��� Graphics �Ļ��Ʒ�������ʱ���Զ������ɵ�����

            /* ���д�����ע�Ͳ鿴������Ч�� */

            // 1. �߶� / ����
            // 
			drawLine(g);

            // 2. ���� / �����
            // drawRect(g);

            // 3. Բ�� / ����
            // drawArc(g);

            // 4. ��Բ
            drawOval(g);

            // 5. ͼƬ
            // drawImage(g);

            // 6. �ı�
            drawString(g);
        }

        /**
         * 1. �߶� / ����
         */
        private void drawLine(Graphics g) {
            

            // ���� Graphics �ĸ���, ��Ҫ�ı� Graphics �Ĳ���,
            // �������ʹ�ø���, ����Ӱ�쵽 Graphics ԭ�е�����
            Graphics2D g2d = (Graphics2D) g.create();

            // �����
            g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
            // ���û�����ɫ
            g2d.setColor(Color.RED);

            // 1. ��������߶�: ��(20, 50), ��(200, 50)
            g2d.drawLine(50, 50, 200, 50);

            // 2. ����������: ��(50, 100), ��(100, 130), ��(150, 70), ��(200, 100)
            int[] xPoints = new int[] { 50, 100, 150, 200 };
            int[] yPoints = new int[] { 100, 120, 80, 100 };
            int nPoints = 4;
            g2d.drawPolyline(xPoints, yPoints, nPoints);

            // 3. ��������߶Σ������߿�Ϊ5px��: ��(50, 150), ��(200, 150)
            BasicStroke bs1 = new BasicStroke(5);       // �ʻ������������ʿ��/�߿�Ϊ5px��
            g2d.setStroke(bs1);
            g2d.drawLine(50, 150, 200, 150);

            // 4. ��������: �����߷�Ϊ���ɶΣ� ʵ�߶� �� �հ׶� ����Ϊ��һ�Σ�, ʵ�߶� �� �հ׶� �������,
            //             ���Ƶ�ÿһ�Σ����� ʵ�߶� �� �հ׶Σ��� ���� �� dash ����ģʽ������ȡֵ������
            //             Ԫ�ؿ�ʼѭ��ȡֵ��, �������鼴��ʾÿ�γ��ȷֱ�Ϊ: 5px, 10px, 5px, 10px, ...
            float[] dash = new float[] { 5, 10 };
            BasicStroke bs2 = new BasicStroke(
                    1,                      // ���ʿ��/�߿�
                    BasicStroke.CAP_SQUARE,
                    BasicStroke.JOIN_MITER,
                    10.0f,
                    dash,                   // ����ģʽ����
                    0.0f
            );
            g2d.setStroke(bs2);
            g2d.drawLine(50, 200, 200, 200);

            // �Լ������ĸ�������Ҫ���ٵ�
            g2d.dispose();
        }

        /**
         * 2. ���� / �����
         */
        private void drawRect(Graphics g) {
            
            Graphics2D g2d = (Graphics2D) g.create();

            g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
            g2d.setColor(Color.GRAY);

            // 1. ����һ������: ���(30, 20), ��80, ��100
            g2d.drawRect(30, 20, 80, 100);

            // 2. ���һ������
            g2d.fillRect(140, 20, 80, 100);

            // 3. ����һ��Բ�Ǿ���: ���(30, 150), ��80, ��100, Բ�ǿ�30, Բ�Ǹ�30
            g2d.drawRoundRect(30, 150, 80, 100, 30, 30);

            // 4. ����һ�������(��β����): ��(140, 150), ��(180, 250), ��(220, 200)
            int[] xPoints = new int[] { 140, 180, 220};
            int[] yPoints = new int[] { 150,  250, 200};
            int nPoints = 3;
            g2d.drawPolygon(xPoints, yPoints, nPoints);

            g2d.dispose();
        }

        /**
         * 3. Բ�� / ����
         */
        private void drawArc(Graphics g) {
            
            Graphics2D g2d = (Graphics2D) g.create();

            g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
            g2d.setColor(Color.RED);

            // 1. ����һ��Բ��: ��Բ�����о��� ���Ͻ�����Ϊ(0, 0), ��100, ��100,
            //                ���Ŀ�ʼ�Ƕ�Ϊ0��, ��Ҫ���ƵĽǶ���Ϊ-90��,
            //                ��Բ�ұ�ˮƽ��Ϊ0��, ��ʱ��Ϊ���Ƕ�, ˳ʱ��Ϊ���Ƕ�
            g2d.drawArc(0, 0, 100, 100, 0, -90);

            // 2. ����һ��Բ: Բ�����о��� ���Ͻ�����Ϊ(120, 20), ���Ϊ100
            g2d.drawArc(120, 20, 100, 100, 0, 360);

            g2d.setColor(Color.GRAY);

            // 3. ���һ������
            g2d.fillArc(80, 150, 100, 100, 90, 270);

            g2d.dispose();
        }

        /**
         * 4. ��Բ (ʵ����ͨ������360�ȵ�Բ��/����Ҳ�ܴﵽ����Բ/��Բ��Ч��)
         */
        private void drawOval(Graphics g) {
            
            Graphics2D g2d = (Graphics2D) g.create();

            g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
            g2d.setColor(Color.RED);

            // 1. ����һ��Բ: Բ�����о��� ���Ͻ�����Ϊ(0, 0), ���Ϊ100
            g2d.drawOval(0, 0, 200, 100);

            g2d.setColor(Color.GRAY);

            // 2. ���һ����Բ
            g2d.fillOval(120, 100, 100, 150);

            g2d.dispose();
        }

        /**
         * 5. ͼƬ
         */
        private void drawImage(Graphics g) {
            
            Graphics2D g2d = (Graphics2D) g.create();

            // �ӱ��ض�ȡһ��ͼƬ
            String filepath = "demo.jpg";
            Image image = Toolkit.getDefaultToolkit().getImage(filepath);

            // ����ͼƬ�������ߴ��Ĳ���ͼƬԭ���Ŀ��, ��ͼƬ�����ʵ����Ż��ƣ�
            g2d.drawImage(image, 50, 50, image.getWidth(this), image.getHeight(this), this);

            g2d.dispose();
        }

        /**
         * 6. �ı�
         */
        private void drawString(Graphics g) {
            
            Graphics2D g2d = (Graphics2D) g.create();

            g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

            // ����������ʽ, null ��ʾʹ��Ĭ������, Font.PLAIN Ϊ��ͨ��ʽ, ��СΪ 25px
            g2d.setFont(new Font(null, Font.PLAIN, 25));

            // �����ı�, �����������ָ�����ı����ƺ�� ���½� ��λ��
            // �״λ�����Ҫ��ʼ������, ������Ҫ�Ϻ�ʱ
            g2d.drawString("Hello World!", 20, 60);
            g2d.drawString("���, ����!", 20, 120);

            g2d.dispose();
        }

    }
}
