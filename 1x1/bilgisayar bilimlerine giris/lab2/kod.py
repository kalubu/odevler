import numpy as np

i = 0
j = 0
n = 3
rotation = "left"

M = [[1,3,5], [7,9,11], [13,15,17]]
R = [[0,0,0], [0,0,0], [0,0,0]]
if (rotation == "left"):
    for i in range(3):
        for j in range(3):
            R[n-j-1][i] = M[i][j]
            
elif (rotation == "right"):
    for i in range(3):
        for j in range(3):
            R[j][n-i-1] = M[i][j]
arr = np.array(R)
print(arr)
