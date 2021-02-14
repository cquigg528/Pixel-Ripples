/**
 * @file stack.cpp
 * Implementation of the Stack class.
 *
 */
/**
 * Default constructor. Remember to initialize any variables you need
 * and allocate any required memory. The initial size of `items` should
 * be DEFAULTCAPACITY defined in stack.h.
 *
 */

template <class T> Stack<T>::Stack()
{
  // allocate memory with default initial size
  items = new T[DEFAULTCAPACITY];

  // initialize member variables
  max_items = DEFAULTCAPACITY;
  num_items = 0;
}

/**
 * Destructor. Remember to free any memory allocated.
 *
 */
template <class T> Stack<T>::~Stack()
{
  // free memory, redirect ptr
  delete[] items;
  items = NULL;
}

/**
 * Adds the parameter object to the top of the Stack.  Resize should be
 * called by multiplying current capacity EXPANSIONFACTOR defined in stack.h.
 *
 * @param value The object to be added to the Stack.
 */
template <class T> void Stack<T>::push(const T &newItem)
{
  // check if we need a resize
  if (size() + 1 > capacity()) {
    int new_size = capacity() * EXPANSIONFACTOR;

    // resize up
    resize(new_size);

    // add new parameter object to top of stack
    items[size()] = newItem;
    num_items++;

  } else {
    items[size()] = newItem;
    num_items++;
  }
  
};

/**
 * Removes the object on top of the Stack, and returns it.
 * You may assume this function is only called when the Stack is not empty.
 * If the size of the stack changes to strictly less than 1 / SHRINKWHEN
 * (where SHRINKWHEN is defined in stack.h)after the item is removed,
 * the Stack should be resized by 1 / EXPANSIONFACTOR.
 * The capacity of the stack should never decrease below DEFAULTCAPACITY
 * to avoid corner cases where the stack size goes to zero.
 *
 * @return The element that was at the top of the Stack.
 */
template <class T> T Stack<T>::pop()
{
  T popped_obj = items[size() - 1];

  num_items--;
  // check for resize, prevent a resize setting size < DEFAULTCAPACITY
  if ((num_items < (capacity() / SHRINKWHEN)) && ((capacity() / EXPANSIONFACTOR) >= DEFAULTCAPACITY)) {
    resize(capacity() / EXPANSIONFACTOR);
  } 
  
  return popped_obj;
};

/**
 * Finds the object on top of the Stack, and returns it to the caller.
 * Unlike pop(), this operation does not alter the Stack itself.
 *  You may assume this function is only called when the Stack is not empty.
 *
 * @return The element at the top of the Stack.
 */
template <class T> T Stack<T>::peek()
{
  return items[size() - 1];
};

/**
 * Determines if the Stack is empty.
 *
 * @return Whether or not the stack is empty (bool).
 */
template <class T> bool Stack<T>::empty() const
{
  return num_items == 0;
};

/**
 * Return the maximum number of items the stack can hold.
 *
 * Note: This is an implementation detail we would normally hide.
 * We include it here for testing purposes.
 *
 * @return Maximum number of items the stack can hold (int)
 */
template <class T> size_t Stack<T>::capacity() const
{
  return max_items;
};

/**
 * Return the number of items on the stack.
 *
 * @return Number of items on the stack (int)
 */
template <class T> size_t Stack<T>::size() const
{
  return num_items;
};

/**
 * Resize the the member variable `items`.
 * Don't forget to free up any memory that is no longer used.
 *
 * @param n The size of the stack after resizing
 */
template <class T> void Stack<T>::resize(size_t n)
{
  // temp array
  T * new_items = new T[n];

  // copy existing values
  for (size_t i=0; i < size(); i++) {
    new_items[i] = items[i];
  }

  // free old memory
  delete[] items;

  // assign new array to member variable
  items = new_items;

  // update max_size
  max_items = n;
};