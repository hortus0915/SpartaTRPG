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
	RESULT, //�ܼ���� -> Ȯ�εǾ����ϴ�? �����Ǿ����ϴ�? �����ϳ�
	BATTLEINIT, //������ �����մϴ� OR ���Ϳ� �����߽��ϴ�
};

enum class SELECTPOPUPTYPE
{
	DONGEONINIT, //������ �����Ұ���
	BOXCHOICE, //���� ������ �ƴ���
	KEYCHOICE, //���� ȹ���Ұ���
	NEXTDUNGEONCHOICE, //���� �������� ������
};

