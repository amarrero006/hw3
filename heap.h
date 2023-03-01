#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
    /**
     * @brief Construct a new Heap object
     *
     * @param m ary-ness of heap tree (default to 2)
     * @param c binary predicate function/functor that takes two items
     *          as an argument and returns a bool if the first argument has
     *          priority over the second.
     */
    Heap(int m=2, PComparator c = PComparator());

    /**
    * @brief Destroy the Heap object
    *
    */
    ~Heap();

    /**
     * @brief Push an item to the heap
     *
     * @param item item to heap
     */
    void push(const T& item);

    /**
     * @brief Returns the top (priority) item
     *
     * @return T const& top priority item
     * @throw std::underflow_error if the heap is empty
     */
    T const & top() const;

    /**
     * @brief Remove the top priority item
     *
     * @throw std::underflow_error if the heap is empty
     */
    void pop();

    /// returns true if the heap is empty

    /**
     * @brief Returns true if the heap is empty
     *
     */
    bool empty() const;

    /**
   * @brief Returns size of the heap
   *
   */
    size_t size() const;

private:
    /// Add whatever helper functions and data members you need below
    std::vector<T> data;
    void heapify(int index);
    int m_;
    PComparator c;

};

// Add implementation of member functions here


// We will start top() for you to handle the case of
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
    // Here we use exceptions to handle the case of trying
    // to access the top element of an empty heap
    if(empty()){
        // ================================
        // throw the appropriate exception
        // ================================
        throw std::underflow_error("Heap is empty");

    }
    // If we get here we know the heap has at least 1 item
    // Add code to return the top element
    return data.front();

}


// We will start pop() for you to handle the case of
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
    if(empty()){
        // ================================
        // throw the appropriate exception
        // ================================
    throw std::underflow_error("Heap is empty");

    }
    data[0] = data.back();
    data.pop_back();
    heapify(0);

}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T &item) {

    data.push_back(item);
    int index = data.size() - 1;
    while(index!=0){
        int parent_index = (index - 1) / m_;
        T& current = data[index];
        T& parent = data[parent_index];
        if(!c(current, parent)){
            break;
        }
        std::swap(current, parent);
        index = parent_index;
    }

}

template <typename T, typename PComparator>
void Heap<T, PComparator>::heapify(int index) {
    std::vector<unsigned int> children_indexes;
    for(int i = 1; i <= m_; i++){
        children_indexes.push_back(m_*index + i);
    }
    int highest = index;
    for(unsigned int i = 0; i < children_indexes.size(); i++){
        if(children_indexes[i] < data.size() && c(data[children_indexes[i]], data[highest]) ) {
            highest = children_indexes[i];
        }
    }

    if(highest != index){
        std::swap(data[index], data[highest]);
        heapify(highest);
    }
}

template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c) : m_(m), c(c){

}

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap(){
    data.clear();
}

template <typename T, typename PComarator>
bool Heap<T, PComarator>::empty() const {
    return data.empty();
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const {
    return data.size();
}


#endif

