import java.awt.*;

import javax.swing.ImageIcon;

public class Paddle{
	private int x, y, width, height;
	private int maxWidth;
	private int minWidth;
	ImageIcon slingshot; //패들 이미지 변수생성
	
	public Paddle(int X, int Y, int Width, int Height){
		x = X;
		y = Y;
		width = Width;
		height = Height;
		maxWidth = width*2;
		minWidth = width/2;
		slingshot = new ImageIcon("./slingshot.png"); //패들 이미지 불러오기
	}
	public void setX(int X){
		x = X;
	}
	
	public int getY(){
		return y;
	}
	
	public int getWidth(){
		return width;
	}
	
	public void setWidth(int Width){
		if(Width > maxWidth || Width < minWidth){
			return;
		}else{
			width = Width;
		}
	}
	
	public boolean hitLeft(int X, int Y){
		if((X >= x) && (X <= x+(width/2)) && ((y == Y)||(y == Y - 1))){
			return true;
		}
		return false;
	}
	public boolean hitRight(int X, int Y){
		if(((X >= x+(width/2)) && (X <= x+width)) && ((y == Y)||(y == Y - 1))){
			return true;
		}
		return false;
	}
	
	public boolean absorbPill(Pill p){
		if((p.getX() < x + width) && (p.getX()+ p.getWidth() > x) && (y == p.getY()+20
				)){
			p.absorbed(this);
			return true;
		}
		return false;
	}
	
	public void draw(Graphics g){
		g.drawImage(slingshot.getImage(), x, y, width, height, null);
	}
}