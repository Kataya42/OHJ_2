#include "swap.hh"

extern int i;
extern int j;

void swap(int& i, int& j){
    int temp = i;
    i = j;
    j = temp;
}
