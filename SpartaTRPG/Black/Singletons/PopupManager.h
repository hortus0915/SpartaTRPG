#pragma once

#include <vector>
#include <map>

using namespace std;

#include "../Singletons/SingletonMacro.h"
#include "../../Red/PopupType.h"
#include "../../Red/Popup.h"

#include "../../Red/NPCDialoguePopup.h"

#define MAPPOPUP_WIDTH 81
#define MAPPOPUP_HEIGHT 17

#define POPUPSTRING_MAXWIDTH 77
#define POPUPSTRING_MAXHEIGHT 15

using namespace std;

class MainGame;

typedef map<PopupType, Popup*>				PopupMap;

class PopupManager
{
	SINGLETON(PopupManager, :activePopup(nullptr))

private:
	MainGame* mainGame;

	PopupMap  mPopupList;
	Popup* activePopup;
public:
	void Init(MainGame* _mg);

	void Update(float deltaTime);
	void Render();
	void PopupActiveOff();

    bool CheckPopupActive();

	inline const Popup* GetActivePopup() { return activePopup; }

    template<class T, void (T::* Method)(int) = nullptr>
    Popup* InitPopup(PopupType _popupType,
        T* obj,
        std::vector<std::string>* _customString = nullptr,
        int _leftPadding = 0, int _rightPadding = 0,
        int _upPadding = 0, int _downPadding = 0,
        int posX = 0, int posY = 0,
        int width = 0, int height = 0)
    {
        PopupActiveOff();

        auto it = mPopupList.find(_popupType);
        if (it == mPopupList.end() || it->second == nullptr)
            return nullptr;

        activePopup = it->second;

        if (_popupType == PopupType::NPCDIALOGUEPOPUP)
        {
            ((NPCDialoguePopup*)activePopup)->SetPosWH(posX, posY, width, height);
        }

        activePopup->Init();
        activePopup->SetCustomStringPadding(_leftPadding, _rightPadding, _upPadding, _downPadding);
        activePopup->SetCustonStrings(_customString);

        if (Method != nullptr) {
            if (obj) {
                activePopup->SetPopupActiveCallback(
                    +[](int v, void* u) { (static_cast<T*>(u)->*Method)(v); },
                    obj
                );
            }
            else {
                activePopup->SetPopupActiveCallback(nullptr, nullptr);
            }
        }
        else {
            // Method 생략 = 콜백 없음
            activePopup->SetPopupActiveCallback(nullptr, nullptr);
        }
        activePopup->LateInit();
        activePopup->SetActive();
        return activePopup;
    }
};
