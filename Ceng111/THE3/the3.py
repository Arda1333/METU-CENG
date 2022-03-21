# -*- coding: utf-8 -*-
"""
Created on Sun Jan 31 16:36:48 2021

@author: Arda Çavuşoğlu
"""

def add_datum(datum, parent, tree): # This function adds datum such as price, amount or a child node to parent
	if parent == tree[0]:
		tree.append(datum)
	else:
		for i in range(1, len(tree)):
			if type(tree[i]) == list:
				add_datum(datum, parent, tree[i])

def find_root_node(part_list): # This function finds the root node of a part list
	root = part_list[0][0]
	changed = True
	while changed:
		changed = False
		for lst in part_list:
			for datum in lst:
				if type(datum) == tuple and datum[1] == root:
					root = lst[0]
					changed = True
	return root

def in_tree(node, tree): # This function returns True if node is in tree; otherwise None
	if node == tree[0]:
		return True
	else:
		for i in range(1, len(tree)):
			if type(tree[i]) == list and in_tree(node, tree[i]):
				return in_tree(node, tree[i])

def make_tree(part_list): # This function creates a tree from a part list
	tree = [find_root_node(part_list)] # The tree is initialised and the root node is added
	queue1 = part_list[:]
	queue2 = part_list[:] # I used 2 queues because I didn't want to modify the original list
	while queue1 != []:
		queue1 = queue2
		for nested_list in queue1:
			if in_tree(nested_list[0], tree):
				for i in range(len(nested_list)):
					if type(nested_list[i]) == tuple: 
						node = [nested_list[i][1], nested_list[i][0]] # The name of the part and the required amount are added here
						add_datum(node, nested_list[0], tree)
				if type(nested_list[-1]) == float: # The price of the part is added here
					add_datum(nested_list[-1], nested_list[0], tree)
				queue2.remove(nested_list) # Nodes that are added to the tree are removed from the queue
	return tree

def check_price(tree): # This function calculates the total price of a part list tree
	if type(tree[-1]) == float and type(tree[-2]) != str:
		return tree[-1] * tree[-2]
	elif type(tree[-1]) == float and type(tree[-2]) == str:
		return tree[-1]
	multiplier = 1
	total_price = 0
	for i in range(len(tree)):
		if type(tree[i]) == int:
			multiplier = tree[i]
		elif type(tree[i]) == list:
			total_price += check_price(tree[i])
		if i == len(tree) - 1:
			return multiplier * total_price

def check_parts(tree): # This function returns a nested list of basic parts and their required amounts from a part list tree
	if type(tree[-1]) == float and len(tree) == 3:
		return [[tree[1], tree[0]]]
	elif type(tree[-1]) == float and len(tree) == 2:
		return [[1, tree[0]]]
	multiplier = 1
	basic_parts = []
	for i in range(len(tree)):
		if type(tree[i]) == int:
			multiplier = tree[i]
		elif i == len(tree) - 1:
			basic_parts += check_parts(tree[i])
			for i in basic_parts:
				i[0] = i[0] * multiplier
		elif type(tree[i]) == list:
			basic_parts += check_parts(tree[i])		
	return basic_parts		


def calculate_price(part_list):
	tree = make_tree(part_list)
	return check_price(tree)


def required_parts(part_list):
	tree = make_tree(part_list)
	basic_parts = check_parts(tree)
	required = []
	for part in basic_parts: # Here the lists of parts are turned into tuples
		required.append(tuple(part))
	return required


def stock_check(part_list, stock_list):
	required = required_parts(part_list)
	short_parts = []
	for part in required:
		in_stock = False
		for item in stock_list:
			if part[1] == item[1]:
				if part[0] > item[0]:
					short_parts.append((part[1], part[0] - item[0]))
				in_stock = True
				break
		if not in_stock:
			short_parts.append((part[1], part[0]))
	return short_parts