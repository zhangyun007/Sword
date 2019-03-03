from flask import Flask
from flask_script import Manager #pip install flask-script
from flask import redirect
from flask import request
from flask import abort
from flask import render_template

app = Flask(__name__)
manager = Manager(app)

@app.route('/')
def hello_world():
    '''return 'Hello World!'''
    user_agent = request.headers.get('User-Agent')
    return '<p> youre browser is %s </p>' % user_agent

@app.route('/test')
def hello_test():
	return render_template('index.html')
	# return 'Hello Test!', 400
    # return redirect("http://www.baidu.com");

@app.route('/poem',methods=['POST','GET'])
def hello_poem():
    return render_template('poem.html')
    

@app.route('/user/<name>')
def user(name):
	return render_template('user.html', name = name)


@app.route('/user/<path:username>')
def show_user_profile(username):
    # show the user profile for that user
    return 'User %s' % username


@app.route('/post/<int:post_id>')
def show_post(post_id):
    # show the post with the given id, the id is an integer
    return 'Post %d' % post_id


@app.route("/add/<int:a>/<int:b>") 
def add(a, b): 
     return "%s" %  (a+b) 


print(app.url_map)
print(app.view_functions)

if __name__ == '__main__':
    manager.run()
