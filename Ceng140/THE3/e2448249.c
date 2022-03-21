#include <stdio.h>
#include <stdlib.h>
#include "the3.h"




int is_same_apartment(Apartment* apartment, char* name)
{
	char *apartment_name;

	apartment_name = apartment -> name;

	while(*apartment_name == *name)
	{
		if(*apartment_name == '\0') return 1;

		apartment_name++;
		name++;
	}

	return 0;
}




Apartment* add_apartment(Apartment* head, int index, char* apartment_name, int max_bandwidth)
{
	Apartment *new_apt, *curr, *prev;
	int i;

	curr = head;
	prev = NULL;
	new_apt = (Apartment*) malloc(sizeof(Apartment));

	new_apt -> name = apartment_name;
	new_apt -> max_bandwidth = max_bandwidth;
	new_apt -> flat_list = NULL;
	new_apt -> next = new_apt;

	if(head == NULL)
	{
		head = new_apt;
		return head;
	}

	for(i = 0; i < index; i++)
	{
		prev = curr;
		curr = curr -> next;
	}


	if(index == 0)
	{
		prev = head;
		while(prev -> next != head) prev = prev -> next;
		head = new_apt;
	}

	prev -> next = new_apt;
	new_apt -> next = curr;
	return head;
	
}


void add_flat(Apartment* head, char* apartment_name, int index, int flat_id, int initial_bandwidth)
{
	Apartment *apt;
	Flat *curr, *prev, *new_flat;
	int i, available, total = 0;

	curr = NULL;
	prev = NULL;
	new_flat = (Flat*) malloc(sizeof(Flat));
	new_flat -> id = flat_id;
	new_flat -> is_empty = 0;
	new_flat -> next = NULL;
	new_flat -> prev = NULL;

	apt = head;
	while(!is_same_apartment(apt, apartment_name)) apt = apt -> next;
	
	curr = apt -> flat_list;

	while(curr != NULL)
	{
		total += curr -> initial_bandwidth;
		curr = curr -> next;
	}

	available = (apt -> max_bandwidth) - total;

	if(available < initial_bandwidth) new_flat -> initial_bandwidth = available;
	else new_flat -> initial_bandwidth = initial_bandwidth;



	curr = apt -> flat_list;

	if(curr == NULL)
	{
		apt -> flat_list = new_flat;
		return;
	}

	for(i = 0; i < index; i++)
	{
		prev = curr;
		curr = curr -> next;
	}


	if(index == 0)
	{
		new_flat -> next = curr;
		curr -> prev = new_flat;
		apt -> flat_list = new_flat;
		return;
	}

	if(curr == NULL)
	{
		prev -> next = new_flat;
		new_flat -> prev = prev;
		return;
	}

	new_flat -> next = curr;
	new_flat -> prev = prev;
	prev -> next = new_flat;
	curr -> prev = new_flat;
}


Apartment* remove_apartment(Apartment* head, char* apartment_name)
{
	Apartment *prev_apt, *curr_apt;
	Flat *curr, *next;

	curr_apt = head;
	prev_apt = NULL;

	while(!is_same_apartment(curr_apt, apartment_name))
	{
		prev_apt = curr_apt;
		curr_apt = curr_apt -> next;
	}

	curr = curr_apt -> flat_list;
	next = curr_apt -> flat_list;

	while(curr != NULL)
	{
		next = curr -> next;
		free(curr);
		curr = next;
	}

	if(prev_apt == NULL)
	{
		if(curr_apt -> next == curr_apt) head = NULL;

		else
		{
			prev_apt = curr_apt;

			while(prev_apt -> next != curr_apt) prev_apt = prev_apt -> next;

			prev_apt -> next = curr_apt -> next;
			head = curr_apt -> next;
		}
	}
	
	else prev_apt -> next = curr_apt -> next;

	free(curr_apt);

	return head;
}


void make_flat_empty(Apartment* head, char* apartment_name, int flat_id)
{
	Apartment *apt;
	Flat *flat;

	apt = head;

	while(!is_same_apartment(apt, apartment_name)) apt = apt -> next;

	flat = apt -> flat_list;

	while(flat -> id != flat_id) flat = flat -> next;

	flat -> is_empty = 1;
	flat -> initial_bandwidth = 0;
}


int find_sum_of_max_bandwidths(Apartment* head)
{
	Apartment *apt;
	int sum = 0;

	if(head == NULL) return 0;

	apt = head;

	do
	{
		sum += apt -> max_bandwidth;

		apt = apt -> next;
	} while(apt != head);

	return sum;
}


Apartment* merge_two_apartments(Apartment* head, char* apartment_name_1, char* apartment_name_2)
{
	Apartment *apt1, *apt2, *prev;
	Flat *flat1, *flat2;

	apt1 = head;
	apt2 = head;
	prev = NULL;

	while(!is_same_apartment(apt1, apartment_name_1)) apt1 = apt1 -> next;

	while(!is_same_apartment(apt2, apartment_name_2))
	{
		prev = apt2;
	 	apt2 = apt2 -> next;
	}

	flat1 = apt1 -> flat_list;
	flat2 = apt2 -> flat_list;

	if(flat1 != NULL)
	{
		while(flat1 -> next != NULL) flat1 = flat1 -> next;
	}


	if(flat1)
	{
		flat1 -> next = flat2;

		if(flat2) flat2 -> prev = flat1;
	}

	else apt1 -> flat_list = flat2;


	apt1 -> max_bandwidth += apt2 -> max_bandwidth;

	if(prev == NULL)
	{
		prev = head;

		while(prev -> next != head) prev = prev -> next;

		head = apt2 -> next;
	}

	prev -> next = apt2 -> next;

	free(apt2);

	return head;
}


void relocate_flats_to_same_apartment(Apartment* head, char* new_apartment_name, int flat_id_to_shift, int* flat_id_list)
{
	Apartment *new_apt, *curr_apt;
	Flat *new_flat, *shifted_flat;
	int curr_id, is_found = 0;

	new_apt = head;

	/*finding the new apartment*/
	while(!is_same_apartment(new_apt, new_apartment_name)) new_apt = new_apt -> next;
	/**/

	/*finding the flat to get shifted*/
	shifted_flat = new_apt -> flat_list;

	while(shifted_flat -> id != flat_id_to_shift) shifted_flat = shifted_flat -> next;
	/**/


	/*going through all the ids in the list*/
	while(*flat_id_list != 0)
	{
		curr_id = *flat_id_list;
		curr_apt = head;

		/*finding the flat with current id*/
		is_found = 0;

		while(1)
		{
			new_flat = curr_apt -> flat_list;

			if(new_flat)
			{
				while(new_flat != NULL)
				{
					if(new_flat -> id == curr_id)
					{
						is_found = 1;
						break;
					}

					new_flat = new_flat -> next;
				}
			}
			if(is_found) break;

			curr_apt = curr_apt -> next;
		}
		/**/

		/*Readjusting the old apartment of the new flat*/
		if(new_flat -> next) (new_flat -> next) -> prev = new_flat -> prev;


		if(new_flat -> prev) (new_flat -> prev) -> next = new_flat -> next;

		else curr_apt -> flat_list = new_flat -> next;
		

		curr_apt -> max_bandwidth -= new_flat -> initial_bandwidth;
		/**/


		/*inserting the new flat into the new apartment*/
		new_flat -> next = shifted_flat;

		if(shifted_flat -> prev) 
		{
			(shifted_flat -> prev) -> next = new_flat;
			new_flat -> prev = shifted_flat -> prev;
		}

		else 
		{
			new_apt -> flat_list = new_flat;
			new_flat -> prev = NULL;
		}

		shifted_flat -> prev = new_flat;
		
		new_apt -> max_bandwidth += new_flat -> initial_bandwidth;
		/**/

		flat_id_list++;
	}
	/**/
}