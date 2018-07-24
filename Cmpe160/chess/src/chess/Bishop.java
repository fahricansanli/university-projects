package chess;

import java.awt.Color;
import java.awt.Graphics;

public class Bishop extends Piece{

	public Bishop(boolean isBlack)
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

		g.fillOval(positionX+(int)(squareWidth*2.0/6.0), 
				positionY+squareWidth/25, 
				squareWidth/3, squareWidth/3);
		g.fillOval(positionX+(int)(squareWidth*1.5/6.0), 
				positionY+(int)(squareWidth*1.5/5.0), 
				squareWidth/2, squareWidth/8);
		g.fillOval(positionX+(int)(squareWidth*2.2/6.0), 
				positionY+squareWidth/3, 
				squareWidth/4, squareWidth/3);
		g.fillRect(positionX+(int)(squareWidth*1.0/4.0), 
				positionY+(int)(squareWidth*3.0/5.0), 
				squareWidth/2, squareWidth/5);

	}

	@Override
	public boolean canMove(int x, int y,int fromX,int fromY,int toX,int toY,Piece pieces[][]) {
		// TODO Auto-generated method stub
		if(Math.abs(x)==Math.abs(y)){
			if(toX>fromX&&toY>fromY){
				int j=fromY+1;
				for(int i=fromX+1;i<toX;i++){
					if(pieces[i][j]!=null){
						return false;
					}
					j++;
				}
				
			}
			if(toX<fromX&&toY<fromY){
				int j=toY+1;
				for(int i=toX+1;i<fromX;i++){
					if(pieces[i][j]!=null){
						return false;
					}
					j++;
				}
			}
			if(toX>fromX&&toY<fromY){
				int j=fromY-1;
				for(int i=fromX+1;i<toX;i++){
					if(pieces[i][j]!=null){
						return false;
					}
					j--;
				}
			}
			if(toX<fromX&&toY>fromY){
				int j=fromY+1;
				for(int i=fromX-1;i>toX;i--){
					if(pieces[i][j]!=null){
						return false;
					}
					j++;
				}
			}
			
		}
		if(Math.abs(x)==Math.abs(y)){
			return true;

		}
		return false;

	}

	@Override
	public boolean canCapture(int x, int y,int fromX,int fromY,int toX,int toY,Piece pieces[][]) {
		// TODO Auto-generated method stub
		if(Math.abs(x)==Math.abs(y)){
			if(toX>fromX&&toY>fromY){
				int j=fromY+1;
				for(int i=fromX+1;i<toX;i++){
					if(pieces[i][j]!=null){
						return false;
					}
					j++;
				}
				
			}
			if(toX<fromX&&toY<fromY){
				int j=toY+1;
				for(int i=toX+1;i<fromX;i++){
					if(pieces[i][j]!=null){
						return false;
					}
					j++;
				}
			}
			if(toX>fromX&&toY<fromY){
				int j=fromY-1;
				for(int i=fromX+1;i<toX;i++){
					if(pieces[i][j]!=null){
						return false;
					}
					j--;
				}
			}
			if(toX<fromX&&toY>fromY){
				int j=fromY+1;
				for(int i=fromX-1;i>toX;i--){
					if(pieces[i][j]!=null){
						return false;
					}
					j++;
				}
			}
			
		}
		if(Math.abs(x)==Math.abs(y)){
			return true;

		}
		return false;

	}
}

