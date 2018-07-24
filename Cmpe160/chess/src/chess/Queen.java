package chess;

import java.awt.Color;
import java.awt.Graphics;

public class Queen extends Piece {
	
	public Queen(boolean isBlack)
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
		g.fillOval(positionX+(int)(squareWidth*2.8/6.0), 
				positionY+(int)(squareWidth*0.1/25.0), 
				squareWidth/15, squareWidth/3);
		g.fillOval(positionX+(int)(squareWidth*3.6/6.0), 
				positionY+(int)(squareWidth*0.1/25.0), 
				squareWidth/15, squareWidth/3);
		g.fillOval(positionX+(int)(squareWidth*2.0/6.0), 
				positionY+(int)(squareWidth*0.1/25.0), 
				squareWidth/15, squareWidth/3);
		g.fillOval(positionX+(int)(squareWidth*2.0/6.0), 
				positionY+squareWidth/8, 
				squareWidth/3, squareWidth/3);
		g.fillOval(positionX+(int)(squareWidth*1.5/6.0), 
				positionY+(int)(squareWidth*1.5/5.0), 
				squareWidth/2, squareWidth/8);
		g.fillRect(positionX+(int)(squareWidth*4.0/10.0), 
				positionY+squareWidth/4, 
				squareWidth/5, squareWidth/2);
		g.fillRect(positionX+(int)(squareWidth*1.0/4.0), 
				positionY+(int)(squareWidth*3.0/5.0), 
				squareWidth/2, squareWidth/5);
		
	}

	@Override
	public boolean canMove(int x, int y,int fromX,int fromY,int toX,int toY,Piece pieces[][]) {
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
		if(x==0||y==0){
			return true;
		}
		else if(Math.abs(x)==Math.abs(y)){
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
		if(x==0||y==0){
			return true;
		}
		else if(Math.abs(x)==Math.abs(y)){
			return true;
		}
		return false;
	
	}

}

