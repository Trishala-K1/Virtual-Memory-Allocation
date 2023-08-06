#include "oslabs.h"

int count_page_faults_fifo(struct PTE page_table[TABLEMAX],int table_cnt, int refrence_string[REFERENCEMAX],int reference_cnt,int frame_pool[POOLMAX],int frame_cnt) {

    int i, j, curr_time, page_faults, smallest_last, smallest_last_location;

    page_faults = 0;
    curr_time = 1;
    for(i = 0; i < reference_cnt; i++) {
        if(page_table[refrence_string[i]].is_valid == 1) {
            page_table[refrence_string[i]].last_access_timestamp = curr_time;
            page_table[refrence_string[i]].reference_count++;
        } else {
            if(frame_cnt != 0) {
                (frame_cnt)--;
                page_table[refrence_string[i]].is_valid = 1;
                page_table[refrence_string[i]].frame_number = frame_pool[frame_cnt];
                page_table[refrence_string[i]].arrival_timestamp = curr_time;
                page_table[refrence_string[i]].last_access_timestamp = curr_time;
                page_table[refrence_string[i]].reference_count = 1;
                page_faults++;
            } else {
                smallest_last = curr_time;
                for(j = 0; j < table_cnt; j++) {
                    if((page_table[j].is_valid == 1) && (page_table[j].last_access_timestamp < smallest_last)) {
                        smallest_last_location = j;
                        smallest_last = page_table[j].last_access_timestamp;
                    }
                }

                page_table[smallest_last_location].is_valid = 0;
                page_table[refrence_string[i]].frame_number = page_table[smallest_last_location].frame_number;
                page_table[smallest_last_location].frame_number = -1;
                page_table[smallest_last_location].arrival_timestamp = 0;
                page_table[smallest_last_location].last_access_timestamp = 0;
                page_table[smallest_last_location].reference_count = 0;
                page_table[refrence_string[i]].is_valid = 1;
                page_table[refrence_string[i]].arrival_timestamp = curr_time;
                page_table[refrence_string[i]].last_access_timestamp = curr_time;
                page_table[refrence_string[i]].reference_count = 1;
                page_faults++;
            }
        }
        curr_time++;
    }
    return page_faults;
}
int count_page_faults_lfu(struct PTE page_table[TABLEMAX],int table_cnt, int refrence_string[REFERENCEMAX],int reference_cnt,int frame_pool[POOLMAX],int frame_cnt) {

    int i, j, curr_time, page_faults, smallest_ref, smallest_ref_location, first_guess;

    page_faults = 0;
    curr_time = 1;
    for(i = 0; i < reference_cnt; i++) {
        if(page_table[refrence_string[i]].is_valid == 1) {
            page_table[refrence_string[i]].last_access_timestamp = curr_time;
            page_table[refrence_string[i]].reference_count++;
        } else {
            if(frame_cnt != 0) {
                (frame_cnt)--;
                page_table[refrence_string[i]].is_valid = 1;
                page_table[refrence_string[i]].frame_number = frame_pool[frame_cnt];
                page_table[refrence_string[i]].arrival_timestamp = curr_time;
                page_table[refrence_string[i]].last_access_timestamp = curr_time;
                page_table[refrence_string[i]].reference_count = 1;
                page_faults++;
            } else {
                first_guess = 1;
                smallest_ref = 0;
                for(j = 0; j < table_cnt; j++) {
                    if(page_table[j].is_valid == 1) {
                        if(first_guess) {
                            smallest_ref = page_table[j].reference_count;
                            smallest_ref_location = j;
                            first_guess = 0;
                        } else if(page_table[j].reference_count < smallest_ref) {
                            smallest_ref = page_table[j].reference_count;
                            smallest_ref_location = j;
                        } else if(page_table[j].reference_count == smallest_ref) {
                            if(page_table[j].arrival_timestamp < page_table[smallest_ref_location].arrival_timestamp) {
                                smallest_ref = page_table[j].reference_count;
                                smallest_ref_location = j;
                            }
                        }
                    }
                }

                page_table[smallest_ref_location].is_valid = 0;
                page_table[refrence_string[i]].frame_number = page_table[smallest_ref_location].frame_number;
                page_table[smallest_ref_location].frame_number = -1;
                page_table[smallest_ref_location].arrival_timestamp = 0;
                page_table[smallest_ref_location].last_access_timestamp = 0;
                page_table[smallest_ref_location].reference_count = 0;
                page_table[refrence_string[i]].is_valid = 1;
                page_table[refrence_string[i]].arrival_timestamp = curr_time;
                page_table[refrence_string[i]].last_access_timestamp = curr_time;
                page_table[refrence_string[i]].reference_count = 1;
                page_faults++;
            }
        }
        curr_time++;
    }
    return page_faults;
}
int count_page_faults_lru(struct PTE page_table[TABLEMAX],int table_cnt, int refrence_string[REFERENCEMAX],int reference_cnt,int frame_pool[POOLMAX],int frame_cnt) {

    int i, j, curr_time, page_faults, smallest_last, smallest_last_location, first_guess;

    page_faults = 0;
    curr_time = 1;
    for(i = 0; i < reference_cnt; i++) {
        if(page_table[refrence_string[i]].is_valid == 1) {
            page_table[refrence_string[i]].last_access_timestamp = curr_time;
            page_table[refrence_string[i]].reference_count++;
        } else {
            if(frame_cnt != 0) {
                (frame_cnt)--;
                page_table[refrence_string[i]].is_valid = 1;
                page_table[refrence_string[i]].frame_number = frame_pool[frame_cnt];
                page_table[refrence_string[i]].arrival_timestamp = curr_time;
                page_table[refrence_string[i]].last_access_timestamp = curr_time;
                page_table[refrence_string[i]].reference_count = 1;
                page_faults++;
            } else {
                first_guess = 1;
                smallest_last = curr_time;
                for(j = 0; j < table_cnt; j++) {
                    if(page_table[j].is_valid == 1) {
                        if(first_guess) {
                            smallest_last = page_table[j].last_access_timestamp;
                            smallest_last_location = j;
                            first_guess = 0;
                        } else if(page_table[j].last_access_timestamp < smallest_last) {
                            smallest_last = page_table[j].last_access_timestamp;
                            smallest_last_location = j;
                        }
                    }
                }

                page_table[smallest_last_location].is_valid = 0;
                page_table[refrence_string[i]].frame_number = page_table[smallest_last_location].frame_number;
                page_table[smallest_last_location].frame_number = -1;
                page_table[smallest_last_location].arrival_timestamp = 0;
                page_table[smallest_last_location].last_access_timestamp = 0;
                page_table[smallest_last_location].reference_count = 0;
                page_table[refrence_string[i]].is_valid = 1;
                page_table[refrence_string[i]].arrival_timestamp = curr_time;
                page_table[refrence_string[i]].last_access_timestamp = curr_time;
                page_table[refrence_string[i]].reference_count = 1;
                page_faults++;
            }
        }
        curr_time++;
    }
    return page_faults;
}
int process_page_access_fifo(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number, int frame_pool[POOLMAX],int *frame_cnt, int current_timestamp) {

    int i, smallest_arrival, smallest_arrival_location;

    if(page_table[page_number].is_valid == 1) {
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count +=1;

        return page_table[page_number].frame_number;
    } else {
        if(*frame_cnt != 0) {
            (*frame_cnt)--;
            page_table[page_number].is_valid = 1;
            page_table[page_number].frame_number = frame_pool[*frame_cnt];
            page_table[page_number].arrival_timestamp = current_timestamp;
            page_table[page_number].last_access_timestamp = current_timestamp;
            page_table[page_number].reference_count = 1;

            return page_table[page_number].frame_number;
        } else {
            smallest_arrival = current_timestamp;
            for(i = 0; i < *table_cnt; i++) {
                if((page_table[i].is_valid == 1) && (page_table[i].arrival_timestamp < smallest_arrival)) {
                    smallest_arrival_location = i;
                    smallest_arrival = page_table[i].arrival_timestamp;
                }
            }

            page_table[smallest_arrival_location].is_valid = 0;
            page_table[page_number].frame_number = page_table[smallest_arrival_location].frame_number;
            page_table[smallest_arrival_location].frame_number = -1;
            page_table[smallest_arrival_location].arrival_timestamp = 0;
            page_table[smallest_arrival_location].last_access_timestamp = 0;
            page_table[smallest_arrival_location].reference_count = 0;
            page_table[page_number].is_valid = 1;
            page_table[page_number].arrival_timestamp = current_timestamp;
            page_table[page_number].last_access_timestamp = current_timestamp;
            page_table[page_number].reference_count = 1;

            return page_table[page_number].frame_number;
        }
    }
}
int process_page_access_lfu(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number, int frame_pool[POOLMAX],int *frame_cnt, int current_timestamp) {

    int i, smallest_last, smallest_last_location;

    if(page_table[page_number].is_valid == 1) {
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count +=1;

        return page_table[page_number].frame_number;
    } else {
        if(*frame_cnt != 0) {
            (*frame_cnt)--;
            page_table[page_number].is_valid = 1;
            page_table[page_number].frame_number = frame_pool[*frame_cnt];
            page_table[page_number].arrival_timestamp = current_timestamp;
            page_table[page_number].last_access_timestamp = current_timestamp;
            page_table[page_number].reference_count = 1;

            return page_table[page_number].frame_number;
        } else {
            smallest_last = current_timestamp;
            for(i = 0; i < *table_cnt; i++) {
                if((page_table[i].is_valid == 1) && (page_table[i].last_access_timestamp < smallest_last)) {
                    smallest_last_location = i;
                    smallest_last = page_table[i].last_access_timestamp;
                }
            }

            page_table[smallest_last_location].is_valid = 0;
            page_table[page_number].frame_number = page_table[smallest_last_location].frame_number;
            page_table[smallest_last_location].frame_number = -1;
            page_table[smallest_last_location].arrival_timestamp = 0;
            page_table[smallest_last_location].last_access_timestamp = 0;
            page_table[smallest_last_location].reference_count = 0;
            page_table[page_number].is_valid = 1;
            page_table[page_number].arrival_timestamp = current_timestamp;
            page_table[page_number].last_access_timestamp = current_timestamp;
            page_table[page_number].reference_count = 1;

            return page_table[page_number].frame_number;
        }
    }
}
int process_page_access_lru(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number, int frame_pool[POOLMAX],int *frame_cnt, int current_timestamp) {

    int i, smallest_ref, smallest_ref_location, first_guess;

    if(page_table[page_number].is_valid == 1) {
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count +=1;

        return page_table[page_number].frame_number;
    } else {
        if(*frame_cnt != 0) {
            (*frame_cnt)--;
            page_table[page_number].is_valid = 1;
            page_table[page_number].frame_number = frame_pool[*frame_cnt];
            page_table[page_number].arrival_timestamp = current_timestamp;
            page_table[page_number].last_access_timestamp = current_timestamp;
            page_table[page_number].reference_count = 1;

            return page_table[page_number].frame_number;
        } else {
            first_guess = 1;
            smallest_ref = 0;
            for(i = 0; i < *table_cnt; i++) {
                if(page_table[i].is_valid == 1) {
                    if(first_guess) {
                        smallest_ref = page_table[i].reference_count;
                        smallest_ref_location = i;
                        first_guess = 0;
                    } else if(page_table[i].reference_count < smallest_ref) {
                        smallest_ref = page_table[i].reference_count;
                        smallest_ref_location = i;
                    } else if(page_table[i].reference_count == smallest_ref) {
                        if(page_table[i].arrival_timestamp < page_table[smallest_ref_location].arrival_timestamp) {
                            smallest_ref = page_table[i].reference_count;
                            smallest_ref_location = i;
                        }
                    }
                }
            }

            page_table[smallest_ref_location].is_valid = 0;
            page_table[page_number].frame_number = page_table[smallest_ref_location].frame_number;
            page_table[smallest_ref_location].frame_number = -1;
            page_table[smallest_ref_location].arrival_timestamp = 0;
            page_table[smallest_ref_location].last_access_timestamp = 0;
            page_table[smallest_ref_location].reference_count = 0;
            page_table[page_number].is_valid = 1;
            page_table[page_number].arrival_timestamp = current_timestamp;
            page_table[page_number].last_access_timestamp = current_timestamp;
            page_table[page_number].reference_count = 1;

            return page_table[page_number].frame_number;
        }
    }
}
