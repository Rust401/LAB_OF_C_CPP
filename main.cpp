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
    OneTry(dudes,1.0f);
    dudes[0].display();
    Indicators indicator;
    oneValidation(dudes,indicator);
    indicator.display()
;
}