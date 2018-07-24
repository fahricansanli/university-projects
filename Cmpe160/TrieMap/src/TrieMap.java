import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;



public class TrieMap<T> extends TrieMapBase<T> {

	int alphabetsize;
	Node<T> root;
	int count;
	
	class Node<T> {
		String key;
		T value;
		Node<T>[] children=new Node[alphabetsize];

		public Node(String key,T value){
			this.key=key;
			this.value=value;

		}
		public Node(String key){
			this.key=key;
			value=null;

		}


	}
	public TrieMap(int i) {
		alphabetsize=i;
		root=new Node("");
		count=1;
	}

	/**
	 * Returns 	true if key appears in text as a substring;
	 * 			false, otherwise
	 * 
	 * Use Trie data structure to solve the problem
	 */
	public static boolean containsSubstr(String text, String key) {
		int length=key.length();
		TrieMap<String> map = new TrieMap<String>(26);
		while(text.length()/length>=1){
			map.insert(text.substring(0,length),"v1");
			text=text.substring(1);

		}
		return map.search(key)=="v1";
	}

	/**
	 * Returns how many times the word in the parameter appears in the book.
	 * Each word in book is separated by a white space. 
	 * 
	 * Use Trie data structure to solve the problem
	 */
	public static int wordCount(String book, String word) {
		Scanner scan=new Scanner(book);
		int amount=0;
		while(scan.hasNext()){
			String temp=scan.next();
			if(temp.length()==word.length()){
				if(TrieMap.containsSubstr(temp,word)){
					amount++;
				}
			}
		}
		return amount;
	}

	/**
	 * Returns the array of unique words in the book given as parameter.
	 * Each word in book is separated by a white space.
	 *  
	 * Use Trie data structure to solve the problem
	 */
	public static String[] uniqueWords(String book) {
		Scanner scan=new Scanner(book);
		TrieMap<String> map = new TrieMap<String>(26);
		ArrayList<String> words=new ArrayList<String>();
		while(scan.hasNext()){
			String word=scan.next();
			if("v1"!=map.search(word)){
				map.insert(word,"v1");
				words.add(word);
			}
		}
		String[] unique =new String[words.size()];
		for(int i=0;i<words.size();i++){
			unique[i]=words.get(i);
		}
		return unique;
	}

	/**
	 * Recommends word completions based on the user history.
	 * 
	 * Among all the strings in the user history, the method takes 
	 * those that start with a given incomplete word S, 
	 * sort the words according to their frequencies (how many 
	 * times they are written), and recommend the 3 most frequently written ones.
	 * 
	 * @param userHistory 
	 * 			the words written previously by the user
	 * 
	 * @param incompleteWords 
	 * 			the list of strings to be autocompleted
	 * @return 
	 * 			a Sx3 array that contains the recommendations
	 * 			for each word to be autocompleted.
	 * 
	 * Use Trie data structure to solve the problem
	 */
	public static String[][] autoComplete(String[] userHistory, String[] incompleteWords){
		TrieMap<String> map = new TrieMap<String>(26);
		String book="";
		for(int i=0;i<userHistory.length;i++){
			book=book+userHistory[i]+" ";
		}
		int s=incompleteWords.length;
		String[][] autocompletedWord =new String[s][3];
		for(int i=0;i<s;i++){
			int location=0;
			String word=incompleteWords[i];
			String[]tempp=new String[userHistory.length];
			for(int j=0;j<userHistory.length;j++){
				if(userHistory[j].length()>=word.length()&&map.containsSubstr(userHistory[j].substring(0,word.length()),word)){
					boolean notincluded=true;
					for(int g=0;g<tempp.length;g++){
						if(tempp[g]!=null&&tempp[g].equals(userHistory[j])){
							notincluded=false;
						}
					}
					if(notincluded){
						tempp[location]=userHistory[j];
						location++;
					}
				}
			}
			String[]temp=new String[location];
			for(int e=0;e<location;e++){
				temp[e]=tempp[e];
			}
			for(int a=0;a<temp.length;a++){
				for(int b=1;b<temp.length-a;b++){
					if(map.wordCount(book,temp[b-1])<map.wordCount(book,temp[b])){
						String temporary=temp[b-1];
						temp[b-1]=temp[b];
						temp[b]=temporary;
					}
				}
			}
			if(temp.length>=3){
				autocompletedWord[i][0]=temp[0];
				autocompletedWord[i][1]=temp[1];
				autocompletedWord[i][2]=temp[2];
			}
			else if(temp.length==2){
				autocompletedWord[i][0]=temp[0];
				autocompletedWord[i][1]=temp[1];
				autocompletedWord[i][2]=null;
			}
			else if(temp.length==1){
				autocompletedWord[i][0]=temp[0];
				autocompletedWord[i][1]=null;
				autocompletedWord[i][2]=null;
			}
			else if(temp.length==0){
				autocompletedWord[i][0]=null;
				autocompletedWord[i][1]=null;
				autocompletedWord[i][2]=null;
			}

		}
		return autocompletedWord;
	}

	@Override
	public void insert(String key, T value) {
		// TODO Auto-generated method stub
		key=key.toLowerCase();
		int size=key.length();
		for(int a=0;a<size;a++){
			if(key.charAt(a)-96>alphabetsize){
				return;
			}
		}
		String k="";
		Node<T> current=root;
		for(int j=0;j<size;j++){
			char a=key.charAt(0);
			k=k+a;
			int i=a-97;
			if(i+1>alphabetsize){
				return;
			}
			else{
				if(current.children[i]==null){
					current.children[i]=new Node(k);
					count++;
					current=current.children[i];
				}
				else{
					current=current.children[i];
				}
				if(key.length()!=1){
					key=key.substring(1);

				}
			}
		}
		current.value=value;




	}

	@Override
	public boolean delete(String key) {
		// TODO Auto-generated method stub
		key=key.toLowerCase();
		int size=key.length();
		Node<T> current=root;
		for(int j=1;j<=size;j++){
			char a=key.charAt(0);
			int i=(int)a-97;
			if(i+1>alphabetsize){
				return false;
			}
			else{
				if(current.children[i]==null&&j<size){
					return false;				
				}
				else if(current.children[i]!=null&&j==size){
					if(current.children[i].value!=null){
						current.children[i].value=null;
						return true;
					}
					else return false;
				}
				else if(current.children[i]==null&&j==size){
					return false;

				}
				if(j!=size){
					current=current.children[i];
				}
				if(key.length()!=1){
					key=key.substring(1);
				}



			}

		}
		return false;
	}

	@Override
	public T search(String key) {
		// TODO Auto-generated method stub
		key=key.toLowerCase();
		Node<T> current=root;
		int size=key.length();
		for(int j=0;j<size;j++){
			char a=key.charAt(0);
			int i=(int)a-97;

			if(i+1>alphabetsize){
				return null;
			}

			else{
				if(current.children[i]==null){
					return null;
				}
				else{
					current=current.children[i];
				}
			}
			if(key.length()!=1){
				key=key.substring(1);
			}

		}
		return current.value;
	}

	@Override
	public int nodeCount() {
		// TODO Auto-generated method stub
		return count;
	}

	@Override
	public ArrayList<T> returnBFSOrder() {
		// TODO Auto-generated method stub
		ArrayList<T> list=new ArrayList<T>();
		Queue<Node> queue=new LinkedList<Node>();
		Node<T> current=root;
		queue.add(root);
		while(!queue.isEmpty()){
			Node popped=queue.poll();
			if(popped.value!=null){
				list.add((T) popped.value);
			}
			for(int i=0;i<alphabetsize;i++){
				if(popped.children[i]!=null)
					queue.add(popped.children[i]);
			}

		}
		return list;
	}

}


