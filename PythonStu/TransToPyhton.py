# -*- coding: utf-8 -*-
import random
import Vertex
import numpy as np
import Queue



class Tree:

    size_of_v = 0
    size_of_e = 0
    V = np.array([], Vertex)
    E = None

    max_deg_v = 0

    #Random Tree Generator:
    def __init__(self, size):

        self.size_of_v = size
        self.size_of_e = size-1

        self.E = np.zeros((size,size))

        maximum_degree = 0
        much_left = self.size_of_e

        size_A = random.randint(1,size-1)
        size_B = size - size_A

        is_good = False


        while not is_good:

            for i in range(0,size):
               np.insert(self.V,Vertex(i,0))

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

                    if self.E[A_index][x]:
                        continue

                    much_left-=1

                    self.E[A_index][x] = True
                    self.E[x][A_index] = True

                    self.V[x].AddNei(A_index)
                    self.V[A_index].AddNei(x)

                    if self.V[x].degree > maximum_degree:
                        maximum_degree = self.V[x].degree
                        self.max_deg_v = x

                    if self.V[A_index].degree > maximum_degree:
                        maximum_degree = self.V[A_index].degree
                        self.max_deg_v = A_index

                    A_index+=1

# ************************* End Of 1st condition ************

            else :
                for i in range(0, size_A):

                    # Index 'i' represents the A side.

                   self.E[B_index][i] = True
                   self.E[i][B_index] = True

                   self.V[i].AddNei(B_index)
                   self.V[B_index].AddNei(i)

                   B_index+=1
                   much_left-=1


                while much_left!=0 :

                    if B_index == size:
                        B_index = size_A

                    x = random.randint(0,size_A-1) # x is an index for side A.

                    if self.E[B_index][x]:
                        continue

                    much_left-=1

                    self.E[B_index][x] = True
                    self.E[x][B_index] = True

                    self.V[x].AddNei(B_index)
                    self.V[B_index].AddNei(x)

                    if self.V[x].degree > maximum_degree:
                        maximum_degree = self.V[x].degree
                        self.max_deg_v = x

                    if self.V[B_index].degree > maximum_degree:
                        maximum_degree = self.V[A_index].degree
                        self.max_deg_v = B_index

                    B_index+=1

# ************************ End of 2nd Condition ******************************
            is_good = self.BFS(size)
            if not is_good:
                self.V = np.array([], Vertex)
                self.E = np.zeros((size, size))
                maximum_degree = 0


#  ************************************ End of __init__ ***************************************

    def SubGraph(self, index_to_remove : int, x_or_nx : bool):
        newT: Tree = self

        maxi = 0

        if x_or_nx:  # T - x, xEV

          newT.size_of_v -= 1
          newT.size_of_e -= 1 + self.V[index_to_remove].degree
          newT.V.remove(index_to_remove)










        if not x_or_nx: # T - N[x], xEV
            newT.size_of_v -= (1+self.V[index_to_remove].degree)
            newT.size_of_e = newT.size_of_v-1





    def BFS(self,size):
        
        
        color = np.zeros(size,int)
        num_of_nil = size
        num_of_e = 0
        color[0] = 1
        
        Q_index=0
        
        Que = []
        Que.append(0)
        
        while len(Que)!=0:
            
            for bol in self.E[Que[Q_index]]:
                
                if bol == True and 
            
            
        

        
                

        if num_of_nil!=1 or num_of_e!=self.size_of_e:
            return False
        return True
    
    


# ***************************** End Of BFS *************************************














