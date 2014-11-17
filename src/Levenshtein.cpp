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


void Levenshtein::setSentences(const WordList& a, const WordList& b) {
    sentenceA=a;
    sentenceB=b;
}

void Levenshtein::printDistanceMatrix() {
    for(int i=0;i<sentenceA.size();i++) {
        for(int j=0;j<sentenceB.size();j++) {
            std::cout<<" " << distances[i][j];
        }
        std::cout<<std::endl;
    }
}

void Levenshtein::printEditMatrix() {
    std::string output{""};
    for(int i=0;i<sentenceA.size();i++) {
        for(int j=0;j<sentenceB.size();j++) {
            switch(distances[i][j]) {
                case INS: output="INS";break;
                case SUB: output="SUB";break;
                case NO: output="NO";break;
                case DEL: output="DEL";break;
            }
            std::cout<<" " << output;
        }
        std::cout<<std::endl;
    }
}


Cost Levenshtein::getWER() {
    return 0;
}


void Levenshtein::calculateDistance() {

    std::cout << "Starting computing the distance matrix. Initial Part. "<<std::endl;
    /*******************Initialize the distance matrix/ default cases *****************************/
    if(sentenceA[0].compare(sentenceB[0])!=0) {
        distances[0][0]=1;
    }
    else {
        distances[0][0]=0;
    }

    Cost j=distances[0][0];
    for(size_t i=1;i<sentenceA.size();i++,j++) {
        distances[0][i]=j;
    }
    j=distances[0][0];
    for(size_t i=1;i<sentenceB.size();i++,j++) {
        distances[i][0]=j;
    }

    /******************Start computing the non-trivial cases ***************************************/


    std::cout<<"Computing the distances for the non-trivial cases now. "<<std::endl;
    for(unsigned int i=1;i<sentenceA.size();i++) {
        for(unsigned int j=1;j<sentenceB.size();j++) {
            edits[i][j]=determineEditOperation(sentenceA[i],sentenceB[j]);
            distances[i][j]=        (sentenceA[i]!=sentenceB[j])      ?       getPreviousCost(i,j)+1      :       getPreviousCost(i,j);
        }
    }
}
