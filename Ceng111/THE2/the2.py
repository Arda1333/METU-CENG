#
# WRITE YOUR CODE HERE AND SEND ONLY THIS FILE TO US.
#
# DO NOT DEFINE get_data() here. Check before submitting

import math
import random
from evaluator import *    # get_data() will come from this import


universe = get_data()
uni_state = universe[6]
M = universe[0]
N = universe[1]
D = universe[2]
K = universe[3]
LAMBDA = universe[4]
MU = universe[5]
directions = ["Forward", "Forward Right", "Right", "Backward Right", "Backward", "Backward Left", "Left", "Forward Left"]
weight = [MU*(1/2), MU*(1/8), (1/2)*(1-MU-MU**2), (2/5)*(MU**2), (1/5)*(MU**2), (2/5)*(MU**2), (1/2)*(1-MU-MU**2), MU*(1/8)]

def move_person(direction, person, uni_state):
	""" 
	A helper function that updates person's coordinate according to direction
	"""
	global N, M
	ini_coordinate = person[0]
	last_move = person[1]
	move_table = [(0, 1), (-1, 1), (-1, 0), (-1, -1), (0, -1), (1, -1), (1, 0), (1, 1)]
	if direction == "Forward":
		person[0] = (ini_coordinate[0] + move_table[last_move][0], ini_coordinate[1] + move_table[last_move][1])
	elif direction == "Forward Right":
		person[0] = (ini_coordinate[0] + move_table[(last_move+1)%8][0], ini_coordinate[1] + move_table[(last_move+1)%8][1])
		person[1] = (last_move + 1) % 8
	elif direction == "Right":
		person[0] = (ini_coordinate[0] + move_table[(last_move+2)%8][0], ini_coordinate[1] + move_table[(last_move+2)%8][1])
		person[1] = (last_move + 2) % 8
	elif direction == "Backward Right":
		person[0] = (ini_coordinate[0] + move_table[(last_move+3)%8][0], ini_coordinate[1] + move_table[(last_move+3)%8][1])
		person[1] = (last_move + 3) % 8
	elif direction == "Backward":
		person[0] = (ini_coordinate[0] + move_table[(last_move+4)%8][0], ini_coordinate[1] + move_table[(last_move+4)%8][1])
		person[1] = (last_move + 4) % 8
	elif direction == "Backward Left":
		person[0] = (ini_coordinate[0] + move_table[(last_move+5)%8][0], ini_coordinate[1] + move_table[(last_move+5)%8][1])
		person[1] = (last_move + 5) % 8
	elif direction == "Left":
		person[0] = (ini_coordinate[0] + move_table[(last_move+6)%8][0], ini_coordinate[1] + move_table[(last_move+6)%8][1])
		person[1] = (last_move + 6) % 8
	elif direction == "Forward Left":
		person[0] = (ini_coordinate[0] + move_table[(last_move+7)%8][0], ini_coordinate[1] + move_table[(last_move+7)%8][1])
		person[1] = (last_move + 7) % 8
	
	for i in uni_state: # This is to check if the new coordinate of person was not preoccupied
		if i == person:
			continue
		elif i[0] == person[0]:
			person[0] = ini_coordinate
			person[1] = last_move
	
	if person[0][0] >= N or person[0][1] >= M or person[0][0] < 0 or person[0][1] < 0: # This is to check if the new coordinate of person is out of bounds
		person[0] = ini_coordinate
		person[1] = last_move
	
	

def contamination(person1, person2, uni_state, infec_states):
	""" 
	A helper funciton that calculates the probability of infection according to distance and whether
	the involved people are wearing masks.
	After that, it stores the infection statuses in infec_states according to this probability
	"""
	global D, K, LAMBDA  
	distance = ((person1[0][0] - person2[0][0])**2 + (person1[0][1] - person2[0][1])**2)**0.5
	if distance <= D:
		mask_amount = person1.count("masked") + person2.count("masked")
		probability = min(1, K / (distance**2)) / (LAMBDA ** mask_amount)
		# Whether person gets infected or not is calculated here
		if person1[3] == "notinfected" and person2[3] == "infected":
			infec_states[uni_state.index(person1)] = random.choices(["infected", "notinfected"], [probability, 1-probability], k = 1)[0]
		elif person1[3] == "infected" and person2[3] == "notinfected":
			infec_states[uni_state.index(person2)] = random.choices(["infected", "notinfected"], [probability, 1-probability], k = 1)[0]

def new_move():
	global uni_state, M, N, D, K, LAMBDA, MU, directions, weight
	copy_uni = uni_state[:]
	infec_state = []
	for person in uni_state: # The infection states are to be stored here until the end of time-stamp
		infec_state.append(person[3])
	for person in copy_uni: # This loop relocates every person in uni_state
		direction = random.choices(directions, weights = weight, k = 1)[0]
		move_person(direction, person, copy_uni)
	for i in range(len(copy_uni)): # This loop stores every person's infection state
		for j in range(i+1, len(copy_uni)):
			contamination(copy_uni[i], copy_uni[j], copy_uni, infec_state)
	for i in range(len(infec_state)): # The infection states are applied to the people
		copy_uni[i][3] = infec_state[i]
	uni_state = copy_uni[:]
	return uni_state
