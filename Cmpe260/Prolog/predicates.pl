%        KNOWLEDGE BASE 

team(realmadrid, madrid).
team(juventus, torino).
team(galatasaray, istanbul).
team(kobenhavn, copenhagen).
team(manutd, manchester).
team(realsociedad, sansebastian).
team(shaktard, donetsk).
team(bleverkusen, leverkusen).
team(omarseille, marseille).
team(arsenal, london).
team(fcnapoli, napoli).
team(bdortmund, dortmund).

match(1, galatasaray, 1, realmadrid, 6).
match(1, kobenhavn, 1, juventus, 1).
match(1, manutd, 4, bleverkusen, 2).
match(1, realsociedad, 0, shaktard, 2).
match(1, omarseille, 1, arsenal, 2).
match(1, fcnapoli, 2, bdortmund, 1).

match(2, juventus, 2, galatasaray, 2).
match(2, realmadrid, 4, kobenhavn, 0).
match(2, shaktard, 2, manutd, 3).
match(2, bleverkusen, 1, realsociedad, 1).
match(2, bdortmund, 3, omarseille, 0).
match(2, arsenal, 2, fcnapoli, 0).

match(3, galatasaray, 3, kobenhavn, 1).
match(3, realmadrid, 2, juventus, 1).
match(3, manutd, 1, realsociedad, 0).
match(3, bleverkusen, 4, shaktard, 0).
match(3, omarseille, 1, fcnapoli, 2).
match(3, arsenal, 1, bdortmund, 2).

match(4, kobenhavn, 1, galatasaray, 0).
match(4, juventus, 2, realmadrid, 2).
match(4, bleverkusen, 0, manutd, 5).
match(4, shaktard, 4, realsociedad, 0).
match(4, fcnapoli, 4, omarseille, 2).
match(4, bdortmund, 0, arsenal, 1).

match(5, realmadrid, 4, galatasaray, 1).
match(5, juventus, 3, kobenhavn, 1).
match(5, realsociedad, 0, manutd, 0).
match(5, shaktard, 0, bleverkusen, 0).
match(5, bdortmund, 3, fcnapoli, 1).
match(5, arsenal, 2, omarseille, 0).

match(6, galatasaray, 1, juventus, 0).
match(6, kobenhavn, 0, realmadrid, 2).
match(6, manutd, 1, shaktard, 0).
match(6, realsociedad, 2, bleverkusen, 0).
match(6, omarseille, 1, bdortmund, 2).
match(6, fcnapoli, 2, arsenal, 0).



/* Predicate that return a list of all teams in the league and the total number.It ıs used for order predicate*/
allteams(L,N):-findall(X,team(X,Y),L),
length(L,N).

/* Predicate that take two parameters L and N. Return L as a list of all teams and N as a number of teams.Findall is a built-in function to find all solutions which meet with the specified goal
and permutation is a built-in function to make sure that there are so many possible result.*/
allTeams(L,N):-findall(X,team(X,Y),Q),
permutation(Q,L),
length(L,N).

/* Predicate to form a list of teams that is defeated by given team T. This predicate looks for all matches when T is a home team or away team. It also evaluates the totat number of teams that meets with the goal.*/
wins(T,W,L,N):-team(T,_),
findall(F,(match(X,T,G,F,J),G>J,X=<W),A),
findall(F,(match(X,F,G,T,J),J>G,X=<W),B),
append(A,B,L),
length(L,N).

/* Predicate to form a list of teams that defeated given team T. This predicate looks for all matches when T is a home team or away team. It also evaluates the totat number of teams that meets with the goal.*/
losses(T,W,L,N):-team(T,_),
findall(F,(match(X,T,G,F,J),J>G,X=<W),A),
findall(F,(match(X,F,G,T,J),G>J,X=<W),B),
append(A,B,L),
length(L,N).

/* Predicate to form a list of teams that has equal score with given team T in a match. This predicate looks for all matches when T is a home team or away team. It also evaluates the totat number of teams that meets with the goal.*/
draws(T,W,L,N):-team(T,_),
findall(F,(match(X,T,G,F,J),J=G,X=<W),A),
findall(F,(match(X,F,G,T,J),G=J,X=<W),B),
append(A,B,L),
length(L,N).

/* Predicate that evaluates the total number of goals scored by given team T. It uses findall function to find all scores that meet with our goal.*/
scored(T,W,C):-team(T,_),
findall(G,(match(X,T,G,F,J),X=<W),A),
findall(G,(match(X,F,J,T,G),X=<W),B),
append(A,B,Y),
sum_list(Y,C).

/* Predicate that evaluates the total number of goals conceded by given team T. It uses findall function to find all scores that meet with our goal.*/
conceded(T,W,C):-team(T,_),
findall(J,(match(X,T,G,F,J),X=<W),A),
findall(J,(match(X,F,J,T,G),X=<W),B),
append(A,B,Y),
sum_list(Y,C).

/* Predicate to evaluate a substraction expression. It takes two parameters and returns the result as C.*/
subtract(X,Y,C):- C is X - Y.

/* Predicate to return average of a team T in given week W. It first find total the number of goals scored and then evaluate the total number of goals conceded. After these steps, it uses substract predicate to subtract number of conceded goals from scored goals.
Then it returns result as C. */
average(T,W,C):-team(T,_),
findall(G,(match(X,T,G,F,J),X=<W),A),
findall(G,(match(X,F,J,T,G),X=<W),B),
append(A,B,Y),
sum_list(Y,M),
findall(J,(match(X,T,G,F,J),X=<W),D),
findall(J,(match(X,F,J,T,G),X=<W),E),
append(D,E,F),
sum_list(F,N),
subtract(M,N,C).

/* All insertion sorts are used to sort teams regarding their average in a given week W
This one is a base case. If the given list is empty it returns an empty list.*/
insertionsort([],[],W).
/* This one is a base case. If the given list contains one element it returns the same list.*/
insertionsort([A],[A],W).
/* This one is main function. It takes the head of list and evaluate the rest of list by sending the rest of the list to itself and call insert function to compare two teams' average to determine order.*/
insertionsort([H|T], Out,W):-
  insertionsort(T,Z,W),
  insert(H,Z,Out,W).
/* This predicate is base case. If one of the team is empty, it returns a list of that contains nonempty team.*/
insert(X, [], [X],W).
/* This predicate is to compare given two teams' average and then order them correctly. It uses the average predicate to evaluate the averages of the teams.*/
insert(X, [H|T], [X,H|T],W):-
  average(X,W,A),
  average(H,W,B),
  A > B.
/* This predicate is to compare given two teams' average and then order them correctly. It uses the average predicate to evaluate the averages of the teams.*/
insert(X, [H|T], [H|Z],W):-
  average(X,W,A),
  average(H,W,B),
  A =< B,
  insert(X,T,Z,W).

/* Predicate to return a list of teams that are ordered according to their averages in a given week W. It uses insertionsort predicate*/
order(L,W):-allteams(Q,N),
insertionsort(Q,L,W).
/* This one is base case. If the number reaches 0, it stops the recursive call.*/
take(0,X,[]).
/* This predicate to find top three of ordered list in a given week W. At each step it takes head and append to new list. Then decrease the number and call itself again.*/
take(N,[H|T],[H|R]):- 
    N>0, M is N-1,
    take(M,T,R). 
/* Predicate to return a list of top three teams of given week W. It uses take function to find top three.*/
topThree(L,W):-allteams(Q,N),
insertionsort(Q,B,W),
take(3,B,L).
