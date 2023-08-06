#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "oslabs.h"

/* process_page_access_fifo */
int process_page_access_fifo(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number, int frame_pool[POOLMAX],int *frame_cnt, int current_timestamp);
/* count_page_faults_fifo */
int count_page_faults_fifo(struct PTE page_table[TABLEMAX],int table_cnt, int refrence_string[REFERENCEMAX],int reference_cnt,int frame_pool[POOLMAX],int frame_cnt);
/* process_page_access_lru */
int process_page_access_lru(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number, int frame_pool[POOLMAX],int *frame_cnt, int current_timestamp);
/* count_page_faults_lru */
int count_page_faults_lru(struct PTE page_table[TABLEMAX],int table_cnt, int refrence_string[REFERENCEMAX],int reference_cnt,int frame_pool[POOLMAX],int frame_cnt);
/* process_page_access_lfu */
int process_page_access_lfu(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number, int frame_pool[POOLMAX],int *frame_cnt, int current_timestamp);
/* count_page_faults_lfu */
int count_page_faults_lfu(struct PTE page_table[TABLEMAX],int table_cnt, int refrence_string[REFERENCEMAX],int reference_cnt,int frame_pool[POOLMAX],int frame_cnt);


int process_page_access_fifo(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number, int frame_pool[POOLMAX],int *frame_cnt, int current_timestamp){
	int fn;
		fn = frame_pool[*frame_cnt - 1];

		page_table[page_number].frame_number = fn;
		page_table[page_number].arrival_timestamp = current_timestamp;
		page_table[page_number].last_access_timestamp = current_timestamp;
		page_table[page_number].reference_count = 1;
		page_table[page_number].is_valid = 1;

		(*frame_cnt)--;
		return(fn);
	}
	
	
	int position = -1;
	for(int i = 0; i < *table_cnt; i++){
		if(page_table[i].is_valid && page_table[i].arrival_timestamp < min_ts){
			min_ts = page_table[i].arrival_timestamp;
			position = i;
		}
	}
	
	fn = page_table[position].frame_number;
	
	page_table[position].is_valid = 0;
	page_table[position].frame_number = -1;
	page_table[position].arrival_timestamp = -1;
	page_table[position].last_access_timestamp = -1;
	page_table[position].reference_count = -1;
	page_table[page_number].frame_number = fn;
	page_table[page_number].arrival_timestamp = current_timestamp;
	page_table[page_number].last_access_timestamp = current_timestamp;
	page_table[page_number].reference_count = 1;
	page_table[page_number].is_valid = 1;
	return(fn);
		
}


int count_page_faults_fifo(struct PTE page_table[TABLEMAX],int table_cnt, int refrence_string[REFERENCEMAX],int reference_cnt,int frame_pool[POOLMAX],int frame_cnt){
	int current_timestamp = 1;
	int page_faults = 0;
	int fn;
	int min_ts = INT_MAX;
	int position = -1;

	for(int i = 0; i < reference_cnt; i++){
		current_timestamp++;
		int logical_page_number = refrence_string[i];
	
		if(page_table[logical_page_number].is_valid){
			page_table[logical_page_number].last_access_timestamp = current_timestamp;
			page_table[logical_page_number].reference_count++;
		}else{

			page_faults++;
			if(frame_cnt > 0){
				page_table[logical_page_number].is_valid = 1;
				page_table[logical_page_number].frame_number = frame_pool[frame_cnt - 1];
				page_table[logical_page_number].arrival_timestamp = current_timestamp;
				page_table[logical_page_number].last_access_timestamp = current_timestamp;
				page_table[logical_page_number].reference_count = 1;
				//Remove frame from process frame pool
				frame_pool[frame_cnt - 1] = -1;
				frame_cnt--;
			} else {
				min_ts = INT_MAX;
				position = -1;
				for(int j = 0; j < table_cnt; j++){
					if(page_table[j].is_valid && page_table[j].arrival_timestamp < min_ts){
						min_ts = page_table[j].arrival_timestamp;
						position = j;
					}
				}
				fn = page_table[position].frame_number;
				page_table[position].is_valid = 0;
				page_table[position].frame_number = -1;
				page_table[position].arrival_timestamp = -1;
				page_table[position].last_access_timestamp = -1;
				page_table[position].reference_count = -1;
				page_table[logical_page_number].frame_number = fn;
				page_table[logical_page_number].arrival_timestamp = current_timestamp;
				page_table[logical_page_number].last_access_timestamp = current_timestamp;
				page_table[logical_page_number].reference_count = 1;
				page_table[logical_page_number].is_valid = 1;
			}
		}

	}
	return(page_faults);
}



int process_page_access_lru(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number, int frame_pool[POOLMAX],int *frame_cnt, int current_timestamp){
	int fn;
	if(page_table[page_number].is_valid){
		
		page_table[page_number].last_access_timestamp = current_timestamp;
		page_table[page_number].reference_count ++;
		return(page_table[page_number].frame_number);
	}
	
	if(*frame_cnt > 0){
		
		fn = frame_pool[*frame_cnt - 1];

		page_table[page_number].frame_number = fn;
		page_table[page_number].arrival_timestamp = current_timestamp;
		page_table[page_number].last_access_timestamp = current_timestamp;
		page_table[page_number].reference_count = 1;
		page_table[page_number].is_valid = 1;

		(*frame_cnt)--;
		return(fn);
	}
	
	int min_ts = INT_MAX;
	int position = -1;
	for(int i = 0; i < *table_cnt; i++){
		if(page_table[i].is_valid && page_table[i].last_access_timestamp < min_ts){
			min_ts = page_table[i].last_access_timestamp;
			position = i;
		}
	}
	fn = page_table[position].frame_number;
	page_table[position].is_valid = 0;
	page_table[position].frame_number = -1;
	page_table[position].arrival_timestamp = -1;
	page_table[position].last_access_timestamp = -1;
	page_table[position].reference_count = -1;
	page_table[page_number].frame_number = fn;
	page_table[page_number].arrival_timestamp = current_timestamp;
	page_table[page_number].last_access_timestamp = current_timestamp;
	page_table[page_number].reference_count = 1;
	page_table[page_number].is_valid = 1;
	return(fn);
}
int count_page_faults_lru(struct PTE page_table[TABLEMAX],int table_cnt, int refrence_string[REFERENCEMAX],int reference_cnt,int frame_pool[POOLMAX],int frame_cnt){
	int current_timestamp = 1;
	int page_faults = 0;
	int fn;
	int min_ts = INT_MAX;
	int position = -1;

	for(int i = 0; i < reference_cnt; i++){
		current_timestamp++;
		int logical_page_number = refrence_string[i];
	
		if(page_table[logical_page_number].is_valid){
			page_table[logical_page_number].last_access_timestamp = current_timestamp;
			page_table[logical_page_number].reference_count++;
		}else{
			page_faults++;
			if(frame_cnt > 0){
				page_table[logical_page_number].is_valid = 1;
				page_table[logical_page_number].frame_number = frame_pool[frame_cnt - 1];
				page_table[logical_page_number].arrival_timestamp = current_timestamp;
				page_table[logical_page_number].last_access_timestamp = current_timestamp;
				page_table[logical_page_number].reference_count = 1;
				frame_pool[frame_cnt - 1] = -1;
				frame_cnt--;
			} else {
				min_ts = INT_MAX;
				position = -1;
				for(int j = 0; j < table_cnt; j++){
					if(page_table[j].is_valid && page_table[j].last_access_timestamp < min_ts){
						min_ts = page_table[j].last_access_timestamp;
						position = j;
					}
				}
				fn = page_table[position].frame_number;
				page_table[position].is_valid = 0;
				page_table[position].frame_number = -1;
				page_table[position].arrival_timestamp = -1;
				page_table[position].last_access_timestamp = -1;
				page_table[position].reference_count = -1;
				page_table[logical_page_number].frame_number = fn;
				page_table[logical_page_number].arrival_timestamp = current_timestamp;
				page_table[logical_page_number].last_access_timestamp = current_timestamp;
				page_table[logical_page_number].reference_count = 1;
				page_table[logical_page_number].is_valid = 1;
			}
		}

	}
	return(page_faults);
}
int process_page_access_lfu(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number, int frame_pool[POOLMAX],int *frame_cnt, int current_timestamp){
	int fn;
	if(page_table[page_number].is_valid){
		page_table[page_number].last_access_timestamp = current_timestamp;
		page_table[page_number].reference_count ++;
		return(page_table[page_number].frame_number);
	}
	if(*frame_cnt > 0){

		fn = frame_pool[*frame_cnt - 1];

		page_table[page_number].frame_number = fn;
		page_table[page_number].arrival_timestamp = current_timestamp;
		page_table[page_number].last_access_timestamp = current_timestamp;
		page_table[page_number].reference_count = 1;
		page_table[page_number].is_valid = 1;

		(*frame_cnt)--;
		return(fn);
	}
	
	int min_ts = INT_MAX;
	int min_at = INT_MAX;
	int position = -1;
	for(int i = 0; i < *table_cnt; i++){
		if(page_table[i].is_valid && page_table[i].reference_count < min_ts){
			min_ts = page_table[i].reference_count;
			position = i;
			min_at = page_table[i].arrival_timestamp;
		}else if(page_table[i].is_valid && page_table[i].reference_count == min_ts){
			if(page_table[i].arrival_timestamp < min_at){
				min_ts = page_table[i].reference_count;
				position = i;
				min_at = page_table[i].arrival_timestamp;
			}
		}
	}
	fn = page_table[position].frame_number;
	page_table[position].is_valid = 0;
	page_table[position].frame_number = -1;
	page_table[position].arrival_timestamp = -1;
	page_table[position].last_access_timestamp = -1;
	page_table[position].reference_count = -1;
	page_table[page_number].frame_number = fn;
	page_table[page_number].arrival_timestamp = current_timestamp;
	page_table[page_number].last_access_timestamp = current_timestamp;
	page_table[page_number].reference_count = 1;
	page_table[page_number].is_valid = 1;
	return(fn);
}
/* count_page_faults_lfu */
int count_page_faults_lfu(struct PTE page_table[TABLEMAX],int table_cnt, int refrence_string[REFERENCEMAX],int reference_cnt,int frame_pool[POOLMAX],int frame_cnt){
	int current_timestamp = 1;
	int page_faults = 0;
	int fn;
	int min_at = INT_MAX;
	int min_ts = INT_MAX;
	int position = -1;

	for(int i = 0; i < reference_cnt; i++){
		current_timestamp++;
		int logical_page_number = refrence_string[i];
	
		if(page_table[logical_page_number].is_valid){
			page_table[logical_page_number].last_access_timestamp = current_timestamp;
			page_table[logical_page_number].reference_count++;
		}else{
		
			page_faults++;
			if(frame_cnt > 0){
				page_table[logical_page_number].is_valid = 1;
				page_table[logical_page_number].frame_number = frame_pool[frame_cnt - 1];
				page_table[logical_page_number].arrival_timestamp = current_timestamp;
				page_table[logical_page_number].last_access_timestamp = current_timestamp;
				page_table[logical_page_number].reference_count = 1;
				//Remove frame from process frame pool
				frame_pool[frame_cnt - 1] = -1;
				frame_cnt--;
			} else {
				min_ts = INT_MAX;
				min_at = INT_MAX;
				position = -1;
				for(int j = 0; j < table_cnt; j++){
					if(page_table[j].is_valid && page_table[j].reference_count < min_ts){
						min_ts = page_table[j].reference_count;
						min_at = page_table[j].arrival_timestamp;
						position = j;
					}else if(page_table[j].is_valid && page_table[j].reference_count == min_ts){
						if(page_table[j].arrival_timestamp < min_at){
							min_ts = page_table[j].reference_count;
							position = j;
							min_at = page_table[j].arrival_timestamp;
						}
					}
				}
				fn = page_table[position].frame_number;
				page_table[position].is_valid = 0;
				page_table[position].frame_number = -1;
				page_table[position].arrival_timestamp = -1;
				page_table[position].last_access_timestamp = -1;
				page_table[position].reference_count = -1;
				page_table[logical_page_number].frame_number = fn;
				page_table[logical_page_number].arrival_timestamp = current_timestamp;
				page_table[logical_page_number].last_access_timestamp = current_timestamp;
				page_table[logical_page_number].reference_count = 1;
				page_table[logical_page_number].is_valid = 1;
			}
		}

	}
	return(page_faults);
}
