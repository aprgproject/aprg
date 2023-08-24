import numpy as np
import matplotlib.pyplot as plt

graph_dimensions = (7, 7,)  # in inches
figure = plt.figure(figsize=graph_dimensions)
axes = plt.axes(projection='3d')

# Data for a three-dimensional line
# z_line = np.linspace(0, 15, 1000)
# x_line = np.sin(z_line)
# y_line = np.cos(z_line)
# axes.plot3D(x_line, y_line, z_line, 'gray')

# Data for three-dimensional scattered points
# z_data = 15 * np.random.random(100)
# x_data = np.sin(z_data) + 0.1 * np.random.randn(100)
# y_data = np.cos(z_data) + 0.1 * np.random.randn(100)
# axes.scatter3D(x_data, y_data, z_data, c=z_data, cmap='Greens')

# Three-dimensional Contour Plots


def function_to_graph(x_value, y_value):
    return np.sin(np.sqrt(x_value ** 2 + y_value ** 2))


x = np.linspace(-6, 6, 30)
y = np.linspace(-6, 6, 30)

X, Y = np.meshgrid(x, y)
Z = function_to_graph(X, Y)

# ax.contour3D(X, Y, Z, 50, cmap='binary')
axes.plot_surface(X, Y, Z, rstride=1, cstride=1,
                  cmap='viridis', edgecolor='none')
axes.set_xlabel('x')
axes.set_ylabel('y')
axes.set_zlabel('z')
plt.show()
plt.savefig('3d_graph.png')
# save with transparent background useful when doing presentations
# plt.savefig('3d_graph.png', transparent=True)
