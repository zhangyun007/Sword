# Scheme Interpreter in Python

# I am changing this from Peter Norvig, 2010-16, http://norvig.com/lispy.html

from __future__ import division
import math
import operator as op
import builtins

# Types

String = str          			# A Lisp String is implemented as a Python str
Number = (int, float, bool) 	# A Lisp Number is implemented as a Python int or float
# List中可以包含List、Number或者String
List   = list         			# A Lisp List is implemented as a Python list

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
        'list-ref':lambda x, y: x[y], 
		'append':  op.add,  	# 连接两个列表
		'length':  len, 		# 列表长度
		'map':     map,
		'print':   print,
		'exit':	   exit,
        'begin':    lambda *x: x[-1],   # (begin (...) (...) (...)) 返回最后一项
        'procedure?': callable,
        'null?':   lambda x: x == [], 
		'number?': lambda x: isinstance(x, Number),   
        'string?': lambda x: isinstance(x, String),
		'list?':   lambda x: isinstance(x,List), 
}
env_g.update(vars(math)) # sin, cos, sqrt, pi, ...
print(env_g)

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
	# 注意，转换次序。bool?
    try: 
        return int(token)
    except ValueError:
        try: 
            return float(token)
        except ValueError:
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

# 为什么begin是Scheme内置过程，而lambda和if不是内置过程呢？
# 哪些是过程，哪些是关键字？

isa = isinstance

def eval(x, env):
    while True:
        if x == []:
            return
        # 可能是字符串常量、变量名或者bool值(True和False)怎么区分处理？
        if isa(x, String):      # variable reference
            #如果x在环境变量里，那么很可能是一个变量，而不是字符串。
            if x in env.keys():
                return env[x]
            if x == "True" or x == "False":
                return bool(x)
          
            # 也可能是程序写错，用了未定义的变量。
            return x
        elif not isa(x, List):   # constant literal
            return x                
        elif x[0] == 'env':         # (env) 打印环境变量
            print(env)            
        # define 和 set定义赋值变量
        elif x[0] == 'define':         # (define name exp)
            (_, name, exp) = x
            print(name)
            if name not in env.keys():
                env[name] = eval(exp, env)
            else:
                print("Error Message: define [" + name + "] again.")
        elif x[0] == 'set!':           # (set! name exp)
            (_, name, exp) = x
            if name in env.keys():
                env[name] = eval(exp, env)
            else:
                print("Error Message: [" + name + "] not define.")
        elif x[0] == 'lambda':         # (lambda (name...) body)
            (_, parms, body) = x
            return Procedure(parms, body, env)
        elif x[0] == 'if':             # (if test conseq alt)
            (_, test, conseq, alt) = x
            exp = (conseq if eval(test, env) else alt)
            return eval(exp, env)
        # (for (define i 0) (< i 100) (+ i 1) ()) 
        # 返回最后一项的计算结果 -- 循环体
        elif x[0] == 'for':
            # for 循环体内使用公用一个新的env，
            if (len(x) != 5):
                print("Error Message: [for] needs 4 args.")
            # (define i 0)作为for程序块内部变量，上一层不可见。
            eval(x[1], env) 
            print(env)
            '''
            parse(x[3])
            while True:
                eval(x[3], env)
                if eval(x[2], env) == True:
                    '''
            proc = eval(x[4], env)                 # (proc arg...)
            print(proc)
            args = [eval(exp, env) for exp in x[1:]]
            return proc(*args)
        else:                          # (proc arg...)
            proc = eval(x[0], env)
            print(proc)
            args = [eval(exp, env) for exp in x[1:]]
            return proc(*args)
        return

repl()