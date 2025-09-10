#include "PoketmonNaming.h"
#include <codecvt>
#include <locale>
#include <Windows.h>

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
    const size_t len = wcslen(wstr.c_str()) + 1;
    const size_t new_len = len * 2;
    char* c = new char[new_len];
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), len, c, new_len, nullptr, nullptr);
    std::string temp = c;
    delete[] c;

    return temp;
}
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

        // 1) 모음 처리
        if (isJungChar) {
            if (hasJong) {
                // 종성이 이미 있는 상태에서 모음 → 종성을 떼어내어 초성으로
                wchar_t movedCho = jong;
                result.push_back(makeHangul(cho, jung, L' '));
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
                // 중성 합성 시도
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
                    flush();
                    cho = L'ㅇ';
                    jung = c;
                    hasCho = true;
                    hasJung = true;
                    i++;
                    continue;
                }
            }
            i++;
            continue;
        }

        // 2) 자음 처리
        if (isChoChar) {
            if (!hasCho) {
                cho = c; hasCho = true;
                i++;
                continue;
            }
            if (hasCho && !hasJung) {
                result.push_back(cho);
                cho = c;
                hasCho = true;
                hasJung = false;
                hasJong = false;
                jung = jong = L' ';
                i++;
                continue;
            }
            if (hasCho && hasJung && !hasJong) {
                if (i + 1 < n && JUNGSEONG.find(input[i + 1]) != std::wstring::npos) {
                    flush();
                    cho = c;
                    hasCho = true;
                    i++;
                    continue;
                }
                else {
                    // 겹받침 가능성
                    if (i + 1 < n && CHOSEONG.find(input[i + 1]) != std::wstring::npos) {
                        std::wstring key;
                        key.push_back(c);
                        key.push_back(input[i + 1]);
                        auto it = jongseongCompose.find(key);
                        if (it != jongseongCompose.end()) {
                            // 단, 그 뒤에 모음이 오면 겹받침 불가
                            if (!(i + 2 < n && JUNGSEONG.find(input[i + 2]) != std::wstring::npos)) {
                                jong = it->second;
                                hasJong = true;
                                i += 2;
                                continue;
                            }
                        }
                    }
                    jong = c;
                    hasJong = true;
                    i++;
                    continue;
                }
            }
            if (hasCho && hasJung && hasJong) {
                std::wstring key;
                key.push_back(jong);
                key.push_back(c);
                auto it = jongseongCompose.find(key);
                if (it != jongseongCompose.end()) {
                    jong = it->second;
                    hasJong = true;
                    i++;

                    // 🔹 다음 글자가 모음이면 겹받침을 분리
                    if (i < n && JUNGSEONG.find(input[i]) != std::wstring::npos) {
                        wchar_t first = it->first[0];
                        wchar_t second = it->first[1];

                        // 앞 자음만 받침으로 확정
                        result.push_back(makeHangul(cho, jung, first));

                        // 새 음절 시작
                        cho = second;
                        jung = input[i];
                        hasCho = true;
                        hasJung = true;
                        hasJong = false;
                        jong = L' ';
                        i++; // 모음도 소비
                    }
                    continue;
                }
                else {
                    flush();
                    cho = c; hasCho = true;
                    i++;
                    continue;
                }
            }
            i++;
            continue;
        }

        // 3) 기타 문자 처리
        flush();
        result.push_back(c);
        i++;
    }

    if (hasCho || hasJung || hasJong) flush();
    result.push_back('\0');
    return result;
}


// 외부에서 호출하는 함수: UTF-8 string 반환
std::string PoketmonNaming::Compose(const std::vector<wchar_t>& input) {
    std::wstring wres = composeW(input);
    return toUTF8(wres);
}
