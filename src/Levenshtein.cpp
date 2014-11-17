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
        case NO: break; ///Do nothing, just for the compiler to stop warning.
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

EditOperation Levenshtein::determineEditOperation(const Word& a,const Word& b) {
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


Cost Levenshtein::getPreviousCost(const unsigned int i, const unsigned int j) {
    return std::min(distances[i-1][j-1],std::min(distances[i-1][j],distances[i][j-1]));
}


void Levenshtein::calculateDistance(const WordList& a, const WordList& b) {
    /*******************Initialize the distance matrix/ default cases *****************************/
    if(a[0].compare(b[0])!=0) {
        distances[0][0]=1;
    }
    else {
        distances[0][0]=0;
    }

    Cost j=distances[0][0];
    for(size_t i=1;i<a.size();i++,j++) {
        distances[0][i]=j;
    }
    j=distances[0][0];
    for(size_t i=1;i<b.size();i++,j++) {
        distances[i][0]=j;
    }
    /******************Start computing the non-trivial cases ***************************************/
    for(unsigned int i=1;i<a.size();i++) {
        for(unsigned int j=1;j<b.size();j++) {
            edits[i][j]=determineEditOperation(a[i],b[j]);
            distances[i][j]=(a[i]!=b[j])?getPreviousCost(i,j)+1:getPreviousCost(i,j);
        }
    }
}
