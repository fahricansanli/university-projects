package project3;

import java.io.*;
import java.util.*;
public class xox_game {
	public static void main(String[]args) throws IOException{
		Random rand=new Random();
		Scanner console=new Scanner(System.in);
		String[][] board=new String[6][6];
		System.out.println("Do you want to start a new game");
		String answer=console.next();
		makingBoard(answer,board);
		int count=0;
		while(proceed(board)==0){
			if(count%2==0){
				System.out.println("Your turn dear user, Please Make a move");
				String move=console.next();
				while(!(move.equalsIgnoreCase("C")||move.equalsIgnoreCase("M"))){
					console.nextInt();
					console.nextInt();
					System.out.println("Please make a valid move ");
					move=console.next();
				}
				if(move.equalsIgnoreCase("C")){
					changeMove(board,console.nextInt(),console.nextInt(),console,count,rand);
				}
				else if(move.equalsIgnoreCase("M"))
					moveMove(board,console.nextInt(),console.nextInt(),console.nextInt(),console.nextInt(),console,count,rand);
				if(proceed(board)==1){
					System.out.println("User wins");
					break;
				}
				if(proceed(board)==2){
					System.out.println("Computer wins");
					break;
				}
			}
			else{
				System.out.println("Computer's turn");
				int a=rand.nextInt(2);
				if(a==0||count==1){

					if(!there(board)){
						computerMove(board,console,count,rand);
					}
					else
						changeMove(board,rand.nextInt(6),rand.nextInt(6),console,count,rand);


				}

				else if(a==1){
					computerMove(board,console,count,rand);
				}
				if(proceed(board)==1){
					System.out.println("User wins");
					break;
				}
				if(proceed(board)==2){
					System.out.println("Computer wins");
					break;
				}
			}
			count++;
		}

	}

	/*  makingboard method takes two parameters.One of them is a string as a preference of user if he/she want to play default game.
	 *The other parameter is an array of Strings to produce the board. 
	 */
	public static void makingBoard(String answer,String[][] board)throws IOException{
		File myFile = new File("input.txt");
		//System.out.println("Attempting to read from file in: "+myFile.getCanonicalPath());
		Scanner input=new Scanner(myFile);
		if(answer.equalsIgnoreCase("yes")){
			for(int i=0;i<6;i++){
				for(int j=0;j<6;j++){
					board[i][j]="B";
				}
			}
		}
		else{
			while(input.hasNextLine()){
				for(int i=0;i<=5;i++){
					String a=input.nextLine();
					for(int j=0;j<=5;j++){
						board[i][j]=a.substring(j,j+1);
					}

				}
			}
		}
		print(board);



	}	  		  
	// The method of print is used to print the board.�t takes board as parameter.		 
	public static void print(String[][] board){
		for(int i=0;i<6;i++){
			for(int j=0;j<6;j++){
				System.out.print(board[i][j]);
			}
			System.out.println();
		}


	}	
	/* possibleChange method takes a board and two integers as parameters.The method checks whether change
	 * move is possible by looking at given coordinates.If it is blank it returns true.Otherwise it returns false. 
	 */
	public static boolean possibleChange(String[][] board,int a,int b){
		/* a denotes first row
				  b denotes first column  */

		if(board[a][b].equals("O")||board[a][b].equals("X")){
			return false;
		}
		if(a>=1&&b>=1&&a<=4&&b<=4){
			return false;
		}


		return true;

	}		
	/* possibleMove method takes a board ,four integer as coordinates and one integer to decide whose turn as parameters.
	 * It examine the board by looking if certain conditions are engaged.Count parameter tell method it is user's turn or
	 * computer's turn.If conditions are available it returns true otherwise it returns false.		 		  
	 */
	public static boolean possibleMove(String[][] board,int a1,int b1,int a2,int b2,int count){
		/* a1 denotes first row
		 * b1 denotes first column
		 * a2 denotes second row
		 * b2 denotes second column
		 * This if state checks that if given coordinates are at outer shell or inner shell.If it is in inner shell 
		 * it returns false.
		 */
		if((a1>=1&&b1>=1&&a1<=4&&b1<=4))
			return false;
		//This if state is used when it is user's turn.This one checks that if there is X at given coordinates.
		if(count%2==0){
			if(!board[a1][b1].equals("X"))
				return false;

		}
		//This if state is used when it is computer's turn.This one checks that if there is O at given coordinates.
		if(count%2==1){
			if(!board[a1][b1].equals("O"))
				return false;

		}
		return true;

	}
	/* possibleMove2 method takes a board and four integers as parameters.
	 * It specifically look into if the movement of points that is at outer shell but not at the corner
	 */
	public static boolean possibleMove2(String[][] board,int a1,int b1,int a2,int b2){
		/* a1 denotes first row
				  b1 denotes first column
				  a2 denotes second row
				  b2 denotes second column  */
		//This if state checks that if it is possible to move a point between second and fifth row in the outher shell.
		if(a1>=1&&a1<=4&&((a1!=a2)||(b2!=0&&b2!=5))){
			return false;

		}
		//This if state checks that if it is possible to move a point between second and fifth column in the outher shell.
		else if(b1>=1&&b1<=4&&((b1!=b2)||(a2!=0&&a2!=5))){
			return false;
		}
		else if(a1==a2&&b1==b2){
			return false;
		}
		else if(((a1==0||a1==5)&&(b1==0||b1==5))&&((a2!=0&&a2!=5)||(b2!=0&&b2!=5))){
			return false;
		}

		else return true;			

	}
	/* computerMove method is used to perform the move movement of computer.
	 */
	public static void computerMove(String[][] board,Scanner console,int count,Random rand){
		// g and h is used to find the index of last "O" at the board to make it move.
		int g=0;
		int h=0;
		int i=0;
		int j=0;
		int e=0;
		int f=0;
		// i and j is the coordinates of "O" that will be moved.
		// e and f is the coordinates of where the O  will be moved.
		for(g=0;g<=5;g++){
			for(h=0;h<=5;h++){
				if(board[g][h].equals("O")&&!(g>=1&&g<=4&&h>=1&&h<=4)){
					i=g;
					j=h;
				}
			}

		}
		//This if state is used to check whether there is available "O" to move.
		if(i==0&&j==0&&!board[0][0].equals("O")){
			changeMove(board,rand.nextInt(6),rand.nextInt(6),console,count,rand);

		}
		else{
			if(i==0||i==5){

				if(j<=4&&j>=1){
					if(i==0){
						e=5;
					}
					else if(i==5){
						e=0;
					}
					f=j;


				}
				else if(j==0||j==5){
					e=rand.nextInt(2);
					if(i==0){
						if(e==0){
							f=5-j;
						}
						else if(e==1){
							e=5;f=j;
						}
					}
					if(i==5){
						if(e==1){
							e=5;f=5-j;
						}
						else if(e==0){
							f=j;
						}
					}

				}
			}
			else if(i>=1&&i<=4){
				e=i;
				f=5-j;
			}
			System.out.println("M"+" "+i+" "+j+" "+e+" "+f);
			moveMove(board,i,j,e,f,console,count,rand);



		}

	}		
	/* The method named changeMove take diverse parameters.This method's main goal is to change given 
	 * coordinates with right letter
	 */
	public static void changeMove(String[][] board,int a,int b,Scanner console,int count,Random rand){
		// a and b denotes the given coordinates.
		while(!possibleChange(board,a,b)){
			if(count%2==0){
				System.out.println("Try again");
				console.next();
				a=console.nextInt();
				b=console.nextInt();
			}
			else{
				a=rand.nextInt(6);
				b=rand.nextInt(6);
			}

		}

		if(count%2==0){
			board[a][b]="X";
		}
		else if(count%2==1){
			System.out.println("C"+" "+a+" "+b);
			board[a][b]="O";
		}


		print(board);




	}
	/*moveMove method is used to perform the move movement during the game.�t takes board and
	 * coordinates as parameters.
	 */ 
	public static void moveMove(String[][] board,int a1,int b1,int a2,int b2,Scanner console,int count,Random rand){
		// a1,b1,a2,b2 denotes the given coordinates.
		while(!possibleMove(board,a1,b1,a2,b2,count)||!possibleMove2(board,a1,b1,a2,b2)){
			if(count%2==0){
				System.out.println("Please try again");
				console.next();
				a1=console.nextInt();
				b1=console.nextInt();
				a2=console.nextInt();
				b2=console.nextInt();
			}
			else if(count%2==1){
				a1=rand.nextInt(6);
				b1=rand.nextInt(6);
				a2=rand.nextInt(6);
				b2=rand.nextInt(6);

			}
		}


		//This if state is used to perform move of the points at the corner.
		if(a1==0&&b1==0||a1==0&&b1==5||a1==5&&b1==0||a1==5&&b1==5){
			if(a1==0&&a2==0||a1==5&&a2==5){
				if(b2==5){
					String e=board[a1][0];
					for(int i=0;i<=4;i++){
						board[a1][i]=board[a1][i+1];

					}
					board[a1][5]=e;
				}
				else if(b2==0){
					String e=board[a1][5];
					for(int i=5;i>=1;i--){
						board[a1][i]=board[a1][i-1];
					}
					board[a1][0]=e;
				}
			}

			else if(b1==0&&b2==0||b1==5&&b2==5){
				if(a2==5){
					String e=board[0][b1];
					for(int i=0;i<=4;i++){
						board[i][b1]=board[i+1][b1];
					}
					board[5][b1]=e;
				}
				else if(a2==0){
					String e=board[5][b1];
					for(int i=5;i>=1;i--){
						board[i][b1]=board[i-1][b1];

					}
					board[0][b1]=e;

				}
			}
		}
		else {
			//This if state is used to perform move of the points at outer shell and between second and fifth row.
			if(b1==1&&b2==1||b1==2&&b2==2||b1==3&&b2==3||b1==4&&b2==4||b1==5&&b2==5){
				if(a2==5){
					String e=board[0][b1];
					for(int i=0;i<=4;i++){
						board[i][b1]=board[i+1][b1];
					}
					board[5][b1]=e;
				}
				else if(a2==0){
					String e=board[5][b1];
					for(int i=5;i>=1;i--){
						board[i][b1]=board[i-1][b1];

					}
					board[0][b1]=e;

				}

			}
			//This if state is used to perform move of points at outer shell and between second and fifth column.
			else if(a1==1&&a2==1||a1==2&&a2==2||a1==3&&a2==3||a1==4&&a2==4||a1==5&&a2==5){
				if(b2==5){
					String e=board[a1][0];
					for(int i=0;i<=4;i++){
						board[a1][i]=board[a1][i+1];

					}
					board[a1][5]=e;
				}
				else if(b2==0){
					String e=board[a1][5];
					for(int i=5;i>=1;i--){
						board[a1][i]=board[a1][i-1];
					}
					board[a1][0]=e;
				}



			}
		}
		print(board);



	}
	// proceed method takes a board as parameters.It is used to check if there is a winner.
	public static int  proceed(String[][] board){
		//String e is used to produce each row
		//String f is used to produce each column
		String e="";
		String f="";
		int a=0;
		for(int i=0;i<=5;i++){
			for(int j=0;j<=5;j++){
				e=e+board[i][j];
				f=f+board[j][i];
			}
			if(e.equals("XXXXXX")||f.equals("XXXXXX"))
				a=1;
			else
				if(e.equals("OOOOOO")||f.equals("OOOOOO"))
					a=2;




			e="";
			f="";

		}
		return a;
	}
	/* The method named there is used to check whether there is a available blank to change for computer
	 * �f there is no available blank to change this method returns false so that computer makes move.
	 */
	public static boolean there(String[][] board){
		boolean x=false;
		for(int i=0;i<=5;i++){
			for(int j=0;j<=5;j++){
				if(board[i][j].equals("B")&&!(i>=1&&i<=4&&j>=1&&j<=4))
					x=true;
			}
		}
		return x;
	}

}
