#include "Levenshtein.h"

#include <climits>

#define INVALID_INPUT UINT_MAX

Levenshtein::Levenshtein()
{
    //ctor
}

Levenshtein::~Levenshtein()
{
    //dtor
}

Cost Levenshtein::getCost(EditOperation type) {
    switch(type) {
        case DEL: return deletionCost;
        case INS: return insertionCost;
        case SUB: return substitutionCost;

        default: return INVALID_INPUT;/**< Case if no valid input was given. */
    }
}

void Levenshtein::setCost(EditOperation type, Cost newValue) {
    switch(type) {
        case DEL: deletionCost=newValue; break;
        case INS: insertionCost=newValue; break;
        case SUB: substitutionCost=newValue; break;
        default: ;///Do nothing, just for the compiler to stop warning.
    }
}
