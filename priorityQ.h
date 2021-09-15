//
//  priorityQ.h
//
//
//  Created by Tiana Sumaoang on 8/2/21.
//

#ifndef priorityQ_h
#define priorityQ_h



template <class Type>
class priorityQ{
    
public:
    
    priorityQ(int = 10);
    priorityQ(const priorityQ<Type>&);
    ~priorityQ();
    const priorityQ<Type>& operator=(const priorityQ<Type>&);
    void insert(const Type&);
    void remove();
    Type getHighestPriority() const;
    bool isEmpty() const;
    size_t getSize() const;
    
private:
    
    void bubbleUp(int);
    void bubbleDown(int);
    
    size_t capacity;
    size_t size;
    Type * heapArray;
    
};





#endif /* priorityQ_h */
