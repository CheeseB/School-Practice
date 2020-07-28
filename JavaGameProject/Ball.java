import javax.swing.*;
import java.awt.*;

public class Ball{
	private int xCoord, yCoord,radius, width, height;
	private int xDir = 1, yDir = 2 ;
	ImageIcon bird1; //�� �̹��� ���� ����
	ImageIcon bird2;
	
	public Ball(int x, int y , int r, int xD, int yD){
		xCoord = x;
		yCoord = y;
		setRadius(r);
		bird1 = new ImageIcon("./angrybird1.png");
		bird2 = new ImageIcon("./angrybird2.png");
	}
	public int getX(){
		return xCoord;
	}
	public int getY(){
		return yCoord;
	}
	public void setX(int x){
		xCoord = x;
	}//setX�޼ҵ� ���� �ۼ�
	
	public void setY(int y){
		yCoord = y;
	}
	public int getRadius(){
		return radius;
	}

	public void setXDir(int x){
		xDir = x;
	} 
	public void setYDir(int y){
		yDir = y;
	}
	
	public void setRadius(int r){
		radius = r;
	}
	public void move(){
		xCoord = xCoord + xDir;
		yCoord  = yCoord + yDir;
	}
	public void draw(Graphics g){
		if(xDir>=0)
		g.drawImage(bird1.getImage(), xCoord - radius, yCoord - radius, radius * 2, radius * 2, null); //���� ���� �����ϰ� �ޱ׸����� �̹����� ����
		else
		g.drawImage(bird2.getImage(), xCoord - radius, yCoord - radius, radius * 2, radius * 2, null);
	}

}

