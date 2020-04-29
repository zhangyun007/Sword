#lang Racket

(define zipcodes '(
 (96774 ookala hawaii)
 (90001 losangeles california)
 (90263 malibu california)
 (10044 newyork newyork)
 (87263 malibu california)
 ))

;第三项
(caddr (car zipcodes))

(define find 
	(lambda (x zipcodes)
		(if (eq? zipcodes `())
			`()			; 最后一项作为返回值，return `()
			(if (eq? x (caddr (car zipcodes)))    						
				(cons (car (car zipcodes)) (find x (cdr zipcodes)))	
				(find x (cdr zipcodes))
            ) 
		)
	)        
)
 
(find `california zipcodes)