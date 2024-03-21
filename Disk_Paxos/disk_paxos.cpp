#include <iostream>
#include <vector>
std::vector<std::vector<int>> disk;
const int DISK_NUMBER = 3;
const int PROCESSOR_NUMBER = 2;
std::vector<int> non_Init_Blks;
struct dblock{
    int mbal;
    int bal;
    int inp;
};
#define NOTANINPUT 9527

void start_ballot(dblock &dblock_, int mbal_){
    dblock_.bal = 0;
    dblock_.inp = NOTANINPUT;
    dblock_.mbal = mbal_;
}
void read_disk(int i, int j){

}
bool check_validation(){
    return true;
}
void commit(){

}
void write_disk(){

}
int maximal_bal_input_value(){

}
/*
1. return true if no abort, otherwise false.
*/ 
bool disk_paxos(dblock &dblock_, int phase){
    // concurrently handle all disks
    int success_write_count = 0;
    for(int i = 0; i < DISK_NUMBER; i++) {
        // all processors
        bool valid = true;
        write_disk();
        for(int j = 0; j < PROCESSOR_NUMBER; j++) {
            read_disk(i, j);
            if(!check_validation()){
                valid = false;
                break;
            }
        }
        success_write_count += valid;
        if(success_write_count > DISK_NUMBER/2 + 1){
            break;
        }
    }
    if(success_write_count < DISK_NUMBER/2+1){
        return false;
    }

    if(phase == 1){
        dblock_.bal = dblock_.mbal;
        if(non_Init_Blks.empty()){
            dblock_.inp = 1327; // your value
        }else{
            dblock_.inp = maximal_bal_input_value();
        }
    }else{
        commit();
    }
    return true;
}

void restart_after_failure(){

}


int main() {
    // processor 1
    dblock dblock1;
    start_ballot(dblock1, 1);
    // processor 2
    dblock dblock2;
    start_ballot(dblock2, 2);
    // 多线程测试
    // 输入的值到底是什么？
    // 它能保证输出的值是一致的
    // 记录谁是主
    disk_paxos(dblock1, 1);
    disk_paxos(dblock1, 2);
    disk_paxos(dblock2, 1);
    disk_paxos(dblock2, 2);
    // 并发访问，但是不加锁，最终要保证输出的值一致
    return 0;
}