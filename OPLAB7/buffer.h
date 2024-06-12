#pragma once
#include <iostream>

template<class T>
class CircularBuffer {
 private:
  size_t head_ = 0;
  size_t tail_ = 0;
  size_t capacity_ = 0;
  size_t size_ = 0;
  T *buffer;
 public:
  CircularBuffer() = default;
  // default constructor

  ~CircularBuffer() {
    // destructor
    delete[] buffer;
  };

  explicit CircularBuffer(size_t x) : capacity_(x) {
    // size constructor
    buffer = new T[x];
  };

  CircularBuffer(size_t x, const T &value) : capacity_(x), size_(x) {
    // size & value fill constructor
    buffer = new T[x];
    for (size_t i = 0; i < x; ++i) {
      buffer[i] = value;
    }
  };

  CircularBuffer(const CircularBuffer &other) : capacity_(other.capacity_), head_(other.head_),
                                                tail_(other.tail_), size_(other.size_) {
    // copy constructor
    buffer = new T[capacity_];
    for (size_t i = 0; i < capacity_; ++i) {
      buffer[i] = other[i];
    }
  };

  bool operator==(const CircularBuffer<T> &other) {
    if (size_ != other.size_ || head_ != other.head_ || tail_ != other.tail_) {
      return false;
    }
    for (size_t i = 0; i < size_; ++i) {
      if (buffer[i] != other.buffer[i]) {
        return false;
      }
    }
    return true;
  }

  bool operator!=(const CircularBuffer<T> &other) {
    return !(*this == other); // inverse for '==' operator (NOT SIMILAR AS INFINITE RECURSION WITH '!=')
  }

  CircularBuffer &operator=(const CircularBuffer &other) {
    if (this != &other) {
      delete[] buffer;
      buffer = new T[other.capacity_];
      tail_ = other.tail_;
      head_ = other.head_;
      size_ = other.size_;
      capacity_ = other.capacity_;
      for (size_t i = 0; i < size_; ++i) {
        buffer[i] = other.buffer[i];
      }
    }
    return *this;
  }

  CircularBuffer(CircularBuffer &&other) noexcept
  // move constructor
      : head_(other.head_), tail_(other.tail_), capacity_(other.capacity_), size_(other.size_), buffer(other.buffer) {
    other.buffer = nullptr; // resetting the buffer of the moved-from object
    other.capacity_ = 0;
    other.size_ = 0;
    other.head_ = 0;
    other.tail_ = 0;
  }

  CircularBuffer &operator=(CircularBuffer &&other) noexcept {
    // move assignment operator
    if (this != &other) {
      delete[] buffer;
      head_ = other.head_;
      tail_ = other.tail_;
      capacity_ = other.capacity_;
      size_ = other.size_;
      buffer = other.buffer;
      other.buffer = nullptr; // resetting the buffer of the moved-from object
      other.capacity_ = 0;
      other.size_ = 0;
      other.head_ = 0;
      other.tail_ = 0;
    }
    return *this;
  }

  class Iterator : public std::iterator<std::random_access_iterator_tag, T> {
   public:
    using iterator_category = std::random_access_iterator_tag;
    using difference_type = std::ptrdiff_t; // the signed integer type of the result of subtracting two pointers
    using value_type = T;
    using size_type = size_t;
    using pointer = T *;
    using reference = T &;

    value_type *data_;
    value_type *curr_;
    size_type capacity_it;

    // constructors
    Iterator() = default;
    Iterator(value_type *data, size_type capacity) : data_(data), capacity_it(capacity) {}
    Iterator(const value_type *data, value_type *elem, size_type capacity)
        : data_(const_cast<value_type *>(data)), curr_(elem), capacity_it(capacity) {}
    Iterator(const Iterator &other) : data_(other.data_), capacity_it(other.capacity_it), curr_(other.curr_) {}

    Iterator &operator++() {
      // prefix operator '++'
      curr_++;
      if (curr_ == data_ + capacity_it) {
        curr_ = data_;
      }
      return *this;
    };

    Iterator operator++(int) {
      // postfix operator '++'
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    };

    Iterator &operator=(const Iterator &other) {
      if (this != &other) {
        data_ = other.data_;
        curr_ = other.curr_;
        capacity_it = other.capacity_it;
      }
      return *this;
    }

    Iterator &operator--() {
      // prefix operator '--'
      if (curr_ == data_) {
        curr_ = data_ + capacity_it - 1;
      } else {
        curr_--;
      }
      return *this;
    };

    Iterator operator--(int) {
      // postfix operator '--'
      Iterator tmp = *this;
      --(*this);
      return tmp;
    };

    Iterator &operator+=(difference_type d) {
      difference_type index = curr_ - data_ + d;
      if (index >= capacity_it) {
        index -= capacity_it;
      } else if (index < 0) {
        index += capacity_it;
      }
      curr_ = data_ + index;
      return *this;
    };

    Iterator &operator-=(difference_type d) {
      return *this += -d;
    };

    Iterator operator+(difference_type d) const {
      Iterator tmp = *this;
      return tmp += d;
    };

    Iterator operator-(difference_type d) const {
      Iterator tmp = *this;
      return tmp -= d;
    };

    difference_type operator+(const Iterator &rhs) const {
      return curr_ + rhs.curr_;
    }

    difference_type operator-(const Iterator &rhs) const {
      return curr_ - rhs.curr_;
    }

    bool operator==(const Iterator &other_iterator) const {
      return (curr_ == other_iterator.curr_) && (data_ == other_iterator.data_);
    };

    bool operator!=(const Iterator &other_iterator) const {
      return (curr_ != other_iterator.curr_) || (data_ != other_iterator.data_);
    };

    bool operator>(const Iterator &a) const {
      return (curr_ > a.curr_) && (data_ == a.data_);
    };

    bool operator<(const Iterator &a) const {
      return (curr_ < a.curr_) && (data_ == a.data_);
    };

    bool operator<=(const Iterator &a) const {
      return (curr_ <= a.curr_) && (data_ == a.data_);
    };

    bool operator>=(const Iterator &a) const {
      return (curr_ >= a.curr_) && (data_ == a.data_);
    };

    virtual reference operator*() const {
      return *curr_;
    }

    virtual pointer operator->() const {
      return curr_;
    }
  };

  class ConstIterator : public Iterator {
   public:
    using value_type = T;

    // constructors
    ConstIterator() : Iterator() {}
    ConstIterator(const value_type *data, value_type *elem, size_t size) : Iterator(data, elem, size) {}
    explicit ConstIterator(const Iterator &it) : Iterator(it) {}
    ConstIterator(const ConstIterator &other) : Iterator(other) {}

    ConstIterator &operator=(const ConstIterator &other) {
      if (this != &other) {
        Iterator::operator=(other);
      }
      return *this;
    }

    const T *operator->() {
      return &(Iterator::operator*());
    }

    const T &operator*() {
      return Iterator::operator*();
    }
  };

  ConstIterator c_begin() {
    return ConstIterator(&buffer[0], &buffer[0], size_ + 1);
  }

  ConstIterator c_end() {
    return ConstIterator(&buffer[0], &buffer[size_], size_ + 1);
  }

  Iterator begin() {
    return Iterator(&buffer[0], &buffer[0], size_ + 1);
  }

  Iterator end() {
    return Iterator(&buffer[0], &buffer[size_], size_ + 1);
  }

  void push_back(const T &value) {
    if (size_ < capacity_) {
      buffer[tail_] = value;
      tail_++;
      if (tail_ == capacity_) {
        tail_ = 0;
      }
      size_++;
    } else {
      buffer[head_] = value;
      head_++;
      if (head_ == capacity_) {
        head_ = 0;
      }
      tail_++;
      if (tail_ == capacity_) {
        tail_ = 0;
      }
    }
  };

  void pop_back() {
    if (size_ > 0) {
      tail_--;
      if (tail_ < 0) {
        tail_ = capacity_ - 1;
      }
      size_--;
    }
  }

  void push_front(const T &value) {
    if (size_ < capacity_) {
      head_ = (head_ - 1 + capacity_) % capacity_;
      buffer[head_] = value;
      size_++;
    } else {
      buffer[head_] = value;
      head_ = (head_ + 1) % capacity_;
      tail_ = (tail_ + 1) % capacity_;
    }
  }

  void pop_front() {
    if (size_ > 0) {
      head_ = (head_ + 1) % capacity_;
      size_--;
    }
  }

  [[nodiscard]] size_t size() const {
    return size_;
  }

  [[nodiscard]] size_t capacity() const {
    return capacity_;
  }

  [[nodiscard]] bool empty() const {
    return size_ == 0;
  }

  void clear() {
    head_ = 0;
    tail_ = 0;
    size_ = 0;
  }

  Iterator insert(ConstIterator it, const T &value) {
    if (size_ + 1 > capacity_) {
      throw std::out_of_range("Buffer is full");
    }
    if (it < begin() || it > end()) {
      throw std::out_of_range("Iterator is out of range");
    }
    Iterator Begin = begin() + head_;
    Iterator End = begin() + tail_;
    T *old_buffer = new T[capacity_];
    size_ += 1;
    buffer = new T[capacity_];
    while (Begin != End && Begin != it) {
      push_back(*Begin);
      Begin++;
    }
    push_back(value);
    tail_++;
    while (Begin != End) {
      push_back(*Begin);
      Begin++;
    }
    delete[] old_buffer;
    return it;
  }

  Iterator erase(Iterator pos) {
    if (pos < begin() || pos >= end()) {
      throw std::out_of_range("Iterator is out of range");
    }
    Iterator it = pos;
    Iterator next_it = it + 1;
    while (next_it != end()) {
      *it = *next_it;
      ++it;
      ++next_it;
    }
    --tail_;
    --size_;
    if (tail_ < 0) {
      tail_ = capacity_ - 1;
    }
    return pos;
  }

  T &front() {
    return buffer[head_];
  };

  const T &front() const {
    return buffer[head_];
  };

  T &back() {
    if (tail_ == 0) {
      return buffer[capacity_ - 1];
    } else {
      return buffer[tail_ - 1];
    }
  };

  const T &back() const {
    if (tail_ == 0) {
      return buffer[capacity_ - 1];
    } else {
      return buffer[tail_ - 1];
    }
  };

  T &operator[](size_t index) {
    return buffer[(head_ + index) % capacity_];
  }

  const T &operator[](size_t index) const {
    return buffer[(head_ + index) % capacity_];
  }

  void recap(size_t new_capacity) {
    if (new_capacity > capacity_) {
      T *new_buffer = new T[new_capacity];
      for (size_t i = 0; i < size_; ++i) {
        new_buffer[i] = buffer[(head_ + i) % capacity_];
      }
      head_ = 0;
      tail_ = size_;
      capacity_ = new_capacity;
      delete[] buffer;
      buffer = new_buffer;
    }
  };

  void resize(size_t new_size) {
    //
    delete[] buffer;
    buffer = new T[new_size];
    //
    if (new_size > size_) {
      recap(new_size);
      for (size_t i = size_; i < new_size; ++i) {
        push_back(T());
      }
    } else {
      while (size_ > new_size) {
        pop_back();
      }
    }
  };
};