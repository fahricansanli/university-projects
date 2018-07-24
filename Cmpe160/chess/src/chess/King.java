package chess;

import java.awt.Color;
import java.awt.Graphics;

public class King extends Piece{
	
	public King(boolean isBlack)
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
		g.fillRect(positionX+(int)(squareWidth*2.65/6.0), 
				positionY, 
				squareWidth/8, squareWidth/6);
		g.fillRect(positionX+(int)(squareWidth*2.05/6.0), 
				positionY+squareWidth/10, 
				squareWidth/3, squareWidth/6);
		g.fillRect(positionX+(int)(squareWidth*4.0/10.0), 
				positionY+squareWidth/4, 
				squareWidth/5, squareWidth/2);
		g.fillRect(positionX+(int)(squareWidth*1.0/4.0), 
				positionY+(int)(squareWidth*3.0/5.0), 
				squareWidth/2, squareWidth/6);
		
	}

	@Override
	public boolean canMove(int x, int y,int fromX,int fromY,int toX,int toY,Piece pieces[][]) {
		// TODO Auto-generated method stub
		if(Math.pow(x,2)+Math.pow(y,2)==1||Math.pow(x,2)+Math.pow(y,2)==2){
			return true;
		}
		return false;
		
	}

	@Override
	public boolean canCapture(int x, int y,int fromX,int fromY,int toX,int toY,Piece pieces[][]) {
		// TODO Auto-generated method stub
		if(Math.pow(x,2)+Math.pow(y,2)==1||Math.pow(x,2)+Math.pow(y,2)==2){
			return true;
		}
		return false;
	}

}
