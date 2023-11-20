from matplotlib import pyplot as plt
import numpy as np
import math

# ^y = A_phi . ^x


X_coordinates = []

for x_1 in range(20):
    for x_2 in range(20):
        X_coordinates.append([x_1-10, x_2-10])

X_coordinates = np.array(X_coordinates).T




A_1 = np.array([
    [math.cos(math.pi/4), -math.sin(math.pi/4)],
    [math.sin(math.pi/4),  math.cos(math.pi/4)]
])

A_2 = np.array([
    [2, 0],
    [0, 1]
])

A_3 = np.array([
    [3, -1],
    [1, -1]
])

Y_1 = A_1.dot(X_coordinates)
Y_2 = A_2.dot(X_coordinates)
Y_3 = A_3.dot(X_coordinates)

figure, axis = plt.subplots(1, 4)

s=1
axis[0].scatter(X_coordinates[0], X_coordinates[1], s=s)
axis[1].scatter(Y_1[0], Y_1[1], s=s)
axis[2].scatter(Y_2[0], Y_2[1], s=s)
axis[3].scatter(Y_3[0], Y_3[1], s=s)
for ax in axis:
    ax.set_xticks([])
    ax.set_yticks([])


plt.setp(axis, xlim=[-20, 20], ylim=[-20, 20])
plt.autoscale(False)
plt.show()