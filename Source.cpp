#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <iterator>

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
        if (index < 0 || static_cast<std::size_t>(index) >= size)
        {
            throw std::out_of_range("Index is out of range");
        }
    }

    void resize()
    {
        std::size_t newCapacity = (capacity == 0) ? 1 : capacity * 2;
        T* newArray = new T[newCapacity]{};

        for (std::size_t i = 0; i < size; i++)
        {
            newArray[i] = dynamicArray[i];
        }

        delete[] dynamicArray;

        dynamicArray = newArray;
        capacity = newCapacity;
    }

public:
    class Iterator
    {
    private:
        T* ptr_;

    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator(T* ptr = nullptr)
            : ptr_(ptr)
        {
        }

        reference operator*() const
        {
            return *ptr_;
        }

        pointer operator->() const
        {
            return ptr_;
        }

        Iterator& operator++()
        {
            ++ptr_;
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator temp = *this;
            ++ptr_;
            return temp;
        }

        Iterator& operator--()
        {
            --ptr_;
            return *this;
        }

        Iterator operator--(int)
        {
            Iterator temp = *this;
            --ptr_;
            return temp;
        }

        Iterator& operator+=(difference_type n)
        {
            if (n != 0)
            {
                ptr_ += n;
            }

            return *this;
        }

        Iterator& operator-=(difference_type n)
        {
            if (n != 0)
            {
                ptr_ -= n;
            }

            return *this;
        }

        Iterator operator+(difference_type n) const
        {
            Iterator temp = *this;
            temp += n;
            return temp;
        }

        Iterator operator-(difference_type n) const
        {
            Iterator temp = *this;
            temp -= n;
            return temp;
        }

        friend Iterator operator+(
            difference_type n,
            const Iterator& it)
        {
            return it + n;
        }

        difference_type operator-(const Iterator& other) const
        {
            if (ptr_ == other.ptr_)
            {
                return 0;
            }

            return ptr_ - other.ptr_;
        }

        reference operator[](difference_type n) const
        {
            return ptr_[n];
        }

        bool operator==(const Iterator& other) const
        {
            return ptr_ == other.ptr_;
        }

        bool operator!=(const Iterator& other) const
        {
            return ptr_ != other.ptr_;
        }

        bool operator<(const Iterator& other) const
        {
            return ptr_ < other.ptr_;
        }

        bool operator>(const Iterator& other) const
        {
            return ptr_ > other.ptr_;
        }

        bool operator<=(const Iterator& other) const
        {
            return ptr_ <= other.ptr_;
        }

        bool operator>=(const Iterator& other) const
        {
            return ptr_ >= other.ptr_;
        }
    };

    Vector() = default;

    explicit Vector(std::size_t sizeOfArray)
        : size(sizeOfArray), capacity(sizeOfArray)
    {
        if (capacity > 0)
        {
            dynamicArray = new T[capacity]{};
        }
    }

    Vector(const Vector<T>& other)
        : size(other.size), capacity(other.capacity)
    {
        if (capacity > 0)
        {
            dynamicArray = new T[capacity]{};

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
            newArray = new T[other.capacity]{};

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

    Iterator begin()
    {
        return Iterator(dynamicArray);
    }

    Iterator end()
    {
        if (size == 0)
        {
            return begin();
        }

        return Iterator(dynamicArray + size);
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
        if (index < 0 || static_cast<std::size_t>(index) >= N)
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

    bool operator==(const StaticArray<T, N>& other) const
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

    bool operator!=(const StaticArray<T, N>& other) const
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
    Vector<int> intVector(3);

    intVector[0] = 93;
    intVector[1] = 66;
    intVector[2] = 69;

    std::cout << "Before sorting: " << intVector << '\n';

    insertion_sort(intVector);

    std::cout << "After sorting: " << intVector << "\n\n";

    Vector<int> numbers;

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

    std::cout << "Using iterators: ";

    for (Vector<int>::Iterator it = numbers.begin();
        it != numbers.end();
        ++it)
    {
        std::cout << *it << ' ';
    }

    std::cout << '\n';

    std::cout << "Range-based for: ";

    for (int value : numbers)
    {
        std::cout << value << ' ';
    }

    std::cout << '\n';

    Vector<int>::Iterator it = numbers.begin();

    std::cout << "First element: " << *it << '\n';
    std::cout << "Third element: " << *(it + 2) << '\n';
    std::cout << "Second element using iterator[]: "
        << it[1] << '\n';
    std::cout << "Iterator distance: "
        << numbers.end() - numbers.begin() << '\n';

    it = numbers.end();
    --it;

    std::cout << "Last element: " << *it << '\n';

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