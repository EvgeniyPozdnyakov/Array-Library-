//библиотека работы с массивами C++
//разработал Поздняков Е.А. 2019
struct Param_Array
{
	unsigned int countVal;	//Количество элементов в массиве
	void *Prima,*Last;          //Указатель Первичный элемент массива	
								//Указатель Последний элемент массива
};

template<class classType>
class ArrayWork
{	
	ArrayWork<classType> *previous,*next;       //Предыдущий элемент массива	
												//следующий элемент массива
	classType* Element;	
	Param_Array* Paramets;						//Указатель параметров массива

	ArrayWork(classType* value, Param_Array* param, ArrayWork<classType>* previous,  ArrayWork<classType>* next);
public:
	ArrayWork(void);
	
	void AddElement(classType* value);
	classType* GetValue(unsigned int index);
	classType* GetValue(void) {return Element;};
	ArrayWork<classType>* GetValueInt(unsigned int index);
	void InsertValue(unsigned int index, classType* value);
	void DeleteValue(unsigned int index);
	unsigned int GetCount(void){return this->Paramets->countVal;};
	void ClearArray(void);
	
};
template <class classType> 
void ArrayWork<classType>::ClearArray(void)
{
	value_array<classType> *CurDelete = this->Prima;
	for (unsigned int i = 0; i < this->countVal; i++)
	{
		value_array<classType> *NeaxtDel = CurDelete->next;
		if (CurDelete!=NULL)
		{
			delete CurDelete;
		}
		CurDelete = NeaxtDel;
	}
}

template <class classType> 
ArrayWork<classType>::ArrayWork(void)
{	
	this->Paramets = new Param_Array;
	this->Paramets->countVal = 0;
	this->Paramets->Prima = this;
	this->Paramets->Last = this;
	this->previous = this->next = NULL;
	this->Element = NULL;
};
template <class classType> 
ArrayWork<classType>::ArrayWork(classType* value, Param_Array* param, ArrayWork<classType>* previous,  ArrayWork<classType>* next)
{	
	this->Element = value;
	this->Paramets = param;
	this->previous = previous;
	this->next = next;	
};

template <class classType> 
void ArrayWork<classType>::AddElement(classType* value)
	{
		if (this->Paramets->countVal == 0)
		{			
			this->Element = value;
		}
		else
		{		
			ArrayWork<classType>* NewInsElement = new ArrayWork<classType>(value, this->Paramets,
				(ArrayWork<classType>*)this->Paramets->Last,NULL);
			((ArrayWork<classType>*)this->Paramets->Last)->next = NewInsElement;
			this->Paramets->Last = NewInsElement;				
		}		
		this->Paramets->countVal++;
	};

template <class classType> 
classType* ArrayWork<classType>::GetValue(unsigned int index)
{
	if ((index >= this->Paramets->countVal)||(this->Paramets->countVal == 0)) return NULL;
	ArrayWork<classType>* pointer = (ArrayWork<classType>*)this->Paramets->Prima;
	for (unsigned int K = 0; K < index; K++)
	{
		pointer = pointer->next;
	}
	return pointer->GetValue();
};


template <class classType> 
ArrayWork<classType>*  ArrayWork<classType>::GetValueInt(unsigned int index)
{
	if ((index >= this->Paramets->countVal)||(this->Paramets->countVal == 0)) return NULL;
		ArrayWork<classType>* pointer = (ArrayWork<classType>*)this->Paramets->Prima;
		for (unsigned int K = 0; K < index; K++)
		{
			pointer = pointer->next;
		}
		return pointer;
};

	
template <class classType> 
void ArrayWork<classType>::InsertValue(unsigned int index, classType* value)
{
	ArrayWork<classType> *P;
	if (index >= this->Paramets->countVal) return;
	if (index == 0)
	{
		P = new ArrayWork<classType>(this->Element, this->Paramets, this, this->next);
		this->next->previous = P;
		this->next = P;
		this->Element = value;				
		goto exit_fnc;
	}
	if (index == this->Paramets->countVal-1)
	{
		P = (ArrayWork<classType>*)this->Paramets->Last;
		this->Paramets->Last = new ArrayWork<classType>(value, this->Paramets, P, NULL);
		P->next = (ArrayWork<classType>*)this->Paramets->Last;
		goto exit_fnc;
	}
	P = this->GetValueInt(index);
	ArrayWork<classType> *Ins = new ArrayWork<classType>(value, this->Paramets, P->previous, P);	
	P->previous->next = Ins;
	P->previous = Ins;	
exit_fnc:		
	this->Paramets->countVal++;
};	


template <class classType>
void  ArrayWork<classType>::DeleteValue(unsigned int index)
{
	if ((index >= this->Paramets->countVal)||(this->Paramets->countVal == 0)) return;
	ArrayWork<classType> *P;
	if (index == 0)
	{
		this->Element = this->next->GetValue();
		P = (ArrayWork<classType>*)this->next;
		if (this->Paramets->countVal>3)
		{
			this->next = this->next->next;
			this->next->previous = this;
		}
		//Удаляем 2й элемент
		//this->Paramets->Prima = ((ArrayWork<classType>*)this->Paramets->Prima)->next;			
		goto exit_fnc;
	}
	if (index == this->Paramets->countVal-1)
	{
		P = (ArrayWork<classType>*)this->Paramets->Last;
		this->Paramets->Last = ((ArrayWork<classType>*)this->Paramets->Last)->previous;		
		goto exit_fnc;
	}
	P = this->GetValueInt(index);
	P->previous->next = P->next;
	P->next->previous = P->previous;
exit_fnc:
	this->Paramets->countVal--;
	delete P;	
	
};

