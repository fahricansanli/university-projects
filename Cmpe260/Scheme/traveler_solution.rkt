#lang scheme
;2015400096





; Takes one parameter which is a location then returns a list of neighbor cities
(define (RAILWAY-CONNECTION x) (railway x LOCATIONS))
(define (railway x locations)
  (cond ((null? locations) '())
        ((equal? x (car(car locations))) (car(cdr(cdr(car locations)))))
        (else (railway x (cdr locations) ))
        )
  )



; Takes one parameter which is a location then returns the cost of that city
(define (ACCOMMODATION-COST x) (accommodation x LOCATIONS))
(define (accommodation x locations)
  (cond ((null? locations) 0)
        ((equal? x (car(car locations))) (car(cdr(car locations))))
        (else (accommodation x (cdr locations) ))
        ))


; Takes one parameter which is a person then returns the list of interested cities of that person
(define (INTERESTED-CITIES x) (interested x TRAVELERS))
(define (interested x travelers)
  (cond ((null? travelers) '())
        ((equal? x (car(car travelers))) (car(cdr(car travelers))))
        (else (interested x (cdr travelers) ))
        ))



;Takes one parameter which is a person then returns the list of interested activities of that person
(define (INTERESTED-ACTIVITIES x) (activity x TRAVELERS))
(define (activity x travelers)
  (cond ((null? travelers)  '())
        ((equal? x (car(car travelers))) (car(cdr(cdr(car travelers)))))
        (else (activity x (cdr travelers) ))
        ))



; Takes one parameter which is a person then returns the home city of that person
(define (HOME x) (home x TRAVELERS))
(define (home x travelers)
  (cond ((null? travelers)  '())
        ((equal? x (car(car travelers))) (car(cdr(cdr(cdr(car travelers))))))
        (else (home x (cdr travelers) ))
        ))



; Takes one parameter which is a location then returns the list of people from that location
(define (TRAVELER-FROM x) (from x TRAVELERS))
(define (from x travelers)
  (cond ((null? travelers) '())
        ((equal? x (car(cdr(cdr(cdr(car travelers)))))) (from2 x travelers))
        (else (from x (cdr travelers)))))

(define (from2 x travelers)
  (cons (car(car travelers)) (from x (cdr travelers)))
  )



; To check if given atom is in list
(define (member atom list)
  (cond ((null? list) #f)
        ((equal? atom (car list)) #t)
        (else (member atom (cdr list)))))



; Takes one parameter which is a location then returns the list of people interested in this city
(define (INTERESTED-IN-CITY x) (city x TRAVELERS))
(define (city x travelers)
  (cond ((null? travelers) '())
        ((member x (car(cdr(car travelers)))) (city2 x travelers))
        (else (city x (cdr travelers)))))

(define (city2 x travelers)
  (cons (car(car travelers)) (city x (cdr travelers)))
  )



; Takes one parameter which is a location then returns the list of people interested in this activity
(define (INTERESTED-IN-ACTIVITY x) (leisure x TRAVELERS))
(define (leisure x travelers)
  (cond ((null? travelers) '())
        ((member x (car(cdr(cdr(car travelers))))) (leisure2 x travelers))
        (else (leisure x (cdr travelers)))))

(define (leisure2 x travelers)
  (cons (car(car travelers)) (leisure x (cdr travelers)))
  )





; To remove duplicate elements from a list
(define (remove-duplicates l)
  (cond ((null? l)
         '())
        ((member (car l) (cdr l))
         (remove-duplicates (cdr l)))
        (else
         (cons (car l) (remove-duplicates (cdr l))))))


; To append a list to another list if the elements of first list are not in the second list
(define (append list1 list2 list3)
  (cond ((null? list1) list3)
        ((not (member (car list1) list2)) (cons (car list1) (append (cdr list1) list2 list3)))
        (else  (append (cdr list1) list2 list3))
        ))
; To append a list to another list
(define (append2 list1 list2)
  (cond ((null? list1) list2)
        (else (cons (car list1 ) (append2 (cdr list1) list2)))))

; To delete all instances of given element from a list
(define delete
  (lambda (item list)
    (cond
     ((equal? item (car list)) (cdr list))
     (else (cons (car list) (delete item (cdr list)))))))


; Takes one parameter which is a location then returns the list of all cities reachable from this city
(define (RAILWAY-NETWORK x ) (network x (RAILWAY-CONNECTION x) (list x)  (list x) ))
(define (network a x y z)
  (cond ((null? z) (reverse(delete a (remove-duplicates y))))
        (else (network a (RAILWAY-CONNECTION (car( append2 (append x  y (cdr z)) (list 1) ))) (append2 (reverse x) y) (append x  y (cdr z))))))





; Returns the list of activities of a city
(define (activity-city x locations)
  (cond ((null? locations) '())
        ((equal? x (car(car locations)))  car(cdr(cdr(cdr(car locations)))))
        (else (activity-city x (cdr locations) ))
        ))

; To check if given two list has a common element
(define (member2 atom list list1)
  (cond ((null? atom) #f)
        ((null? list) (member2 (cdr atom) list1  list1))
        ((equal? (car atom) (car list)) #t)
        (else (member2 atom (cdr list) list1))))


; Takes two parameters. First one is a person and the second one is a location. Then returns the accommodation expense
(define (ACCOMMODATION-EXPENSES x y) (expense x y TRAVELERS))
(define (expense x y travelers)
  (cond ((equal? (HOME x) y) 0)
        ((member2 (INTERESTED-ACTIVITIES x) (car(activity-city y LOCATIONS)) (car(activity-city y LOCATIONS)) ) (* 3 (ACCOMMODATION-COST y)) )
        (else (ACCOMMODATION-COST y))
        ))


; Takes two parameters. First one is a person and the second one is a location. Then returns the travel expense
(define (TRAVEL-EXPENSES x y) (expense2 x y))
(define (expense2 x y )
  (cond ((equal? y (HOME x)) 0)
        ((member y (RAILWAY-NETWORK ( HOME x))) 100)
        (else 200)
              ))


; Take two parameters and returns the sum of accomodation and travel expense
(define (EXPENSES x y) (+ (TRAVEL-EXPENSES x y) (ACCOMMODATION-EXPENSES x y)))




; Takes two parameters which are two number. Then returns the list of cities that are in that range
(define (IN-BETWEEN x y) (price x y LOCATIONS))
(define (price x y locations)
  (cond ((null? locations) '())
        ( (and (<= (car(cdr(car locations))) y) (>= (car(cdr(car locations))) x)  ) (price2 x y locations))
        (else (price x y (cdr locations)))))

(define (price2 x y locations)
  (cons (car(car locations)) (price x y (cdr locations)))
  )

