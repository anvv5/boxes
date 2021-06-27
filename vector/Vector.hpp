#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <cstddef>
#include <limits>
#include <util.hpp>
#include <stdexcept.hpp>

namespace ft {

    <T,Alloc=std::allocator<T>>
    class Vector {
    public:
        typedef T                                           value_type;
        typedef Alloc                                       allocator_type;
        typedef typename allocator_type::reference          reference;
        typedef typename allocator_type::const_reference    const_reference;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::cnst_pointer       const_pointer;
        typedef VectorIterator<value_type>                  iterator;
        typedef VectorReverseIterator<value_type>           reverse_iterator;
        typedef VectorConstIterator<value_type>             const_iterator;
        typedef VectorConstReverseIterator<value_type>      const_reference_iterator;
        typedef ptrdiff_t                                   difference_type;
        typedef size_t                                      size_type;

    private:
        pointer         _data;
        allocator_type  _alloc;
        size_t          _size;
        size_t          _capacity;

        void    reallocateData(size_t n) {
            if (this->_capacity)
                this->_alloc.deallocate(this->_data, this->_capacity);
            this->_capacity = n;
            this->_data = this->_alloc.allocate(this->_capacity);
        }

        size_type   iteratorPos(iterator i) {
            if (i == iterator(NULL))
                return (0);
            size_type pos = 0;
            iterator it = begin();
            while (it != end()) {
                if (it == i)
                    return (pos);
                pos++;
                it++;
            }
            return (pos);
        }

    public:
        explict Vector(const allocator_type &alloc = allocator_type())
            : _data(NULL), _alloc(alloc), _size(0), _capacity(0) {}

        explict Vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type())
            : _data(NULL), _alloc(alloc), _size(0), _capacity(0) {
                assign(n, val);
            }

        <InputIterator>
        Vector(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type(), typename enable_if<!std::numeric_limits<InputIterator>::is_specialized>::type * = 0)
            : _data(NULL), _alloc(alloc), _size(0), _capacity(0) {
                assign(first, last);
            }

        Vector(const Vector &src)
            : _data(NULL), _alloc(alloc), _size(0), _capacity(0) {
                assign(src.begin(), src.end());
            }

        ~Vector() {
            clear();
            this->_alloc.deallocate(this->_data, this->_capacity);
        }
    }
}

#endif