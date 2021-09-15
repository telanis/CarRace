/*
 Name: Tiana Sumaoang
 Description: Get car data from file, make them race!
 Input: File containing car info
 Output: Race results to console
 
 */

#include <iostream>
#include "priorityQ.h"
#include <fstream>
#include <vector>

//DEFAULT CONSTRUCTOR
template <class Type>
priorityQ<Type>::priorityQ(int capacity){
    
    this -> capacity = capacity;
    size = 0;
    heapArray = new Type [this -> capacity];
    
}


//COPY CONSTRUCTOR
template <class Type>
priorityQ<Type>::priorityQ(const priorityQ<Type>& copy){
    
    delete [] heapArray;

    heapArray = new Type [copy.capacity];
    capacity = copy.capacity;
    size = copy.size;
    
    for(int i = 1; i < size + 1; i++){
        heapArray[i] = copy.heapAraray[i];
    }
    
    
}
 

//DECONSTRUCTOR
template <class Type>
priorityQ<Type>::~priorityQ(){
    
    delete [] heapArray;
    
}


/*
 function_identifier: positions item at index in
 its correct position
 parameters: int index
 return value: N/A
 */
template <class Type>
void priorityQ<Type>::bubbleUp(int index){
    
    int parent = index/2;
    Type tmp;
        
    while(parent != 0){
        if(heapArray[index] > heapArray[parent]){
            //switch
            tmp = heapArray[parent];
            heapArray[parent] = heapArray[index];
            heapArray[index] = tmp;
            
            //update indexes
            index = parent;
            parent = index/2;
        }
        else
            return;
    
    }
    
}


/*
 function_identifier: positions item at index in
 its correct position
 parameters: int index
 return value: N/A
 */
template <class Type>
void priorityQ<Type>::bubbleDown(int index){
    
    Type tmp;
    int small = index * 2; //uwu
    int big = small + 1;
    
    
    while(index * 2 < size){
        //bubble down to smallest child
        if(heapArray[small] > heapArray[big]){
            //switch
            small ++;
            big --;
        }
        
    if(heapArray[big] > heapArray[index]){
        //switch values
        tmp = heapArray[big];
        heapArray[big] = heapArray[index];
        heapArray[index] = tmp;
        
        //update indexes
        index = big;
        small = index * 2;
        big = small + 1;
    }
    else
        return;
    }
    
}


/*
 function_identifier: overrides = operator
 parameters: priorityQ rhs
 return value: priorityQ &
 */
template <class Type>
const priorityQ<Type>& priorityQ<Type>::operator=(const priorityQ<Type>& rhs){
    
    
    return * priorityQ(rhs);
}


/*
 function_identifier: inserts new item, resizes if needed
 parameters: Type& item
 return value: N/A
 */
template <class Type>
void priorityQ<Type>::insert(const Type& item){
 
    size++;
    heapArray[size] = item;

    
    if(size >= capacity * 0.5){
        
        
        int oldCap = capacity;
        Type * tmp = heapArray;
        capacity = capacity + 10;
        heapArray = new Type[capacity];
        
        for(int i = 1; i < size + 1; i++){
            heapArray[i] = tmp[i];
        }
        
        delete [] tmp;
        
    }
       
    bubbleUp(size);
    
}


/*
 function_identifier: removes highest priority element
 parameters: N/A
 return value: N/A
 */
template <class Type>
void priorityQ<Type>::remove(){

    if(size == 0)
        return;
    
    Type tmp = heapArray[size];
    
    heapArray[1] = tmp;
    size--;
    bubbleDown(1);
    
}


/*
 function_identifier: returns highest priority
 parameters: N/A
 return value: Type item in 1st index
 */
template <class Type>
Type priorityQ<Type>::getHighestPriority() const{

    return heapArray[1];

}


/*
 function_identifier: return true if empty
 parameters: N/A
 return value: bool
 */
template <class Type>
bool priorityQ<Type>::isEmpty() const{
    
    if(size == 0)
        return true;
    else
        return false;
    
}


/*
 function_identifier: returns size
 parameters: N/A
 return value: size_t size
 */
template <class Type>
size_t priorityQ<Type>::getSize() const {
    
    return size;
    
}


//car structure definition
struct carType{
    std::string name;
    int currentSpeed;
    double distance;
    int maxSpeed;
    
    
    bool operator > (carType rhs){
        if (this -> distance > rhs.distance)
            return true;
        else
            return false;
    }
};


/*
 function_identifier: checks if a file exists
 parameters: string name
 return value: true or false
 */
bool fileCheck (std::string name) {
    std::ifstream infile (name);
    return infile.good();
}


/*
 function_identifier: main function recieves file name, inserts cars
 into priorityQ and outputs winners in order
 parameters: N/A
 return value: N/A
 */
int main() {

    std::string fileName;
    std::string s;
    
    //prompt for file
    std::cout << "File name: ";
    std::cin >> fileName;


    //check if file exists
    while(fileCheck(fileName) == false){
        std::cout << "Please input valid file name: ";
        std::cin >> fileName;
    }
        
    std::ifstream infile (fileName);
    
    priorityQ<carType> race;
    
    //input cars into priorityQ
    while (infile >> s){
        carType car;
        car.name = s;
        infile >> car.maxSpeed;
        car.distance = car.currentSpeed = 0;
        race.insert(car);
    }
    infile.close();
    
    //start the race
    int rank = 1;
    int vsize = race.getSize();
    int count;
    //while there are still cars in the race
    while(!race.isEmpty()){
        std::vector<carType> storage (vsize);
        count = 0;
        int v = vsize;
        for(int i = 1; i < v + 1; i++){
            carType c = race.getHighestPriority();
            if(c.distance >= 10000){
                std::cout << "Rank "<< rank << ": " << c.name << std::endl;
                rank++;
                vsize--;
                
            }
            //update speed and distance
            else{
                c.currentSpeed = rand() % (c.maxSpeed/2) + ((c.maxSpeed/2) + 1);
                c.distance = c.distance + (c.currentSpeed/360.0);
                storage[count] = c;
                count++;
            }
            race.remove();
        }
        
        //insert cars back into priorityQ
        for(int j = 0; j < vsize; j++)
            race.insert(storage[j]);
        
    }

    return 0;
}
