/** \brief This class provides methods and stores data needed to compute the Levenshtein-distance of two
 *  given strings.
 */

#include "Typedef.h"
#ifndef LEVENSHTEIN_H
#define LEVENSHTEIN_H



class Levenshtein
{

    public:

        Levenshtein(SentenceList& a, SentenceList& b):Levenshtein(a,b,1,1,1) {};
        Levenshtein(SentenceList& a, SentenceList& b, Cost pen):Levenshtein(a,b,pen,pen,pen) {};

        /**< This is the basic ctor of this class. */
        Levenshtein(SentenceList& a, SentenceList& b, Cost subPen, Cost insPen, Cost delPen):sentenceA(a),sentenceB(b),substitutionCost(subPen),deletionCost(delPen),insertionCost(insPen) {

        };
        virtual ~Levenshtein();


        /** \brief This function allows to set the penalties for Substitution, deletion or insertion individually.
         *
         * \param type The type of the edit operation.
         * \param newCost The new cost for the edit operation.
         *
         */
        void setCost(const EditOperation& type, const Cost newCost);
        Cost getCost(const EditOperation& type);
        void setEditOperation(EditMatrix& mtx,const unsigned int i, const unsigned int j, EditOperation operation);
        EditOperation getEditOperation(EditMatrix& mtx, const unsigned int i, const unsigned int j);
        EditOperation determineEditOperation(const Word& a, const Word& b);
        Cost getPreviousCost(const unsigned int i, const unsigned int j);
        void calculateDistance(const WordList& a,const WordList& b);
    protected:
    private:
        SentenceList& sentenceA, sentenceB;/**< Set of sentences to compare. */
        Cost substitutionCost, deletionCost, insertionCost;
        DistanceMatrix distances;
        EditMatrix edits;
};

#endif // LEVENSHTEIN_H
