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

    std::size_t get_size() const
    {
        return size;
    }
};

template <typename T>
void insertion_sort(Vector<T>& arr)
{
    for (std::size_t i = 1; i < arr.get_size(); i++)
    {
        T value = arr[static_cast<int>(i)];
        int j = static_cast<int>(i) - 1;

        while (j >= 0 && arr[j] > value)
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = value;
    }
}

template <typename T, std::size_t N>
class StaticArray
{
private:
    static_assert(
        N > 0,
        "StaticArray size must be greater than zero"
        );

    T data_[N]{};

    void checkIndex(int index) const
    {
        if (index < 0 ||
            static_cast<std::size_t>(index) >= N)
        {
            throw std::out_of_range("Index is out of range");
        }
    }

public:
    StaticArray() = default;

    StaticArray(const StaticArray<T, N>& other)
    {
        for (std::size_t i = 0; i < N; i++)
        {
            data_[i] = other.data_[i];
        }
    }

    StaticArray<T, N>& operator=(
        const StaticArray<T, N>& other)
    {
        if (this == &other)
        {
            return *this;
        }

        for (std::size_t i = 0; i < N; i++)
        {
            data_[i] = other.data_[i];
        }

        return *this;
    }

    T& operator[](int index)
    {
        checkIndex(index);
        return data_[index];
    }

    const T& operator[](int index) const
    {
        checkIndex(index);
        return data_[index];
    }

    explicit operator bool() const
    {
        return N > 0;
    }

    bool operator==(
        const StaticArray<T, N>& other) const
    {
        for (std::size_t i = 0; i < N; i++)
        {
            if (data_[i] != other.data_[i])
            {
                return false;
            }
        }

        return true;
    }

    bool operator!=(
        const StaticArray<T, N>& other) const
    {
        return !(*this == other);
    }

    void set(int index, const T& newValue)
    {
        checkIndex(index);
        data_[index] = newValue;
    }

    T get(int index) const
    {
        checkIndex(index);
        return data_[index];
    }
};

int main()
{
    Vector<int> intVector;

    intVector.resize(3);
    intVector[0] = 93;
    intVector[1] = 66;
    intVector[2] = 69;

    insertion_sort(intVector);

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
        std::cout << "\nVector error: "
            << exception.what()
            << '\n';
    }

    StaticArray<int, 3> staticIntArray;

    staticIntArray[0] = 10;
    staticIntArray[1] = 20;
    staticIntArray[2] = 30;

    std::cout << "\nStaticArray<int, 3>:\n";

    for (int i = 0; i < 3; i++)
    {
        std::cout << staticIntArray[i] << '\n';
    }

    StaticArray<double, 2> staticDoubleArray;

    staticDoubleArray.set(0, 1.25);
    staticDoubleArray.set(1, 2.5);

    std::cout << "\nStaticArray<double, 2>:\n";

    for (int i = 0; i < 2; i++)
    {
        std::cout << staticDoubleArray.get(i) << '\n';
    }

    StaticArray<int, 3> copiedStaticArray =
        staticIntArray;

    StaticArray<int, 3> assignedStaticArray;
    assignedStaticArray = staticIntArray;

    std::cout << std::boolalpha;

    std::cout << "\nCopied arrays are equal: "
        << (staticIntArray == copiedStaticArray)
        << '\n';

    std::cout << "Assigned arrays are equal: "
        << (staticIntArray == assignedStaticArray)
        << '\n';

    copiedStaticArray[0] = 100;

    std::cout << "Arrays are different after change: "
        << (staticIntArray != copiedStaticArray)
        << '\n';

    try
    {
        std::cout << staticIntArray[5] << '\n';
    }
    catch (const std::out_of_range& exception)
    {
        std::cout << "\nStaticArray error: "
            << exception.what()
            << '\n';
    }

    return 0;
}