#lang Racket

;ChezSchme�򿪻�����
(#%$assembly-output #t)

(integer? 12)
(real? 12.4)
(string? "abc")
(symbol? 'a)
(atom? 12)

(list? (cons 3 4))

;quote����'����ע��һ��()֮������ݡ�
(quote (+ 1 2))

;list����һ���б�, list��+����ϵͳ���ú���(procudre)
(list + 1 2)
(list (lambda x (+ x 1)) 3 4 list)

;(procedure? quote)�ᵼ���﷨����˵��quote�������ú�����Ҳ�����ǡ��ؼ��֡����ߡ������֡�
(procedure? list)
(procedure? values)
(procedure? +)

(define-values (x y) (values 1 2))

(define xy 123)
(define-values (get-x put-x!)
       (values
       (lambda () xy)
       (lambda (v) (set! xy v))))


;��begin��ʼ������,���е���佫˳��ִ��,���һ���Ǻ����ķ���ֵ 
; lambda������Ҳһ����
(define (fun x) (begin (display "abc") '(12 3 54) '("abcd")))
;x��ֵΪ`("abcd")
(define y (fun 6))


(define newdisplay (lambda (x) (begin (display x)(newline))))
(define tt (lambda args (for-each newdisplay args)))
(tt 'abc 'efg 'tomson)


(eval '(+ 1 2))
(apply + (list 1 3 5 6))


;�ֵ� -- һ�ֳ��������ݽṹ�� Python,JavaScript�ж��иýṹ
(define z (list (cons "Dict" "�ֵ�") (cons "test" "����")))


;��������
(define m 10)
(define n 12)
(define t)
(set! t m)
(set! m n)
(set! n t)


(define a (list 1 2 3 4))     ; a is '(1 2 3 4)

(define (list-set! list k val)
    (if (zero? k)
        (set-car! list val)
        (list-set! (cdr list) (- k 1) val)))

(list-set! a 2 100)           ; a is '(1 2 100 4)

(set-car! (list-tail a 2) 716)


(define new-table (make-vector 3 (make-vector 3 #f)))
(vector-set! (vector-ref new-table 0) 0 42) ; we modify a single position ...


;д�ļ�
(define out (open-output-file "some-file-1"))
(display "hello world" out)
;(close-ouput-port out)


;call/cc����������һ��������Ϊ���������ң���Ϊ�����ĺ���Ҳֻ����һ��������
(define fun (lambda (k) 5 4 (k (list 7 4 5)) 3 6))
(fun display)

;��ͨ�ĺ������ã����غ��������е����һ���б�ļ�����, ��call/cc���ã�������ú����ڼ�������һ���б�󷵻�������ͬʱ��ֹ�ú����ļ��㡣
;
(call/cc fun)

(call/cc (lambda (return)
        (for-each (lambda (x) (if (< x 0) (return x)))
                '(99 88 77 66 55))
        #t))
        
(call/cc (lambda (return)
         (for-each (lambda (x) (if (< x 0) (return x)))
                '(11 22 33 44 -55 66 77))
        #t))