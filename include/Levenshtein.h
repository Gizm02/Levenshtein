/** \brief This class provides methods and stores data needed to compute the Levenshtein-distance of two
 *  given strings.
 */


#ifndef LEVENSHTEIN_H
#define LEVENSHTEIN_H

#include <vector>
#include <string>
#include <memory>

using Cost=unsigned int;
using CostPtr=std::shared_ptr<Cost>;
using Word=std::string;
using WordList=std::vector<Word>;
using SentenceList=std::vector<WordList>;
using DistanceMatrix=std::vector<std::vector<Cost>>;
using BackPtrMatrix=std::vector<std::vector<CostPtr>>;/**< Stores for each field of the DistanceMatrix its predecessor of the Levenshtein-algorithm. */

enum EditOperation {NO, SUB, INS, DEL};
using EditMatrix=std::vector<std::vector<EditOperation>>;

class Levenshtein
{

    public:

        Levenshtein(WordList& a, WordList& b):Levenshtein(a,b,1,1,1) {};
        Levenshtein(WordList& a, WordList& b, Cost pen):Levenshtein(a,b,pen,pen,pen) {};

        /**< This is the basic ctor of this class. */
        Levenshtein(WordList& a, WordList& b, Cost subPen, Cost insPen, Cost delPen):sentenceA(a),sentenceB(b),substitutionCost(subPen),deletionCost(delPen),insertionCost(insPen) {};
        virtual ~Levenshtein();


        /** \brief This function allows to set the penalties for Substitution, deletion or insertion individually.
         *
         * \param old This is one of the
         * \param
         * \return
         *
         */
        void setCost(const EditOperation& type, const Cost newCost);
        Cost getCost(const EditOperation& type);
        void setEditOperation(EditMatrix& mtx,const unsigned int i, const unsigned int j, EditOperation operation);
        EditOperation getEditOperation(EditMatrix& mtx, const unsigned int i, const unsigned int j);
        EditOperation determineEditOperation(Word& a, Word& b);
    protected:
    private:
        WordList& sentenceA, sentenceB;/**< Sentences to compare. */
        Cost substitutionCost, deletionCost, insertionCost;
        DistanceMatrix distances;
        EditMatrix edits;
};

#endif // LEVENSHTEIN_H
