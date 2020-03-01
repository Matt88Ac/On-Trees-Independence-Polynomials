
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


   def __init__(self, size):
       self.
