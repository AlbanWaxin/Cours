import Agent as ag
import random as rd
import time

pos = [ag.loc_A, ag.loc_B]
etat = ['Clean', 'Dirty']

def testAgent():
    a = ag.ReflexVacuumAgent()
    for i in range(10000):
        percept = [rd.choice(pos), rd.choice(etat)]
        print(percept)
        time.sleep(0.01)
        print(a.program(percept))
testAgent()