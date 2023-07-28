#include "oslabs.h"



int process_page_access_fifo(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number,
 int frame_pool[POOLMAX],int *frame_cnt, int current_timestamp)  {
    if(page_table[page_number].is_valid){
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count+=1;
        return page_table[page_number].frame_number;
    }
    else{
        if(*frame_cnt>0){
            int freedframe = frame_pool[*frame_cnt-1];
            page_table[page_number].frame_number = freedframe;
            page_table[page_number].last_access_timestamp =current_timestamp;
            page_table[page_number].reference_count+=1;
            page_table[page_number].is_valid =1;
            *frame_cnt-=1;
            return freedframe;  
        }
        else{
            int i=0,smallest = 9999,pos;
            for(i;i<*table_cnt;i++){
                if(page_table[i].is_valid){
                if(page_table[i].arrival_timestamp < smallest){
                    smallest = page_table[i].arrival_timestamp;
                    pos =i;
                }
                }
            }
            page_table[pos].is_valid =0;
            page_table[pos].arrival_timestamp =0;
            page_table[pos].last_access_timestamp=0;
            page_table[pos].reference_count=0;
            int frnum = page_table[pos].frame_number; 
            page_table[pos].frame_number = -1;


            page_table[page_number].arrival_timestamp = current_timestamp;
            page_table[page_number].last_access_timestamp = current_timestamp;
            page_table[page_number].reference_count = 1;
            page_table[page_number].frame_number= frnum;
            page_table[page_number].is_valid =1;
            return frnum;
        }
    }
 }



int count_page_faults_fifo(struct PTE page_table[TABLEMAX],int table_cnt, int refrence_string[REFERENCEMAX],
 int refrence_cnt,int frame_pool[POOLMAX],int frame_cnt){
   int timestamp =1,i=0,faults =0;
    for(i;i<refrence_cnt-2;i++){
        if(page_table[refrence_string[i]].is_valid){
            page_table[refrence_string[i]].last_access_timestamp = timestamp;
            page_table[refrence_string[i]].reference_count+=1;
            timestamp+=1;
        }
        else{
        if(frame_cnt>0){
            int freedframe = frame_pool[frame_cnt-1];
            frame_cnt-=1;
            page_table[refrence_string[i]].frame_number = freedframe;
            page_table[refrence_string[i]].arrival_timestamp = timestamp;
            page_table[refrence_string[i]].last_access_timestamp = timestamp;
            page_table[refrence_string[i]].reference_count+=1;
            page_table[refrence_string[i]].is_valid =1;
            faults+=1;
            timestamp+=1;
        }
        else{
            int j=0,smallest=999,pos;
            for(j;j<table_cnt;j++){
                if(page_table[j].is_valid){
                    if(page_table[j].last_access_timestamp<smallest){
                    pos =j;
                    smallest = page_table[j].last_access_timestamp;
                    }
                }
            }

            page_table[pos].is_valid =0;
            page_table[pos].arrival_timestamp =0;
            page_table[pos].last_access_timestamp=0;
            page_table[pos].reference_count=0;
            int frnum = page_table[pos].frame_number; 
            page_table[pos].frame_number = -1;

            page_table[refrence_string[i]].frame_number = frnum;
            page_table[refrence_string[i]].arrival_timestamp = timestamp;
            page_table[refrence_string[i]].last_access_timestamp = timestamp;
            page_table[refrence_string[i]].reference_count=1;
          
            faults+=1;
            timestamp+=1;
        }
    }

    }
return faults;
 }



int process_page_access_lru(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number, int frame_pool[POOLMAX],
 int *frame_cnt, int current_timestamp){
     if(page_table[page_number].is_valid == 1){
         page_table[page_number].reference_count+=1;
         page_table[page_number].last_access_timestamp = current_timestamp;
         return page_table[page_number].frame_number;
     }
     else{
         if(*frame_cnt>0){
            int freedframe = frame_pool[*frame_cnt-1];
            page_table[page_number].frame_number = freedframe;
            page_table[page_number].last_access_timestamp =current_timestamp;
            page_table[page_number].reference_count+=1;
            page_table[page_number].is_valid =1;
            *frame_cnt-=1;
            return freedframe;
         }
         else{
             int i=0,smallest = 9999,pos;
            for(i;i<*table_cnt;i++){
                if(page_table[i].is_valid){
                if(page_table[i].arrival_timestamp < smallest){
                    smallest = page_table[i].arrival_timestamp;
                    pos =i;
                }
                }
            }
            page_table[pos].is_valid =0;
            page_table[pos].arrival_timestamp =0;
            page_table[pos].last_access_timestamp=0;
            page_table[pos].reference_count=0;
            int frnum = page_table[pos].frame_number; 
            page_table[pos].frame_number = -1;


            page_table[page_number].arrival_timestamp = current_timestamp;
            page_table[page_number].last_access_timestamp = current_timestamp;
            page_table[page_number].reference_count = 1;
            page_table[page_number].frame_number= frnum;
            page_table[page_number].is_valid =1;
            return frnum;
        }
     }
}


int count_page_faults_lru(struct PTE page_table[TABLEMAX],int table_cnt, int refrence_string[REFERENCEMAX],
int reference_cnt,int frame_pool[POOLMAX],int frame_cnt){
    int timestamp =1,i=0,faults =0;
    for(i;i<reference_cnt-1;i++){
        if(page_table[refrence_string[i]].is_valid){
            page_table[refrence_string[i]].last_access_timestamp = timestamp;
            page_table[refrence_string[i]].reference_count+=1;
            timestamp+=1;
        }
        else{
        if(frame_cnt>0){
            int freedframe = frame_pool[frame_cnt-1];
            frame_cnt-=1;
            page_table[refrence_string[i]].frame_number = freedframe;
            page_table[refrence_string[i]].arrival_timestamp = timestamp;
            page_table[refrence_string[i]].last_access_timestamp = timestamp;
            page_table[refrence_string[i]].reference_count+=1;
            page_table[refrence_string[i]].is_valid =1;
            faults+=1;
            timestamp+=1;
        }
        else{
            int j=0,smallest=999,pos;
            for(j;j<table_cnt;j++){
                if(page_table[j].is_valid){
                    if(page_table[j].last_access_timestamp<smallest){
                    pos =j;
                    smallest = page_table[j].last_access_timestamp;
                    }
                }
            }

            page_table[pos].is_valid =0;
            page_table[pos].arrival_timestamp =0;
            page_table[pos].last_access_timestamp=0;
            page_table[pos].reference_count=0;
            int frnum = page_table[pos].frame_number; 
            page_table[pos].frame_number = -1;

            page_table[refrence_string[i]].frame_number = frnum;
            page_table[refrence_string[i]].arrival_timestamp = timestamp;
            page_table[refrence_string[i]].last_access_timestamp = timestamp;
            page_table[refrence_string[i]].reference_count=1;
          
            faults+=1;
            timestamp+=1;
        }
    }

    }
return faults;
}


int process_page_access_lfu(struct PTE page_table[TABLEMAX],int *table_cnt, int page_number,
int frame_pool[POOLMAX],int *frame_cnt, int current_timestamp){
    if(page_table[page_number].is_valid){
        page_table[page_number].last_access_timestamp = current_timestamp;
        page_table[page_number].reference_count+=1;
        return page_table[page_number].frame_number;
    }
    else{
        if(*frame_cnt>0){
            int freedframe = frame_pool[*frame_cnt-1];
            page_table[page_number].frame_number = freedframe;
            page_table[page_number].last_access_timestamp =current_timestamp;
            page_table[page_number].reference_count+=1;
            page_table[page_number].is_valid =1;
            *frame_cnt-=1;
            return freedframe;  
        }
        else{
            int i=0,smallest = 9999,pos;
            for(i;i<*table_cnt;i++){
                if(page_table[i].is_valid){
                if(page_table[i].reference_count < smallest){
                    smallest = page_table[i].reference_count;
                    pos =i;
                }
                }
            }

            for(i=0;i<*table_cnt;i++){
                if(page_table[pos].reference_count == page_table[i].reference_count ){
                    if(page_table[i].arrival_timestamp < page_table[pos].arrival_timestamp){
                        pos =i;
                    }
                }
            }
            page_table[pos].is_valid =0;
            page_table[pos].arrival_timestamp =0;
            page_table[pos].last_access_timestamp=0;
            page_table[pos].reference_count=0;
            int frnum = page_table[pos].frame_number; 
            page_table[pos].frame_number = -1;


            page_table[page_number].arrival_timestamp = current_timestamp;
            page_table[page_number].last_access_timestamp = current_timestamp;
            page_table[page_number].reference_count = 1;
            page_table[page_number].frame_number= frnum;
            page_table[page_number].is_valid =1;
            return frnum;
        }
    }

 }


int count_page_faults_lfu(struct PTE page_table[TABLEMAX],int table_cnt,
int refrence_string[REFERENCEMAX],int reference_cnt,int frame_pool[POOLMAX],int frame_cnt){
int timestamp =1,i=0,faults =0;
    for(i;i<=reference_cnt;i++){
        if(page_table[refrence_string[i]].is_valid){
            page_table[refrence_string[i]].last_access_timestamp = timestamp;
            page_table[refrence_string[i]].reference_count+=1;
            timestamp+=1;
        }
        else{
        if(frame_cnt>0){
            int freedframe = frame_pool[frame_cnt-1];
            frame_cnt-=1;
            page_table[refrence_string[i]].frame_number = freedframe;
            page_table[refrence_string[i]].arrival_timestamp = timestamp;
            page_table[refrence_string[i]].last_access_timestamp = timestamp;
            page_table[refrence_string[i]].reference_count+=1;
            page_table[refrence_string[i]].is_valid =1;
            faults+=1;
            timestamp+=1;
        }
        else{
            int j=0,smallest=999,pos;
            for(j;j<table_cnt;j++){
                if(page_table[j].is_valid){
                    if(page_table[j].arrival_timestamp<smallest){
                    pos =j;
                    smallest = page_table[j].arrival_timestamp;
                    }
                }
            }
            int k;
            for(k=0;k<table_cnt;k++){
                if(page_table[pos].reference_count == page_table[k].reference_count ){
                    if(page_table[k].arrival_timestamp < page_table[pos].arrival_timestamp){
                        pos =k;
                    }
                }
            }

            page_table[pos].is_valid =0;
            page_table[pos].arrival_timestamp =0;
            page_table[pos].last_access_timestamp=0;
            page_table[pos].reference_count=0;
            int frnum = page_table[pos].frame_number; 
            page_table[pos].frame_number = -1;

            page_table[refrence_string[i]].frame_number = frnum;
            page_table[refrence_string[i]].arrival_timestamp = timestamp;
            page_table[refrence_string[i]].last_access_timestamp = timestamp;
            page_table[refrence_string[i]].reference_count=1;
          
            faults+=1;
            timestamp+=1;
        }
    }

    }
    
return faults;

}
