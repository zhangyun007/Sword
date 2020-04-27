#lang Racket

(define (range n) (if (eq? n 1) (list 1) (append (range (- n 1)) (cons n `()))))

;将列表乘以整数
(define (mul n m)
  (if (> (length m) 1) (cons (* n (car m)) (mul n (cdr m))) (list (* n (car m))))
  )

(define x (range 100))
(list-ref x 45)
(mul 3 x)

(define newdisplay (lambda (x) (begin (display x)(newline))))
(define tt (lambda args (for-each newdisplay args)))
(tt 'abc 'efg 'tomson)


;map和for-each格式相同。map返回一个值，for-each没有返回值。

(map (lambda (x) (* x x)) ‘(1 2 3))

(map + ‘(1 3 5)‘ (2 4 6))
(map (lambda (x y) (* x y))‘(1 2 3)‘(2 4 6))

(define sum 0)
(for-each (lambda (x) (set! sum (+ sum x))) ‘(1 2 3 4))