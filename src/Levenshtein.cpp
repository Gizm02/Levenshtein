#include "Levenshtein.h"

#include <climits>

#define INVALID_INPUT UINT_MAX


Levenshtein::~Levenshtein()
{
    //dtor
}


void Levenshtein::setCost(const EditOperation& type, const Cost newCost) {
    switch(type) {
        case DEL: deletionCost=newCost; break;
        case INS: insertionCost=newCost; break;
        case SUB: substitutionCost=newCost; break;
        default: break;///Do nothing, just for the compiler to stop warning.
    }
}


Cost Levenshtein::getCost(const EditOperation& type) {
    switch(type) {
        case DEL: return deletionCost;
        case INS: return insertionCost;
        case SUB: return substitutionCost;
        case NO: return 0;
        default: return INVALID_INPUT;/**< Case if no valid input was given. */
    }
}

EditOperation Levenshtein::determineEditOperation(Word& a, Word& b) {
    if(a.empty() && !b.empty()) {
        return INS;
    }
    else if(b.empty() && !a.empty()) {
        return DEL;
    }
    else if(a.compare(b)!=0) {
        return SUB;
    }
    return NO;
}
/*DistanceMatrix getDistanceMatrix() {
    return distances;
}*/

void Levenshtein::setEditOperation(EditMatrix& mtx,const unsigned int i, const unsigned int j, EditOperation operation) {
    mtx[i][j]=operation;
}

EditOperation Levenshtein::getEditOperation(EditMatrix& mtx, const unsigned int i, const unsigned int j) {
    return mtx[i][j];
}
