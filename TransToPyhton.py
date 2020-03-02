# -*- coding: utf-8 -*-


import random
import numpy as np



class Vertex() :
    ind = 0
    neighbors = []
    degree = 0

    def __init__(self, index=0, deg=0):
        self.ind = index
        self.degree = deg

    def AddNei (self, nindex):
        self.neighbors.append(nindex)
        self.degree += 1

    def GetDegree(self):
        return self.degree

    def GetIndex(self):
        return self.ind

    def GetNeib(self):
        return self.neighbors



class Tree():
  
    size_of_v = 0
    size_of_e = 0
    V = []
    E =[[]]
    max_deg_v = 0

    #Random Tree Generator. 
    def __init__(self, size):
        self.size_of_v = size
        self.size_of_e = size-1

        maximum_degree = 0
        much_left = self.size_of_e

        for i in range(0,size):
            self.V.append(Vertex(i,0))
            for j in range(0,size):
                self.E[i][j] = False
         

        size_A = random.randint(1,size-1)
        size_B = size - size_A

        A_index = 0
        B_index = size_A

        if size_A >= size_B:

            for i in range(B_index, size):
               
                # Index 'i' represents the B side.

               self.E[A_index][i] = True
               self.E[i][A_index] = True

               self.V[i].AddNei(A_index)
               self.V[A_index].AddNei(i)

               A_index+=1
               much_left-=1


            while much_left!=0 :

                if A_index == size_A:
                    A_index = 0

                x = random.randint(size_A,size-1) # x is an index for side B.

                if self.E[A_index][x] == True:
                    continue

                much_left-=1
                self.E[A_index][x] = True
                self.E[x][A_index] = True

                self.V[x].AddNei(A_index)
                self.V[A_index].AddNei(x)













      






