# -*- coding: utf-8 -*-


import Trees as Tr
import Independence_Polys as IP

T = Tr.Tree(10)
T.print_rel()

P = IP.IndeP(10)

print(P.The_Polynom)
# print(P.The_Tree.print_rel())
# P.The_Polynom.show_graph(-10, 10)
# print(P.The_Polynom.roots())
