#include <iostream>

class Vector
{
private:
    unsigned int size = 0;
    int* dynamicArray = nullptr;

public:
    Vector(int sizeOfArray)
    {
        size = sizeOfArray;
        dynamicArray = new int[size];
    }

    ~Vector()
    {
        delete[] dynamicArray;
    }

    void resize(int newSize)
    {
        int* newArray = new int[newSize];

        int copySize = size;

        if (newSize < size)
        {
            copySize = newSize;
        }

        for (int i = 0; i < copySize; i++)
        {
            newArray[i] = dynamicArray[i];
        }

        delete[] dynamicArray;

        dynamicArray = newArray;
        size = newSize;
    }

    void set(int index, int newValue)
    {
        dynamicArray[index] = newValue;
    }

    int get(int index) const
    {
        return dynamicArray[index];
    }
};

int main()
{
    Vector myVector(3);

    myVector.set(0, 66);
    myVector.set(1, 69);
    myVector.set(2, 93);

    std::cout << myVector.get(0) << '\n';
    std::cout << myVector.get(1) << '\n';
    std::cout << myVector.get(2) << '\n';

    myVector.resize(5);

    myVector.set(3, 99);
    myVector.set(4, 101);

    std::cout << myVector.get(0) << '\n';
    std::cout << myVector.get(1) << '\n';
    std::cout << myVector.get(2) << '\n';
    std::cout << myVector.get(3) << '\n';
    std::cout << myVector.get(4) << '\n';

    return 0;
}