/*
 * TODO: Complete this class!
 */

/// Your welcome
#include <assert.h>
#include <iostream>
#include <string>

//
template <typename T>
class MyVector
{
	public:
		
		/*******************
		 * Static constants
		 ******************/
		
		/// Default capacity
		static constexpr size_t DEFAULT_CAPACITY = 64;
		
		/// Minimum capacity
		static constexpr size_t MINIMUM_CAPACITY = 8;
		
		/*****************************
		 * Constructors / Destructors
		 ****************************/
		
		/// Normal constructor
		MyVector(size_t capacity = MyVector::DEFAULT_CAPACITY) {
			
			this->elements_ = new T[capacity];
			this->capacity_ = capacity;
			this->size_ = 0;
		}
		
		/// Copy constructor
		MyVector(const MyVector& other) {
		//FOR Copying another vecotr into your vector
		
			copyOther(other);
		}
		
		/**
		 * Destructor
		 * Should call clear() so each element gets its destructor called.
		 * Then, de-allocate the internal array and make it a nullptr, if its not already a nullptr.
		 */
		~MyVector() {
			
			this-> clear();				//calls clear, destructs each element
			if(this->elements_ != nullptr)		// if not alr null set to null
			{
				delete[]this->elements_;
				this->elements_ = nullptr;
			}
		}
		
		/************
		 * Operators
		 ************/
		
		///	Assignment operator
		MyVector& operator=(const MyVector& rhs) {
		
			copyOther(rhs);
			return *this;
				
		}
		
		/// Operator overload to at()
		T& operator[](size_t index) const {
			
			return this->at(index);

		}
		
		/************
		 * Accessors
		 ************/
		
		/// Return the number of valid elements in our data
		size_t size() const {

			return this->size_;				 // Use "this->" so the compiler doesnt get confused member varables and functions

		}
		
		/// Return the capacity of our internal array
		size_t capacity() const {

			return this->capacity_;

		}
		
		/**
		 * Check whether our vector is empty
		 * Return true if we have zero elements in our array (regardless of capacity)
		 * Otherwise, return false
		 */
		bool empty() const {
			
			return this->size_ == 0; // can add  ? true : false, not neccessary

		}
		
		/// Return a reference to the element at an index
		T& at(size_t index) const {
			
			if( index >= size_ ) throw std::range_error( "index out of bounds" );
			return  this->elements_[index];

		}
		
		/***********
		 * Mutators
		 ***********/
		
		/**
		 * Reserve capacity in advance, if our capacity isn't currently large enough.
		 * Useful if we know we're about to add a large number of elements, and we'd like to avoid the overhead of many internal changes to capacity.
		 */
		void reserve(size_t capacity) {
		
			if(capacity > capacity_)
				this->changeCapacity(capacity);
				
		}
		
		/**
		 * Set an element at an index.
		 * Throws range error if outside the size boundary.
		 * Returns a reference to the newly set element (not the original)
		 */
		T& set(size_t index, const T& element) {
			
			if(index > size_ - 1) throw std::range_error("Set error: index is greater than size");
			this->elements_[index].~T(); //deallocate element being replaced first
			
			this->elements_[index] = element;
			return this->elements_[index];

		}
		
		/**
		 * Add an element onto the end of our vector, increasing the size by 1
		 * Should rely on the insert() function to avoid repeating code.
		 * Returns a reference to the newly inserted element
		 */
		T& push_back(const T& element) {

			this->insert(size_ , element);
			return this->elements_[size_ - 1];

		}
		
		/**
		 * Remove the last element in our vector, decreasing the size by 1
		 * Should rely on the erase() function to avoid repeating code.
		 * Returns the new size.
		 */
		size_t pop_back() {

			this->erase(size_ - 1);
			return this->size_;

		}
		
		/**
		 * Insert an element at some index in our vector, increasing the size by 1
		 * 
		 * Scoot all elements at index and beyond, one to the right. This
		 * makes a "hole" available at the index, where you can then place
		 * the new element.
		 * 
		 * Returns a reference to the newly added element (not the original).
		 */
		T& insert(size_t index, const T& element) {

			//IF user attempts to insert element at an index greater than the capactity throw an error
			//And i suppose if they try to insert at a neg. element also throw an error.
			if(index > size_ ) throw std::range_error("Error, Index is greater than the capacity");
			//ADD an if statement to change capacity if scootching creates an out of bounds sitution
			computeAppropriateCapacity(size_, capacity_);
			// If array is empty add to front
			if(size_ > 0)
			{
				for(size_t i = (size_ - 1); i >= index ; --i)
				{
					elements_[i + 1 ] = elements_[i];	// scootching algo
				}
			}
			this->elements_[index] = element;
			
			++size_;
			T& a = elements_[index];
			return a;

		}
		
		/**
		 * Erase one element in our vector at the specified index, decreasing the size by 1.
		 * 
		 * This means you'd then have to scoot elements to the left to fill the "hole"
		 * 	left by the erased element.
		 * 
		 * Throws std::range_error if the index is out of bounds.
		 * 
		 * Calls the erased element's destructor.
		 * 
		 * Returns the new size.
		 */
		size_t erase(size_t index) {
			
			if(empty() == true) throw std::range_error("Attempted to erase an element from an empty vector");
			if(index > size_ - 1) throw std::range_error("Index greater than number of elements");
			this->elements_[index].~T();
			computeAppropriateCapacity(size_, capacity_);
			//call erased elements destructor
			
			
			for(size_t i = index; i < (size_-1); ++i)
			{
				this->elements_[i] = this->elements_[i + 1];
			}

			--this->size_;
			return this->size_;

		}
		
		/**
		 * Calls each element's destructor, then clears our internal
		 * data by setting size to zero and resetting the capacity.
		*/
		void clear() {
			
			/*for (each element : array)
				//destruct each element
				this->elements[i].~T();
			*/
			for(size_t i = 0; i < size_; ++i)
			{
				this->elements_[i].~T();
			}
			this->size_ = 0;
			this->capacity_ = MyVector::DEFAULT_CAPACITY;

		}
	
	/**
	 * Begin private members and methods.
	 * Private methods can often contain useful helper functions,
	 * or functions to reduce repeated code.
	*/
	private:
		
		/// Number of valid elements currently in our vector
		size_t size_ = 0;
		
		/// Capacity of our vector; The actual size of our internal array
		size_t capacity_ = 0;
		
		/**
		 * Our internal array of elements of type T.
		 * Starts off as a null pointer.
		 */
		T* elements_ = nullptr;
		
		/**
		 * Helper function that is called whenever we need to change the capacity of our vector
		 * Should throw std::range_error when asked to change to a capacity that cannot hold our existing elements.
		 * It's probably a good idea to make an additional helper function that decides
		 * 	whether to change capacity at all (and to what new capacity), that your public functions can rely upon.
		 */
		void changeCapacity(size_t c) {

			if(c < size_) throw std::range_error("This capacity can't hold existing elements");
			
			capacity_ = c;
			//create a new array of type T
			T* newElements_ = new T[capacity_]; 
			//copy elemetns from old array to this new array we just created
			for (size_t i = 0; i < size_ ; ++i)
				newElements_[i] = elements_[i];
			//delete old array
			delete[] elements_;
			//assign newarray to old array name
			elements_ = newElements_;

		}
		
		void computeAppropriateCapacity(size_t size, size_t current_capacity) {
		
			if (size >= current_capacity){
				changeCapacity(current_capacity * 2); //doubles tha capacity when full
				return;
			}
			if(size <= (current_capacity / 3) && current_capacity != MINIMUM_CAPACITY){ //halves the capacity when size is 1/3 of it, makes sure we don't halve the min cap
				changeCapacity(current_capacity / 2);
				return;
			}
		}

		
		/**
		 * Copy another vector's elements into our own, by value.
		 * Does not simply copy the other vector's array's pointer
		 * Does not care about matching the capacity exactly.
		 * This is a helper function relied upon by the copy constructor and the assignment operator,
		 * 	to avoid repeated code.
		 * 
		 * You will probably want to make additional helper functions to make this one easier.
		 * Here is a suggested strategy for copying the internal array:
		 * 1. Deallocate the current array for 'this' (if it is already allocated)
		 * 2. Allocate a new array for 'this' of the appropriate size
		 * 3. Use a loop to copy elements one-by-one (by value)
		 * 4. Copy other relevant properties from the 'other' to 'this'
		 */
		void copyOther(const MyVector& other) {
			
			if( this != &other){
				delete[] this-> elements_;	// deallocate curr array if alr allocated
			}
			this->elements_ = new T[other.capacity_];	// allocate new arrray with new size
			for (size_t i = 0; i < other.capacity_; ++i)
			{
				this->elements_[i] = other.elements_[i]; // copy the other elements into this
			}
			this->capacity_ = other.capacity_;		//set capacity and size to other;s size and cap
			this->size_ = other.size_;

		}
};