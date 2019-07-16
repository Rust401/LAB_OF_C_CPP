#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <time.h> 
#include <limits.h>
#include <iostream>


int main(){
    volatile uint64_t a;
    volatile uint64_t* p=new volatile uint64_t;
    for(uint64_t i=0;i<10000;++i){
        a=i;
        *p=i;
        
    }
    if(a%100==0)std::cout<<a<<" "<<*p<<std::endl;
    return 0;
}