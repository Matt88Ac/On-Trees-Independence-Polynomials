# -*- coding: utf-8 -*-
import random
import Vertex
import numpy as np


class Tree:

    size_of_v = 0
    size_of_e = 0
    V = np.array([], Vertex.Vertex)
    E = None
    origin = 0
    
    max_deg_v = None

    #Random Tree Generator:
    def __init__(self, size):

        if size == 0:
            return
        
        self.size_of_v = size
        self.size_of_e = size-1
        
        self.origin = size

        self.E = np.zeros((size,size))

        maximum_degree = 0
        much_left = self.size_of_e

        size_A = random.randint(1,size-1)
        size_B = size - size_A

        is_good = False


        while not is_good:

            for i in range(0,size):
              self.V =  np.insert(self.V,i,Vertex.Vertex(i,0))
           
            A_index = 0
            B_index = size_A

            if size_A >= size_B:

                for i in range(B_index, size):

                    # Index 'i' represents the B side.

                   self.E[A_index][i] = True
                   self.E[i][A_index] = True

                   self.V[i].AddNei(A_index)
                   self.V[A_index].AddNei(i)

                  
                   much_left-=1
                   
                   if self.V[A_index].degree > maximum_degree:
                        maximum_degree = self.V[A_index].degree
                        self.max_deg_v = self.V[A_index]
                      
                   if self.V[i].degree > maximum_degree:
                        maximum_degree = self.V[i].degree
                        self.max_deg_v = self.V[i]
                  
                   A_index+=1

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
                        self.max_deg_v = self.V[x]

                    if self.V[A_index].degree > maximum_degree:
                        maximum_degree = self.V[A_index].degree
                        self.max_deg_v = self.V[A_index]

                    A_index+=1

# ************************* End Of 1st condition ************

            else :
                for i in range(0, size_A):

                    # Index 'i' represents the A side.

                   self.E[B_index][i] = True
                   self.E[i][B_index] = True

                   self.V[i].AddNei(B_index)
                   self.V[B_index].AddNei(i)
                   
                   if self.V[B_index].degree > maximum_degree:
                        maximum_degree = self.V[B_index].degree
                        self.max_deg_v = self.V[B_index]
                        
                   if self.V[i].degree > maximum_degree:
                        maximum_degree = self.V[i].degree
                        self.max_deg_v = self.V[i]
                  
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
                        self.max_deg_v = self.V[x]

                    if self.V[B_index].degree > maximum_degree:
                        maximum_degree = self.V[B_index].degree
                        self.max_deg_v = self.V[B_index]

                    B_index+=1

# ************************ End of 2nd Condition ******************************
            is_good = self.BFS(size)
            if not is_good:
                self.V = np.array([], Vertex.Vertex)
                self.E = np.zeros((size, size))
                maximum_degree = 0
                


#  ************************************ End of __init__ ***************************************

    def SubGraph(self, index_to_remove : Vertex.Vertex, x_or_nx : bool): 
        
        newT = Tree(0)
        newT.size_of_v = self.size_of_v
      
        newT.V = np.array(self.V,Vertex.Vertex)
        #newT.V = self.V
        newT.origin = self.origin
        newT.size_of_e = self.size_of_e
        newT.max_deg_v = newT.V[0]
        
        maxi = 0

        if x_or_nx:  # T - x, xEV
            
            for v in newT.V:
                if v.AreNeighbors(index_to_remove.ind) == True:
                    v.RemoveNeigh(index_to_remove.ind)
                    newT.size_of_e-=1
                    
                if v.GetDegree() > maxi:
                    maxi = v.GetDegree()
                    newT.max_deg_v = v
            
            newT.V = newT.V[newT.V != index_to_remove]
            newT.size_of_v-=1
            


        else: # T - N[x], xEV
            newT.size_of_v -= 1
            
            tmpo_to_remove = []
                
            for v in newT.V:
                if v.AreNeighbors(index_to_remove.ind) == True:
                    tmpo_to_remove.append(v.ind)
                    newT.V = newT.V[newT.V != v]
                    newT.size_of_v -= 1
            
            
            newT.V = newT.V[newT.V != index_to_remove.ind]                    
            for v in newT.V:
                for index in tmpo_to_remove:
                    if v.AreNeighbors(index) == True:
                        v.RemoveNeigh(index)
                        newT.size_of_e -=1
                
                if v.GetDegree() > maxi:
                    maxi = v.GetDegree()
                    newT.max_deg_v = v
                        

        return newT


    def BFS(self,size):
        color = np.repeat(0,self.size_of_v)
        num_of_nil = size
        num_of_e = 0
        color[0] = 1
        
        
        Que = []
        Que.append(0)
        Q_index = 0
        
        while Q_index<self.size_of_v and Q_index < len(Que): 
            for i in range(0,self.size_of_v):
               if self.E[i][Que[Q_index]] == True and color[i] == 0:
                   Que.append(i)
                   color[i] = 1
                   num_of_e+=1
                   num_of_nil-=1
            
            color[Que[Q_index]] = 2
            Q_index+=1
          
        if num_of_nil!=1 or num_of_e!=self.size_of_e:
            return False
        return True
    
    


# ***************************** End Of BFS *************************************
        
    
    def isKn(self):
        return self.size_of_e==self.size_of_v*(self.size_of_v-1)/2
    
    def print_rel(self):
        print("|V| = {0}".format(self.size_of_v))
        print("E = ")
        for i in range(0, self.size_of_v):
            for j in range(i, self.size_of_v):
                if self.E[i][j] == True:
                    print('[ V{0}, V{1} ], '.format(i,j))
                    
        
        


