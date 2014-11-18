#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <vector>
#include <string>
#include <memory>

#define DBG 1

using Cost=unsigned int;
using CostPtr=std::shared_ptr<Cost>;
using Word=std::string;
using WordList=std::vector<Word>;
using SentenceList=std::vector<WordList>;
using CostVector=std::vector<Cost>;
using DistanceMatrix=std::vector<CostVector>;

///The BackPtrMatrix is not needed yet but do not remove it for further refinement of the functionality.
using BackPtrMatrix=std::vector<std::vector<CostPtr>>;/**< Stores for each field of the DistanceMatrix its predecessor of the Levenshtein-algorithm. */

enum EditOperation {NO, SUB, INS, DEL};
using EditVector=std::vector<EditOperation>; //Not used yet, used it one time but it doesn't hurt anybody to let it stay.
using EditMatrix=std::vector<EditVector>;

#endif // TYPEDEF_H
