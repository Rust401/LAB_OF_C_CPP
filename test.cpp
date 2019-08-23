#include<stdio.h>
#include<memory>
#include<vector>
#include<iostream>
#include<unistd.h>
#include<random>
#include<time.h>

const std::string fileName="./hanpi.txt";
FILE* fp;

static std::default_random_engine e(time(0));
static std::uniform_real_distribution<float> u(0,2);

std::vector<double> getDudeBeforeAvg(const double dude){
    double div_1=u(e);
    double div_2=-u(e);
    double div_3=0-div_1-div_2;
    return {dude+div_1,dude+div_2,dude+div_3};
}

std::vector<std::vector<double> > getResult(const std::vector<double>& inputValue){
    std::vector<std::vector<double>> result;
    for(auto dude:inputValue){
        result.push_back(getDudeBeforeAvg(dude));
    }
    return result;
}

void Display(const std::vector<std::vector<double>>& result){
    for(auto dude:result){
        for(int i=0;i<dude.size();++i){
            std::cout<<dude[i]<<" ";
        }
        std::cout<<std::endl;
    }
}

std::vector<double> readFromFile(FILE* fp){
    double input,output;
    std::vector<double> result;
    if((fp=fopen(fileName.c_str(),"r"))==nullptr){
        printf("File open error!\n");
        exit(0);
    }
    fseek(fp,0L,SEEK_END);
    uint64_t size=ftell(fp);
    rewind(fp);
    while(ftell(fp)<size){
        fscanf(fp,"%lf\t%lf\n",&input,&output);
        result.push_back(input);
        result.push_back(output);
    }
    return result;
}

int main()
{
    Display(getResult(readFromFile(fp)));
    return 0;
}