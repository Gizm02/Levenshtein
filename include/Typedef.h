#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <vector>
#include <string>
#include <memory>

using Cost=unsigned int;
using CostPtr=std::shared_ptr<Cost>;
using Word=std::string;
using WordList=std::vector<Word>;
using SentenceList=std::vector<WordList>;
using CostVector=std::vector<Cost>;
using DistanceMatrix=std::vector<CostVector>;
using BackPtrMatrix=std::vector<std::vector<CostPtr>>;/**< Stores for each field of the DistanceMatrix its predecessor of the Levenshtein-algorithm. */

enum EditOperation {NO, SUB, INS, DEL};
enum ToBePrinted {DISTANCE,EDIT};
using EditVector=std::vector<EditOperation>; //Not used yet, used it one time but it doesn't hurt anybody to let it stay.
using EditMatrix=std::vector<EditVector>;

#endif // TYPEDEF_H
