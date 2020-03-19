
import numpy as np

class Vertex:
    ind = 0
    degree = 0

    def __init__(self, index=0, deg=0):
        self.ind = index
        self.degree = deg
        self.neighbors = np.array([], Vertex)

    def AddNei (self, vert):
        np.insert(self.neighbors,vert)   
        self.degree += 1

    def GetDegree(self):
        return self.degree

    def GetIndex(self):
        return self.ind
    
    def RemoveNeigh(self, vert):
        np.delete(self.neighbors,vert)
        self.degree-=1

    def GetNeib(self):
        return self.neighbors

    def __del__(self):
        self.degree = 0
        self.neighbors.clear()


