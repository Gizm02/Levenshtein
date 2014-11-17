/** \brief This class provides methods and stores data needed to compute the Levenshtein-distance of two
 *  given strings.
 */

#include "Typedef.h"
#ifndef LEVENSHTEIN_H
#define LEVENSHTEIN_H

#include <iostream>

class Levenshtein
{

    public:
        Levenshtein(WordList& a, WordList& b):Levenshtein(a,b,1,1,1) {};
        Levenshtein(WordList& a, WordList& b, Cost pen):Levenshtein(a,b,pen,pen,pen) {};

        /**< This is the basic ctor of this class. */
        Levenshtein(WordList& a, WordList& b, Cost subPen, Cost insPen, Cost delPen):sentenceA(a),sentenceB(b),substitutionCost(subPen),deletionCost(delPen),insertionCost(insPen) {
            std::cout << "Size of a is: "<<a.size()<<std::endl;
            std::cout << "Size of b is: "<<b.size()<<std::endl;



            /*! Idea: Provide a method to change the references a and b for recycling the Levenshtein-obj in the main.cpp
                and moreover, just compare two sentences in each call of the computeDistance(...) method.
            */

            /// Matrices with |A| rows
            distances.resize(a.size());
            edits.resize(a.size());


            /// And |B| columns.
            for(int j=0;j<a.size();j++) {
                distances[j].resize(b.size());
                edits[j].resize(b.size());
            }
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
        void calculateDistance();/*!<Calculate the word distance between two sentences.*/
        void setSentences(const WordList& a, const WordList& b);
        void printDistanceMatrix();
        void printEditMatrix();
        Cost getWER();
    protected:
    private:
        WordList& sentenceA, sentenceB;/**< Set of sentences to compare. */
        Cost substitutionCost, deletionCost, insertionCost;
        DistanceMatrix distances; ///Must be initialized first with their respective sizes!
        EditMatrix edits;
};

#endif // LEVENSHTEIN_H
