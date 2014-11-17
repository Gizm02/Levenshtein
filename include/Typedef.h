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
using DistanceMatrix=std::vector<std::vector<Cost>>;
using BackPtrMatrix=std::vector<std::vector<CostPtr>>;/**< Stores for each field of the DistanceMatrix its predecessor of the Levenshtein-algorithm. */

enum EditOperation {NO, SUB, INS, DEL};
using EditMatrix=std::vector<std::vector<EditOperation>>;

#endif // TYPEDEF_H
