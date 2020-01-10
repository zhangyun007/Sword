from pyglet.gl import *

# Direct OpenGL commands to this window.
window = pyglet.window.Window()

@window.event
def on_draw():
    glClear(GL_COLOR_BUFFER_BIT)
    glLoadIdentity()
    #gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0)
    
    #将立方体的八个顶点保存到一个数组里面
    vertex_list = [
        [-0.5, -0.5, -0.5],
        [0.5, -0.5, -0.5],
        [-0.5,  0.5, -0.5],
        [0.5,  0.5, -0.5],
        [-0.5, -0.5,  0.5],
        [0.5, -0.5,  0.5],
        [-0.5,  0.5,  0.5],
        [0.5,  0.5,  0.5]
    ]
    
    index_list = [
        [0, 2, 3, 1],
        [0, 4, 6, 2],
        [0, 1, 5, 4],
        [4, 5, 7, 6],
        [1, 3, 7, 5],
        [2, 6, 7, 3]
    ]
    
    #绘制的时候代码很简单
    glBegin(GL_QUADS);
    for i in range(6):         # 有六个面，循环六次
        for j in range(4):     # 每个面有四个顶点，循环四次
            glVertex3fv(vertex_list[index_list[i][j]]);
    glEnd();
    
pyglet.app.run()