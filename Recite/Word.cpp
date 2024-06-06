#include "Word.h"

Word::Word(QObject *parent)
	: QObject(parent)
{
	this->pageIndex = 0;
	this->spelling = "NaN";
}

Word::Word()
{
	this->pageIndex = 0;
	this->spelling = "NaN";
}

Word::Word(const Word& another)
{
	this->pageIndex = another.pageIndex;
	this->spelling = another.spelling;
	this->meanings = another.meanings;
	this->type = another.type;
	this->synonyms = another.synonyms;
	this->nearSynonyms = another.nearSynonyms;
	this->antonyms = another.antonyms;
	this->similar = another.similar;
	this->noun = another.noun;
	this->verb = another.verb;
	this->adj = another.adj;
	this->adv = another.adv;
	this->usefulExpressions = another.usefulExpressions;
}

Word& Word::operator=(const Word& another)
{
	if (&another == this)
	{
		return *this;
	}
	this->pageIndex = another.pageIndex;
	this->spelling = another.spelling;
	this->meanings = another.meanings;
	this->type = another.type;
	this->synonyms = another.synonyms;
	this->nearSynonyms = another.nearSynonyms;
	this->antonyms = another.antonyms;
	this->similar = another.similar;
	this->noun = another.noun;
	this->verb = another.verb;
	this->adj = another.adj;
	this->adv = another.adv;
	this->usefulExpressions = another.usefulExpressions;

	return *this;
}

Word::Word(int pageIndex, QString spelling)
{
	this->pageIndex = pageIndex;
	this->spelling = spelling;
}

Word::~Word()
{}
