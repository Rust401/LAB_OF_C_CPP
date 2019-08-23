#include<stdio.h>
#include<memory>
#include<vector>
#include<iostream>
#include<unistd.h>
#include<random>
#include<time.h>
#include<unordered_set>
#include<algorithm>

#define timePeriod 5
#define numsOfGame 5
#define dataMatrix std::vector<std::vector<Cell>>
#define duelSet std::unordered_set<std::string>



struct Cell
{
    bool hasElement;
    std::string duel;
    Cell(const std::string& duel="??"){
        hasElement=false;
        this->duel=duel;
    }
};

std::vector<char> teams={'A','B','C','D','E','F'};
duelSet remainDule;
dataMatrix matrix(numsOfGame,std::vector<Cell>(timePeriod,Cell()));


std::unordered_set<std::string> duelInit(const std::vector<char> teams){
    std::unordered_set<std::string> result;
    for(int i=0;i<teams.size();++i){
        for(int j=i+1;j<teams.size();++j){
            std::string tmp;
            tmp+=teams[i];
            tmp+=teams[j];
            result.insert(tmp);
        }
    }
    return result;
}

void DisplayDuel(const std::unordered_set<std::string>& dudes){
    for(auto dude:dudes){
        std::cout<<dude<<std::endl;
    }
}

void DisplayMatrix(const std::vector<std::vector<Cell>>& matrix){
    for(int i=0;i<matrix.size();++i){
        for(int j=0;j<matrix[0].size();++j){
            std::cout<<matrix[i][j].duel<<" ";
        }
        std::cout<<std::endl;
    }
}

void matrixInit(std::vector<std::vector<Cell>>& matrix){
    for(int i=0;i<timePeriod;++i){
        matrix[i][i].hasElement=true;
        std::string tmp;
        tmp+=teams[0];
        tmp+=teams[i+1];
        remainDule.erase(tmp);
        matrix[i][i].duel=tmp;
    }
}

int main()
{
    remainDule=duelInit(teams);
    matrixInit(matrix);
    DisplayDuel(remainDule);
    DisplayMatrix(matrix);
    for(int i=0;i<numsOfGame;++i){
        int slow=0;
        int fast=0;
        std::unordered_set<char> tmp={'A','B','C','D','E','F'};
        for(int j=0;j<timePeriod;++j){
            if(matrix[i][j].hasElement){
                tmp.erase(matrix[i][j].duel[0]);
                tmp.erase(matrix[i][j].duel[1]);
            }
        }
        std::vector<char> tmpVector(tmp.size());
        std::copy(tmp.begin(),tmp.end(),tmpVector.begin());
        sort(tmpVector.begin(),tmpVector.end());
        for(auto dude:tmpVector){
            std::cout<<dude<<" "<<std::endl;
        }
        break;

    }

    

}