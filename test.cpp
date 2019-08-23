#include <bits/stdc++.h>


FILE* fp;

int main()
{
    double a,b;
    fp=fopen("./hanpi.txt","r");
    if(fp==nullptr)exit(0);
    fseek(fp,0L,SEEK_END);
    uint64_t size=ftell(fp);
    std::cout<<size<<std::endl;
    rewind(fp);

    while(ftell(fp)<size){
        std::cout<<ftell(fp)<<std::endl;
        fscanf(fp,"%lf\t%lf\n",&a,&b);
        std::cout<<fp<<std::endl;
        std::cout<<ftell(fp)<<std::endl;
        std::cout<<a<<" "<<b<<std::endl;
        std::cout<<" "<<std::endl;
        
        
    }

    fclose(fp);
    return 0;
}