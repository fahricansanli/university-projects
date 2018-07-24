package chess;

import java.awt.Color;
import java.awt.Graphics;

public class Rook extends Piece{
	
	public Rook (boolean isBlack)
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
		g.fillRect(positionX+(int)(squareWidth*3.8/6.0), 
				positionY, 
				squareWidth/8, squareWidth/6);
		g.fillRect(positionX+(int)(squareWidth*2.65/6.0), 
				positionY, 
				squareWidth/8, squareWidth/6);
		g.fillRect(positionX+(int)(squareWidth*1.5/6.0), 
				positionY, 
				squareWidth/8, squareWidth/6);
		g.fillRect(positionX+(int)(squareWidth*1.5/6.0), 
				positionY+squareWidth/8, 
				squareWidth/2, squareWidth/5);
		g.fillRect(positionX+(int)(squareWidth*3.8/10.0), 
				positionY+squareWidth/4, 
				squareWidth/4, squareWidth/2);
		g.fillRect(positionX+(int)(squareWidth*1.0/4.0), 
				positionY+(int)(squareWidth*3.0/5.0), 
				squareWidth/2, squareWidth/5);
		
	}

	@Override
	public boolean canMove(int x, int y,int fromX,int fromY,int toX,int toY,Piece pieces[][]) {
		// TODO Auto-generated method stub
		if(x==0){
			if(toY>fromY){
				for(int i=fromY+1;i<=toY;i++){
					if(pieces[fromX][i]!=null){
						return false;
					}
				}
			}
			else if(toY<fromY){
				for(int i=toY;i<fromY;i++){
					if(pieces[fromX][i]!=null){
						return false;
					}
				}
				
			}
		}
		if(y==0){
			if(toX>fromX){
				for(int i=fromX+1;i<=toX;i++){
					if(pieces[i][fromY]!=null){
						return false;
					}
				}
			}
			else if(toX<fromX){
				for(int i=toX;i<fromX;i++){
					if(pieces[i][fromY]!=null){
						return false;
					}
				}
				
			}
		}
		if(x==0||y==0){
			return true;
		}
		return false;
		
	}

	@Override
	public boolean canCapture(int x, int y,int fromX,int fromY,int toX,int toY,Piece pieces[][]) {
		// TODO Auto-generated method stub
		if(x==0){
			if(toY>fromY){
				for(int i=fromY+1;i<toY;i++){
					if(pieces[fromX][i]!=null){
						return false;
					}
				}
			}
			else if(toY<fromY){
				for(int i=toY+1;i<fromY;i++){
					if(pieces[fromX][i]!=null){
						return false;
					}
				}
				
			}
		}
		if(y==0){
			if(toX>fromX){
				for(int i=fromX+1;i<toX;i++){
					if(pieces[i][fromY]!=null){
						return false;
					}
				}
			}
			else if(toX<fromX){
				for(int i=toX+1;i<fromX;i++){
					if(pieces[i][fromY]!=null){
						return false;
					}
				}
				
			}
		}
		if(x==0||y==0){
			return true;
		}
		return false;
	}

}
