# Scheme Interpreter in Python

# I am changing this from Peter Norvig, 2010-16, http://norvig.com/lispy.html

from __future__ import division
import math
import operator as op
import builtins

Bool = bool
String = str          			# A Lisp String is implemented as a Python str
Number = (int, float) 	        # A Lisp Number is implemented as a Python int or float
# List中可以包含List、Number、String、Bool
List   = list         			# A Lisp List is implemented as a Python list
Dict   = dict

isa = isinstance


# 跳出for while循环体，找到外层的while或者for循环。
# (while (< i 20) (begin (print (* 2 i)) (if (= i 15) break) (set i (+ i 2))))
def break_fun(x, y):
    pass

# 从当前函数返回
def return_fun(x, y):
    pass

              
    
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
        # 得到字符串列表
        tmp = parse(input(prompt))
        print(tmp)
        
        # 为每一项赋予其类型
        val = eval(tmp, env_g)
        if val is not None: 
            print(lispstr(val))

def lispstr(exp):
    "Convert a Python object back into a Lisp-readable string."
    if isinstance(exp, List):
        return '(' + ' '.join(map(lispstr, exp)) + ')' 
    else:
        return str(exp)

# 每个过程中包括其定义的变量，也就是env.
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

# 为什么begin是Scheme内置过程，而lambda和if不是内置过程呢？哪些是过程，哪些是关键字？
# 传入env参数是列表或者字典的指针


# env中有两个变量，其中my存放函数执行时新增的变量；father指向上层环境变量。
# 查找变量时，必须沿着叶子节点一直找到根。
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
        while True:
            if var in e.my.keys():
                return e.my[var]
            else:
                e = e.father
            # 只有env_g的father为None
            if e == None:    
                return None
                    
env_g = env(None);

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
        'car':     lambda x: x[0],
        'cdr':     lambda x: x[1:], 
        'list':    lambda *x: list(x), 
        # 考虑用[]实现列表下标
        'list-ref':lambda x, y: x[y], 
		'append':  op.add,  	# 连接两个列表
		'length':  len, 		# 列表长度
		'map':     map,
		'print':   print,
		'exit':	   exit,
        'begin':    lambda *x: x[-1],   # (begin (...) (...) (...)) 返回最后一项
        'procedure?': callable,
        'null?':   lambda x: x == [], 
		'number?': lambda x: isa(x, Number),   
        'string?': lambda x: isa(x, String),
		'list?':   lambda x: isa(x, List), 
        'dict?':    lambda x: isa(x, Dict),
})

env_g.my.update(vars(math)) # sin, cos, sqrt, pi, ...
 
# x： 待解析的list
# e:  env对象
def eval(x, e):
    
    while True:
        if x == []:
            return
            
        # 函数调用
        if isa(x, List):
            
            # 处理多余的括号，使得 ((+ 3 4 ))也能算
            if len(x) == 1 and isa(x[0], List):
                return eval(x[0], e)
                
            # 打印当前的环境。
            if x[0] == 'env':
                for i in e.my.keys():
                    print(i, " : ", e.my[i])
            
            elif x[0] == 'define':
                # 定义函数
                
                # 定义变量
                if x[1] not in e.my.keys():
                    e.my[x[1]] = eval(x[2], e)
                else:
                    print("Error Message: define [" + x[1] + "] again.")
            
            elif x[0] == 'set':
                if x[1] in e.my.keys():
                    e.my[x[1]] = eval(x[2], e)
                else:
                    print("Error Message: [" + x[1] + "] not define.")
            
            elif x[0] == 'lambda':
                # (define a (lambda x (print x)))
                # (lambda parms body)
                return Procedure(x[1], x[2], e)
                
            elif x[0] == 'if':
                #(if (test) (conseq) (alt)) 
                if eval(x[1], e) == True:
                    return eval(x[2], e)
                else:
                    if len(x) == 4:
                        return eval(x[3], e)
               
            elif x[0] == 'while':
                # (define i 12)
                # (while (< x 40) (begin (print x) (set x (+ x 1))))
                if (len(x) != 3):
                    print("Error Message: [while] needs 2 args.")
                while eval(x[1], e):
                    eval(x[2], e)
                    
            elif x[0] == 'for':
            
                #      (define i 0)
                # (for (set i 0) (< i 100) (set i (+ i 1)) ()) 
                if (len(x) != 5):
                    print("Error Message: [for] needs 4 args.")
                    
                eval(x[1], e)
                while True:
                    if eval(x[2], e) == True:
                        eval(x[4], e)
                    else:
                        break
                    eval(x[3], e)     # (+ i 1) 
        
            else:
                proc = find(x[0], e)
                if proc:
                    args = []
                    for i in x[1:]:
                        args = args + [eval(i, e)]
                    return proc(*args)
                else:
                    print("Error Message: Procedure ", x[0], " not define.")
            
        if isa(x, String):
            #如果x在环境变量里，那么很可能是一个变量，而不是字符串。
            value = find(x, e)
            if value != None:
                return value
            else:
                return x
                
        return x   

repl()