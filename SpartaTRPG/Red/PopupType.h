#pragma once

class Popup;

enum class PopupType
{
	RESULTPOPUP,
	SELECTPOPUP,
	//SHOPPOPUP,
	//INVENTORY,
};

enum class RESULTPOPUPTYPE
{
	RESULT, //단순결과 -> 확인되었습니다? 결정되었습니다? 둘중하나
	BATTLEINIT, //전투에 입장합니다 OR 몬스터와 조우했습니다
};

enum class SELECTPOPUPTYPE
{
	DONGEONINIT, //던전에 입장할건지
	BOXCHOICE, //상자 열건지 아닌지
	KEYCHOICE, //열쇠 획득할건지
	NEXTDUNGEONCHOICE, //다음 던전으로 갈건지
};

