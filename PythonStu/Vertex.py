
import numpy as np

class Vertex:
    ind = 0
    degree = 0
    neighbors = []

    def __init__(self, index=0, deg=0):
        self.ind = index
        self.degree = deg

    def AddNei (self, vert):
        self.neighbors.append(vert)   
        self.degree += 1

    def GetDegree(self):
        return self.degree

    def GetIndex(self):
        return self.ind
    
    def RemoveNeigh(self, vert):
        self.neighbors =  self.neighbors[self.neighbors != vert]
        self.degree-=1    

    def GetNeib(self):
        return self.neighbors
    

        


def AreNeighbors(v1: Vertex, vert: Vertex):     
   
    
    for v in v1.neighbors:
        if v.ind == vert.ind:
            return True
   
    for v in vert.neighbors:
         if v.ind == v1.ind:
             return True 
    
    return False



