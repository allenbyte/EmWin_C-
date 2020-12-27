#include "msignal.h"
/*
template<class T1>
class SlotBase
{
public:
	virtual void Exec(T1 param1) = 0;
};

template<class T, class T1>
class SlotImpl : public SlotBase<T1>
{
public:
	SlotImpl(T* pObj, void (T::*func)(T1))
	{
		m_pObj = pObj;
		m_Func = func;
	}

	void Exec(T1 param1)
	{
		(m_pObj->*m_Func)(param1);
	}

private:
	T* m_pObj;
	void (T::*m_Func)(T1);
};


template<class T1>
class Slot
{
public:
	template<class T>
	Slot(T* pObj, void (T::*func)(T1))
	{
		m_pSlotBase = new SlotImpl<T, T1>(pObj, func);
	}

	~Slot()
	{
		delete m_pSlotBase;
	}

	void Exec(T1 param1)
	{
		m_pSlotBase->Exec(param1);
	}

private:
	SlotBase<T1>* m_pSlotBase;
};

template<class T1>

template<class T> void MSignal<T1>::Bind(T* pObj, void (T::*func)(T1))
{
	m_pSlotSet.push_back(new Slot<T1>(pObj, func));
}


template<class T1>
void MSignal<T1>::operator()(T1 param1)
{
	for (int i = 0; i<(int)m_pSlotSet.size(); i++)
	{
		m_pSlotSet[i]->Exec(param1);
	}
}
*/

