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
	Brick[][] brick = new Brick[9][5]; //벽돌 수 변경
	int balls = 5, bricksLeft = 45;
	Thread myThread;
	int xSpeed;
	ArrayList<Pill> pills = new ArrayList<Pill>();
	int waitTime;
	int score; //점수 변수 생성
	
	/*이미지 변수 생성*/
	ImageIcon background;
	ImageIcon feverback;
	ImageIcon win;
	ImageIcon loose;
	ImageIcon fever;
	
	public BreakoutPanel(int width, int height){
		super.setSize(width, height);
		
		createBricks();
		
		/*이미지 객체 생성*/
		background = new ImageIcon("./background.jpg");
		feverback = new ImageIcon("./feverback.jpg");
		win = new ImageIcon("./win.png");
		loose = new ImageIcon("./loose.png");
		fever = new ImageIcon("./fever.png");
		
		p = new Paddle(width/2,height-(height/10),width/9,height/15);
		addMouseMotionListener(new PanelMotionListener());
		b = new Ball(getWidth()/2,getHeight()/2,getWidth()/60,1,1);
		
		
		waitTime = Integer.parseInt(JOptionPane.showInputDialog(null,
			"속도를 어떻게 하겠습니까? (숫자가 클수록 느려집니다.)",
			"환경 설정",
			JOptionPane.QUESTION_MESSAGE));
  			
		myThread = new Thread(this);
		myThread.start();
		myThread.suspend();
		addMouseListener(new PanelListener());
		playSound("main.au"); //배경음악 재생

	}
	
	public void createBricks(){
		int widthDistance = getWidth()/9-5; //벽돌 가로간격 변경
		int heightDistance = getHeight()/15; //벽돌 세로간격 변경
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
					getWidth()/10+5,getHeight()/17,random,metal); //벽돌 크기 변경
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
			
			//속도 최대치 조절
			if (Math.abs(xSpeed) > 2){
				if(xSpeed > 2)
					xSpeed--;
				if(xSpeed < 2)
					xSpeed++;
			}
			/*공이 일직선으로 갈 때 벽돌사이로 통과하는 것 방지*/
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
				playSound("item.au"); //커지는 아이템 획득 시 소리재생, 점수 증가 
				}
				else if(tempPill.getType()== tempPill.SMALL) {
				score--; 
				playSound("item.au"); //작아지는 아이템 획득 시 소리재생, 점수감소
				}
			}else if(tempPill.getY() > getHeight())
				pills.remove(i);
		}
	}
	
	public void checkPaddle(int x1, int y1){
			if(p.hitLeft(x1,y1)){
				playSound("paddle.au"); //패들에 닿았을 시 소리재생
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
							else score++; //강한벽돌 사라지면 점수2, 약한벽돌 사라지면 점수1 증가(밑에도 동일)

							if(score>=30 && bricksLeft>=10)
								score+=3; //피버타임 시 벽돌점수+3 (밑에도 동일)
							
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
		g.drawImage(background.getImage(), 0, 0, null); //배경 이미지 불러오기
		setOpaque(false); //이미지 불투명
		if(score>=30 && bricksLeft>=10) {//피버타임 시 배경이미지 변경
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
		
		/*남은 생명 문구 변경후 위치조정, 점수 표시 */
		g.setFont(new Font("HY바다L",Font.PLAIN, 30));
		g.setColor(Color.black);
		g.drawString("남은 횟수: ♥ * " + Integer.toString(balls), getWidth() - 270, getHeight() - 500);
		g.drawString("점수: "+score, getWidth() - 195, getHeight() - 540);
		
		for(Pill p: pills){
			p.draw(g);
		}
		
		/*이겼을 때, 졌을 때 화면 변경*/
		if(balls == 0 && bricksLeft!=0) //조건을 하나 더 추가함으로서 이겼을때에도 진 문구가 나오는 문제 해결
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
				b.setX(getWidth()/2); //다시시작할 때 x좌표 초기화
				b.setY(getHeight()/2);
				p.setWidth(getWidth()/7); // 다시 시작할 때 패들 길이 초기화
				bricksLeft = 45;
				score=0; //다시 시작할 때 점수초기화
				repaint();
				start();
			}
		}
	}
}