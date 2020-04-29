#lang Racket

(define (range n) (if (eq? n 1) (list 1) (append (range (- n 1)) (cons n `()))))

;将整数乘以列表
(define (mul n m)
  (if (> (length m) 1) (cons (* n (car m)) (mul n (cdr m))) (list (* n (car m))))
  )

(define x (range 100))
(list-ref x 45)
(mul 3 x)

(define newdisplay (lambda (x) (begin (display x)(newline))))
(define tt (lambda args (for-each newdisplay args)))
(tt 'abc 'efg 'tomson)

;以begin开始的语句块，其中的语句将顺序执行，最后一项是函数的返回值
(define (fun x) (begin (display "abc") `(12 3 54) `("abcd"))

;x的值为`("abcd")
(define x (fun 6))

;map和for-each格式相同。map返回一个值，for-each没有返回值。

(map (lambda (x) (* x x)) ‘(1 2 3))

(map + ‘(1 3 5)‘ (2 4 6))
(map (lambda (x y) (* x y))‘(1 2 3)‘(2 4 6))

(define sum 0)
(for-each (lambda (x) (set! sum (+ sum x))) ‘(1 2 3 4))

(for-each (lambda (x) (begin (display (* 2 x)) (newline))) (list 2 4 6 2 12 65))

(apply + (list 1 3 5 6))


;字典数据结构
(define y (list (cons "Dict" "字典") (cons "test" "测试")))

(tcp-listen 1024 10 #t "127.0.0.1")


(define (swap) (let ((c y)) (set! y x) (set! x c) ))

;写文件
(define out (open-output-file some-file))
(display "hello world" out)
;(close-ouput-port out)