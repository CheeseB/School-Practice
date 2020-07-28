import java.awt.*;

import javax.swing.ImageIcon;

public class Pill{
	public static final int BIG = 1;
	public static final int SMALL = 2;
	public static final int NOTHING = 3;
	
	int x, y,width,height,type;
	ImageIcon pig; //아이템 이미지 변수생성
	
	public Pill(int X, int Y,int Width, int Height, int Type){
		this.x = X;
		this.y = Y;
		this.width = Width;
		this.height = Height;
		this.type = Type;
	}
	
	public void drop(){
		y += 1;
	}
	public int getY(){
		return y;
	}
	public int getX(){
		return x;
	}
	public int getWidth(){
		return width;
	}
	public int getType(){
		return type;
	}
	
	public void absorbed(Paddle p){
		if(getType() == BIG){
			p.setWidth(p.getWidth()+30); //아이템 돼지1 획득 시 커지는 정도 변경(최대 =처음 길이+2회)
		}else if(getType() == SMALL){
			p.setWidth(p.getWidth()-30); //아이템 돼지2 획득 시 작아지는 정도 변경(최소=처음 길이+1회)
		}
	}
	public void draw(Graphics g){
		if(type == NOTHING){
			return;
		}else if(type == BIG){
			pig = new ImageIcon("./pig1.png"); //아이템 돼지1 불러오기
			g.drawImage(pig.getImage(), x, y, null); //아이템 이미지1 변경
		}else if(type == SMALL){
			pig = new ImageIcon("./pig2.png"); //아이템 돼지2 불러오기
			g.drawImage(pig.getImage(), x, y, null); //아이템 이미지2 변경
		}
	}
}