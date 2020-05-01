;#lang Racket

(integer? 12)
(real? 12.4)
(string? "abc")

(symbol? 'a)
(atom? 12)

;返回结果3
(+ 1 2)

;'，要么引用单个变量，表示一个符号；要么引用一个(...)，表示列表 我认为这两种情况可以分开，用两个关键词区分，更为明显。
;quote意为引用,如果之后跟一个(...),直接返回列表,不对其进行计算。
(quote (+ 1 2))

;list构造一个列表, list和+都是系统内置函数(procudre)
(list + 1 2)
(list (lambda x (+ x 1)) 3 4 list)

(procedure? list)
(procedure? values)
(procedure? +)

;注意cons和append的区别：前者构造一个pair，两个参数分别为左右部；后者将第一个参数的最后一项和第二个参数构造一个pair，作为原list的最后一项。
(cons (list 1 2) 3)
(define a (append (list 1 2) 3))
;返回#f，也许错了，应该返回#t。
(list? a)

(define-values (x y) (values 1 2))

(define xy 123)
(define-values (get-x put-x!)
       (values
       (lambda () xy)
       (lambda (v) (set! xy v))))

;(procedure? quote)会导致语法错误，说明quote不是内置函数，也许算是“关键字”或者“保留字”

(define (range n) (if (eq? n 1) (list 1) (append (range (- n 1)) (cons n '()))))

;初始值和停止条件,为什么两个小括号?
(do ((i 0 (+ i 1)))     ; 初始值和 step 条件
    ((> i 4))			; 停止条件,取值为 #f 时停止
    (display i)       	; 循环主体 (命令)
)

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


;map和for-each格式相同。map返回一个值,for-each没有返回值。

;三者都能运行。这里有问题：通常人们会希望少打几个字，而使用'。
(map (lambda (x) (* x x)) '(1 2 3))
(map (lambda (x) (* x x)) (quote (1 2 3)))
(map (lambda (x) (* x x)) (list 1 2 3))


(map + '(1 3 5) '(2 4 6))
(map (lambda (x y) (* x y)) '(1 2 3) '(2 4 6))

(define sum 0)
(for-each (lambda (x) (set! sum (+ sum x))) '(1 2 3 4))

(for-each (lambda (x) (begin (display (* 2 x)) (newline))) (list 2 4 6 2 12 65))

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