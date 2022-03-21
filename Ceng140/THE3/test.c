#include "the3.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int index = 2, max_bandwidth = 85, i, initial_bandwidth = 45, flat_id = 12, sum, id_list[] = {11, 5, 0};
	char name1[4] = "X", name2[4] = "Y", name3[4] = "Z", *name = "Q";
	Apartment *no1, *no2, *no3, *head, *curr_apt;
	Flat *flat1, *flat2, *flat3, *curr_flat, *flat4, *flat5, *flat6, *flat7, *flat8, *flat9;

	no1 = (Apartment*) malloc(sizeof(Apartment));
	no2 = (Apartment*) malloc(sizeof(Apartment));
	no3 = (Apartment*) malloc(sizeof(Apartment));
	no1 -> next = no2;
	no1 -> name = name1;
	no2 -> next = no3;
	no2 -> name = name2;
	no3 -> next = no1;
	no3 -> name = name3;
	no1 -> max_bandwidth = 55;
	no2 -> max_bandwidth = 65;
	no3 -> max_bandwidth = 75;
	head = no1;

	flat4 = (Flat*) malloc(sizeof(Flat));
	flat5 = (Flat*) malloc(sizeof(Flat));
	flat6 = (Flat*) malloc(sizeof(Flat));
	flat4 -> initial_bandwidth = 25;
	flat5 -> initial_bandwidth = 0;
	flat6 -> initial_bandwidth = 10;
	flat4 -> id = 2;
	flat5 -> id = 3;
	flat6 -> id = 5;
	flat4 -> next = flat5;
	flat4 -> prev = NULL;
	flat5 -> next = flat6;
	flat5 -> prev = flat4;
	flat6 -> next = NULL;
	flat6 -> prev = flat5;
	no1 -> flat_list = flat4;
	/*no1 -> flat_list = NULL;*/


	flat7 = (Flat*) malloc(sizeof(Flat));
	flat8 = (Flat*) malloc(sizeof(Flat));
	flat9 = (Flat*) malloc(sizeof(Flat));
	flat7 -> initial_bandwidth = 30;
	flat8 -> initial_bandwidth = 15;
	flat9 -> initial_bandwidth = 20;
	flat7 -> id = 10;
	flat8 -> id = 1;
	flat9 -> id = 4;
	flat7 -> next = flat8;
	flat7 -> prev = NULL;
	flat8 -> next = flat9;
	flat8 -> prev = flat7;
	flat9 -> next = NULL;
	flat9 -> prev = flat8;
	no2 -> flat_list = flat7;
	/*no2 -> flat_list = NULL;*/

	flat1 = (Flat*) malloc(sizeof(Flat));
	flat2 = (Flat*) malloc(sizeof(Flat));
	flat3 = (Flat*) malloc(sizeof(Flat));
	flat1 -> initial_bandwidth = 20;
	flat2 -> initial_bandwidth = 10;
	flat3 -> initial_bandwidth = 15;
	flat1 -> id = 9;
	flat2 -> id = 7;
	flat3 -> id = 11;
	flat1 -> next = flat2;
	flat1 -> prev = NULL;
	flat2 -> next = flat3;
	flat2 -> prev = flat1;
	flat3 -> next = NULL;
	flat3 -> prev = flat2;
	no3 -> flat_list = flat1;
	/*no3 -> flat_list = NULL;*/	


	head = add_apartment(head, index, name, max_bandwidth);

	add_flat(head, name, 0, flat_id, initial_bandwidth);

	head = remove_apartment(head, name);
	


	make_flat_empty(head, "Z", 11);
	printf("is empty:%d\n", flat3 -> is_empty);
	printf("\n");


	sum = find_sum_of_max_bandwidths(head);
	printf("sum:%d\n", sum);
	printf("\n");


	/*head = merge_two_apartments(head, name1, name3);*/



	/*relocate_flats_to_same_apartment(head, "Y", 4, id_list);*/


	curr_apt = head;
	do
	{
		printf("apt name:%s, max bandwidth:%d\n", curr_apt -> name, curr_apt -> max_bandwidth);

		curr_flat = curr_apt -> flat_list;

		while(curr_flat != NULL)
		{
			printf("flat id:%d, initial bandwidth:%d\n", curr_flat -> id, curr_flat -> initial_bandwidth);
			curr_flat = curr_flat -> next;
		}

		printf("\n");

		curr_apt = curr_apt -> next;
	}while(curr_apt != head);


	return 0;
}