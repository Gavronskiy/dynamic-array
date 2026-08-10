#include <iostream>
#include <stdexcept>
#include <cstddef>

template <typename T>
class Vector
{
private:
    std::size_t size = 0;
    T* dynamicArray = nullptr;

    void checkIndex(int index) const
    {
        if (index < 0 ||
            static_cast<std::size_t>(index) >= size)
        {
            throw std::out_of_range("Index is out of range");
        }
    }

public:
    Vector() = default;

    explicit Vector(std::size_t sizeOfArray)
    {
        size = sizeOfArray;

        if (size > 0)
        {
            dynamicArray = new T[size];
        }
    }

    Vector(const Vector<T>& other)
    {
        size = other.size;

        if (size > 0)
        {
            dynamicArray = new T[size];

            for (std::size_t i = 0; i < size; i++)
            {
                dynamicArray[i] = other.dynamicArray[i];
            }
        }
    }

    ~Vector()
    {
        delete[] dynamicArray;
    }

    Vector<T>& operator=(const Vector<T>& other)
    {
        if (this == &other)
        {
            return *this;
        }

        T* newArray = nullptr;

        if (other.size > 0)
        {
            newArray = new T[other.size];

            for (std::size_t i = 0; i < other.size; i++)
            {
                newArray[i] = other.dynamicArray[i];
            }
        }

        delete[] dynamicArray;

        dynamicArray = newArray;
        size = other.size;

        return *this;
    }

    T& operator[](int index)
    {
        checkIndex(index);
        return dynamicArray[index];
    }

    const T& operator[](int index) const
    {
        checkIndex(index);
        return dynamicArray[index];
    }

    explicit operator bool() const
    {
        return size > 0;
    }

    bool operator==(const Vector<T>& other) const
    {
        if (size != other.size)
        {
            return false;
        }

        for (std::size_t i = 0; i < size; i++)
        {
            if (dynamicArray[i] != other.dynamicArray[i])
            {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const Vector<T>& other) const
    {
        return !(*this == other);
    }

    void resize(std::size_t newSize)
    {
        T* newArray = nullptr;

        if (newSize > 0)
        {
            newArray = new T[newSize];
        }

        std::size_t copySize = size;

        if (newSize < size)
        {
            copySize = newSize;
        }

        for (std::size_t i = 0; i < copySize; i++)
        {
            newArray[i] = dynamicArray[i];
        }

        delete[] dynamicArray;

        dynamicArray = newArray;
        size = newSize;
    }

    void set(int index, const T& newValue)
    {
        checkIndex(index);
        dynamicArray[index] = newValue;
    }

    T get(int index) const
    {
        checkIndex(index);
        return dynamicArray[index];
    }
};

int main()
{
    Vector<int> intVector;

    intVector.resize(3);
    intVector[0] = 66;
    intVector[1] = 69;
    intVector[2] = 93;

    std::cout << "Vector<int>:\n";

    for (int i = 0; i < 3; i++)
    {
        std::cout << intVector[i] << '\n';
    }

    Vector<double> doubleVector;

    doubleVector.resize(3);
    doubleVector[0] = 1.5;
    doubleVector[1] = 2.75;
    doubleVector[2] = 3.14;

    std::cout << "\nVector<double>:\n";

    for (int i = 0; i < 3; i++)
    {
        std::cout << doubleVector[i] << '\n';
    }

    try
    {
        std::cout << intVector[5] << '\n';
    }
    catch (const std::out_of_range& exception)
    {
        std::cout << "\nError: "
            << exception.what()
            << '\n';
    }

    return 0;
}