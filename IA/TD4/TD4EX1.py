import numpy as np
import matplotlib.pyplot as plt

def descente_gradient(X,T,theta,tau,max_iter):
    assert len(X) == len(T)
    w = [abs(np.random.randn()) for i in range(len(X[0]))]
    while max_iter > 0:
        for i in range(len(X)):
            w = w + tau * (T[i]-(np.dot(X[i],w))) * X[i]
        max_iter -= 1
    return w


def afficher_regression(W, X, T):
    plt.plot([x[1] for x in X], T, 'o')
    print(W,X)
    f = lambda x: W[0]+W[1]*x
    L = [f(x) for x in [x[1] for x in X]]
    plt.plot([x[1] for x in X],L)
    plt.show()

X = np.array([[1,0.1],[1,0.2],[1,0.3],[1,0.3],[1,0.5],[1,0.4]])
T = np.array([3.5, 5.2, 4.5, 5.3,6.5,4.1])
theta = 0.0001
tau = 0.01
max_iter = 10000

afficher_regression(descente_gradient(X,T,theta,tau,max_iter), X, T)

