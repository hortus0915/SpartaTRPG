#pragma once

#define SAFE_DELETE(p)	\
if (p)					\
{						\
	delete p;			\
	p = nullptr;		\
}						\


#define SAFE_RELEASE_DELETE(p)	\
if (p)							\
{								\
	p->Release();				\
	delete p;					\
	p = nullptr;				\
}								\


#define SAFE_DELETE_ARR(p)	\
if (p)						\
{							\
	delete[] p;				\
	p = nullptr;			\
}							\

#define MAX_SCREEN_WIDTH  100
#define MAX_SCREEN_HEIGTH 25
#define TITLE "Spartaaaaaaaaaaaaaaa!!!!!!!!!!!"
