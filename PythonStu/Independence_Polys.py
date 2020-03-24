# -*- coding: utf-8 -*-

import Polynomials as poly
import Trees as trs

class IndeP:
    The_Polynom = None
    The_Tree = None
    
    def __init__(self, size):
        
        self.The_Tree = trs.Tree(size)
        self.The_Polynom = self.ComputePOL(self.The_Tree) 

    def ComputePOL(self, tree = trs.Tree):
        
        if tree.size_of_v == 0:
            return poly.Polynomial([1])
        
        elif tree.isKn() == True:
            res = [1,tree.size_of_v]            
            return poly.Polynomial(res)
        
        
        temp=self.ComputePOL( tree.SubGraph(tree.max_deg_v, False))*poly.Polynomial([1,1])
        temp += self.ComputePOL(tree.SubGraph( tree.max_deg_v, True ))
               
        return temp

        
     

