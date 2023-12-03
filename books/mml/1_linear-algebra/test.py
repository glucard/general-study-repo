import numpy as np

B = np.array([
    [1,0],
    [0,1]
])

C = np.array([
    [1, 1],
    [1, -1]
])

A = np.array([
    [2, 1],
    [1, 2]
])

Ã = np.array([
    [3, 0],
    [0, 1]
])
x_coordinates = np.array([
    [3],
    [-2]
])

x = B.dot(A.dot(x_coordinates))
print(x)

x = C.dot(Ã.dot(x_coordinates))
print(x)
