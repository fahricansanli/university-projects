package project2;

import java.util.*;
public class swap_game {
	public static void main(String[] args){
		Scanner console=new Scanner(System.in);
		System.out.println("Welcome to this weird game of SWAP");
		System.out.print("Do you want to use the default board configuration ");
		String answer=console.next();
		String board=makingBoard(answer,console);
		System.out.print("\nHow many moves do you want to make?");

		int move=console.nextInt();     // Move  is the number of movement that user wants
		System.out.println("Make a move and press enter.After each move,the board configuraiton and your total points will \nbe printed.Input the cordinates to be swapped.\n");
		System.out.println(hint1(board,move,0));//0 is a random number it means nothing for program
		for(int i=1;i<=move;i++){
			int x1=console.nextInt();   // x1 is a variable to denote first coordinate's row
			int y1=console.nextInt();   // y1 is a variable to denote first coordinate's column
			int x2=console.nextInt();   // x2 is a variable to denote second coordinate's row
			int y2=console.nextInt();   // y2 is a variable to denote second coordinate's column
			int ind1=cordinates(x1-1,y1-1);  //ind1  is the number of index in the string board that correspond to first coordinate
			int ind2=cordinates(x2-1,y2-1);  //ind2  is the number of index in the string board that correspond to second coordinate
			board=swap(board,ind1,ind2);
			System.out.println("\nThis is the board configuration now: ");
			System.out.println(board.substring(0,4));
			System.out.println(board.substring(4,8));
			System.out.println(board.substring(8,12));
			System.out.println(board.substring(12));
			System.out.println("\nYour total score is "+score(board));
			if(i!=move){
				System.out.println(hint1(board,move,i));
			}
		}
		System.out.println("\nThank you for playing this game.");






	}
	// makingBoard method is used to determine the board that user want to play
	public static String makingBoard(String answer,Scanner console){
		String sum=""; // sum is used to form a board when user want to play with his/her own board design
		String board;
		if(answer.equalsIgnoreCase("yes")){
			board="AGBERTFFAKEMGVJA";
		}
		else {
			for(int i=1;i<=4;i++){ // i is defined as the number of row
				System.out.print("Enter row "+i+" of the board: ");
				sum=sum+console.next();
			}
			board=sum;
		}
		System.out.println("\nThis is the board configuration now: ");
		System.out.println(board.substring(0,4));
		System.out.println(board.substring(4,8));
		System.out.println(board.substring(8,12));
		System.out.println(board.substring(12));
		return board;
	}

	/* The method of swap takes a board and two index that correspond to coordinates user writes as parameters
	 then swap method changes places of letters that correspond to index and rewrite the board.

	 */
	//ind1  is the number of index in the string board that correspond to first coordinate
	//ind2  is the number of index in the string board that correspond to second coordinate
	public static String swap(String board,int ind1,int ind2){
		if(ind1<ind2){
			board=board.substring(0,ind1)+board.charAt(ind2)+board.substring(ind1+1,ind2)+board.charAt(ind1)+board.substring(ind2+1);
		}
		else {
			board=board.substring(0,ind2)+board.charAt(ind1)+board.substring(ind2+1,ind1)+board.charAt(ind2)+board.substring(ind1+1);

		}
		return board;
	}

	/* The method of coordinates takes  two specific integer that user writes then calculates the corresponding
	 index of that specific integers each time.

	 */
	//x1 and y1 is the coordinates that user writes
	public static int cordinates(int x1,int y1){
		int ind=4*x1+y1;
		return ind;
	}

	/* The method of score takes a string  as parameter and scan each row of the board to calculate the score of user.
	 �f two same letter comes one after the other in a row then method increases the score 
	 */

	public static int score(String board){
		int score=0;
		for(int i=0;i<=3;i++){
			for(int a=0;a<=2;a++){
				if(board.charAt(4*i+a)==board.charAt(4*i+a+1)){
					score++;
				}
			}
		}
		return score;
	}
	/* The method of hint1 takes a string as parameter.Then method suggest a possible movement to user to 
	 increase the score .Method creates possible movements then calculates its score and compares its score 
     with  board's score that comes as parameter.Then when the score of possible movement is bigger than the first board,it 
     finds the corresponding coordinates.Then returns it.  

	 */
	////move is the number of that player want to play and movedone is the rest number of move after each move
	public static String hint1(String board,int move,int movedone){ 
		String suggest2="There is no avilable option";
		int x1 = 0,y1 = 0,x2 = 0,y2 = 0; //x1 and y1 denotes the first coordinate and x2 , y2 denotes the second coordinate
		int  firstboard=score(board);  // firstboard store the score of the first board.
		String first=board;    //first store the model of board that comes as parameter

		/*
		 */
		for(int i=0;i<=15;i++){  //i is used to define the first character to swap

			for(int a=1;a<=15;a++){  // a is used to define the second character to swap
				if(i!=a)
					if(i<a){
						board=first.substring(0,i)+first.charAt(a)+first.substring(i+1,a)+first.charAt(i)+first.substring(a+1);
					}
					else
						board=first.substring(0,a)+first.charAt(i)+first.substring(a+1,i)+first.charAt(a)+first.substring(i+1);


				//This if statements compares the boards to find possible coordinates to increase score.		    		    

				if(score(board)>firstboard){  
					firstboard=score(board);

					//these for loops find the coordinates	

					for(int x=0;x<=3;x++){
						for(int y=0;y<=3;y++){
							if(4*x+y==i){
								x1=x+1;
								y1=y+1;

							}

						}
					}
					for(int x=0;x<=3;x++){
						for(int y=0;y<=3;y++){
							if(4*x+y==a){
								x2=x+1;
								y2=y+1;
							}

						}
					}



				}
				else if ((score(board)==firstboard)&&((move-movedone)>=2)){
					if(suggest2.equals("There is no avilable option"))
						suggest2=hint2(board,i,a);

				}
			}
		}

		if(x1!=0){
			String suggest="Hint : You can swap "+"("+x1+","+y1+") "+" and "+"("+x2+","+y2+")"+" to get higher point \n";
			return suggest;
		}
		else 
			return suggest2;



	}
	/* The method of hint2 takes a board and two numbers as parameters.Board represents the version of board that comes from hint1 
	 * Number i and a represent the index of letters that are changed in the initial board to search if it increases score after 2 moves.
	 * Hint2 searches if there are a possible way to increase score in two steps
	 */
	public static String hint2(String board,int i,int a){ //i and a are index of letters that are changed in hint1
		int a1 = 0,b1 = 0,a2 = 0,b2 = 0; //a1 and b1 denotes the first coordinate and a2 , b2 denotes the second coordinate
		int  firstboard=score(board);  // firstboard store the score of the first board.
		String first=board;    //first store the model of board that comes as parameter

		/*
		 */
		for(int e=0;e<=15;e++){  //e is used to define the first character to swap

			for(int f=1;f<=15;f++){  // f is used to define the second character to swap

				if((e!=f)&&(first.charAt(e)!=first.charAt(f))){
					if(e<f){
						board=first.substring(0,e)+first.charAt(f)+first.substring(e+1,f)+first.charAt(e)+first.substring(f+1);
					}
					else
						board=first.substring(0,f)+first.charAt(e)+first.substring(f+1,e)+first.charAt(f)+first.substring(e+1);


					//This if statements compares the boards to find possible coordinates to increase score.		    		    

					if(score(board)>firstboard){  

						//these for loops find the coordinates	
						for(int x=0;x<=3;x++){
							for(int y=0;y<=3;y++){
								if(4*x+y==i){
									a1=x+1;
									b1=y+1;

								}

							}
						}
						for(int x=0;x<=3;x++){
							for(int y=0;y<=3;y++){
								if(4*x+y==a){
									a2=x+1;
									b2=y+1;
								}

							}
						}



					}
				}	
			}
		}
		if(a1!=0){
			String suggest="Hint : You can swap "+"("+a1+","+b1+") "+" and "+"("+a2+","+b2+")"+" to get higher point \n";
			return suggest;
		}
		else
			return "There is no avilable option";

	}

}
