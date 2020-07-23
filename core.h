#include <vector>
#include <limits.h>
#include "para.h"
#include "dude.h"
#include "indicator.h"

void nextDude(Dude& preDude,Dude& currentDude, uint32_t index, double depth, double hammerMass);

void OneTry(std::vector<Dude>& dudes, double depth,double hammerMass);

void oneValidation(std::vector<Dude>& dudes, Indicators& indicators);

std::vector<std::pair<double,double>> getChainShape(std::vector<Dude>& dudes);

void saveTheChainShapeToFile(std::vector<std::pair<double,double> >& points);