import java.util.*;

public class Main {

	public static void main(String[] args) {
		TrieMap<String> myMap = new TrieMap<String>(3);

		// Task1 Tests...

		System.out.println("=== TASK1 TESTS ARE HERE ===\n");
		long start = System.currentTimeMillis();

		myMap.insert("cc", "v1");
		ArrayList<String> bfsOrder = myMap.returnBFSOrder();

		for (String str : bfsOrder) 
			System.out.print(str + ", ");

		System.out.println();
		System.out.println("Node count (3) == " + myMap.nodeCount());


		myMap.insert("baac","v2");
		bfsOrder = myMap.returnBFSOrder();
		for (String str : bfsOrder) 
			System.out.print(str + ", ");

		System.out.println();
		System.out.println("Node count (7) == " + myMap.nodeCount());


		myMap.insert("b", "v3");
		bfsOrder = myMap.returnBFSOrder();
		for (String str : bfsOrder) 
			System.out.print(str + ", ");

		System.out.println();
		System.out.println("Node count (7) == " + myMap.nodeCount());


		myMap.insert("bab","v4");
		bfsOrder = myMap.returnBFSOrder();
		for (String str : bfsOrder) 
			System.out.print(str + ", ");

		System.out.println();
		System.out.println("Node count (8) == " + myMap.nodeCount());


		myMap.insert("c", "v5");
		bfsOrder = myMap.returnBFSOrder();
		for (String str : bfsOrder) 
			System.out.print(str + ", ");

		System.out.println();
		System.out.println("Node count (8) == " + myMap.nodeCount());


		myMap.insert("acc", "v6");
		bfsOrder = myMap.returnBFSOrder();
		for (String str : bfsOrder) 
			System.out.print(str + ", ");

		System.out.println();
		System.out.println("Node count: (11) == " + myMap.nodeCount());

		myMap.insert("ababcab", "v12345");
		bfsOrder = myMap.returnBFSOrder();
		for (String str : bfsOrder) 
			System.out.print(str + ", ");

		System.out.println();
		System.out.println("Node count: (17) == " + myMap.nodeCount());

		System.out.println();
		System.out.println("Should be 'v1' == " + myMap.search("cc"));
		System.out.println("Should be 'v2' == " + myMap.search("baac"));
		System.out.println("Should be 'v3' == " + myMap.search("b"));
		System.out.println("Should be 'v4' == " + myMap.search("bab"));
		System.out.println("Should be 'v5' == " + myMap.search("c"));
		System.out.println("Should be 'v6' == " + myMap.search("acc"));
		System.out.println("Should be 'v12345' == " + myMap.search("ababcab"));
		System.out.println("Should be 'null' == " + myMap.search("abb"));
		System.out.println("Should be 'null' == " + myMap.search("bac"));
		System.out.println("Should be 'null' == " + myMap.search("cb"));
		System.out.println("Should be 'null' == " + myMap.search("ba"));
		System.out.println("Should be 'null' == " + myMap.search("a"));

		long end = System.currentTimeMillis();

		System.out.println();
		System.out.println("Time passed : " + (end-start) + "ms");
		System.out.println();
		System.out.println();


		//Task2 Tests...

		System.out.println("=== TASK2 TESTS ARE HERE ===\n");
		start = System.currentTimeMillis();

		System.out.println("Should be true == " + TrieMap.containsSubstr("abcdefg", "a"));
		System.out.println("Should be true == " + TrieMap.containsSubstr("abcdefg", "bcd"));
		System.out.println("Should be true == " + TrieMap.containsSubstr("abcdefg", "g"));
		System.out.println("Should be true == " + TrieMap.containsSubstr("a", "a"));
		System.out.println("Should be true == " + TrieMap.containsSubstr("denemehaha", "ha"));
		System.out.println("Should be true == " + TrieMap.containsSubstr("birikiucdortbesaltiyedikedietiyedi", "et"));
		System.out.println("Should be false == " + TrieMap.containsSubstr("abcdefg", "h"));
		System.out.println("Should be false == " + TrieMap.containsSubstr("berke", "keke"));
		System.out.println("Should be false == " + TrieMap.containsSubstr("", "fb"));
		System.out.println("Should be false but is actually true == " + TrieMap.containsSubstr("esra", "qeqo"));

		end = System.currentTimeMillis();

		System.out.println();
		System.out.println("Time passed : " + (end-start) + "ms");
		System.out.println();
		System.out.println();


		//Task3 Tests...

		System.out.println("=== TASK3 TESTS ARE HERE ===\n");
		start = System.currentTimeMillis();

		System.out.println("(3) == " + TrieMap.wordCount("ali reads a book and ali is a good boy and ali is clever", "ali"));
		System.out.println("(2) == " + TrieMap.wordCount("ali at ayse ekmek yedi yedi alti bes ali at ayse ye ye ye", "ayse"));
		System.out.println("(0) == " + TrieMap.wordCount("berke", "ali"));
		System.out.println("(0) == " + TrieMap.wordCount("berke", "berk"));
		System.out.println("(0) == " + TrieMap.wordCount("begeregeke", "geke"));
		System.out.println("(6) == " + TrieMap.wordCount("ali ali ali ali ali ali ayse ayse mahmut tugrul", "ali"));
		System.out.println("(2) == " + TrieMap.wordCount("to be or not to be", "be"));
		System.out.println("(0) == " + TrieMap.wordCount("", "to"));

		end = System.currentTimeMillis();

		System.out.println();
		System.out.println("Time passed : " + (end-start) + "ms");
		System.out.println();
		System.out.println();
		
		
		//Task4 Tests...
		
		System.out.println("=== TASK4 TESTS ARE HERE ===\n");
		start = System.currentTimeMillis();
		
		System.out.println("Answer: [be, or, to, not]");
		System.out.println("Your answer: " + Arrays.toString(TrieMap.uniqueWords("to be or not to be")));
		
		System.out.println("Answer: []");
		System.out.println("Your answer: " + Arrays.toString(TrieMap.uniqueWords("")));
		
		System.out.println("Answer: [aci, ama, bir, tatli]");
		System.out.println("Your answer: " + Arrays.toString(TrieMap.uniqueWords("aci ama tatli bir aci")));
		
		System.out.println("Answer: [f, fa, fac, face, faceb, facebo, faceboo, facebook]");
		System.out.println("Your answer: " + Arrays.toString(TrieMap.uniqueWords("f f f fa f fa fac face faceb facebo faceboo facebook")));
		
		end = System.currentTimeMillis();

		System.out.println();
		System.out.println("Time passed : " + (end-start) + "ms");
		System.out.println();
		System.out.println();
		
		
		//Task5 Test...
		
		System.out.println("=== TASK5 TESTS ARE HERE ===\n");
		start = System.currentTimeMillis();
		
		String s1[] = {"f", "fa", "fa", "fac", "fac", "fac", "face", "face", "face", "face", };
		String s2[] = {"face", "fac", "fa", "f"};
		
		String s3[] = {"berke", "berke", "berke", "baba", "badana", "baba"};
		String s4[] = {"b"};
		
		String s5[] = {"fbone", "fbtwo", "fbthree","film", "film", "film", "film", "filim", "f", "fone", "fbtwo", "fbthree", "fbthree", "fbone", "berke", "bilmem", "ne"};
		String s6[] = {"f", "fb", "fbone", "b"};
		
		String s7[] = {};
		String s8[] = {"random"};
		
		System.out.println("Answer: [[face, null, null], [face, fac, null], [face, fac, fa], [face, fac, fa]]");
		System.out.println("Your Answer: " + Arrays.deepToString(TrieMap.autoComplete(s1, s2)));
		
		System.out.println("Answer: [[berke, baba, badana]]");
		System.out.println("Your Answer: " + Arrays.deepToString(TrieMap.autoComplete(s3, s4)));
		
		System.out.println("Answer: [[film, fbthree, fbone], [fbthree, fbone, fbtwo], [fbone, null, null], [berke, bilmem, null]]");
		System.out.println("Your Answer: " + Arrays.deepToString(TrieMap.autoComplete(s5, s6)));
		
		System.out.println("Answer: [[null, null, null]]");
		System.out.println("Your answer: " + Arrays.deepToString(TrieMap.autoComplete(s7, s8)));

		end = System.currentTimeMillis();

		System.out.println();
		System.out.println("Time passed : " + (end-start) + "ms");
		System.out.println();
		System.out.println();
		
		System.out.println("TESTING DONE");

	}
}