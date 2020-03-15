#include "array_operations.hh"


int greatest_v1(int *itemptr, int size){

    int max = *itemptr;
    for(int i = 0; i < size; i++){
        if (*itemptr > max) {
            max = *itemptr;
        }
        itemptr++;
    }
    return max;
}

int greatest_v2(int *itemptr, int *endptr){

    int max = *itemptr;
    while(itemptr != endptr){
        if (*itemptr > max) {
            max = *itemptr;
        }
        itemptr++;
    }
    return max;

}

void copy(int *itemptr, int *endptr, int *targetptr){

    while(itemptr != endptr){
        int max = *itemptr;
        *targetptr = max;
        itemptr++;
        targetptr++;
    }
}


void reverse(int *leftptr, int *rightptr){
    rightptr--;
    while (*leftptr < *rightptr){
        int temp = *leftptr;
        *leftptr = *rightptr;
        *rightptr = temp;
        leftptr++;
        rightptr--;
    }
}
