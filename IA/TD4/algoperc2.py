# A. Hafiane, INSA CVL,
# cours STI 3A

import numpy as np
import matplotlib.pyplot as plt
import pandas as pnd


#------------------------#
# Algo perceptron        #         
#------------------------#
def perce(X,t,eta, seuil,max_iter):
    N,D=np.shape(X)
 
    w=np.random.normal(0,1,D+1) #(w[0],w[1],w[2],...,w[D])
    nb_iter= 0          # compteur d'iterations
    mal_classe=seuil+1  # initialisation du nombre de points mal classes

    while(mal_classe>seuil) and (nb_iter<max_iter):
        nb_iter=nb_iter+1
        mal_classe=0
        Dw=np.zeros(D) # initialisation du delta du gradient
        Dw0=0
        for i in range(0,N):
	    	#y = w0 + w[1]*X[i,1]+w[2]X[i,2]....
            # si on veut faire une fonction d'activation
            # f = np.tanh(np.dot(w[1:D+1],X[i,:])+w[0]), condition t[i]*f<0
            if(t[i]*(np.dot(w[1:D+1],X[i,:])+w[0])<0):
                mal_classe=mal_classe+1
                Dw =Dw-t[i]*X[i,:]  #calcul du changement
               	Dw0=Dw0-t[i]
        w[1:D+1]=w[1:D+1]-eta*Dw # mise a jour du vecteur W
        w[0]=w[0]-eta*Dw0
    print (w)
    return  w

#----------------------------------------#
# fonction calcul echantillon mal classe #         
#----------------------------------------#
def calcul_erreur(X,t,W):
    N,D=np.shape(X);
    w=W[1:D+1]
    w0=W[0]
    erreur=0; 
    for i in range(0,N):
        h = np.dot(w,X[i,:])+w0

        if h*t[i]<0:  # echantillon mal classe
            erreur=erreur+1

    return erreur/float(N), erreur # pourcentage d'erreur et nombre d'echantillons mal classes


#------------------------#
# preparation de donnees #         
#------------------------#

# lecture du fichier de donnees
A = pnd.read_csv("data.csv",header=None)
A = A.to_numpy()

X=A[:,0:4] # echantillons (vecteur)

t=A[:,4] # les labels ou les classes



# 50 % de donnees pour l'apprentissage
X_a=X[0:25]                 # 50% d'echantillon de la classe  +1
X_a=np.vstack((X_a,X[50:75])) # ajout au tableau 50%  d'echantillon de la classe -1

t1=t[0:25]                  # label classe +1    
t1=np.hstack((t1,t[50:75])) # label classe -1


#------------------------#
# apprentissage          #         
#------------------------#

#plt.scatter(X[0:50,1],X[0:50,2],color='b')
#plt.scatter(X[50:100,1],X[50:100,2],color='r')
#plt.show()
#print t1

eta = 0.01
seuil = 3
max_iter=1000; 

W = perce(X_a,t1,eta,seuil,max_iter)


#------------------------#
# evaluation de l'erreur #         
#------------------------#
X_b=X[26:50]                 # 50% d'echantillon de la classe  +1
X_b=np.vstack((X_b,X[76:100])) # ajout au tableau 50%  d'echantillon de la classe -1

t2=t[26:50]                  # label classe +1    
t2=np.hstack((t2,t[76:100])) # label classe -1


print (calcul_erreur(X_b,t2,W))
