package chess;

import java.awt.Color;
import java.awt.Graphics;

public class Knight extends Piece {
	
	public Knight(boolean isBlack)
	{
		super(isBlack);
	}
	
	@Override
	public void drawYourself(Graphics g, int positionX, int positionY, int squareWidth) {
		// TODO Auto-generated method stub
		
		
		if(isBlack)
		{
			g.setColor(Color.black);
		}
		else
		{
			g.setColor(Color.pink);
		}
		g.fillRect(positionX+(int)(squareWidth*2.2/6.0), 
				positionY+(int)(squareWidth*0.5/5.0), 
				squareWidth/2-5, squareWidth/8);
		g.fillOval(positionX+(int)(squareWidth*1.7/6.0), 
				positionY+squareWidth/30, 
				squareWidth/2-8, squareWidth/3);
		g.fillOval(positionX+(int)(squareWidth*1.7/6.0), 
				positionY+squareWidth/5, 
				squareWidth/3+10, squareWidth/2-3);
		g.fillRect(positionX+(int)(squareWidth*1.0/4.0), 
				positionY+(int)(squareWidth*3.0/5.0), 
				squareWidth/2, squareWidth/5);
		
		g.fillRect(positionX+(int)(squareWidth*1.19/4.0), 
				positionY+(int)(squareWidth*1.0/5.0), 
				squareWidth/10, squareWidth/2+5);
		
	}

	@Override
	public boolean canMove(int x, int y,int fromX,int fromY,int toX,int toY,Piece pieces[][]) {
		// TODO Auto-generated method stub
		if(Math.pow(x,2)+Math.pow(y,2)==5){
			return true;
		}
		return false;
		
	}

	@Override
	public boolean canCapture(int x, int y,int fromX,int fromY,int toX,int toY,Piece pieces[][]) {
		// TODO Auto-generated method stub
		if(Math.pow(x,2)+Math.pow(y,2)==5){
			return true;
		}
		return false;
	}

}

