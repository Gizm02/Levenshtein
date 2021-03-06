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
        default: std::cerr<<"This value is not a valid parameter value for Levenshtein::getCost! "<<std::endl; return INVALID_INPUT;/**< Case if no valid input was given. */
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

void Levenshtein::setEditOperation(const unsigned int i, const unsigned int j, EditOperation operation) {
    edits[i][j]=operation;
}

EditOperation Levenshtein::getEditOperation(const unsigned int i, const unsigned int j) {
    if(i<edits.size() && j<edits[i].size()) {/**< Only allow parameters */
        return edits[i][j];
    }
    #if DBG>0
        std::cerr<<"Index out of bounds error in"<<__FILE__<< "at line "<<__LINE__ <<std::endl;
    #endif
    return NO;
}


Cost Levenshtein::getPreviousCost(const unsigned int i, const unsigned int j) {
    if(i>0 && j >0) {
        return std::min(distances[i-1][j-1],std::min(distances[i-1][j],distances[i][j-1]));
    }
    #if DBG>0
        std::cerr<<"One of the indices is out of bounds!"<<std::endl;
    #endif // DBG
}


void Levenshtein::setSentences(const WordList& a, const WordList& b) {
    sentenceA=a;
    sentenceB=b;
    update(a.size(),b.size());
    #if DBG>0
        std::cout<<"Updated the matrices "<<std::endl;
    #endif
}



void Levenshtein::update(const unsigned int rows, const unsigned int columns) {/**< problem: columns is not equal in all words */
            for(unsigned int i=0;i<distances.size();i++) {/**< Clear the matrices. */
                distances.at(i).clear();
                edits.at(i).clear();
            }
            /// Matrices with |A| rows
            distances.resize(rows);
            edits.resize(rows);

            /// And |B| columns.
            for(unsigned int i=0;i<rows;++i) {
                distances[i].resize(columns);
                edits[i].resize(columns);
            }
}

void Levenshtein::printDistanceMatrix() {
    std::cout<<"Print the distance matrix d[i][j]. "<<std::endl;
    for(int i=0;i<distances.size();i++) {
        for(int j=0;j<distances[i].size();j++) {
            std::cout<<std::setw(5);
            std::cout<< distances[i][j];
        }
        std::cout<<std::endl;
    }
}

void Levenshtein::printEditMatrix() {
    std::cout<<"Print the editing matrix edit[i][j]. "<<std::endl;
    std::string output{""};
    for(int i=0;i<edits.size();i++) {
        for(int j=0;j<edits[i].size();j++) {
            switch(edits[i][j]) {
                case INS: output="INS";break;
                case SUB: output="SUB";break;
                case NO: output="NO";break;
                case DEL: output="DEL";break;
            }
            std::cout<<std::setw(6);
            std::cout << output;
        }
        std::cout<<std::endl;
    }
}


double Levenshtein::getWER(Cost& distance,size_t referenceSize) {
    double retValue=static_cast<double>(distance)/referenceSize;
    return retValue;
}

void Levenshtein::countEditingOperations(Cost& insertions,Cost& deletion, Cost& substitutions) {/**< Always call after computation of the distance matrix! */

}

void Levenshtein::printSentences(const WordList& a, const WordList& b) {
    std::cout<<"Print the spoken sentence:"<<std::endl;
    for(auto const& word: a) {
        std::cout<<word<<" ";
    }
    std::cout<<std::endl;
    std::cout<<"Print the recognized sentence:"<<std::endl;
    for(auto const& word: b) {
        std::cout<<word<<" ";
    }
    std::cout<<std::endl;
}

void Levenshtein::calculateDistance() {
    Levenshtein::calculateDistance(sentenceA,sentenceB);
}

Cost Levenshtein::getDistance(const unsigned int i, const unsigned int j) {
    if(i<distances.size() && j <distances.at(i).size()) {
        return distances[i][j];
    }
    ///No valid parameters:
    std::cerr<<"Invalid arguments. Passed indeces hurt the boundaries of the distance matrix!"<<std::endl;
    return INVALID_INPUT;
}

void Levenshtein::calculateDistance(const WordList& senA, const WordList& senB)
 {
    Levenshtein::update(senA.size(),senB.size());
    #if DBG>0
        std::cout<<"Updated the matrices "<<std::endl;
        std::cout << "Starting computing the distance matrix. Initial Part. "<<std::endl;
    #endif
    /*******************Initialize the distance matrix/ default cases *****************************/
    if(senA.at(0).compare(senB.at(0))!=0) {
        distances.at(0).at(0)=1;
        edits.at(0).at(0)=determineEditOperation(senA.at(0),senB.at(0));
    }
    else {
        distances.at(0).at(0)=0;
        edits.at(0).at(0)=NO;
    }
    Cost j=distances.at(0).at(0)+1;
    #if DBG>0
        std::cout<<"Until now everything is just fine. File "<<__FILE__<<", line "<<__LINE__<<std::endl;
    #endif // DBG
    size_t minSize=std::min(senA.size(),senB.size());
    size_t i;
    for(i=1;i<minSize;++i) {
        distances.at(0).at(i)=j;
        distances.at(i).at(0)=j;
        edits.at(0).at(i)=DEL;
        edits.at(i).at(0)=INS;
        ++j;
    }


    if(senA.size()<senB.size()) {
        /// i=senA.size()
        #if DBG>0
            std::cout<<"Until now everything is just fine. File "<<__FILE__<<", line "<<__LINE__<<std::endl;
        #endif // DBG
        for(;i<senB.size();++i) {
            distances.at(0).at(i)=j;
            edits.at(0).at(i)=INS;
            ++j;
        }
    }
    else  if(senA.size()>senB.size()) {
        #if DBG>0
            std::cout<<"Until now everything is just fine. File "<<__FILE__<<", line "<<__LINE__<<std::endl;
        #endif // DBG
        for(;i<senA.size();++i) {
            distances.at(i).at(0)=j;
            edits.at(i).at(0)=DEL;
            ++j;
        }
    }

    #if DBG>0
        std::cout<<"Until now everything is just fine. File "<<__FILE__<<", line "<<__LINE__<<std::endl;
    #endif // DBG

    /******************Start computing the non-trivial cases ***************************************/

    #if DBG>0
        std::cout<<"Computing the distances for the non-trivial cases now. "<<std::endl;
        std::cout<<"It is senA.size()=="<<senA.size()<<" and senB.size()=="<<senB.size()<<std::endl;
    #endif
    for(unsigned int i=1;i<senA.size();++i) {
        for(unsigned int j=1;j<senB.size();++j) {
            if(i<=j) {
                edits.at(i).at(j)=determineEditOperation(senA.at(i),senB.at(j));
            }
            else { ///i > j, values beyond the diagonal axis
                edits.at(i).at(j)=INS;
            }
            Cost editingCosts;
            switch(edits.at(i).at(j)) {
                case INS: editingCosts=insertionCost; break;
                case SUB: editingCosts=substitutionCost; break;
                case DEL: editingCosts=deletionCost;break;
                default: editingCosts=0; break; ///case edits.at(i).at(j)==NO
            }
            distances.at(i).at(j)=getPreviousCost(i,j)+editingCosts;
        }
    }
}
