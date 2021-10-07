#include <iostream>

using namespace std;

template <class T>
class MyArray
{
	int count;
	int grow;
	T* arr;
public:
	MyArray();
	MyArray(int count);
	MyArray(T* arr, int count);
	~MyArray();
	int GetSize();
	void SetSize(int size, int grow = 1);
	int GetUpperBound();
	bool IsEmpty();
	void FreeExtra();
	void RemoveAll();
	T GetAt(int index);
	void SetAt(int temp);
	T operator[](int index)
	{
		return arr[index];
	}
	void Add(T element);
	void Append(MyArray& arr);
	MyArray<T>* operator=(MyArray& arr)
	{
		for (int i = 0; i < this->count; i++)
		{
			this->arr[i] = arr.GetAt(i);
		}
		return this;
	}
	T* GetData();
	void InsertAt(int index);
	void RemoveAt(int index);
	void Print();
};

int main()
{
	MyArray<int> obj;
	obj.SetSize(10, 5);
	for (int i = 1; i < 11; i++)
	{
		obj.Add(i);
		obj.Print();
	}
	obj.Print();
	cout << "Index: " << obj.GetUpperBound();
	if (obj.IsEmpty())
	{
		cout << "\nArray isn't empty\n";
	}
	else
	{
		cout << "\nArray is empty\n";
	}
	obj.Print();
	for (int i = 11; i < 17; i++)
	{
		obj.Add(i);
	}
	obj.FreeExtra();
	obj.Print();
	cout << obj.GetAt(7) << endl;
	obj.SetAt(8);
	obj.Print();
	cout << obj.GetData() << endl;
	MyArray<int> obj2;
	obj2.SetSize(10, 5);
	for (int i = 1; i < 11; i++)
	{
		obj2.Add(i);
		obj2.Print();
	}
	obj.Append(obj2);
	MyArray<int> obj3;
	obj3.SetSize(10, 5);
	obj3 = obj2;
	obj3.Print();
	obj.InsertAt(10);
	obj.Print();
	obj.RemoveAt(10);
	obj.Print();
}

template<class T>
MyArray<T>::MyArray()
{
	this->count = 0;
	this->arr = nullptr;
	this->grow = 1;
}

template<class T>
MyArray<T>::MyArray(int count)
{
	this->count = count;
	this->arr = nullptr;
	this->grow = 1;
}

template<class T>
MyArray<T>::MyArray(T* arr, int count)
{
	this->count = count;
	this->arr = new T[this->count];
	this->grow = 1;
	for (int i = 0; i < count; i++)
	{
		this->arr[i] = arr[i];
	}
}

template<class T>
MyArray<T>::~MyArray()
{
	RemoveAll();
}

template<class T>
int MyArray<T>::GetSize()
{
	return this->count;
}

template<class T>
void MyArray<T>::SetSize(int size, int grow)
{
	if (this->count < size)
	{
		if (this->arr != nullptr)
		{
			T* temp = new T[this->count];
			for (int i = 0; i < this->count; i++)
			{
				temp[i] = this->arr[i];
			}
			delete[]this->arr;
			this->arr = nullptr;
			this->arr = new T[size];
			for (int i = 0; i < size; i++)
			{
				if (i < this->count)
				{
					this->arr[i] = temp[i];
				}
				else
				{
					this->arr[i] = 0;
				}
			}
			delete[]temp;
			temp = nullptr;
		}
		else if(this->arr == nullptr)
		{
			this->arr = new T[size];
			for (int i = 0; i < size; i++)
			{
				this->arr[i] = 0;
			}
		}
	}
	else if (this->count > size)
	{
		if (this->arr != nullptr)
		{
			T* temp = new T[size];
			for (int i = 0; i < size; i++)
			{
				temp[i] = this->arr[i];
			}
			delete[]this->arr;
			this->arr = nullptr;
			this->arr = new T[size];
			for (int i = 0; i < size; i++)
			{
				this->arr[i] = temp[i];
			}
			delete[]temp;
			temp = nullptr;
		}
		else if(this->arr == nullptr)
		{
			this->arr = new T[size];
			for (int i = 0; i < size; i++)
			{
				this->arr[i] = 0;
			}
		}
	}
	else
	{
		if (this->arr == nullptr)
		{
			this->arr = new T[size];
			for (int i = 0; i < size; i++)
			{
				this->arr[i] = 0;
			}
		}
	}
	this->count = size;
	this->grow = grow;
}

template<class T>
int MyArray<T>::GetUpperBound()
{
	for (int i = 0; i < this->count; i++)
	{
		if (this->arr[i] != 0 && this->arr[i] + 1 == 0)
		{
			return i - 1;
		}
	}
	return this->count - 1;
}

template<class T>
bool MyArray<T>::IsEmpty()
{
	for (int i = 0; i < this->count; i++)
	{
		if (this->arr[i] > 0)
		{
			return true;
		}
	}
	return false;
}

template<class T>
void MyArray<T>::FreeExtra()
{
	T* temp = new T[this->count];
	int tempIndex;
	for (int i = 0; i < this->count; i++)
	{
		temp[i] = this->arr[i];
		if (this->arr[i] == 0)
		{
			tempIndex = i;
			break;
		}
		tempIndex = i + 1;
	}
	delete[]this->arr;
	this->arr = nullptr;
	this->count = tempIndex;
	this->arr = new T[this->count];
	for (int i = 0; i < this->count; i++)
	{
		this->arr[i] = temp[i];
	}
	delete[]temp;
	temp = nullptr;
}

template<class T>
T* MyArray<T>::GetData()
{
	return this->arr;
}

template<class T>
void MyArray<T>::InsertAt(int index)
{
	T* temp = new T[this->count + 1];
	for (int i = 0; i < this->count + 1; i++)
	{
		if (index == i)
		{
			temp[i] = 77;
		}
		if (i < index)
		{
			temp[i] = this->arr[i];
		}
		else if (i > index)
		{
			temp[i] = this->arr[i - 1];
		}
	}
	delete[]this->arr;
	this->arr = nullptr;
	this->arr = new T[this->count + 1];
	for (int i = 0; i < this->count + 1; i++)
	{
		this->arr[i] = temp[i];
	}
	this->count++;
}

template<class T>
void MyArray<T>::RemoveAt(int index)
{
	T* temp = new T[this->count - 1];
	for (int i = 0; i < this->count; i++)
	{
		if (i < index)
		{
			temp[i] = this->arr[i];
		}
		else if (i > index)
		{
			temp[i - 1] = this->arr[i];
		}
	}
	delete[]this->arr;
	this->arr = nullptr;
	this->arr = new T[this->count - 1];
	for (int i = 0; i < this->count - 1; i++)
	{
		this->arr[i] = temp[i];
	}
	this->count--;
}

template<class T>
void MyArray<T>::Print()
{
	for (int i = 0; i < this->count; i++)
	{
		cout << this->arr[i] << " ";
	}
	cout << endl;
}

template<class T>
void MyArray<T>::RemoveAll()
{
	delete[]this->arr;
	this->arr = nullptr;
}

template<class T>
T MyArray<T>::GetAt(int index)
{
	return arr[index];
}

template<class T>
void MyArray<T>::SetAt(int temp)
{
	while (temp < 0 || temp > (this->count - 1))
	{
		cout << "\nEnter correct index: ";
		cin >> temp;
	}
	int temp2;
	cout << "\nEnter new value: ";
	cin >> temp2;
	cout << endl;
	this->arr[temp] = temp2;
}

template<class T>
void MyArray<T>::Add(T element)
{
	T* temp = new T[this->count];
	if (this->arr != nullptr)
	{
		for (int i = 0; i < this->count; i++)
		{
			temp[i] = this->arr[i];
		}
		if (this->arr[this->count - 1] != 0)
		{
			delete[]this->arr;
			this->arr = nullptr;
			this->count += this->grow;
			this->arr = new T[this->count];
			for (int i = 0; i < this->count - this->grow; i++)
			{
				this->arr[i] = temp[i];
			}
			this->arr[this->count - this->grow] = element;
			for (int i = this->count - this->grow + 1; i < this->count; i++)
			{
				this->arr[i] = 0;
			}
		}
		else
		{
			delete[]this->arr;
			this->arr = nullptr;
			this->arr = new T[this->count];
			int tempIndex = 0;
			for (int i = 0; i < this->count; i++)
			{
				for (int i = 0; i < this->count; i++)
				{
					if (temp[i] == 0)
					{
						this->arr[i] = element;
						tempIndex = i;
						break;
					}
					this->arr[i] = temp[i];
				}
			}
			for (int i = tempIndex + 1; i < this->count; i++)
			{
				this->arr[i] = 0;
			}
		}
	}
	else
	{
		this->arr[0] = element;
	}
	delete[]temp;
	temp = nullptr;
}

template<class T>
void MyArray<T>::Append(MyArray& arr)
{
	T* temp = new T[this->count + arr.GetSize()];
	for (int i = 0; i < this->count + arr.GetSize();i++)
	{
		if (i < this->count)
		{
			temp[i] = this->arr[i];
		}
		else
		{
			temp[i] = arr.GetAt(i - this->count);
		}
		cout << temp[i] << " ";
	}
	cout << endl;
}
