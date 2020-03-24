# -*- coding: utf-8 -*-

import Independence_Polys as IP
P = IP.IndeP(10)

print(P.The_Polynom)
print(P.The_Tree.print_rel())
P.The_Polynom.show_graph(-10, 10)
print(P.The_Polynom.roots())


