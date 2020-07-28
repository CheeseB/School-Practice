import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import java.lang.Thread;
import sun.audio.*;
import java.io.*;
import java.util.ArrayList;

public class BreakoutPanel extends JPanel implements Runnable{
	
	Paddle p;
	Ball b;
	Brick[][] brick = new Brick[9][5]; //���� �� ����
	int balls = 5, bricksLeft = 45;
	Thread myThread;
	int xSpeed;
	ArrayList<Pill> pills = new ArrayList<Pill>();
	int waitTime;
	int score; //���� ���� ����
	
	/*�̹��� ���� ����*/
	ImageIcon background;
	ImageIcon feverback;
	ImageIcon win;
	ImageIcon loose;
	ImageIcon fever;
	
	public BreakoutPanel(int width, int height){
		super.setSize(width, height);
		
		createBricks();
		
		/*�̹��� ��ü ����*/
		background = new ImageIcon("./background.jpg");
		feverback = new ImageIcon("./feverback.jpg");
		win = new ImageIcon("./win.png");
		loose = new ImageIcon("./loose.png");
		fever = new ImageIcon("./fever.png");
		
		p = new Paddle(width/2,height-(height/10),width/9,height/15);
		addMouseMotionListener(new PanelMotionListener());
		b = new Ball(getWidth()/2,getHeight()/2,getWidth()/60,1,1);
		
		
		waitTime = Integer.parseInt(JOptionPane.showInputDialog(null,
			"�ӵ��� ��� �ϰڽ��ϱ�? (���ڰ� Ŭ���� �������ϴ�.)",
			"ȯ�� ����",
			JOptionPane.QUESTION_MESSAGE));
  			
		myThread = new Thread(this);
		myThread.start();
		myThread.suspend();
		addMouseListener(new PanelListener());
		playSound("main.au"); //������� ���

	}
	
	public void createBricks(){
		int widthDistance = getWidth()/9-5; //���� ���ΰ��� ����
		int heightDistance = getHeight()/15; //���� ���ΰ��� ����
		boolean metal = true;
		for(int X = 0; X < 9; X++){
			for(int Y = 0; Y < 5; Y++){
				int random = (int)(Math.random()*13) + 1;
				if(random > 5 && random <= 13)
					random = 3;
				if(random == 4 || random == 5)
					random = 2;
				metal = (Y < 2);
				brick[X][Y] = new Brick(X*(widthDistance+5),(heightDistance/2)+(Y*heightDistance),
					getWidth()/10+5,getHeight()/17,random,metal); //���� ũ�� ����
			}
		}
	}
	
	public void start(){
		myThread.resume();
	}

  	public void stop(){
		myThread.suspend();
	}

  	public void run(){
  		xSpeed = 1;
		while(true){
			int x1 = b.getX();
			int y1 = b.getY();
			
			//�ӵ� �ִ�ġ ����
			if (Math.abs(xSpeed) > 2){
				if(xSpeed > 2)
					xSpeed--;
				if(xSpeed < 2)
					xSpeed++;
			}
			/*���� ���������� �� �� �������̷� ����ϴ� �� ����*/
			if(Math.abs(xSpeed)==0) {
				for(int i = 0; i<8 ; i++)
					for(int j = 0 ; j<5 ; j++){
						if((x1>(brick[i][j].getX()+brick[i][j].getWidth()))&&(x1<brick[i+1][j].getX()))
						this.checkBricks(x1+6, y1);
					}
			}

			checkPaddle(x1,y1);
			
			checkWall(x1,y1);
				
			checkBricks(x1,y1);
				
			checkLives();
		
			checkIfOut(y1);
			
			b.move();
			
			dropPills();
			
			checkPillList();
			
			repaint();
			try {myThread.sleep(waitTime);}
			catch (InterruptedException e ) {}
		}
	}
	


	public void placePill(Pill p){
		pills.add(p);
	}
	
	public void dropPills(){
		for(int i = 0; i < pills.size(); i++){
			Pill tempPill = pills.get(i);
			tempPill.drop();
			pills.set(i,tempPill);
		}
	}
	
	public void checkLives(){
		if(bricksLeft == 0){
			repaint();
			stop();
		}
	}
	
	public void checkPillList(){
		for(int i = 0; i < pills.size(); i++){
			Pill tempPill = pills.get(i);
			if(p.absorbPill(tempPill)){
				pills.remove(i);
				
				if(tempPill.getType()== tempPill.BIG) {
				score++;
				playSound("item.au"); //Ŀ���� ������ ȹ�� �� �Ҹ����, ���� ���� 
				}
				else if(tempPill.getType()== tempPill.SMALL) {
				score--; 
				playSound("item.au"); //�۾����� ������ ȹ�� �� �Ҹ����, ��������
				}
			}else if(tempPill.getY() > getHeight())
				pills.remove(i);
		}
	}
	
	public void checkPaddle(int x1, int y1){
			if(p.hitLeft(x1,y1)){
				playSound("paddle.au"); //�е鿡 ����� �� �Ҹ����
				b.setYDir(-2);
				xSpeed += -1;
				b.setXDir(xSpeed);
			}else if(p.hitRight(x1,y1)){
				playSound("paddle.au");
				b.setYDir(-2);
				xSpeed += 1;
				b.setXDir(xSpeed);
			}
	}
	
	public void checkWall(int x1, int y1){
			if(x1+getWidth()/40 >= getWidth())
				xSpeed = -Math.abs(xSpeed);
				b.setXDir(xSpeed);
			if(x1-getWidth()/40 <= 0)
				xSpeed = Math.abs(xSpeed);
				b.setXDir(xSpeed);
			if(y1-getWidth()/40 <= 0)
				b.setYDir(2);
	}
	
    public void checkBricks(int x1, int y1){
    		for(int X = 0; X < 9; X++)
				for(int Y = 0; Y < 5; Y++){
					if(brick[X][Y].hitBottom(x1,y1)){
						playSound("brick.au");
						b.setYDir(2);
						if(brick[X][Y].destroyed()){
							bricksLeft--;
							if(Y==0||Y==1) score+=2;
							else score++; //���Ѻ��� ������� ����2, ���Ѻ��� ������� ����1 ����(�ؿ��� ����)

							if(score>=30 && bricksLeft>=10)
								score+=3; //�ǹ�Ÿ�� �� ��������+3 (�ؿ��� ����)
							
							placePill(brick[X][Y].pill);
						}
					}
					if(brick[X][Y].hitLeft(x1,y1)){
						playSound("brick.au");
						xSpeed = -xSpeed;
						b.setXDir(xSpeed);
						if(brick[X][Y].destroyed()){
							bricksLeft--;
							if(Y==0||Y==1) score+=2;
							else score++;
							
							if(score>=30 && bricksLeft>=10)
								score+=3;
							
							placePill(brick[X][Y].pill);
						}
					}
					if(brick[X][Y].hitRight(x1,y1)){
						playSound("brick.au");
						xSpeed = -xSpeed;
						b.setXDir(xSpeed);
						if(brick[X][Y].destroyed()){
							bricksLeft--;
							if(Y==0||Y==1) score+=2;
							else score++;
							
							if(score>=30 && bricksLeft>=10)
								score+=3;
							
							placePill(brick[X][Y].pill);
						}
					}
					if(brick[X][Y].hitTop(x1,y1)){
						playSound("brick.au");
						b.setYDir(-2);
						if(brick[X][Y].destroyed()){
							bricksLeft--;
							if(Y==0||Y==1) score+=2;
							else score++;
							
							if(score>=30 && bricksLeft>=10)
								score+=3;
							
							placePill(brick[X][Y].pill);
						}
					}
				}
    }
    
    public void checkIfOut(int y1){
    	if(y1 > p.getY() + 10){
			balls --;
			b.setY(getHeight()/2); 
			playSound("drop.au");
			repaint();
			stop();
		}
    }

    private void playSound(String file){
    	
    	try{
    		InputStream in = new FileInputStream(file);
    		AudioStream as = new AudioStream(in);
			AudioPlayer.player.start(as);
		}catch(FileNotFoundException exc){
			System.out.println(exc);
		}catch(IOException exc){
			System.out.println(exc);
		}
    }
    
	public void paintComponent(Graphics g){
		g.drawImage(background.getImage(), 0, 0, null); //��� �̹��� �ҷ�����
		setOpaque(false); //�̹��� ������
		if(score>=30 && bricksLeft>=10) {//�ǹ�Ÿ�� �� ����̹��� ����
			g.drawImage(feverback.getImage(), 0, 0, getWidth(), getHeight(), null);
			g.drawImage(fever.getImage(), 230, 600, null);
		}
		
		super.paintComponent(g);
		p.draw(g);
		b.draw(g);
		for(int X = 0; X < 9; X++)
			for(int Y = 0; Y < 5; Y++)
				brick[X][Y].draw(g);
		g.setColor(Color.BLACK);
		
		/*���� ���� ���� ������ ��ġ����, ���� ǥ�� */
		g.setFont(new Font("HY�ٴ�L",Font.PLAIN, 30));
		g.setColor(Color.black);
		g.drawString("���� Ƚ��: �� * " + Integer.toString(balls), getWidth() - 270, getHeight() - 500);
		g.drawString("����: "+score, getWidth() - 195, getHeight() - 540);
		
		for(Pill p: pills){
			p.draw(g);
		}
		
		/*�̰��� ��, ���� �� ȭ�� ����*/
		if(balls == 0 && bricksLeft!=0) //������ �ϳ� �� �߰������μ� �̰��������� �� ������ ������ ���� �ذ�
				g.drawImage(loose.getImage(), 80, 100, null);
				
		if(bricksLeft == 0)
				g.drawImage(win.getImage(), 70, 100, null);
		
	}
	
	private class PanelMotionListener extends MouseMotionAdapter{
		public void mouseMoved(MouseEvent e){
			int newX = e.getX()-getWidth()/17;
			p.setX(newX);
			repaint();
		}
	}
	private class PanelListener extends MouseAdapter{
		public void mousePressed(MouseEvent e){
			if (balls>0){
				start();
			}else{
				balls = 5;
				createBricks();
				for(int X = 0; X < 9; X++){
					for(int Y = 0; Y < 5; Y++){
						brick[X][Y].setVisible(true);
					}
				}
				b.setX(getWidth()/2); //�ٽý����� �� x��ǥ �ʱ�ȭ
				b.setY(getHeight()/2);
				p.setWidth(getWidth()/7); // �ٽ� ������ �� �е� ���� �ʱ�ȭ
				bricksLeft = 45;
				score=0; //�ٽ� ������ �� �����ʱ�ȭ
				repaint();
				start();
			}
		}
	}
}