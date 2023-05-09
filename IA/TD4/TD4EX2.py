import numpy as np
import matplotlib.pyplot as plt

# Créer un échantillon

X1 = [0.5,0.4,0.4,2.3,2.1,2.2]
X2 = [3,3,4,5,5,4.5]

X= np.array([[1,0.5,3],[1,0.4,3],[1,0.4,4],[1,2.3,5],[1,2.1,5],[1,2.2,4.5]])
T = np.array([1,1,1,-1,-1,-1])

plt.plot(X1,X2,'o')

def f(X):
    return [5 - 0.5*X[i] for i in range(len(X))]

def perceptron(X,T):
    w = np.random.randn(len(X[0]))
    print(w)
    eta = 0.001
    max_iter = 0
    k = 1
    while max_iter < 10000:
        k = 0
        dw = [0,0,0]
        for i in range(len(X[0])):
            if T[i]*np.dot(w,X[i]) < 0:
                k += 1
                dw = dw + eta * T[i] * X[i]
        max_iter += 1
        w = w + dw
    print(max_iter)
    return w

def afficher(Z,w):
    print(w)
    plt.plot(Z,[-w[0]/w[2]-(w[1]/w[2])*z for z in Z])
    plt.show()


Z = np.linspace(0, 3, 100)
afficher(Z,perceptron(X,T))


