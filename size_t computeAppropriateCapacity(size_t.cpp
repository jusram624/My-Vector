size_t computeAppropriateCapacity(size_t size, size_t current_capacity) {
	// TODO: Your code here
	//Example computAppCap(100, 64)
    if (size < current_capacity)
	     return current_capacity;
		 
    if (size >= current_capacity){
        current_capacity *= 2
		return current_capacity;
	}
	    
	if(size < (current_capacity / 3)){
		current_capacity = current_capacity / 2;
		return current_capacity;
	}
	    
}
