# -*- coding: utf-8 -*-
"""
Created on Sun Jan 31 19:50:39 2021

@author: Arda Çavuşoğlu
"""
from the3 import *
from inputs import *

part_list = [["bike", (2, "wheel"), (1, "frame")], ["wheel", (1, "rim"), (1, "spoke"), (1, "hub")], ["rim", 60.0], ["spoke", 120.0], ["hub", (2, "gear"), (1, "axle")], ["gear", 25.0], ["axle", (5, "bolt"), (7, "nut")], ["bolt", 0.1], ["nut", 0.15], ["frame", (1, "rearframe"), (1, "frontframe")], ["rearframe", 175.0], ["frontframe", (1, "fork"), (2, "handle")], ["fork", 22.5], ["handle", 10.0]]
stock_list = [(2, "rim"), (2, "spoke"), (4, "gear"), (8, "bolt"), (12, "nut"), (1, "rearframe"), (1, "fork"), (1, "handle")]
#tree = make_tree(part_list1)
#print(tree)
#print(calculate_price(part_list8))
#print(required_parts(part_list8))
#print(stock_check(part_list8, stock_list8))
#print(part_list1)

#def prev_make_tree(part_list):
#	tree = [find_root_node(part_list)] # The tree is initialised and the root node is added
#	for nested_list in part_list:
#		for i in range(len(nested_list)):
#			if type(nested_list[i]) == tuple: 
#				node = [nested_list[i][1], nested_list[i][0]] # The name of the part and the required amount are added here
#				add_datum(node, nested_list[0], tree)
#		if type(nested_list[-1]) == float: # The price of the part is added here
#			add_datum(nested_list[-1], nested_list[0], tree)
#	return tree
