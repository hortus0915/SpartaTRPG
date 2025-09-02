#pragma once

#define SINGLETON(CLASSNAME, initialize)					\
private:													\
	static CLASSNAME* instance;								\
	CLASSNAME() initialize {}								\
	~CLASSNAME()											\
	{														\
		Release();											\
		if (instance)										\
			delete instance;								\
	}														\
															\
public:														\
	CLASSNAME(const CLASSNAME& ref) = delete;				\
	CLASSNAME& operator=(const CLASSNAME& ref) = delete;	\
	static CLASSNAME* GetInstance()							\
	{														\
		if (instance == nullptr)							\
			instance = new CLASSNAME();						\
		return instance;									\
	}														\
	void Release();											\
