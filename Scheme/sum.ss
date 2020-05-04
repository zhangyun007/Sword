#lang Racket

;尾部递归
(time
  (define (sum x r)
      (if (eq? x 0)
          0
       (sum (- x 1) (+ x r))
       )
    )
   (sum 10000 0)
 )

;循环
(time 
    (define sum 0)
    (do ((i 0 (+ i 1)))         ; 初始值和 step 条件
        ((> i 10000))			; 停止条件,取值为 #f 时停止
        (set! sum (+ sum i))
        (display " ")
        (display sum)
        (newline)
    )
    sum
)


;(cons n '())是一个list
(define (range n) (if (eq? n 1) (list 1) (append (range (- n 1)) (cons n '()))))
(define (range n) (if (eq? n 1) (list 1) (append (range (- n 1)) (list n))))

( time
   (define sum 0)
   (for-each (lambda (x) (set! sum (+ sum x))) (range 10000))
   sum
)


;将整数乘以列表
(define (mul n m)
  (if (> (length m) 1) (cons (* n (car m)) (mul n (cdr m))) (list (* n (car m))))
  )

(define x (range 100))
(list-ref x 45)
(mul 3 x)


;map和for-each格式相同。map返回一个值,for-each没有返回值。

;三者都能运行。
(map (lambda (x) (* x x)) '(1 2 3))
(map (lambda (x) (* x x)) (quote (1 2 3)))
(map (lambda (x) (* x x)) (list 1 2 3))


(map + '(1 3 5) '(2 4 6))
(map (lambda (x y) (* x y)) '(1 2 3) '(2 4 6))