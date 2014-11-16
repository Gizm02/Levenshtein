/** \brief This class provides methods and stores data needed to compute the Levenshtein-distance of two
 *  given strings.
 */


#ifndef LEVENSHTEIN_H
#define LEVENSHTEIN_H

#include <vector>
#include <string>

typedef unsigned int Cost;
typedef std::string Word;
typedef std::vector<Word> WordList;
typedef std::vector<WordList> SentenceList;

enum EditOperation {NO, SUB, INS, DEL};


class Levenshtein
{
    public:
        Levenshtein();
        Levenshtein(WordList a, WordList b):Levenshtein(a,b,1,1,1) {};
        Levenshtein(WordList a, WordList b, Cost pen):Levenshtein(a,b,pen,pen,pen) {};

        /**< This is the basic ctor of this class. */
        Levenshtein(WordList a, WordList b, Cost subPen, Cost insPen, Cost delPen):sentenceA(a),sentenceB(b),substitutionCost(subPen),deletionCost(delPen),insertionCost(insPen) {};
        virtual ~Levenshtein();


        /** \brief This function allows to set the penalties for Substitution, deletion or insertion individually.
         *
         * \param old This is one of the
         * \param
         * \return
         *
         */
        void setCost(EditOperation type, Cost newValue);
        Cost getCost(EditOperation type);

    protected:
    private:
        WordList sentenceA, sentenceB;/**< Sentences to compare. */
        Cost substitutionCost, deletionCost, insertionCost;
};

#endif // LEVENSHTEIN_H
