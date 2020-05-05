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

# 环境变量（全局变量），用户可以修改。
env_g = {
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
}
env_g.update(vars(math)) # sin, cos, sqrt, pi, ...

a = dir(__builtins__)

# Parsing: parse, tokenize, and read_from_tokens

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
        tmp = parse(input(prompt))
        print(tmp)
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
    def __init__(self, parms, body, env):
        self.parms, self.body, self.env = parms, body, env
    def __call__(self, *args): 
        # parms是形参，args是实参
        for i in range(len(self.parms)):
            self.env[self.parms[i]] = args[i]
        return eval(self.body, self.env)

# 为什么begin是Scheme内置过程，而lambda和if不是内置过程呢？哪些是过程，哪些是关键字？
# 传入env参数是列表或者字典的指针

def eval(x, env):
    while True:
        if x == []:
            return
        # 可能是字符串常量或者变量名，怎么区分处理？
        if isa(x, String):
            #如果x在环境变量里，那么很可能是一个变量，而不是字符串。
            if x in env.keys():
                return env[x]          
            return x
        elif not isa(x, List):
            return x   
        if x[0] in keywords.keys():
            return keywords[x[0]](x, env)
        else:
            return other_fun(x, env)

def env_fun(x, y):
    print(y)

# 跳出for while循环体
# (while (< i 20) (begin (print (* 2 i)) (if (= i 15) break) (set i (+ i 2))))
def break_fun(x, y):
    pass

# 从当前函数返回
def return_fun(x, y):
    pass

# x传入列表，y传入env
def define_fun(x, y):
    (_, name, exp) = x
    if name not in y.keys():
        y[name] = eval(exp, y)
    else:
        print("Error Message: define [" + name + "] again.")
        
def set_fun(x, y):
    (_, name, exp) = x
    if name in y.keys():
        y[name] = eval(exp, y)
    else:
        print("Error Message: [" + name + "] not define.")

# (if test conseq alt)
def if_fun(x, y):
    (_, test, conseq, alt) = x
    if eval(test, y) == True:
        return eval(conseq, y)
    else:
        if alt != None:
            return eval(alt, y)
        
# (define i 12)
# (while (> i 3) (....))
def while_fun(x, y):
    if (len(x) != 3):
        print("Error Message: [while] needs 2 args.")
    while eval(x[1], y):
        eval(x[2], y)
        
#      (define i 0)
# (for (set i 0) (< i 100) (set i (+ i 1)) ()) 
def for_fun(x, y):
    if (len(x) != 5):
        print("Error Message: [for] needs 4 args.")
    eval(x[1], y)
    while True:
        if eval(x[2], y) == True:
             eval(x[4], y)
        else:
            break
        eval(x[3], y)     # (+ i 1) 

# (define a (lambda x (print x)))
# (lambda parms body)
def lambda_fun(x, y):
    (_, parms, body) = x
    return Procedure(parms, body, y)

# (proc ....) 用户定义函数，用该函数处理
def other_fun(x, y):
    proc = eval(x[0], y)
    args = [eval(exp, y) for exp in x[1:]]
    return proc(*args)

keywords = {
    'env':      env_fun,
    'break':    break_fun,
    'return':   return_fun,
    'define':   define_fun,
    'set':      set_fun,
    'if':       if_fun,
    'while':    while_fun,
    'for':      for_fun,
    'lambda':   lambda_fun,
}

repl()