import pandas as pan
import numpy as np
import matplotlib.pyplot as plt

df = pan.read_csv(r'/home/codecubes/Bureau/cours/Cours/IA/TD4/iris_a.csv')
frame = pan.DataFrame(df,columns=["sepal length","petal length","class"])

#ax1 = frame[0:50].plot(kind="scatter",x="sepal length",y= "petal length",color = "red")
#frame[51:].plot(kind="scatter",x="sepal length",y= "petal length",color = "blue",ax = ax1    )

df["const"] = 1

df = df.sample(len(df),ignore_index=True)

T= df.loc[0:50, "class"].to_numpy()
X = df.loc[0:50, ["const", "sepal length", "petal length"]].to_numpy()
print(T,X)
X2 = df.loc[51:, ["const", "sepal length", "petal length"]].to_numpy()
print(len(X2))
z = np.linspace(4,8 , 10000)

# affichage pyplot des données de X et T

def perceptron(X,T):
    n = len(X)
    w = np.random.rand(len(X[0]))
    tau = 0
    eta = 0.01
    normeOmega = 1
    while normeOmega != 0 and tau < 10000:
        deltaW = np.zeros(3)
        normeOmega = 0
        for i in range(n):
            if T[i] * np.dot(w, X[i]) <= 0:
                normeOmega += 1
                deltaW += eta * T[i] * X[i]
        w += deltaW
        tau += 1
    return w

w = perceptron(X,T)
print(w)
plt.plot(X2[:, 1], X2[:, 2], "ro")
plt.plot(z, -w[0] / w[2] - (w[1] / w[2]) * z, "b")
plt.show()





