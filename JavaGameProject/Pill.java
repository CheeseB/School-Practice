import java.awt.*;

import javax.swing.ImageIcon;

public class Pill{
	public static final int BIG = 1;
	public static final int SMALL = 2;
	public static final int NOTHING = 3;
	
	int x, y,width,height,type;
	ImageIcon pig; //������ �̹��� ��������
	
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
			p.setWidth(p.getWidth()+30); //������ ����1 ȹ�� �� Ŀ���� ���� ����(�ִ� =ó�� ����+2ȸ)
		}else if(getType() == SMALL){
			p.setWidth(p.getWidth()-30); //������ ����2 ȹ�� �� �۾����� ���� ����(�ּ�=ó�� ����+1ȸ)
		}
	}
	public void draw(Graphics g){
		if(type == NOTHING){
			return;
		}else if(type == BIG){
			pig = new ImageIcon("./pig1.png"); //������ ����1 �ҷ�����
			g.drawImage(pig.getImage(), x, y, null); //������ �̹���1 ����
		}else if(type == SMALL){
			pig = new ImageIcon("./pig2.png"); //������ ����2 �ҷ�����
			g.drawImage(pig.getImage(), x, y, null); //������ �̹���2 ����
		}
	}
}