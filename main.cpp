#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include "core.h"
#include "dude.h"
#include "indicator.h"


int main()
{
    std::vector<Dude> dudes;
    OneTry(dudes,0.34f);
    for(int i=0;i<=15;++i){
        dudes[i].display();
    }

    Indicators indicator;
    oneValidation(dudes,indicator);
    indicator.display();
}