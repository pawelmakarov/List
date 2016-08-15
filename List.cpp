#include <iostream>
#include <cstdlib>

using namespace std;

class OutOfMemory {};

template <class Type>
class List {
    private:
        Type *ptr;
        size_t size;
        size_t current;
    public:
        List(size_t size) : size(size), current(0) {
            ptr = (Type*)malloc(size*sizeof(Type));

            if ( ptr == NULL ) {
                throw OutOfMemory();
            }
        }

        size_t getSize() const {
            return current;
        }

        size_t realSize() const {
            return size;
        }

        void append(const Type& value) {
            size_t newCurrent = current + 1;

            if ( newCurrent >= size ) {
                size_t newSize = size + 1;
                Type* newPtr = (Type*)realloc(ptr, newSize*sizeof(Type));

                if ( newPtr == NULL ) {
                    throw OutOfMemory();
                }
                size = newSize;
                ptr = newPtr;
            }

            this->ptr[current] = value;
            current = newCurrent;
        }

        const Type& operator[](size_t index) {
            return this->ptr[index];
        }

        ~List() {
            for ( int i = 0; i < current; i++ ) {
                delete ptr[i];
            }
            free(ptr);
        }

};

class Integer {
    private:
        int value;
    public:
        Integer(int value) : value(value) {}
        int getValue() const {
            return value;
        }
        ~Integer() {
            cout << "I'm deleted! Bye!" << endl;
        }
};

ostream& operator<<(ostream& out, const Integer& obj) {
    out << obj.getValue();
    return out;
}


int main() {
    List<Integer*>* lst = new List<Integer*>(100);

    for ( int i = 0; i < 25; i++ ) {
        lst->append(new Integer(i));
    }

    for ( int i = 0; i < lst->getSize(); i++ ) {
        cout << *((*lst)[i]) << endl;
    }

    delete lst;

    return 0;
}







