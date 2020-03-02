
import random


class Vertex():
    ind = 0
    neighbors =[]
    degree = 0

    def __init__(self, index=0, deg = 0):
        self.ind = index
        self.degree = deg
  
    def AddNei(self,Nindex):
        self.neighbors.append(Nindex) 
        self.degree+=1

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

    def __init__(self, size):
        self.size_of_v = size
        self.size_of_e = size-1

        for i in range(0,size):
            self.V.append(Vertex(i,0))

        size_A = random.randint(1,size-1)
        size_B = size - size_A


        if size_A >= size_B:










      




