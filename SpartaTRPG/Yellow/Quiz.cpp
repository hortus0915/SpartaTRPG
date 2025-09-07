#include "Quiz.h"
#include "../Black/Singletons/CommonManagers.h"
#include <iostream>

Quiz::Quiz() {}

void Quiz::setQuestion(const Question& q) {
    question = q;
}

bool Quiz::Render() {
    int posX = 30, posY = 10;
    int width = 60, height = 1;

    // 문제 출력
    SCENEMANAGER->RenderToBackbuffer(posX, posY, width, height, question.text, 1);

    // 보기 출력
    for (int i = 0; i < 4; ++i) {
        std::string optLine = std::to_string(i + 1) + ". " + question.opts[i];
        SCENEMANAGER->RenderToBackbuffer(posX, posY + i + 2, width, height,optLine, 1);
    }


   
    int choice = 0;
    

    bool correct = (choice - 1 == question.answer);


    return correct;
}
