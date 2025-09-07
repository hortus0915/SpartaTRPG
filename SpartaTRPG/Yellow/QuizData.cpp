#include "QuizDate.h"
#include <vector>

std::vector<Question> LoadQuizData() {
    std::vector<Question> questions = {
        {
            "다음 중 C++에서 동적 메모리 할당 키워드는?",
            { "alloc", "malloc", "new", "create" },
            2
        },
        {
            "다음 중 C++ 표준 컨테이너가 아닌 것은?",
            { "std::vector", "std::hash_map", "std::deque", "std::forward_list" },
            1
        },
        {
            "RAII에 대한 설명으로 옳은 것은?",
            { "런타임 최적화 기법", "리소스를 예외 안전하게 관리하는 관용구", "가비지 컬렉션의 또 다른 이름", "C 언어에만 존재" },
            1
        }
    };
    return questions;
}
