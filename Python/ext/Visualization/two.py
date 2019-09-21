import matplotlib.pyplot as plt
from pylab import *

x = linspace(0, 5, 10)
y = x ** 2

fig, ax = plt.subplots()

ax.plot(x, x**2, label="y = x**2")
ax.plot(x, x**3, label="y = x**3")
ax.legend(loc=2); # upper left corner
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_title('title');

plt.show()