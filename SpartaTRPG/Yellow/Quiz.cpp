#include "Quiz.h"
#include "../Black/Singletons/CommonManagers.h"
#include <iostream>

Quiz::Quiz() {}

void Quiz::setQuestion(const Question& q) {
    question = q;
}



int Quiz::getAnswer()
{
    return question.answer;
}

std::string Quiz::getQuestion()
{
    return question.text;
}

std::string Quiz::getOpt(int i)
{
    return question.opts[i];
}


