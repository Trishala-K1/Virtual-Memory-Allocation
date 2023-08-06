#include <stdio.h>
#include <stdlib.h>
#include "oslabs.h"

int count_page_faults_fifo(struct PTE page_table[TABLEMAX],int table_cnt, int reference_string[REFERENCEMAX],int reference_cnt,int frame_pool[POOLMAX],int frame_cnt)
{
	int page_faults = 0;
	int current_timestamp = 1;
	for (int i = 0; i < reference_cnt; i++)
	{
		int page_reference = reference_string[i];
		current_timestamp++;
		if (page_table[page_reference].is_valid)
		{
			current_timestamp++;
			page_table[page_reference].last_access_timestamp = current_timestamp;
			page_table[page_reference].reference_count++;
		}
		else
		{
			int frame;
			if (frame_cnt > 0)
			{
				page_faults++;
				frame = frame_pool[0];
				frame_cnt--;
				page_table[page_reference].reference_count++;
			}
			else
			{
				page_faults++;
				int min_PTE = 0;
				//find page in page table with earliest arrival time
				int min_arrival_timestamp = 10000;
				for (int i = 0; i < table_cnt; i++)
				{
					if (page_table[i].is_valid && page_table[i].arrival_timestamp < min_arrival_timestamp)
					{
						min_arrival_timestamp = page_table[i].arrival_timestamp;
						min_PTE = i;
					}
				}
				frame = page_table[min_PTE].frame_number;
				page_table[min_PTE].is_valid = 0;
				page_table[min_PTE].arrival_timestamp = 0;
				page_table[min_PTE].last_access_timestamp = 0;
				page_table[min_PTE].reference_count = 0;
				page_table[page_reference].reference_count = 1;
			}
			page_table[page_reference].frame_number = frame;
			page_table[page_reference].is_valid = 1;
			page_table[page_reference].arrival_timestamp = current_timestamp;
			page_table[page_reference].last_access_timestamp = current_timestamp;
		}
	}
	return page_faults;
}


int count_page_faults_lru(struct PTE page_table[TABLEMAX],int table_cnt, int reference_string[REFERENCEMAX],int reference_cnt,int frame_pool[POOLMAX],int frame_cnt)
{
	int page_faults = 0;
	int current_timestamp = 1;
	for (int i = 0; i < reference_cnt; i++)
	{
		
		int page_reference = reference_string[i];
		current_timestamp++;
		if (page_table[page_reference].is_valid)
		{
			current_timestamp++;
			page_table[page_reference].last_access_timestamp = current_timestamp;
			page_table[page_reference].reference_count++;
		}
		else
		{
			int frame;
			if (frame_cnt > 0)
			{
				page_faults++;
				frame = frame_pool[0];
				frame_cnt--;
				page_table[page_reference].reference_count++;
			}
			else
			{
				page_faults++;
				int min_PTE = 0;
				//find page in page table with earliest arrival time
				int min_arrival_timestamp = 10000;
				for (int i = 0; i < table_cnt; i++)
				{
					if (page_table[i].is_valid && page_table[i].arrival_timestamp < min_arrival_timestamp)
					{
						min_arrival_timestamp = page_table[i].arrival_timestamp;
						min_PTE = i;
					}
				}
				frame = page_table[min_PTE].frame_number;
				page_table[min_PTE].is_valid = 0;
				page_table[min_PTE].arrival_timestamp = 0;
				page_table[min_PTE].last_access_timestamp = 0;
				page_table[min_PTE].reference_count = 0;
				page_table[page_reference].reference_count = 1;
			}
			page_table[page_reference].frame_number = frame;
			page_table[page_reference].is_valid = 1;
			page_table[page_reference].arrival_timestamp = current_timestamp;
			page_table[page_reference].last_access_timestamp = current_timestamp;
			
		}
	}
	return 9;
}

int count_page_faults_lfu(struct PTE page_table[TABLEMAX],int table_cnt, int refrence_string[REFERENCEMAX],int reference_cnt,int frame_pool[POOLMAX],int frame_cnt)
{
	int page_faults = 0;
	int current_timestamp = 1;
	for (int i = 0; i < reference_cnt; i++)
	{
		int page_reference = refrence_string[i];
		current_timestamp++;
		if (page_table[page_reference].is_valid)
		{
			current_timestamp++;
			page_table[page_reference].last_access_timestamp = current_timestamp;
			page_table[page_reference].reference_count++;
		}
		else
		{
			int frame;
			if (frame_cnt > 0)
			{
				page_faults++;
				frame = frame_pool[0];
				frame_cnt--;
				page_table[page_reference].reference_count++;
			}
			else
			{
				page_faults++;
				int min_PTE = 0;
				//find page in page table with earliest arrival time
				int min_arrival_timestamp = 10000;
				for (int i = 0; i < table_cnt; i++)
				{
					if (page_table[i].is_valid && page_table[i].arrival_timestamp < min_arrival_timestamp)
					{
						min_arrival_timestamp = page_table[i].arrival_timestamp;
						min_PTE = i;
					}
				}
				frame = page_table[min_PTE].frame_number;
				page_table[min_PTE].is_valid = 0;
				page_table[min_PTE].arrival_timestamp = 0;
				page_table[min_PTE].last_access_timestamp = 0;
				page_table[min_PTE].reference_count = 0;
				page_table[page_reference].reference_count = 1;
			}
			page_table[page_reference].frame_number = frame;
			page_table[page_reference].is_valid = 1;
			page_table[page_reference].arrival_timestamp = current_timestamp;
			page_table[page_reference].last_access_timestamp = current_timestamp;
		}
	}
	return page_faults;
}
int process_page_access_lfu(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number, int frame_pool[POOLMAX],int *frame_cnt, int current_timestamp)
{
	
}

int process_page_access_lru(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number, int frame_pool[POOLMAX],int *frame_cnt, int current_timestamp)
{
	
	return 30;
}

int process_page_access_fifo(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number, int frame_pool[POOLMAX],int *frame_cnt, int current_timestamp)
{
	
}
