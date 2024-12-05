void ZeroMemory(void* _destinationaddress, uint32 _size)
{
	uint32 i;
	uint8* destinationaddress = (uint8*)_destinationaddress;
	for (i = 0; i < _size; i++)
		destinationaddress[i] = 0;
}
void MemoryCopy(void* _destinationaddress, void* _sourceaddress, uint32 _size)
{
	uint32 i;
	uint8* destinationaddress = (uint8*)_destinationaddress;
	uint8* sourceaddress = (uint8*)_sourceaddress;
	for (i = 0; i < _size; i++)
		destinationaddress[i] = sourceaddress[i];
}

float32 Absolute(float32 input);
float64 Absolute(float64 input);
int32 Absolute(int32 input);

struct String
{
	char *string;
	uint32 length;
	String()
	{
		string = 0;
		length = 0;
	}
	String(char * _string)
	{
		for (length = 0; _string[length] != 0; length++);
		length++;

		string = new char[length];

		for (uint32 i = 0; i < length; i++)
			string[i] = _string[i];
	}
	void operator=(char *_string)
	{
		if(string)delete[] string;

		for (length = 0; _string[length] != 0; length++);
		length++;

		string = new char[length];

		for (uint32 i = 0; i< length; i++)
			string[i] = _string[i];
	}
	void operator=(const String &_string)
	{
		if (string)delete[] string;
		length = _string.length;
		string = new char[length];
		memcpy(string, _string.string, sizeof(char)*length);
	}
	void operator=(std::string _string)
	{
		if (string)delete[] string;
		length = _string.length() + 1;
		string = new char[length];
		for (uint32 i = 0; i < length; i++)
			string[i] = _string[i];
	}
	bool operator==(char *_string)
	{
		for (uint32 i = 0; i < length; i++)
		{
			if (string[i] == _string[i])continue;
			return false;
		}
		return true;
	}
	bool operator==(const String &_string)
	{
		if (length != _string.length)return false;
		for (uint32 i = 0; i < length; i++)
		{
			if (string[i] == _string.string[i])continue;
			return false;
		}
		return true;
	}
	void operator+(char *_string)
	{
		if (string)
		{
			uint32 _length;
			for (_length = 0; _string[_length] != 0; _length++);
			_length++;

			char* tempstring = new char[length - 1 + _length - 1 + 1];
			memcpy(tempstring, string, sizeof(char) * (length - 1));
			memcpy(&tempstring[length - 1], _string, sizeof(char) * _length);
			delete[] string;
			string = tempstring;
			length = length - 1 + _length - 1 + 1;
		}
		else
		{
			for (length = 0; _string[length] != 0; length++);
			length++;

			string = new char[length];

			for (uint32 i = 0; i < length; i++)
				string[i] = _string[i];
		}

	}
	void operator+(const String &_string)
	{
		char *tempstring = new char[length -1 + _string.length -1 + 1];
		memcpy(tempstring, string, sizeof(char)*(length-1));
		memcpy(&tempstring[length-1], _string.string, sizeof(char)*_string.length);
		delete[] string;
		string = tempstring;
		length = length - 1 + _string.length - 1 + 1;
	}
	void operator-()
	{
		char* newstring = new char[length - 1];
		for (uint32 i = 0; i < length-2; i++)
			newstring[i] = string[i];
		newstring[length - 2] = 0;
		length--;
		delete string;
		string = newstring;
	}
	void Release()
	{
		delete[] string;
		length = 0;
		string = 0;
	}
	~String()
	{
		delete[] string;
		length = 0;
		string = 0;
	}
};
struct String256
{
	char string[256-4];
	uint32 length;
	//String256()
	//{
	//	string[0] = 0;
	//	length = 0;
	//}
	void Initialize()
	{
		string[0] = 0;
		length = 0;
	}
	//~String256()
	//{
	//	string[0] = 0;
	//	length = 0;
	//}
};

template <typename DataType> 
struct LinkedList
{
	struct Element
	{
		DataType data;
		Element* right;
		Element* left;
		Element()
		{
			right = 0;
			left = 0;
		}
	};
	Element* head, * current, * tail;
	uint32 count;
	DataType Get()
	{
		return current->data;
	}
	void Set(DataType data)
	{
		current->data = data;
	}
	void GotoHead()
	{
		current = head;
	}
	void GotoTail()
	{
		current = tail;
	}
	void GotoIndex(uint32 index)
	{
		current = head;
		for (int i = 0; i < index; i++)
			current = current->right;
	}
	bool MoveRight()
	{
		if (current->right)
		{
			current = current->right;
			return true;
		}
		return false;
	}
	bool MoveLeft()
	{
		if (current->left)
		{
			current = current->left;
			return true;
		}
		return false;
	}
	bool CheckIfHead()
	{
		if (current == head)
			return true;
		return false;
	}
	bool CheckIfTail()
	{
		if (current == tail)
			return true;
		return false;
	}
	bool CheckIfRight()
	{
		if (current->right)
			return true;
		return false;
	}
	bool CheckIfLeft()
	{
		if (current->left)
			return true;
		return false;
	}
	void InsertRight(DataType data)
	{
		if (current)
		{
			if (current->right)
			{
				Element* right = current->right;
				current->right = new Element;
				current->right->data = data;
				current->right->left = current;
				current->right->right = right;
			}
			else
			{
				current->right = new Element;
				current->right->data = data;
				current->right->left = current;
				current->right->right = 0;
				tail = current->right;
			}
		}
		else
		{
			current = new Element;
			current->data = data;
			current->left = 0;
			current->right = 0;
			head = current;
			tail = current;
		}
		count++;
	}
	void InsertLeft(DataType data)
	{
		if (current)
		{
			if (current->left)
			{
				Element* left = current->left;
				current->left = new Element;
				current->left->data = data;
				current->left->right = current;
				current->left->left = left;
			}
			else
			{
				current->left = new Element;
				current->left->data = data;
				current->left->right = current;
				current->left->left = 0;
				head = current->left;
			}
		}
		else
		{
			current = new Element;
			current->data = data;
			current->left = 0;
			current->right = 0;
			head = current;
			tail = current;
		}
		count++;
	}
	void Remove()
	{
		count--;
		if (current->left)current->left->right = current->right;
		if (current->right)current->right->left = current->left;
		delete current;
		current = 0;
	}
	void PushTail(DataType data)
	{
		if (tail)
		{
			Element* newtail = new Element;
			newtail->data = data;
			newtail->left = tail;
			newtail->right = 0;
			tail->right = newtail;
			tail = newtail;
		}
		else
		{
			tail = new Element;
			tail->data = data;
			tail->left = 0;
			tail->right = 0;
			head = tail;
			current = tail;
		}
		count++;
		current = tail;
	}
	DataType PopHead()
	{
		DataType returndata;
		ZeroMemory(&returndata, sizeof(DataType));
		if (head)
		{
			Element* headtobepoped = head;
			if (headtobepoped->right)
			{
				headtobepoped->right->left = 0;
				head = headtobepoped->right;
			}
			else
			{
				head = 0;
				current = 0;
				tail = 0;
			}
			returndata = headtobepoped->data;
			//delete headtobepoped;			
		}
		count--;
		return returndata;
	}

	void operator = (const LinkedList<DataType>& _linkedlist)
	{
		current = _linkedlist.current;
		head = _linkedlist.head;
		tail = _linkedlist.tail;
		count = _linkedlist.count;
	}
	void operator << (DataType data)
	{
		PushTail(data);
	}
	void Append(const LinkedList<DataType>& _linkedlist)
	{	
		if (_linkedlist.count)
		{
			if (tail)
			{
				tail->right = _linkedlist.head;
				_linkedlist.head->left = tail;
				tail = _linkedlist.tail;
				current = _linkedlist.tail;
				count += _linkedlist.count;
			}
			else
			{
				head = _linkedlist.head;
				current = _linkedlist.current;
				tail = _linkedlist.tail;
				count = _linkedlist.count;
			}
		}
	}

	bool VerifyIntegrity()
	{
		Element* _current = head;
		uint32 _count = 0;
		while (_current)
		{
			_count++;
			if (_current->right)
			{
				if (_current->right->left != _current)
					return false;
			}
			_current = _current->right;
		}
		if (_count != count)
			return false;
		return true;
	}
	void Release()
	{
		current = head;
		while (current)
		{
			Element *right = current->right;
			delete current;
			current = right;
		}
		ZeroMemory(this, sizeof(LinkedList));
	}
	LinkedList()
	{
		ZeroMemory(this, sizeof(LinkedList));
	}
};
template <typename DataType>
struct LinkedListAppend
{
	struct Element
	{
		DataType data;
		Element* right;
		Element* left;
		Element()
		{
			right = 0;
			left = 0;
		}
	};
	Element *root ,*head, *current, *tail;
	uint32 count;
	DataType Get()
	{
		return current->data;
	}
	void Set(DataType data)
	{
		current->data = data;
	}
	void GotoHead()
	{
		current = head;
	}
	void GotoTail()
	{
		current = tail;
	}
	void GotoIndex(uint32 index)
	{
		current = head;
		for (uint32 i = 0; i < index; i++)
			current = current->right;
	}
	bool MoveRight()
	{
		if (current->right)
		{
			current = current->right;
			return true;
		}
		return false;
	}
	bool MoveLeft()
	{
		if (current->left)
		{
			current = current->left;
			return true;
		}
		return false;
	}
	bool CheckIfHead()
	{
		if (current == head)
			return true;
		return false;
	}
	bool CheckIfTail()
	{
		if (current == tail)
			return true;
		return false;
	}
	void InsertRight(DataType data)
	{
		if (current)
		{
			if (current->right)
			{
				Element* right = current->right;
				current->right = new Element;
				current->right->data = data;
				current->right->left = current;
				current->right->right = right;
			}
			else
			{
				current->right = new Element;
				current->right->data = data;
				current->right->left = current;
				current->right->right = 0;
				tail = current->right;
			}
		}
		else
		{
			current = new Element;
			current->data = data;
			current->left = 0;
			current->right = 0;
			head = current;
			tail = current;
		}
		count++;
	}
	void InsertLeft(DataType data)
	{
		if (current)
		{
			if (current->left)
			{
				Element* left = current->left;
				current->left = new Element;
				current->left->data = data;
				current->left->right = current;
				current->left->left = left;
			}
			else
			{
				current->left = new Element;
				current->left->data = data;
				current->left->right = current;
				current->left->left = 0;
				head = current->left;
			}
		}
		else
		{
			current = new Element;
			current->data = data;
			current->left = 0;
			current->right = 0;
			head = current;
			tail = current;
		}
		count++;
	}
	void PushTail(DataType data)
	{
		if (tail)
		{
			Element* newtail = new Element;
			newtail->data = data;
			newtail->left = tail;
			newtail->right = 0;
			tail->right = newtail;
			tail = newtail;
		}
		else
		{
			if (root)
			{
				Element* hiddentraveler = root;
				while (hiddentraveler->right)hiddentraveler = hiddentraveler->right;
				tail = new Element;
				tail->data = data;
				tail->left = 0;
				tail->right = 0;
				root = tail;
				head = tail;
				current = tail;
				hiddentraveler->right = tail;
			}
			else
			{
				tail = new Element;
				tail->data = data;
				tail->left = 0;
				tail->right = 0;
				root = tail;
				head = tail;
				current = tail;
			}

		}
		count++;
	}
	DataType PopHead()
	{
		DataType returndata;
		ZeroMemory(&returndata, sizeof(DataType));
		if (head)
		{
			Element* headtobepoped = head;
			if (headtobepoped->right)
			{
				headtobepoped->right->left = 0;
				head = headtobepoped->right;
			}
			else
			{
				head = 0;
				current = 0;
				tail = 0;
			}
			returndata = headtobepoped->data;
		}
		count--;
		return returndata;
	}

	LinkedListAppend()
	{
		ZeroMemory(this, sizeof(LinkedListAppend));
	}
	void Release()
	{
		current = root;
		while (current)
		{
			Element* right = current->right;
			delete current;
			current = right;
		}
		ZeroMemory(this, sizeof(LinkedListAppend));
	}
	~LinkedListAppend()
	{
		current = root;
		while (current)
		{
			Element* right = current->right;
			delete current;
			current = right;
		}
		ZeroMemory(this, sizeof(LinkedListAppend));
	}
};

template <typename DataType>
struct Heap
{
	DataType* data;
	uint32 size;
	Heap()
	{
		ZeroMemory(this, sizeof(Heap));
	}
	~Heap()
	{
		//if(size)
		//	delete[] data;
		//ZeroMemory(this, sizeof(Heap));
	};
	Heap(const Heap& _heap)
	{
		data = new DataType[_heap.size];
		MemoryCopy(data, _heap.data, sizeof(DataType) * _heap.size);
		size = _heap.size;
	}
	void operator = (const Heap& _heap)
	{
		delete[] data;
		data = new DataType[_heap.size];
		MemoryCopy(data, _heap.data, sizeof(DataType) * _heap.size);
		size = _heap.size;
	}
	void operator << (DataType _data)
	{
		DataType* newdata = new DataType[size + 1];
		MemoryCopy(newdata, data, sizeof(DataType) * size);
		newdata[size] = _data;
		delete[] data;
		data = newdata;
		size++;
	}
	void Append(DataType* _data, uint32 _size)
	{
		DataType* newdata = new DataType[size + _size];
		MemoryCopy(newdata, data, sizeof(DataType) * size);
		MemoryCopy(&newdata[size], _data, sizeof(DataType) * _size);
		delete[] data;
		data = newdata;
		size += _size;
	}
	DataType& operator[](uint32 index)
	{
		return data[index];
	}
	const DataType& operator[](uint32 index) const
	{
		return data[index];
	}
	void Release()
	{
		if (size)
			delete[] data;
		ZeroMemory(this, sizeof(Heap));
	}
};

struct File
{
	fstream file;
	uint8  Create(char *_filename)
	{
		ofstream createstream;
		createstream.open(_filename, ios::binary);
		if (createstream)
		{
			createstream.close();
			return 0;
		}
		return 1;
	}
	uint8  Open(char *_filename)
	{
		file.open(_filename, ios::binary | ios::in | ios::out);
		if (file)
			return 0;
		return 1;
	}
	void   Close()
	{
		file.close();
	}
	void  Rewind()
	{
		file.flush();
		file.clear();
		file.seekg(ios::beg);
	}
	bool  Eof()
	{
		return file.eof();
	}
	void  operator>>(void* _in)
	{
		file >> _in;
	}
	void  operator<<(char* _out)
	{
		file << _out;
	}
	void  Seek(uint32 _offset)
	{
		file.seekg(_offset, ios::beg);
	}
	void  Read(void *data, uint32 lenght)
	{
		file.read((char*)data, lenght);
	}
	void  Write(void *data, uint32 lenght)
	{
		file.write((char*)data, lenght);
	}
	void  Flush()
	{
		file.flush();
	}
	~File()
	{
		if (file)file.close();
	}
};