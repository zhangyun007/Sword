from flask import Flask
app = Flask(__name__)

@app.route('/')
def hello():
    return '您好, 欢迎使用“虚拟法庭”。该应用尝试为您遇到的问题做一个做一个判断，该判断基于作者的价值观，而并非依据现实中的法律。'