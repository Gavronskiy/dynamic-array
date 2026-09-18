#include <iostream>
#include <stdexcept>
#include <cstddef>

template <typename T>
class Vector;

template <typename T>
std::ostream& operator<<(std::ostream& out, const Vector<T>& vector);

template <typename T>
std::istream& operator>>(std::istream& in, Vector<T>& vector);

template <typename T>
class Vector
{
private:
    std::size_t size = 0;
    std::size_t capacity = 0;
    T* dynamicArray = nullptr;

    void checkIndex(int index) const
    {
        if (index < 0 ||
            static_cast<std::size_t>(index) >= size)
        {
            throw std::out_of_range("Index is out of range");
        }
    }

    void resize()
    {
        std::size_t newCapacity =
            (capacity == 0) ? 1 : capacity * 2;

        T* newArray = new T[newCapacity];

        for (std::size_t i = 0; i < size; i++)
        {
            newArray[i] = dynamicArray[i];
        }

        delete[] dynamicArray;

        dynamicArray = newArray;
        capacity = newCapacity;
    }

public:
    Vector() = default;

    explicit Vector(std::size_t sizeOfArray)
        : size(sizeOfArray), capacity(sizeOfArray)
    {
        if (capacity > 0)
        {
            dynamicArray = new T[capacity];
        }
    }

    Vector(const Vector<T>& other)
        : size(other.size), capacity(other.capacity)
    {
        if (capacity > 0)
        {
            dynamicArray = new T[capacity];

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

        if (other.capacity > 0)
        {
            newArray = new T[other.capacity];

            for (std::size_t i = 0; i < other.size; i++)
            {
                newArray[i] = other.dynamicArray[i];
            }
        }

        delete[] dynamicArray;

        dynamicArray = newArray;
        size = other.size;
        capacity = other.capacity;

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

    void push_back(const T& value)
    {
        if (size == capacity)
        {
            resize();
        }

        dynamicArray[size] = value;
        ++size;
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
    std::size_t getSize() const
    {
        return size;
    }

    std::size_t getCapacity() const
    {
        return capacity;
    }

    template <typename U>
    friend std::ostream& operator<<(
        std::ostream& out,
        const Vector<U>& vector);

    template <typename U>
    friend std::istream& operator>>(
        std::istream& in,
        Vector<U>& vector);
};

template <typename T>
std::ostream& operator<<(
    std::ostream& out,
    const Vector<T>& vector)
{
    for (std::size_t i = 0; i < vector.size; i++)
    {
        if (i > 0)
        {
            out << ' ';
        }

        out << vector.dynamicArray[i];
    }

    return out;
}

template <typename T>
std::istream& operator>>(
    std::istream& in,
    Vector<T>& vector)
{
    for (std::size_t i = 0; i < vector.size; i++)
    {
        in >> vector.dynamicArray[i];
    }

    return in;
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
    Vector<int> numbers;

    intVector.resize(3);
    intVector[0] = 93;
    intVector[1] = 66;
    intVector[2] = 69;

    insertion_sort(intVector);
    int values[5] = { 66, 69, 93, 101, 202 };

    for (int i = 0; i < 5; i++)
    {
        numbers.push_back(values[i]);

        std::cout << "After push_back(" << values[i] << "): "
            << "size = " << numbers.getSize()
            << ", capacity = " << numbers.getCapacity()
            << '\n';
    }

    std::cout << "\nVector: " << numbers << '\n';

    Vector<int> inputVector(3);

    std::cout << "\nEnter 3 integers: ";
    std::cin >> inputVector;
    std::cout << "Input vector: " << inputVector << '\n';

    Vector<int> copiedNumbers = numbers;
    Vector<int> assignedNumbers;
    assignedNumbers = numbers;

    std::cout << std::boolalpha;
    std::cout << "Copied vector is equal: "
        << (numbers == copiedNumbers) << '\n';
    std::cout << "Assigned vector is equal: "
        << (numbers == assignedNumbers) << '\n';

    try
    {
        std::cout << numbers[10] << '\n';
    }
    catch (const std::out_of_range& exception)
    {
        std::cout << "Vector error: "
            << exception.what() << '\n';
    }

    StaticArray<int, 3> staticIntArray;
    staticIntArray[0] = 10;
    staticIntArray[1] = 20;
    staticIntArray[2] = 30;

    std::cout << "StaticArray<int, 3>: ";

    for (int i = 0; i < 3; i++)
    {
        if (i > 0)
        {
            std::cout << ' ';
        }

        std::cout << staticIntArray[i];
    }

    std::cout << '\n';

    return 0;
}