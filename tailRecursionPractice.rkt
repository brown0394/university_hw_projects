;;201824641 최성찬
;; 1. 숫자를 두 개 입력 받은 후 두 번째 숫자를 첫 번째 숫자만큼 가지고 있는 리스트를 반환하는 함수(A function that takes two numbers and returns a list containing as many second numbers as the first).
;; (replicateTail 3 5) => (5 5 5)
(define (replicate n1 n2)
  (cond((< n1 1) '())
       (else (cons n2 (replicate (- n1 1) n2)))))
(define (makeList) (replicateTail(read) (read)))

(define (replicateTailIn n1 n2 plist)
  (cond((< n1 1) plist)
       (else (replicateTailIn (- n1 1) n2 (cons n2 plist)))))

(define (replicateTail n1 n2) (replicateTailIn n1 n2 '()))

;; 2. 입력 리스트에서 입력받은 숫자만큼의 값만 꺼내오는 함수(A function that returns only the number of values entered in a list)
;; (takeTail 3 ‘(1 2 3 4 5)) => (1 2 3)
(define (take num plist)
  (cond((< num 1) '())
       (else(cons (car plist) (take (- num 1) (cdr plist))))))

(define (takeTailIn num plist pcon)
  (cond((< num 1) pcon)
       (else
        (if (null? pcon)(takeTailIn (- num 1) (cdr plist) (cons (car plist) '()))
            (takeTailIn (- num 1) (cdr plist) (makeOneL pcon (list(car plist))))))))
(define (takeTail num plist) (takeTailIn num plist '()))
;; 3. 입력값 n이 리스트에 존재하는지 확인하는 함수(A function to check if n exists in a list).
;; (elem 3 ‘(1 2 3 4 5)) => #t
(define (elem target plist)
  (cond((null? plist) #f) ((= (car plist) target) #t)
       (else(elem target (cdr plist)))))

;; 4. 리스트의 값을 뒤집는 재귀 함수(A function that returns a list in reverse order).
;; (reverseTail ‘(1 2 3 4 5)) => (5 4 3 2 1)
(define (getLast plist)
  (cond((null? (cdr plist)) (car plist))
       (else(getLast (cdr plist)))))
(define (getBefore plist before)
  (cond((null? before) (getLast plist))
       ((= (car(cdr plist)) before) (car plist))
       (else(getBefore (cdr plist) before))))
(define (makeOneL list1 list2)
  (cond((null? list1)(if(null? list2) '()(cons (car list2) (makeOneL list1 (cdr list2)))))
       (else(cons(car list1)(makeOneL (cdr list1) list2)))))
(define (reverseR plist)
  (cond((null? (cdr plist)) (list(car plist)))
       (else(makeOneL (reverseR (cdr plist)) (list(car plist))))))

(define (reverseIn plist pcon)
  (cond((null? plist) pcon)
       (else (reverseIn (cdr plist) (cons (car plist) pcon)))))
(define (reverseTail plist) (reverseIn plist '()))
;; 5. 가장 큰 값을 반환하는 함수(A function that returns the largest value).
;; (maximumTail ‘(1 2 3 4 5)) => 5
(define (maximum plist)
  (cond((null? plist) 0)
       (else(if (> (car plist) (maximum (cdr plist))) (car plist) (maximum (cdr plist))))))

(define (maximumTailIn plist largest)
  (cond((null? plist) largest)
       (else(if (> (car plist) largest) (maximumTailIn (cdr plist) (car plist)) (maximumTailIn (cdr plist) largest)))))

(define (maximumTail plist) (maximumTailIn plist (car plist)))

;; 6. 10진수 숫자를 입력받아서 2진수 리스트로 변환하는 함수(A function to convert decimal number to binary number).
;; (toBinTail 5) => (1 0 1)
(define (mod lhs rhs)
  (cond((< lhs rhs) lhs) (else(mod (- lhs rhs) rhs))))
(define (intDiv lhs rhs)
  (if (integer? (/ lhs rhs)) (/ lhs rhs) (- (/ lhs rhs) (/ 1 rhs) )))
(define (toBin num)
  (cond((< num 2) (list num))
       (else(makeOneL (toBin (intDiv num 2)) (list(mod num 2))))))
(define (toBinIn num binary)
  (cond((< num 2) (cons num binary))
       (else(toBinIn (intDiv num 2) (cons (mod num 2) binary)))))
(define (toBinTail num) (toBinIn num '()))

;; 7. 두 개의 리스트를 입력으로 받아서 하나의 리스트로 조합하는 함수(A function that takes two lists as input and combines them into a single list).
;; (zip ‘(1 3 5) ‘(2 4)) => ((1 2) (3 4))
(define (zip list1 list2)
  (cond((null? list1)(if(null? list2) '() (cons (car list2) (zip list1 (cdr list2)))))
       ((null? list2)(if(null? list1) '() (cons (car list1) (zip (cdr list1) list2))))
       ((<= (car list1) (car list2)) (cons (car list1) (zip (cdr list1) list2)))
       (else(cons (car list2) (zip list1 (cdr list2))))))

(define (zipTailIn list1 list2 zipped)
  (cond((null? list1)(if(null? list2) zipped (zipTailIn '() (cdr list2) (cons(car list2) zipped))))
       ((null? list2)(zipTailIn (cdr list1) '() (cons(car list1) zipped)))
       ((<= (car list1) (car list2)) (zipTailIn (cdr list1) list2 (cons (car list1) zipped)))
       (else(zipTailIn list1 (cdr list2) (cons (car list2) zipped)))))
(define (zipTail list1 list2) (reverseTail (zipTailIn list1 list2 '())))

;; 8. Merge Sort(https://en.wikipedia.org/wiki/Merge_sort)
;; (mergesort '(5 4 1 2 3)) => (1 2 3 4 5)
(define (takeAfter num plist)
  (cond((null? plist) '())
       ((< num 1) (cons (car plist) (takeAfter num (cdr plist))))
       (else(takeAfter (- num 1) (cdr plist)))))

(define (mergesort plist)
  (cond((null? (cdr plist)) (list(car plist)))
       (else(zipTail (mergesort (takeTail (intDiv (length plist) 2) plist)) (mergesort(takeAfter (intDiv (length plist) 2) plist))))))