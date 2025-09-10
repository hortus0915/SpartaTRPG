#include "PoketmonNaming.h"
#include <codecvt>
#include <locale>

// 테이블 정의
const std::wstring PoketmonNaming::CHOSEONG = L"ㄱㄲㄴㄷㄸㄹㅁㅂㅃㅅㅆㅇㅈㅉㅊㅋㅌㅍㅎ";
const std::wstring PoketmonNaming::JUNGSEONG = L"ㅏㅐㅑㅒㅓㅔㅕㅖㅗㅘㅙㅚㅛㅜㅝㅞㅟㅠㅡㅢㅣ";
const std::wstring PoketmonNaming::JONGSEONG = L" ㄱㄲㄳㄴㄵㄶㄷㄹㄺㄻㄼㄽㄾㄿㅀㅁㅂㅄㅅㅆㅇㅈㅊㅋㅌㅍㅎ";

const std::map<std::wstring, wchar_t> PoketmonNaming::jungseongCompose = {
    {L"ㅗㅏ", L'ㅘ'}, {L"ㅗㅐ", L'ㅙ'}, {L"ㅗㅣ", L'ㅚ'},
    {L"ㅜㅓ", L'ㅝ'}, {L"ㅜㅔ", L'ㅞ'}, {L"ㅜㅣ", L'ㅟ'},
    {L"ㅡㅣ", L'ㅢ'}
};

const std::map<std::wstring, wchar_t> PoketmonNaming::jongseongCompose = {
    {L"ㄱㅅ", L'ㄳ'}, {L"ㄴㅈ", L'ㄵ'}, {L"ㄴㅎ", L'ㄶ'},
    {L"ㄹㄱ", L'ㄺ'}, {L"ㄹㅁ", L'ㄻ'}, {L"ㄹㅂ", L'ㄼ'},
    {L"ㄹㅅ", L'ㄽ'}, {L"ㄹㅌ", L'ㄾ'}, {L"ㄹㅍ", L'ㄿ'}, {L"ㄹㅎ", L'ㅀ'},
    {L"ㅂㅅ", L'ㅄ'}
};

// 유틸리티 함수
int PoketmonNaming::idxIn(const std::wstring& s, wchar_t ch) {
    size_t pos = s.find(ch);
    return (pos == std::wstring::npos) ? -1 : static_cast<int>(pos);
}

wchar_t PoketmonNaming::makeHangul(wchar_t cho, wchar_t jung, wchar_t jong) {
    int choIndex = idxIn(CHOSEONG, cho);
    int jungIndex = idxIn(JUNGSEONG, jung);
    int jongIndex = idxIn(JONGSEONG, jong); // ' '이면 0
    if (choIndex < 0 || jungIndex < 0 || jongIndex < 0) return L'?';
    int SIndex = (choIndex * JUNGSEONG_COUNT + jungIndex) * JONGSEONG_COUNT + jongIndex;
    return static_cast<wchar_t>(HANGUL_BASE + SIndex);
}

// UTF-16 → UTF-8 변환
std::string PoketmonNaming::toUTF8(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> conv;
    return conv.to_bytes(wstr);
}

// 실제 한글 조합 로직 (원래 compose 코드 기반, 결과는 wstring)
std::wstring PoketmonNaming::composeW(const std::vector<wchar_t>& input) {
    std::wstring result;
    size_t i = 0, n = input.size();

    wchar_t cho = L' ', jung = L' ', jong = L' ';
    bool hasCho = false, hasJung = false, hasJong = false;

    auto flush = [&]() {
        if (hasCho && hasJung) {
            result.push_back(makeHangul(cho, jung, hasJong ? jong : L' '));
        }
        else {
            if (hasCho) result.push_back(cho);
            if (hasJung) result.push_back(jung);
            if (hasJong) result.push_back(jong);
        }
        hasCho = hasJung = hasJong = false;
        cho = jung = jong = L' ';
        };

    while (i < n) {
        wchar_t c = input[i];
        bool isChoChar = (CHOSEONG.find(c) != std::wstring::npos);
        bool isJungChar = (JUNGSEONG.find(c) != std::wstring::npos);
        bool isJongChar = (JONGSEONG.find(c) != std::wstring::npos && c != L' ');

        // 여기서는 원래 main.cpp의 compose 로직을 그대로 옮겨와야 함
        // 1) 모음이 들어온 경우
        if (isJungChar) {
            // 특이 케이스: 현재 음절에 받침이 이미 있고 모음이 나오면,
            // 그 받침은 다음 음절의 초성이 되어야 하는 경우가 있음
            if (hasJong) {
                // 예: (초성+중성+종성) + 모음  => 종성을 떼서 다음 초성으로 이동
                wchar_t movedCho = jong;
                // 이전 음절은 받침 없이 확정
                result.push_back(makeHangul(cho, jung, L' '));
                // 새 음절 시작: movedCho + current vowel
                cho = movedCho;
                jung = c;
                hasCho = true;
                hasJung = true;
                hasJong = false;
                jong = L' ';
                i++;
                continue;
            }

            if (!hasCho && !hasJung) {
                // 모음이 먼저 나오면 초성으로 ㅇ을 자동으로 채움
                cho = L'ㅇ';
                jung = c;
                hasCho = true;
                hasJung = true;
                i++;
                continue;
            }
            if (hasCho && !hasJung) {
                jung = c;
                hasJung = true;
                i++;
                continue;
            }
            if (hasCho && hasJung && !hasJong) {
                // 이미 중성이 있는데 또 모음이 들어오면 합성 시도
                std::wstring key;
                key.push_back(jung);
                key.push_back(c);
                auto it = jungseongCompose.find(key);
                if (it != jungseongCompose.end()) {
                    jung = it->second;
                    i++;
                    continue;
                }
                else {
                    // 합성 불가하면 현재 글자 완료 후 새 음절 시작 (초성 자동 ㅇ)
                    flush();
                    cho = L'ㅇ';
                    jung = c;
                    hasCho = true;
                    hasJung = true;
                    i++;
                    continue;
                }
            }
            // 기타 안전 처리
            i++;
            continue;
        }

        // 2) 자음이 들어온 경우
        if (isChoChar) {
            // (A) 아직 초성 없을 때 -> 초성으로 사용
            if (!hasCho) {
                cho = c; hasCho = true;
                i++;
                continue;
            }
            // (B) 초성은 있는데 중성이 없을 때 -> 기존 초성 출력(단독자모)하고 새 초성으로
            if (hasCho && !hasJung) {
                // 같은 패턴: 두 자음 연달아 -> 이전 초성은 단독으로 결과에 추가
                result.push_back(cho);
                cho = c;
                hasCho = true;
                hasJung = false;
                hasJong = false;
                jung = jong = L' ';
                i++;
                continue;
            }
            // (C) 초성+중성 있고 아직 종성 없는 경우 -> 이 자음을 종성으로 쓸지,
            //     아니면 다음 음절의 초성으로 쓸지 판단(lookahead)
            if (hasCho && hasJung && !hasJong) {
                // lookahead: 다음 문자가 있고 그게 모음이면 지금의 자음은 '다음 음절의 초성'이다.
                if (i + 1 < n && JUNGSEONG.find(input[i + 1]) != std::wstring::npos) {
                    // 현재 음절을 확정(종성 없음), 다음 음절의 초성으로 처리
                    flush();
                    cho = c;
                    hasCho = true;
                    i++;
                    continue;
                }
                else {
                    // 다음이 모음이 아니면(없거나 자음) -> 종성으로 사용 가능성을 검토
                    // 우선 겹종성(두 자음 합쳐서 종성) 가능하면 합성 시도
                    if (i + 1 < n && CHOSEONG.find(input[i + 1]) != std::wstring::npos) {
                        std::wstring key;
                        key.push_back(c);
                        key.push_back(input[i + 1]);
                        auto it = jongseongCompose.find(key);
                        if (it != jongseongCompose.end()) {
                            // 단, 합성 후에 그 다음 문자가 모음이면 합성하면 안 됨(그 경우 두번째 자음은 다음 음절 초성)
                            if (!(i + 2 < n && JUNGSEONG.find(input[i + 2]) != std::wstring::npos)) {
                                // 안전: 합성해서 겹받침으로 사용
                                jong = it->second;
                                hasJong = true;
                                i += 2;
                                continue;
                            }
                        }
                    }
                    // 그대로 단일 종성으로 사용
                    jong = c;
                    hasJong = true;
                    i++;
                    continue;
                }
            }
            // (D) 초성+중성+종성 이미 있는 상태 -> 시도: 기존 종성 + 현재 자음으로 겹종성 만들기
            if (hasCho && hasJung && hasJong) {
                std::wstring key;
                key.push_back(jong);
                key.push_back(c);
                auto it = jongseongCompose.find(key);
                if (it != jongseongCompose.end()) {
                    jong = it->second; // 겹받침으로 확장
                    i++;
                    continue;
                }
                else {
                    // 합성 불가하면 현재 음절 확정하고 새 초성 시작
                    flush();
                    cho = c; hasCho = true;
                    i++;
                    continue;
                }
            }
            // fallback
            i++;
            continue;
        }

        // 3) 자모로 인식되지 않는 경우(숫자/특수/영문 등) -> 현재 음절 flush 후 문자 그대로 추가
        flush();
        result.push_back(c);
        // (길어서 생략했지만 그대로 붙여넣으면 됩니다)

        i++; // 안전장치 (실제 로직에서는 상황에 따라 다르게 증가)
    }
    result.push_back('\0');
    if (hasCho || hasJung || hasJong) flush();
    return result;
}

// 외부에서 호출하는 함수: UTF-8 string 반환
std::string PoketmonNaming::Compose(const std::vector<wchar_t>& input) {
    std::wstring wres = composeW(input);
    return toUTF8(wres);
}
