import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import sun.audio.*;

public class GameFile{
	public static void main(String[] args){
		JFrame frame = new JFrame("�ޱ׸� ��������");
		frame.setSize(1000,1000); //ó�� ���� âũ�� ����
		
		/*�޴��� �����*/
		JMenuBar menu = new JMenuBar();
		
		JButton help = new JButton("����");
		frame.setJMenuBar(menu);
		
		menu.add(help);

		help.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				Object obj = arg0.getSource();
				if((JButton) obj == help) {
					Dimension dim = new Dimension(700,300);
					
					final Frame fs = new Frame("�� ���� ��");
					fs.setLocation(250, 300);
					fs.setPreferredSize(dim);
					fs.pack();
					fs.setVisible(true);
					
					JLabel label = new JLabel("<html>1. ���콺�� ������ �¿�� �̵��ϸ� �ޱ׸� ���带 ���� ��� ������ �����ϴ� �����Դϴ�."+
							"<br>"+ " <br>2. ���� �������� ������ ������ ���̰� �������, ������ 1 �����ϸ�<br>���ڵ��� �������� ������ ������ ���̰� �ִ� 2ȸ ª������, ������ 1 �����մϴ�."
							+"<br>"+"<br>3. ���ѻ� ������ �ι��� �ε����� ������� ������ 2 �����ϸ�<br>���ѻ� ������ �ѹ��� �ε����� ������� ������ 1 �����մϴ�."
							+"<br>"+"<br>4. ������ �ִ� 5ȸ �Դϴ�."+"<br>"+"<br>5. 30���� ������ ��õ��� �ǹ�Ÿ���� ����Ǹ�, �ǹ�Ÿ�� �� ���� ���������� 3���� �� �߰��˴ϴ�.",SwingConstants.CENTER);
					fs.add(label);
				
					fs.addWindowListener(new WindowAdapter() {
						public void windowClosing(WindowEvent e) {
							fs.setVisible(false);
							fs.dispose();
							
						}
					});
				}
				
			}
		});
					
		/*������ Ȯ�� �ٲ�*/
		frame.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
		frame.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				if(JOptionPane.showConfirmDialog(frame, "���� �����ðڽ��ϱ�?") == JOptionPane.OK_OPTION) {
					frame.setVisible(false);
					frame.dispose();
				}
			}
		});
		
		BreakoutPanel bPanel = new BreakoutPanel(980,900);
		Container pane = frame.getContentPane();
		pane.add(bPanel);
		frame.setVisible(true);
		
		
	}
}			
