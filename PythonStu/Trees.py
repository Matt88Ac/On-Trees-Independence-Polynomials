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
    
    max_deg_v = 0

    #Random Tree Generator:
    def __init__(self, size):

        if not size:
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
                self.V = np.array([], Vertex.Vertex)
                self.E = np.zeros((size, size))
                maximum_degree = 0


#  ************************************ End of __init__ ***************************************

    def SubGraph(self, index_to_remove : int, x_or_nx : bool):
        
        newT = Tree(0)
        newT.size_of_v = self.size_of_v
        newT.V = self.V
        
        newT.origin = self.origin
        
        newT.size_of_e = self.size_of_e
        
        maxi = 0

        if x_or_nx:  # T - x, xEV
            newT.size_of_v-=1
            newT.size_of_e -= self.Get_Max_Deg_Vert().GetDegree()
            newT.max_deg_v = 0
            
            for i in range(0,self.size_of_v):
                if newT.V[i].AreNeighbors(self.V[index_to_remove]) == True:
                    newT.V[i].RemoveNeigh(self.V[index_to_remove])
                    
                if newT.V[i].GetDegree() > maxi:
                    maxi = newT.V[i].GetDegree()
                    newT.max_deg_v = i
            
            newT.V = newT.V[newT.V != self.V[index_to_remove]]
            
            


        else: # T - N[x], xEV
            newT.size_of_v -= 1 + self.V[index_to_remove].GetDegree()
            
            tmpo_to_remove = []
                
            for i in range(0,self.origin):
                if newT.V[i].AreNeighbors(self.V[index_to_remove]) == True:
                    tmpo_to_remove.append(i)
                    newT.V = newT.V[newT.V != newT.V[i]]
            
                                
            i=0
            for v in newT.V:
                for index in tmpo_to_remove:
                    if v.AreNeighbors(self.V[index]) == True:
                        v.RemoveNeigh(self.V[index])
                
                if v.GetDegree() > maxi:
                    maxi = v.GetDegree()
                    newT.max_deg_v = i
                i+=1
                        

        return newT


    def BFS(self,size):
        
        
        color = np.zeros(size,int)
        num_of_nil = size
        num_of_e = 0
        color[0] = 1
        
        
        Que = []
        Que.append(0)
        
        while len(Que)!=0: 
            for i in range(0,self.size_of_v):
               if self.E[i][Que[0]] == True:
                   if color[i] == 0:
                       Que.append(i)
                       color[i] = 1
                       num_of_e+=1
                       num_of_nil-=1
            
            color[Que[0]] = 2
            Que.remove(Que[0])
          

        if num_of_nil!=1 or num_of_e!=self.size_of_e:
            return False
        return True
    
    


# ***************************** End Of BFS *************************************

    def Get_Max_Deg_Vert(self):
        return self.V[self.max_deg_v]
        
    
    def isKn(self):
        return self.size_of_e==self.size_of_v*(self.size_of_v-1)/2
    
    def print_rel(self):
        print("|V| = {0}".format(self.size_of_v))
        print("E = ")
        for i in range(0, self.size_of_v):
            for j in range(i, self.size_of_v):
                if self.E[i][j] == True:
                    print('[ V{0}, V{1} ], '.format(i,j))
                    
        
        


