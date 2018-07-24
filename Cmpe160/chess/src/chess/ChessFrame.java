package chess;

import java.awt.Graphics;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.Scanner;
import java.util.Stack;
import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.Font;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

public class ChessFrame extends JFrame implements MouseListener, ActionListener{
	JPanel panel=new JPanel();

	/**
	 * width of one square on the board.
	 * Change this to have a bigger or smaller 
	 * game frame. 
	 */

	public static final int SQUARE_WIDTH = 90;

	/**
	 * margins of the board on the frame
	 */
	public static final int BOARD_MARGIN = 110;

	int selectedSquareX = -1;
	int selectedSquareY = -1;
	Piece pieces[][] = new Piece[8][8];
	int count=0;
	Stack<Piece[][]> str=new Stack<Piece[][]>();
	//Piece temp[][]=new Piece[8][8];
	public ChessFrame()
	{
		initializeChessBoard();
		setTitle("Chess Game");
		//let the screen size fit the board size
		setSize(SQUARE_WIDTH*11+BOARD_MARGIN*2, SQUARE_WIDTH*8+BOARD_MARGIN*2);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		addMouseListener(this);
		graph();
		add(panel);

	}
	public void graph(){
		panel.setLayout(null);
		JButton b=new JButton("Undo");
		JButton b1=new JButton("Save");
		b.setBounds(SQUARE_WIDTH*8+BOARD_MARGIN*2, SQUARE_WIDTH+4*BOARD_MARGIN/3, SQUARE_WIDTH, SQUARE_WIDTH/2);
		b1.setBounds(2*BOARD_MARGIN+8*SQUARE_WIDTH, BOARD_MARGIN+SQUARE_WIDTH/3, SQUARE_WIDTH, SQUARE_WIDTH/2);
		panel.add(b);
		panel.add(b1);
		JLabel labels[] =new JLabel[16];
		for(int i=0;i<8;i++){
			labels[i]=new JLabel(""+(char)((int)'A'+i));
			labels[i].setFont(new Font("Serif",Font.BOLD,SQUARE_WIDTH/3));
			if(i==0)
				labels[i].setBounds(BOARD_MARGIN+SQUARE_WIDTH/3, BOARD_MARGIN-SQUARE_WIDTH, SQUARE_WIDTH/2,SQUARE_WIDTH/2);
			if(i==1)
				labels[i].setBounds(BOARD_MARGIN+4*SQUARE_WIDTH/3, BOARD_MARGIN-SQUARE_WIDTH, SQUARE_WIDTH/2,SQUARE_WIDTH/2);
			if(i==2)
				labels[i].setBounds(BOARD_MARGIN+7*SQUARE_WIDTH/3, BOARD_MARGIN-SQUARE_WIDTH, SQUARE_WIDTH/2,SQUARE_WIDTH/2);
		    if(i==3)
		    	labels[i].setBounds(BOARD_MARGIN+10*SQUARE_WIDTH/3, BOARD_MARGIN-SQUARE_WIDTH, SQUARE_WIDTH/2,SQUARE_WIDTH/2);
			if(i==4)
				labels[i].setBounds(BOARD_MARGIN+13*SQUARE_WIDTH/3, BOARD_MARGIN-SQUARE_WIDTH, SQUARE_WIDTH/2,SQUARE_WIDTH/2);
			if(i==5)
				labels[i].setBounds(BOARD_MARGIN+16*SQUARE_WIDTH/3, BOARD_MARGIN-SQUARE_WIDTH, SQUARE_WIDTH/2,SQUARE_WIDTH/2);
			if(i==6)
				labels[i].setBounds(BOARD_MARGIN+19*SQUARE_WIDTH/3, BOARD_MARGIN-SQUARE_WIDTH, SQUARE_WIDTH/2,SQUARE_WIDTH/2);
			if(i==7)
				labels[i].setBounds(BOARD_MARGIN+22*SQUARE_WIDTH/3, BOARD_MARGIN-SQUARE_WIDTH, SQUARE_WIDTH/2,SQUARE_WIDTH/2);
				
			add(labels[i]);

			labels[8+i]=new JLabel(""+(8-i));
			labels[8+i].setFont(new Font("Serif",Font.BOLD,SQUARE_WIDTH/3));
			if(i==0)
				labels[8+i].setBounds(BOARD_MARGIN-SQUARE_WIDTH/2, BOARD_MARGIN+34*SQUARE_WIDTH/5, SQUARE_WIDTH/2, SQUARE_WIDTH/2);
			if(i==1)
				labels[8+i].setBounds(BOARD_MARGIN-SQUARE_WIDTH/2, BOARD_MARGIN+29*SQUARE_WIDTH/5, SQUARE_WIDTH/2, SQUARE_WIDTH/2);
			if(i==2)
				labels[8+i].setBounds(BOARD_MARGIN-SQUARE_WIDTH/2, BOARD_MARGIN+24*SQUARE_WIDTH/5, SQUARE_WIDTH/2, SQUARE_WIDTH/2);
		    if(i==3)
		    	labels[8+i].setBounds(BOARD_MARGIN-SQUARE_WIDTH/2, BOARD_MARGIN+19*SQUARE_WIDTH/5, SQUARE_WIDTH/2, SQUARE_WIDTH/2);
			if(i==4)
				labels[8+i].setBounds(BOARD_MARGIN-SQUARE_WIDTH/2, BOARD_MARGIN+14*SQUARE_WIDTH/5, SQUARE_WIDTH/2, SQUARE_WIDTH/2);
			if(i==5)
				labels[8+i].setBounds(BOARD_MARGIN-SQUARE_WIDTH/2, BOARD_MARGIN+9*SQUARE_WIDTH/5, SQUARE_WIDTH/2, SQUARE_WIDTH/2);
			if(i==6)
				labels[8+i].setBounds(BOARD_MARGIN-SQUARE_WIDTH/2, BOARD_MARGIN+4*SQUARE_WIDTH/5, SQUARE_WIDTH/2, SQUARE_WIDTH/2);
			if(i==7)
				labels[8+i].setBounds(BOARD_MARGIN-SQUARE_WIDTH/2, BOARD_MARGIN-SQUARE_WIDTH/5, SQUARE_WIDTH/2, SQUARE_WIDTH/2);
			add(labels[8+i]);

		}

		b.addActionListener(new ActionListener(){


			public void actionPerformed(ActionEvent e) {
				undo();
				repaint();

			}

		});
		b1.addActionListener(new ActionListener(){


			public void actionPerformed(ActionEvent e) {
				save("game.txt");

			}

		});

	}




	public void initializeChessBoard()
	{

		for(int i = 0; i<8; i++)
		{
			for(int j = 0; j<8; j++)
			{
				if(j == 1)
				{
					//add a black pawn here
					pieces[i][j] = new Pawn(true);
				}
				else if(j == 6)
				{
					//add a white pawn here
					pieces[i][j] = new Pawn(false);
				}
				else if((i==0||i==7)&&j==0){
					pieces[i][j]=new Rook(true);
				}
				else if((i==0||i==7)&&j==7){
					pieces[i][j]=new Rook(false);
				}
				else if((i==1||i==6)&&j==0){
					pieces[i][j]=new Knight(true);
				}
				else if((i==1||i==6)&&j==7){
					pieces[i][j]=new Knight(false);
				}
				else if((i==2||i==5)&&j==0){
					pieces[i][j]=new Bishop(true);
				}
				else if((i==2||i==5)&&j==7){
					pieces[i][j]=new Bishop(false);
				}
				else if(i==3&&j==0){
					pieces[i][j]=new Queen(true);
				}
				else if(i==3&&j==7){
					pieces[i][j]= new Queen(false);
				}
				else if(i==4&&j==0){
					pieces[i][j]=new King(true);
				}
				else if(i==4&&j==7){
					pieces[i][j]=new King(false);
				}
				else
				{

					pieces[i][j] = null;
				}
			}
		}
	}

	@Override
	public void paint(Graphics g) {
		// TODO Auto-generated method stub
		super.paint(g);
		//print the board 's lines to show squares
		for(int i =0;i<8; i++){
			for(int j=0;j<8;j++){
				if((i+j)%2==0){
					g.setColor(Color.WHITE);
				}
				else
					g.setColor(Color.gray);
				g.fillRect(BOARD_MARGIN+(j)*SQUARE_WIDTH, 
						BOARD_MARGIN+(i)*SQUARE_WIDTH, 
						SQUARE_WIDTH, 
						SQUARE_WIDTH);


			}
		}


		//print the pieces
		for(int i = 0; i<8; i++)
		{
			for(int j = 0; j<8; j++)
			{
				if(pieces[i][j] != null)
				{
					pieces[i][j].drawYourself(g, i*SQUARE_WIDTH+BOARD_MARGIN, 
							j*SQUARE_WIDTH+BOARD_MARGIN, SQUARE_WIDTH);
				}
			}
		}


	}
	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
		//System.out.println("Clicked");

	}
	@Override
	public void mousePressed(MouseEvent e) {
		// TODO Auto-generated method stub
		//System.out.println("Pressed");
		//calculate which square is selected 
		selectedSquareX = (e.getX()-BOARD_MARGIN)/SQUARE_WIDTH;
		selectedSquareY = (e.getY()-BOARD_MARGIN)/SQUARE_WIDTH;
		//System.out.println(selectedSquareX+","+selectedSquareY);
	}
	@Override
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub
		//System.out.println("Released");
		//calculate which square is targeted
		int targetSquareX = (e.getX()-BOARD_MARGIN)/SQUARE_WIDTH;
		int targetSquareY = (e.getY()-BOARD_MARGIN)/SQUARE_WIDTH;
		//System.out.println(targetSquareX+","+targetSquareY+"\n");

		//if these are inside the board
		if(selectedSquareX >= 0 && selectedSquareY >= 0 &&
				selectedSquareX < 8 && selectedSquareY < 8 &&
				targetSquareX >= 0 && targetSquareY >= 0 &&
				targetSquareX < 8 && targetSquareY < 8)
		{
			//if a piece is selected (before in mousePressed)
			if(pieces[selectedSquareX][selectedSquareY] != null)
			{
				//get the distance of the drag-drop
				int diffX = targetSquareX - selectedSquareX;
				int diffY = targetSquareY - selectedSquareY;
				//if there is a piece in targeted square
				/*if(pieces[targetSquareX][targetSquareY] != null)
				{

					if(pieces[selectedSquareX][selectedSquareY].canCapture(diffX, diffY,selectedSquareX,selectedSquareY,targetSquareX,targetSquareY,pieces))
					{
						if(pieces[selectedSquareX][selectedSquareY].isBlack!=pieces[targetSquareX][targetSquareY].isBlack
								&&(pieces[selectedSquareX][selectedSquareY].isBlack&&count%2==1||!pieces[selectedSquareX][selectedSquareY].isBlack&&count%2==0)){
							System.out.println("can capture");
							Piece temp[][]=new Piece[8][8];

							this.str.push(turn(temp));
							pieces[targetSquareX][targetSquareY] = 
									pieces[selectedSquareX][selectedSquareY];
							pieces[selectedSquareX][selectedSquareY] = null;
							count++;
							promotion();
							if(count%2==0&&blackMate()){
								undo();								
							}
							else if(count%2==1&&whiteMate()){
								undo();							
							}
							isInCheck();
							isCheckMate();

						}

					}
					else if(pieces[selectedSquareX][selectedSquareY] instanceof King &&pieces[targetSquareX][targetSquareY] instanceof Rook){
						if(targetSquareX>selectedSquareX&&selectedSquareY==targetSquareY){
							castling(true);
							if(count%2==0&&blackMate()){
								undo();								
							}
							else if(count%2==1&&whiteMate()){
								undo();							
							}
						}
						else if(targetSquareX<selectedSquareX&&selectedSquareY==targetSquareY){
							castling(false);
							if(count%2==0&&blackMate()){
								undo();								
							}
							else if(count%2==1&&whiteMate()){
								undo();							
							}
						}
					}
				}

				else
				{
					//if targeted square is empty
					if(pieces[selectedSquareX][selectedSquareY].canMove(diffX, diffY,selectedSquareX,selectedSquareY,targetSquareX,targetSquareY,pieces))
					{ 
						if(pieces[selectedSquareX][selectedSquareY].isBlack&&count%2==1||!pieces[selectedSquareX][selectedSquareY].isBlack&&count%2==0){
							System.out.println("can move");
							Piece temp[][]=new Piece[8][8];

							this.str.push(turn(temp));
							pieces[targetSquareX][targetSquareY] = 
									pieces[selectedSquareX][selectedSquareY];
							pieces[selectedSquareX][selectedSquareY] = null;
							count++;
							promotion();
							if(count%2==0&&blackMate()){
								undo();							
							}
							else if(count%2==1&&whiteMate()){
								undo();							
							}
							isInCheck();
							isCheckMate();

						}
					}
				}*/
				if(pieces[selectedSquareX][selectedSquareY] instanceof King &&pieces[targetSquareX][targetSquareY] instanceof Rook){
					if(targetSquareX>selectedSquareX&&selectedSquareY==targetSquareY){
						castling(true);
						if(count%2==0&&blackMate()){
							undo();								
						}
						else if(count%2==1&&whiteMate()){
							undo();							
						}
					}
					else if(targetSquareX<selectedSquareX&&selectedSquareY==targetSquareY){
						castling(false);
						if(count%2==0&&blackMate()){
							undo();								
						}
						else if(count%2==1&&whiteMate()){
							undo();							
						}
					}
				}
				else{
					String from;
					String to;
					int i1=selectedSquareX;
					int i2=targetSquareX;
					int j1=selectedSquareY;
					int j2=targetSquareY;
					char a=(char)(selectedSquareX+'A');
					char b=(char)(targetSquareX+'A');
					char c=(char)('8'-selectedSquareY);
					char d=(char)('8'-targetSquareY);
					from=""+a+c;
					to=""+b+d;
					move(from,to);
				}

			}

		}

		repaint();
	}
	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
		//System.out.println("Entered");

	}
	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub
		//System.out.println("Exited");

	}
	public Piece[][] turn(Piece[][] temp){
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				temp[i][j]=this.pieces[i][j];
			}
		}
		return temp;
	}
	public boolean move(String from,String to){
		from=from.toUpperCase();
		to=to.toUpperCase();
		int i1=((int)(from.charAt(0)))-65;
		int i2=((int)(to.charAt(0)))-65;
		int j1=56-((int)(from.charAt(1)));
		int j2=56-((int)(to.charAt(1)));
		if(pieces[i1][j1]!=null){
			if(pieces[i2][j2]==null&&pieces[i1][j1].canMove(i2-i1, j2-j1,i1,j1,i2,j2,pieces))
			{ 
				if(pieces[i1][j1].isBlack&&count%2==1||!pieces[i1][j1].isBlack&&count%2==0){
					System.out.println("can move");
					Piece temp[][]=new Piece[8][8];

					this.str.push(turn(temp));
					pieces[i2][j2] = 
							pieces[i1][j1];
					pieces[i1][j1] = null;
					count++;
					promotion();
					if(count%2==0&&blackMate()){
						undo();		
						return false;
					}
					else if(count%2==1&&whiteMate()){
						undo();
						return false;
					}
					repaint();
					isInCheck();
					isCheckmate();
					//repaint();
					return true;

				}

			}
			else if(pieces[i2][j2]!=null&&pieces[i1][j1].canCapture(i2-i1, j2-j1,i1,j1,i2,j2,pieces)){
				if((pieces[i1][j1].isBlack&&count%2==1||!pieces[i1][j1].isBlack&&count%2==0)&&pieces[i1][j1].isBlack!=pieces[i2][j2].isBlack){
					System.out.println("can capture");
					Piece temp[][]=new Piece[8][8];

					this.str.push(turn(temp));
					pieces[i2][j2] = 
							pieces[i1][j1];
					pieces[i1][j1] = null;
					count++;
					promotion();
					if(count%2==0&&blackMate()){
						undo();
						return false;
					}
					else if(count%2==1&&whiteMate()){
						undo();
						return false;
					}
					repaint();
					isInCheck();
					isCheckmate();
					//repaint();
					return true;
				}
			}
		}
		repaint();
		isInCheck();
		return false;
	}
	public String at(String pos){
		pos=pos.toUpperCase();
		int i1=((int)(pos.charAt(0)))-65;
		int j1=56-((int)(pos.charAt(1)));
		String color="";
		String type="";
		if(pieces[i1][j1]==null){
			return "";
		}
		if(pieces[i1][j1].isBlack==true){
			color="black";
		}
		else{
			color="white";
		}
		if(pieces[i1][j1] instanceof Bishop){
			type="bishop";
		}
		else if(pieces[i1][j1] instanceof King){
			type="king";
		}

		else if(pieces[i1][j1] instanceof Pawn){
			type="pawn";
		}
		else if(pieces[i1][j1] instanceof Knight){
			type="knight";
		}
		else if(pieces[i1][j1] instanceof Rook){
			type="rook";
		}else if(pieces[i1][j1] instanceof Queen){
			type="queen";
		}
		return color+"-"+type;



	}
	public void undo(){
		if(!str.isEmpty()){
			Piece temp2[][]=new Piece[8][8];
			temp2=this.str.pop();
			for(int i=0;i<8;i++){
				for(int j=0;j<8;j++){
					this.pieces[i][j]=temp2[i][j];
				}
			}
			count--;
		}


	}
	public boolean isInCheck(){
		if(count%2==0&&whiteMate()){
			System.out.println("White is in check");
			return true;
		}
		else if(count%2==1&&blackMate()){
			System.out.println("Black is in check");
			return true;
		}

		return false;

	}
	public boolean whiteMate(){
		int i=-1;
		int j=-1;
		for(int a=0;a<8;a++){
			for(int b=0;b<8;b++){
				if(pieces[a][b] instanceof King && !pieces[a][b].isBlack){
					i=a;
					j=b;
				}
			}
		}
		for(int a=0;a<8;a++){
			for(int b=0;b<8;b++){
				if(i!=-1){
					if((pieces[i][j] instanceof King&&i!=-1&&(a!=i||b!=j)&&pieces[a][b]!=null&&pieces[a][b].canCapture(i-a, j-b, a, b, i,j, pieces)&&
							pieces[a][b].isBlack!=pieces[i][j].isBlack)){				
						return true;
					}
				}

			}
		}
		return false;
	}
	public boolean blackMate(){
		int e=-1;
		int f=-1;
		for(int a=0;a<8;a++){
			for(int b=0;b<8;b++){
				if(pieces[a][b] instanceof King && pieces[a][b].isBlack){
					e=a;
					f=b;
				}
			}
		}
		for(int a=0;a<8;a++){
			for(int b=0;b<8;b++){
				if(e!=-1){
					if(pieces[e][f] instanceof King&&e!=-1&&(a!=e||b!=f)&&pieces[a][b]!=null&&pieces[a][b].canCapture(e-a, f-b, a, b, e,f, pieces)&&
							pieces[a][b].isBlack!=pieces[e][f].isBlack){
						return true;
					}
				}

			}
		}
		return false;
	}
	public boolean block(){

		for(int a=0;a<8;a++){
			for(int b=0;b<8;b++){
				for(int c=0;c<8;c++){
					for(int d=0;d<8;d++){
						if(pieces[a][b]!=null&&(count%2==0&&!pieces[a][b].isBlack||count%2==1&&pieces[a][b].isBlack)){
							if((pieces[c][d]!=null&&pieces[a][b].isBlack!=pieces[c][d].isBlack&&pieces[a][b].canCapture(c-a,d-b,a, b,c,d, pieces))
									||(pieces[a][b].canMove(c-a,d-b,a, b,c,d, pieces)&&pieces[c][d]==null)){
								Piece temp[][]=new Piece[8][8];
								this.str.push(turn(temp));
								pieces[c][d] =pieces[a][b];
								pieces[a][b] = null;
								count++;

								if(count%2==1){
									if(!whiteMate()){
										undo();
										return false;
									}
								}
								else if(count%2==0){
									if(!blackMate()){
										undo();										
										return false;
									}
								}
								undo();

							}
						}

					}
				}
			}
		}
		return true;
	}



	public boolean isCheckmate(){
		ArrayList<Boolean> list=new ArrayList<Boolean>();
		int i=-1;
		int j=-1;
		int e=-1;
		int f=-1;
		for(int a=0;a<8;a++){
			for(int b=0;b<8;b++){
				if(pieces[a][b] instanceof King && !pieces[a][b].isBlack){
					i=a;
					j=b;
				}
				else if(pieces[a][b] instanceof King && pieces[a][b].isBlack){
					e=a;
					f=b;
				}
			}
		}

		if(i!=-1){
			pieces[i][j]=null;
			for(int a=i-1;a<=i+1;a++){
				for(int b=j-1;b<=j+1;b++){
					if(a>=0&&a<8&&b>=0&&b<8&&pieces[a][b]==null){
						pieces[a][b]=new King(false);
						list.add(whiteMate());
						pieces[a][b]=null;

					}
				}
			}
			pieces[i][j]=new King(false);
			int mate=0;
			for(int a=0;a<list.size();a++){
				if(!list.get(a))
					mate=-1;
			}

			if(mate==0&&block()&&count%2==0){
				System.out.println("White Checkmate");
				JOptionPane.showMessageDialog(null,"Game is over.Black won");
				return true;
			}
		}

		list.clear();
		if(e!=-1){
			pieces[e][f]=null;
			for(int a=e-1;a<=e+1;a++){
				for(int b=f-1;b<=f+1;b++){
					if(a>=0&&a<8&&b>=0&&b<8&&pieces[a][b]==null){
						pieces[a][b]=new King(true);
						list.add(blackMate());
						pieces[a][b]=null;

					}
				}
			}
			pieces[e][f]=new King(true);
			for(int a=0;a<list.size();a++){
				if(!list.get(a))
					return false;
			}
			System.out.println(block());
			if(block()&&count%2==1){
				System.out.println("Black Checkmate");
				JOptionPane.showMessageDialog(null,"Game is over.White won");
				return true;
			}			
		}
		return false;


	}
	public boolean castling(boolean isKingSide){
		if(isKingSide){						
			if(this.pieces[4][0] instanceof King&&this.pieces[4][0].isBlack&&count%2==1
					&&this.pieces[7][0] instanceof Rook&&this.pieces[7][0].isBlack
					&&this.pieces[7][0].canMove(-2,0,7,0,5,0, pieces)){
				Piece temp[][]=new Piece[8][8];

				this.str.push(turn(temp));

				this.pieces[6][0]=this.pieces[4][0];
				this.pieces[4][0]=null;
				this.pieces[5][0]=this.pieces[7][0];
				this.pieces[7][0]=null;
				count++;
				repaint();
				return true;
			}
			else if(this.pieces[4][7] instanceof King&&!this.pieces[4][7].isBlack&&count%2==0
					&&this.pieces[7][7] instanceof Rook&&!this.pieces[7][7].isBlack
					&&this.pieces[7][7].canMove(-2,0,7,7,5,7, pieces)){
				Piece temp[][]=new Piece[8][8];

				this.str.push(turn(temp));

				this.pieces[6][7]=new King(false);
				this.pieces[4][7]=null;
				this.pieces[5][7]=new Rook(false);
				this.pieces[7][7]=null;
				count++;
				repaint();
				return true;
			}

		}
		else{
			if(this.pieces[4][0] instanceof King&&this.pieces[4][0].isBlack&&count%2==1
					&&this.pieces[0][0] instanceof Rook&&this.pieces[0][0].isBlack
					&&this.pieces[0][0].canMove(4,0,0,0,3,0, pieces)){
				Piece temp[][]=new Piece[8][8];

				this.str.push(turn(temp));
				this.pieces[2][0]=this.pieces[4][0];
				this.pieces[4][0]=null;
				this.pieces[3][0]=this.pieces[0][0];
				this.pieces[0][0]=null;
				count++;
				repaint();
				return true;
			}
			else if(this.pieces[4][7] instanceof King&&!this.pieces[4][7].isBlack&&count%2==0
					&&this.pieces[0][7] instanceof Rook&&!this.pieces[0][7].isBlack
					&&this.pieces[0][7].canMove(4,0,0,7,3,7, pieces)){
				Piece temp[][]=new Piece[8][8];

				this.str.push(turn(temp));
				this.pieces[2][7]=this.pieces[4][7];
				this.pieces[4][7]=null;
				this.pieces[3][7]=this.pieces[0][7];
				this.pieces[0][7]=null;
				count++;
				repaint();
				return true;
			}

		}
		return false;

	}
	public void save(String fileName){
		File f=new File(fileName);
		PrintStream out;
		try {
			out = new PrintStream(f);
			if(count%2==0){
				out.println("white");
			}
			else{
				out.println("black");
			}
			for(int i=65;i<=72;i++){
				for(int j=49;j<=56;j++){
					String s=""+(char)i+(char)j;
					int i1=((int)(s.charAt(0)))-65;
					int j1=56-((int)(s.charAt(1)));
					s=s.toLowerCase();
					if(pieces[i1][j1]!=null){
						out.println(at(s)+"-"+s);
					}

				}
			}
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
	}
	public static ChessFrame load(String fileName){
		ChessFrame frame=new ChessFrame();
		for(int i=0;i<8;i++){
			for(int j=0;j<8;j++){
				frame.pieces[i][j]=null;
			}
		}
		Scanner scan;
		try {
			scan = new Scanner(new File(fileName));
			boolean color=true;
			String type="";
			String pos="";
			if(scan.nextLine().equalsIgnoreCase("Black")){
				frame.count=1;
			}
			else
				frame.count=0;
			while(scan.hasNextLine()){
				String s=scan.nextLine();
				String a="";
				for(int i=0;i<s.length();i++){
					if(s.charAt(i)=='-'){
						a=a+" ";
					}
					else
						a=a+s.charAt(i);
				}
				a=a.toUpperCase();
				Scanner line=new Scanner(a);
				if(line.next().equalsIgnoreCase("Black")){
					color=true;
				}
				else{
					color=false;
				}
				type=line.next();
				pos=line.next();
				int i1=((int)(pos.charAt(0)))-65;
				int j1=56-((int)(pos.charAt(1)));
				if(type.equalsIgnoreCase("pawn")){
					frame.pieces[i1][j1]=new Pawn(color);
				}
				else if(type.equalsIgnoreCase("rook")){
					frame.pieces[i1][j1]=new Rook(color);
				}
				else if(type.equalsIgnoreCase("knight")){
					frame.pieces[i1][j1]=new Knight(color);
				}
				else if(type.equalsIgnoreCase("bishop")){
					frame.pieces[i1][j1]=new Bishop(color);
				}
				else if(type.equalsIgnoreCase("queen")){
					frame.pieces[i1][j1]=new Queen(color);
				}
				else if(type.equalsIgnoreCase("King")){
					frame.pieces[i1][j1]=new King(color);
				}


			}
			frame.promotion();
			return frame;
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return frame;
		
	}
	public void promotion(){
		for(int i=0;i<8;i++){
			if(pieces[i][0] instanceof Pawn&&!pieces[i][0].isBlack){
				pieces[i][0]=new Queen(false);
			}
			if(pieces[i][7] instanceof Pawn&&pieces[i][7].isBlack){
				pieces[i][7]=new Queen(true); 

			}
		}
	}
	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO Auto-generated method stub

	}


}
