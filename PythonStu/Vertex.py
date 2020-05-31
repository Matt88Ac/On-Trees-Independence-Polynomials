import numpy as np


class Vertex():
    ind = 0
    degree = 0
    neighbors = np.array([], int)

    def __init__(self, index=0, deg=0):
        self.ind = index
        self.degree = deg

    def AddNei(self, vert: int):
        self.neighbors = np.insert(self.neighbors, 0, vert)
        self.degree += 1

    def GetDegree(self) -> int:
        return self.degree

    def GetIndex(self) -> int:
        return self.ind

    def RemoveNeigh(self, vert: int):
        self.neighbors = self.neighbors[self.neighbors != vert]
        self.degree -= 1

    def GetNeib(self):
        return self.neighbors

    def AreNeighbors(self, vert: int):
        for v in self.neighbors:
            if v == vert:
                return True
        return False
