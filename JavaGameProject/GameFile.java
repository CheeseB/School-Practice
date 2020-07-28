import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.*;
import sun.audio.*;

public class GameFile{
	public static void main(String[] args){
		JFrame frame = new JFrame("앵그리 벽돌깨기");
		frame.setSize(1000,1000); //처음 시작 창크기 변경
		
		/*메뉴바 만들기*/
		JMenuBar menu = new JMenuBar();
		
		JButton help = new JButton("도움말");
		frame.setJMenuBar(menu);
		
		menu.add(help);

		help.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent arg0) {
				Object obj = arg0.getSource();
				if((JButton) obj == help) {
					Dimension dim = new Dimension(700,300);
					
					final Frame fs = new Frame("★ 도움말 ★");
					fs.setLocation(250, 300);
					fs.setPreferredSize(dim);
					fs.pack();
					fs.setVisible(true);
					
					JLabel label = new JLabel("<html>1. 마우스로 새총을 좌우로 이동하며 앵그리 버드를 위로 띄워 벽돌을 제거하는 게임입니다."+
							"<br>"+ " <br>2. 돼지 아이템을 먹으면 새총의 길이가 길어지고, 점수가 1 증가하며<br>모자돼지 아이템을 먹으면 새총의 길이가 최대 2회 짧아지고, 점수가 1 감소합니다."
							+"<br>"+"<br>3. 진한색 벽돌은 두번을 부딪혀야 사라지고 점수가 2 증가하며<br>연한색 벽돌은 한번을 부딪혀야 사라지고 점수가 1 증가합니다."
							+"<br>"+"<br>4. 생명은 최대 5회 입니다."+"<br>"+"<br>5. 30점을 넘으면 잠시동안 피버타임이 진행되며, 피버타임 시 원래 벽돌점수에 3점씩 더 추가됩니다.",SwingConstants.CENTER);
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
					
		/*나가기 확인 바꿈*/
		frame.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
		frame.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				if(JOptionPane.showConfirmDialog(frame, "정말 닫으시겠습니까?") == JOptionPane.OK_OPTION) {
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
