#pragma once
#include <string>
#include <array>

struct Question {
    std::string text;                 // 문제
    std::array<std::string, 4> opts;  // 보기
    int answer;                       // 정답 인덱스 (0~3)
};

class Quiz {
public:
    Quiz();
    void setQuestion(const Question& q);
    int getAnswer();
    std::string getQuestion();
    std::string getOpt(int i);
private:
    Question question;
};
