#ifndef __DYNAMIC_ARRAY_H__
#define __DYNAMIC_ARRAY_H__
#define DYNAMIC_ARRAY_CHUNK_SIZE 5
#define DYNAMIC_ARRAY_INITIAL_CAPACITY 5


template <class T>

class DynamicArray
{

private:
	void increaseCapacity();
	T *mArray = nullptr;
	unsigned int mCapacity;
	unsigned int mSize;
public:
	DynamicArray() {
		mCapacity = DYNAMIC_ARRAY_INITIAL_CAPACITY;
		mSize = 0;
		mArray = new[DYNAMIC_ARRAY_CHUNK_SIZE];
	}
	~DynamicArray();

	unsigned int size() const {

	}

	T operator[ ](unsigned int index) const {
	
	}

	void push_back(T value) {

	}

	T elementAt(unsigned int index) const {
		return mArray(index);
	}

	void insert(T value) {

	}

	void remove(unsigned int index() {

	}

	void empty() {

	}
};
#endif