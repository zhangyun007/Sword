#lang Racket

(integer? 12)
(real? 12.4)
(string? "abc")
(symbol? 'a)
(atom? 12)

(list? (cons 3 4))

;quote或者'用于注释一对()之间的内容。
(quote (+ 1 2))

;list构造一个列表, list和+都是系统内置函数(procudre)
(list + 1 2)
(list (lambda x (+ x 1)) 3 4 list)

;(procedure? quote)会导致语法错误，说明quote不是内置函数，也许算是“关键字”或者“保留字”
(procedure? list)
(procedure? values)
(procedure? +)

(define-values (x y) (values 1 2))

(define xy 123)
(define-values (get-x put-x!)
       (values
       (lambda () xy)
       (lambda (v) (set! xy v))))


;将整数乘以列表
(define (mul n m)
  (if (> (length m) 1) (cons (* n (car m)) (mul n (cdr m))) (list (* n (car m))))
  )

(define x (range 100))
(list-ref x 45)
(mul 3 x)



;以begin开始的语句块,其中的语句将顺序执行,最后一项是函数的返回值
(define (fun x) (begin (display "abc") '(12 3 54) '("abcd")))
;x的值为`("abcd")
(define y (fun 6))


(define newdisplay (lambda (x) (begin (display x)(newline))))
(define tt (lambda args (for-each newdisplay args)))
(tt 'abc 'efg 'tomson)


(eval '(+ 1 2))
(apply + (list 1 3 5 6))


;字典 -- 一种常见的数据结构， Python,JavaScript中都有该结构
(define z (list (cons "Dict" "字典") (cons "test" "测试")))


;交换变量
(define m 10)
(define n 12)
(define t)
(set! t m)
(set! m n)
(set! n t)


;写文件
(define out (open-output-file "some-file-1"))
(display "hello world" out)
;(close-ouput-port out)