#ifndef _MSIGNAL_H_
#define _MSIGNAL_H_

#include <vector>

using std::vector;

#define Connect( sender, signal, receiver, method) (sender)->signal.Bind(receiver, method)
#define Disconnect(sender, signal, receiver, method) (sender)->signal.Rebind(Receiver, method)

template<class T1>
class MSignal
{
private:
	//---------- slot code start -----------------------------------
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

	//-------------------- slot code end -------------------
public:
	template<class T>
	void Bind(T* pObj, void (T::*func)(T1))
	{
		m_pSlotSet.push_back(new SlotImpl<T, T1>(pObj, func));
	}
	/*template<class T>
	void Rebind(T* pObj, void (T::*func)(T1))		//´ý²âÊÔ
	{
		vector < SlotBase<T1>* >::iterator itor;
		for (itor = m_pSlotSet.begin(); itor != m_pSlotSet.end();)
		{
			if ((*itor)->Exec == func)
			{
				itor = m_pSlotSet.erase(itor);
				break;
			}
			else
				itor++;
		}
		//vector< SlotBase<T1>* >(m_pSlotSet).swap(m_pSlotSet);	//ÊÍ·ÅÄÚ´æ
	}*/
	~MSignal()
	{
		for (int i = 0; i<(int)m_pSlotSet.size(); i++)
		{
			delete m_pSlotSet[i];
		}
	}
	void operator()(T1 param1)
	{
		for (int i = 0; i<(int)m_pSlotSet.size(); i++)
		{
			m_pSlotSet[i]->Exec(param1);
		}
	}
private:
	vector < SlotBase<T1>* > m_pSlotSet;
};

#endif


