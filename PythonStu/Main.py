# -*- coding: utf-8 -*-

import Polynomials as Poly
import numpy as np

p = Poly.Polynomial([1,1,1,0,7,8])
t = p.derivative()

print("P = ")
print(p)
print("T =")
print(t)

print("T+P = "); print(t+p)





arr = np.array([5,7,2,4,6], int)

yy = arr[::-1]


