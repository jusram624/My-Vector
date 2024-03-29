template <class T>
T* recreateInternalArray(T* old_array, size_t old_size, size_t newCapacity) {
	// TODO: Your code here
	if(newCapacity <= old_size) throw std::range_error("capacity out of range");

	//oldSize = newCapacity;
	T* new_array = new T[newCapacity];

	for(int i = 0; i < old_size; ++i)
	     new_array[i] = old_array[i];

	delete[] old_array;
	return new_array;
	
}