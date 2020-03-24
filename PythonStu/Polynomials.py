# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt
from itertools import zip_longest

class Polynomial:
    
    coefficients = np.array([], int)
    
    def __init__(self, coef):
        self.coefficients = np.array(coef, int)
    
    def __repr__(self):
        return self.__str__(self)
    
    def __call__(self, x):    
        res = 0
        for coeff in self.coefficients:
            res = res * x + coeff
        return res 
    
    def degree(self):
        return len(self.coefficients)   
            
    def __add__(self, other):
        c1 = self.coefficients
        c2 = other.coefficients
        res = [sum(t) for t in zip_longest(c1, c2, fillvalue=0)]
        return Polynomial(res)
    
    def __sub__(self, other):
        c1 = self.coefficients
        c2 = other.coefficients
        
        res = [t1-t2 for t1, t2 in zip_longest(c1, c2, fillvalue=0)]
        return Polynomial(res)



    def __mul__(self, other):
        leng = self.degree() + other.degree()
        res = np.repeat(0,leng)
        
        for i in range(0, self.degree()):
            for j in range(0, other.degree()):
                res[i+j] += self.coefficients[i]*other.coefficients[j]
            
        return Polynomial(res)
        

    def derivative(self):
        derived_coeffs = []
        exponent = 1
        for i in range(1, len(self.coefficients)):
            derived_coeffs.append(self.coefficients[i] * exponent)
            exponent += 1
        return Polynomial(derived_coeffs)
    
    def __str__(self):
        res = ""     
        for i in range(0, len(self.coefficients)):
            coeff = self.coefficients[i]
            if coeff == 0:
                continue
           
            if i == 0: 
                if coeff < 0:
                    res += " - " +  str(coeff)
                else:
                    res +=  str(coeff)
            
                
            elif i == 1:   
                if coeff == 1:
                    res+= " + X"
                
                elif coeff < 0:
                    res += " - " +  str(-coeff) + "X" 
                else:
                    res += " + " +  str(coeff) + "X"
            
         
            else:
                if coeff == 1:
                    res+= " + X^" + str(i) 
                
                elif coeff < 0:
                    res += " - " +  str(-coeff) + "X^" + str(i)
                else:
                    res += " + " +  str(coeff) + "X^" + str(i)

        return res
    
    def show_graph(self, beg, end):
        X = np.linspace(beg,end)
        F = self(X)
        plt.plot(X,F)
        plt.show()
        
        
     


        
        
        
        
        
        
    