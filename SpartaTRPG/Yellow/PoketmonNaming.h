#pragma once
#include <string>
#include <vector>
#include <map>



class PoketmonNaming {
public:
    // 입력: std::wstring (호환 자모들), 출력: UTF-8 std::string (완성형 한글)
    static std::string Compose(const std::vector<wchar_t>& input);

    static const wchar_t LETTERS[];
    static const char* LETTERS_UTF8[];
    static const int LETTER_COUNT;

private:
    // 유니코드 한글 상수
    static const int HANGUL_BASE = 0xAC00;
    static const int JUNGSEONG_COUNT = 21;
    static const int JONGSEONG_COUNT = 28;

    // 초/중/종성 테이블
    static const std::wstring CHOSEONG;
    static const std::wstring JUNGSEONG;
    static const std::wstring JONGSEONG;

    static const std::map<std::wstring, wchar_t> jungseongCompose;
    static const std::map<std::wstring, wchar_t> jongseongCompose;

    // 내부 유틸리티
    static int idxIn(const std::wstring& s, wchar_t ch);
    static wchar_t makeHangul(wchar_t cho, wchar_t jung, wchar_t jong);

    // 조합 로직 (wstring 반환)
    static std::wstring composeW(const std::vector<wchar_t>& input);

    // UTF-16 → UTF-8 변환
    static std::string toUTF8(const std::wstring& wstr);
};

