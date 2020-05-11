# Scheme Interpreter in Python

# I am changing this from Peter Norvig, 2010-16, http://norvig.com/lispy.html

from __future__ import division
import math
import operator as op
import datetime


Bool = bool
String = str          			# A Lisp String is implemented as a Python str
Number = (int, float) 	        # A Lisp Number is implemented as a Python int or float
# List中可以包含List、Number、String、Bool
List   = list         			# A Lisp List is implemented as a Python list
Tuple  = tuple
Dict   = dict
    

isa = isinstance

# env中有两个变量，其中my存放 [块/函数] 计算时新定义的变量；father指向上层环境变量。
# 查找变量时，必须沿着叶子节点my一直找到根（None）。
class env:
    def __init__(self, fa):
        self.my = {}
        self.father = fa

def find(var, e):
    #print(var)
    #print(e.my.keys())
    if var in e.my.keys():
        return e.my[var]
    else:
        e = e.father
        while e != None:
            if var in e.my.keys():
                return e.my[var]
            else:
                e = e.father
        return None
        
env_g = env(None);

# (call/cc (lambda k (* 5 (k 8) 45)))

# (call/cc (lambda (k) (begin 5 4 (k (list 7 4 5)) 3 6)))

# (call/cc (lambda (k) (begin (define i 0)(while (< i 10)(begin (if (= i 6)(k 123)(begin (print i) (set i (+ i 1)))))))))

# callcc函数里定义一个throw函数, throw作为proc的参数

def callcc(proc):
    "Call proc with current continuation; escape only"
    ball = RuntimeWarning("Sorry, can't continue this continuation any longer.")
    def throw(retval): 
        ball.retval = retval; 
        raise ball
    try:
        return proc(throw)
    except RuntimeWarning as w:
        if w is ball: return ball.retval
        else: raise w


# 环境变量（全局变量），用户可以修改。
env_g.my.update({
        '+':op.add, '-':op.sub, '*':op.mul, '/':op.truediv, 
        '>':op.gt, '<':op.lt, '>=':op.ge, '<=':op.le, '=':op.eq, 
		'not':     op.not_,
		'eq?':     op.is_, 
        'equal?':  op.eq, 
		'max':     max,
        'min':     min,
        'abs':     abs,
		'round':   round,
        
        'tuple':   lambda *x: tuple(x),
        'dict':    lambda x: dict(x),
        
        'car':     lambda x: x[0],
        'cdr':     lambda x: x[1:], 
        'list':    lambda *x: list(x), 
        # 考虑用[]实现列表下标
        'list-ref':lambda x, y: x[y], 
		
        'append':  op.add,  	# 连接两个列表
		'len':     len, 		# 列表长度
		'map':     map,
		'print':   print,
		'exit':	   exit,
        
        'open':    lambda *x: open(x[1:]),
                
        'call/cc': callcc,
        'procedure?': callable,
        'null?':   lambda x: x == [], 
		'number?': lambda x: isa(x, Number),   
        'string?': lambda x: isa(x, String),
		'list?':   lambda x: isa(x, List), 
        'struct?': lambda x: True,
        'dict?':   lambda x: isa(x, Dict),
        
        'dir':     dir,
        'type':    type,
        '.':       lambda x, y: x.y, 
        
        'int': {}
})

env_g.my.update(vars(math)) # sin, cos, sqrt, pi, ...
        
def parse(program):
    "Read a Scheme expression from a string."
    return read_from_tokens(tokenize(program))

def tokenize(s):
    "Convert a string into a list of tokens."
    return s.replace('(',' ( ').replace(')',' ) ').split()

def read_from_tokens(tokens):
    "Read an expression from a sequence of tokens."
    if len(tokens) == 0:
        repl()
    token = tokens.pop(0)
    if '(' == token:
        L = []
        while tokens[0] != ')':
            L.append(read_from_tokens(tokens))
        tokens.pop(0) # pop off ')'
        return L
    elif ')' == token:
        raise SyntaxError('unexpected )')
    else:
	    # 这里将字符串转成具体的数据类型，
        return atom(token)

def atom(token):
	# 注意，转换次序。
    try: 
        return int(token)
    except ValueError:
        try: 
            return float(token)
        except ValueError:
            if token == "True" or token == "False":
                return Bool(token)
            else:
                return String(token)

# call this to entery Interaction.

def repl(prompt='ZhScheme> '):
    "A prompt-read-eval-print loop."
    while True:
        # 读取输入，并解析，得到字符串列表
        tmp = parse(input(prompt))
        print(tmp)
        
        # 分析列表的意义，并计算。
        val = eval(tmp, env_g)
        
        # 打印计算结果
        if val is not None: 
            print(val)
            #print(lispstr(val))

def lispstr(exp):
    "Convert a Python object back into a Lisp-readable string."
    if isinstance(exp, List):
        return '(' + ' '.join(map(lispstr, exp)) + ')' 
    else:
        return str(exp)

# 函数可能有返回值，也可能返回None，也就是没有返回值。
class Procedure(object):
    "A user-defined Scheme procedure."
    def __init__(self, parms, body, e):
        self.parms, self.body, self.e = parms, body, e
    def __call__(self, *args): 
        # parms是形参，args是实参
        for i in range(len(self.parms)):
            self.e.my[self.parms[i]] = args[i]
        
        # 函数体内定义的变量，存在c.my中，只在函数内可见。
        c = env(self.e);
        return eval(self.body, c)

 
# x： 待解析的list
# e:  env对象

# 可能返回一个bool,int,float,string,list或者None

def eval(x, e):
    
    if isa(x, List):
        if x == []:
            return
                
        # 哪些是全局过程，哪些是关键字？
        # 如果希望利用Python内置过程，则放进env_g里。
        # 当计算一个list可能需要递归时（需要传入新的环境），则当作关键字处理。
        
        # 用于注释
        elif x[0] == 'quote':
            return
            
        # 打印当前的环境。
        if x[0] == 'env':
        
            print("variables ...\n")
            for i in e.my.keys():
                print(i, " : ", e.my[i])
            
            return;
            
        elif x[0] == 'time':
        
            start = datetime.datetime.now()
            eval(x[1], e)
            end = datetime.datetime.now()    
            print(end - start)
         
        # type/racket
        # 整型变量 (int a) (int a 3)
        elif x[0] == 'int':
            return
            
        # 动态变量
        elif x[0] == 'define':                
            # 定义变量
            if x[1] not in e.my.keys():
                e.my[x[1]] = eval(x[2], e)
            else:
                print("Error Message: define [" + x[1] + "] again.")
            return
            
        elif x[0] == 'set':                
            # 为变量赋值
            if x[1] in e.my.keys():
                e.my[x[1]] = eval(x[2], e)
            else:
                print("Error Message: [" + x[1] + "] not define.")
            return
            
        # (set-list x 2 12)   设置列表的某一项       
        elif x[0] == 'set-list':
            if len(x) != 4:
                print("Error Message: [set-list] need 4 args.")
                return
            
            a = eval(x[1], e)
            b = eval(x[2], e)
            c = eval(x[3], e)
            
            if isa(a, List):
                a[b] = c
            else:
                print("Error Message: argument 1 must be a list.")
            return
                
        # (begin (...) (...) (...)) 依次执行
        elif x[0] == 'begin':
            for i in range(len(x)):
                if i == len(x) - 1:
                    # 返回最后一项
                    return eval(x[i], e)
                else:
                    eval(x[i+1], e)
            return

        elif x[0] == 'lambda':
            # (define a (lambda x (print x)))
            # (lambda parms body)
            if len(x) != 3:
                print("Error Message: [lambda] needs 2 args.")
                return 
            return Procedure(x[1], x[2], e)
            
        elif x[0] == 'if':
            #(if (test) (conseq) (alt)) 
            if eval(x[1], e) == True:
                return eval(x[2], e)
            else:
                if len(x) == 4:
                    return eval(x[3], e)
            return
           
        #(while (< i 23) (begin (print i) (set i (+ i 1))(if (eq? i 12) (break))))
        elif x[0] == 'while':
        
            # (define i 12)
            # (while (< x 40) (begin (print x) (set x (+ x 1))))
            if (len(x) != 3):
                print("Error Message: [while] needs 2 args.")
                
            while eval(x[1], e):
                # 检测到break，很可能是跳出循环。
                if eval(x[2], e) == 'break':
                    break
            return
            
        # (for (set i 23) (< i 45) (set i (+ i 2)) (begin (print i) (if (eq? i 43) break)))
        elif x[0] == 'for':
        
            # (define i 0)
            # (for (set i 0) (< i 100) (set i (+ i 1)) ()) 
            if (len(x) != 5):
                print("Error Message: [for] needs 4 args.")
                
            eval(x[1], e)
            while True:
                if eval(x[2], e) == True:
                    tmp = eval(x[4], e)
                    if tmp == 'break':
                        break
                else:
                    break
                eval(x[3], e)     # (+ i 1) 步长
                
            return
        
        # 定义类以及数据成员(class point (list (list n 2)(list m (lambda x (* 2 x)))))
        
        elif x[0] == 'class':
            print(x[2])
            tmp = type(x[1],(object,),dict(eval(x[2], e)))
            dir(tmp)
            if x[1] not in e.my.keys():
                e.my[x[1]] = tmp
            else:
                print("Error Message: define [" + x[1] + "] again.")
            return
            
        elif x[0] == 'eval':           
            return
            
        elif x[0] == 'break':
            return 'break'
            
        elif x[0] == 'return':
            return 'return'
            
        else:               
            tmp = find(x[0], e)
            
            # 函数调用
            if callable(tmp):
                args = []
                for i in x[1:]:
                    args = args + [eval(i, e)]
                return tmp(*args)
                
            dir(tmp)
            # (point) 创造对象
            return tmp()
            
    if isa(x, String):
        #如果x在环境变量里，那么很可能是一个变量，而不是字符串。
        value = find(x, e)
        if value != None:
            return value
        else:
            return x
            
    return x   

repl()