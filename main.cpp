#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include "Levenshtein.h"



// definition of data types
///typedef std::string Word;
///typedef std::vector<Word> WordList;
typedef std::vector<WordList> SentenceList;

///enum EditOperation {NO, SUB, INS, DEL};
struct AlignmentElement {
    Word spoken;
    Word recog;
    EditOperation operation;

    AlignmentElement(const Word & spoken, const Word & recog, EditOperation operation) :
	spoken(spoken), recog(recog), operation(operation) {}
};
typedef std::vector<AlignmentElement> Alignment;



// i/o-functionality
void readSentences(std::ifstream & is, SentenceList & s);
void writeAlignment(const Alignment & a, std::ostream & o);


// main
void usage();
int main(int argc, char* argv[]);



// -----------------------------------------------------------------------------
// i/o-functionality

/** \brief  This method reads line-wise sentences from an input file and reads each line word wise.
 *
 * \param   is Input File Stream obj to read from.
 * \param   sentences Two dimensional string vector containg the sentences ought to be compared.
 *
 */
void readSentences(std::ifstream & is, SentenceList & sentences) {
    std::string buffer;
    Word word;
    /**< Read in line from file -> store in buffer -> extract words and store them in sentence -> push sentence to the sentences List. */
    while (std::getline(is, buffer)) {
	if (buffer.size() == 0)
	    continue;
	std::istringstream line(buffer.c_str());/**< Stores the seperate words of a file line. */
	WordList sentence;
	while (line >> word)/**< Read in word wise the current line of the input file. */
	    sentence.push_back(word);
	sentences.push_back(sentence);
    }
}

/*
  How to use writeAlignment:

  1: Alignment alignment;
  2: alignment.push_back(AlignmentElement("HELLO", "HOW", SUB));
  3: alignment.push_back(AlignmentElement("",      "LOW", INS));
  4: writeAlignment(alignment, std::cout);
*/
void writeAlignment(const Alignment & alignment, std::ostream & os) {
    std::ostringstream ossSpoken, ossRecog, ossOperation;
    int length;
    for (Alignment::const_iterator itAlignment = alignment.begin();
	 itAlignment != alignment.end(); ++itAlignment)
	switch (itAlignment->operation) {
	case NO:
	    length = std::max(itAlignment->spoken.size(), itAlignment->recog.size()) + 1;
	    ossSpoken    << std::left << std::setw(length) << itAlignment->spoken;
	    ossRecog     << std::left << std::setw(length) << itAlignment->recog;
	    ossOperation << std::left << std::setw(length) << " ";
	    break;
	case SUB:
	    length = std::max(itAlignment->spoken.size(), itAlignment->recog.size()) + 1;
	    ossSpoken    << std::left << std::setw(length) << itAlignment->spoken;
	    ossRecog     << std::left << std::setw(length) << itAlignment->recog;
	    ossOperation << std::left << std::setw(length) << "S";
	    break;
	case INS:
	    length = itAlignment->recog.size() + 1;
	    ossSpoken    << std::left << std::setw(length) << " ";
	    ossRecog     << std::left << std::setw(length) << itAlignment->recog;
	    ossOperation << std::left << std::setw(length) << "I";
	    break;
	case DEL:
	    length = itAlignment->spoken.size() + 1;
	    ossSpoken    << std::left << std::setw(length) << itAlignment->spoken;
	    ossRecog     << std::left << std::setw(length) << " ";
	    ossOperation << std::left << std::setw(length) << "D";
	    break;
	}
    os << std::endl;
    os << ossSpoken.str()    << std::endl;
    os << ossRecog.str()     << std::endl;
    os << ossOperation.str() << std::endl;
}






// -----------------------------------------------------------------------------
// main

void usage(const char * basename) {
    std::cerr << " usage: " << basename
	      << " <spoken-sentences-file> <recognized-sentences-file>"
	      << std::endl;
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]){
    // check for correct number of command line arguments
    if (argc != 3)
	usage(argv[0]);


    // read spoken and recognized sentences from files
    SentenceList spoken, recog;
    {
	std::ifstream spokenStream(argv[1]);
	if (!spokenStream) {
	    std::cerr << std::endl << "ERROR: " << argv[1] << " could not be opened"
		      << std::endl;
	    return 2;
	}
	std::ifstream recogStream(argv[2]);
	if (!recogStream) {
	    std::cerr << std::endl << "ERROR: " << argv[2] << " could not be opened"
		      << std::endl;
	    return 2;
	}

	readSentences(spokenStream, spoken);
	readSentences(recogStream, recog);
	if (spoken.size() != recog.size()){
	    std::cerr << std::endl << "ERROR: Number of sentences do not match!"
		      << " (" << spoken.size() << "/" << recog.size() << ")"
		      << std::endl;
	    return 3;
	}
    }


    // ... <your code>


    return 0;
}
