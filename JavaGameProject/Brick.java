import java.awt.*;
import java.awt.image.ImageObserver;
import javax.swing.*;

public class Brick{
	private int x, y, width, height, numHits, maxHits;
	private boolean visible;
	public Pill pill;
	ImageIcon brick; // 벽돌 이미지 변수생성

	public Brick(int X, int Y, int Width, int Height, int pillType, boolean Metal){
		x = X;
		y = Y;
		this.width = Width;
		this.height = Height;

		pill = new Pill(x+(width/4),y+(height/4),width/2,height/2,pillType);
		if(Metal){
			maxHits = 2;
			brick = new ImageIcon("./wood2.jpg"); //벽돌 이미지(약한거) 불러오기
		}else{
			maxHits = 1;
			brick = new ImageIcon("./wood1.jpg"); //벽돌 이미지(강한거) 불러오기
		}
		
		numHits = 0;
		visible = true;
	}
	public void setX(int X){
		x = X;
	}
	
	public int getX() {
		return x;
	}
	
	public int getWidth() {
		return width;
	}

	public void addHits(){
		numHits++;
		brick = new ImageIcon("./wood1.jpg");
		if(numHits == maxHits){
			visible = false;
		}
	}
	public boolean hitBottom(int X, int Y){
		if((X>=x) && (X <= x+width) && ((y+height == Y)||(y+height == Y + 1)) && visible == true){
			addHits();
			return true;
		}
		return false;
	}
	
	public void setVisible(boolean b){
		visible = b;
	}
	
	public boolean hitTop(int X, int Y){
		if((X>=x)&&(X <= x+width) && ((y == Y)||(y == Y - 1)) && visible == true){
			addHits();
			return true;
		}
		return false;
	}
	
	public boolean hitLeft(int X, int Y){
		if((Y>=y) && (Y <= y+height) && ((x == X)||(x == X - 1)) && visible == true){
			addHits();
			return true;
		}
		return false;
	}
	
	public boolean hitRight(int X, int Y){
		if((Y>=y) && (Y <= y+height) && ((x+width == X)||(x+width == X - 1)) && visible == true){
			addHits();
			return true;
		}
		return false;
	}
	
	public boolean destroyed(){
		return !visible;
	}
	
	public void draw(Graphics g){
		if(visible){
			g.drawImage(brick.getImage(), x, y, width, height, null); //벽돌 이미지 변경
		}
	}
	
}