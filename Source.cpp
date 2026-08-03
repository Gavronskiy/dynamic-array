#include <iostream>
#include <stdexcept>

class Vector
{
private:
    unsigned int size = 0;
    int* dynamicArray = nullptr;

    void checkIndex(int index) const
    {
        if (index < 0 ||
            static_cast<unsigned int>(index) >= size)
        {
            throw std::out_of_range("Index is out of range");
        }
    }

public:
    Vector(int sizeOfArray)
    {
        size = sizeOfArray;
        dynamicArray = new int[size];
    }

    Vector(const Vector& other)
    {
        size = other.size;
        dynamicArray = new int[size];

        for (unsigned int i = 0; i < size; i++)
        {
            dynamicArray[i] = other.dynamicArray[i];
        }
    }

    ~Vector()
    {
        delete[] dynamicArray;
    }

    Vector& operator=(const Vector& other)
    {
        if (this == &other)
        {
            return *this;
        }

        int* newArray = new int[other.size];

        for (unsigned int i = 0; i < other.size; i++)
        {
            newArray[i] = other.dynamicArray[i];
        }

        delete[] dynamicArray;

        dynamicArray = newArray;
        size = other.size;

        return *this;
    }

    int& operator[](int index)
    {
        checkIndex(index);
        return dynamicArray[index];
    }

    const int& operator[](int index) const
    {
        checkIndex(index);
        return dynamicArray[index];
    }

    bool operator==(const Vector& other) const
    {
        if (size != other.size)
        {
            return false;
        }

        for (unsigned int i = 0; i < size; i++)
        {
            if (dynamicArray[i] != other.dynamicArray[i])
            {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const Vector& other) const
    {
        return !(*this == other);
    }

    void resize(int newSize)
    {
        int* newArray = new int[newSize];

        unsigned int copySize = size;

        if (newSize < size)
        {
            copySize = newSize;
        }

        for (unsigned int i = 0; i < copySize; i++)
        {
            newArray[i] = dynamicArray[i];
        }

        delete[] dynamicArray;

        dynamicArray = newArray;
        size = newSize;
    }

    void set(int index, int newValue)
    {
        checkIndex(index);
        dynamicArray[index] = newValue;
    }

    int get(int index) const
    {
        checkIndex(index);
        return dynamicArray[index];
    }
};

int main()
{
    Vector myVector(3);

    myVector[0] = 66;
    myVector[1] = 69;
    myVector[2] = 93;

    Vector copiedVector = myVector;

    std::cout << copiedVector[0] << '\n';
    std::cout << copiedVector[1] << '\n';
    std::cout << copiedVector[2] << '\n';

    Vector assignedVector(1);

    assignedVector = myVector;

    std::cout << std::boolalpha;

    std::cout << (myVector == copiedVector) << '\n';
    std::cout << (myVector != assignedVector) << '\n';

    copiedVector[0] = 100;

    std::cout << (myVector == copiedVector) << '\n';

    try
    {
        std::cout << myVector[5] << '\n';
    }
    catch (const std::out_of_range& exception)
    {
        std::cout << "Error: "
            << exception.what()
            << '\n';
    }

    return 0;
}