/*
 * Copyright © 2017,2018  Google, Inc.
 *
 *  This is part of HarfBuzz, a text shaping library.
 *
 * Permission is hereby granted, without written agreement and without
 * license or royalty fees, to use, copy, modify, and distribute this
 * software and its documentation for any purpose, provided that the
 * above copyright notice and the following two paragraphs appear in
 * all copies of this software.
 *
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES
 * ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN
 * IF THE COPYRIGHT HOLDER HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 * THE COPYRIGHT HOLDER SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING,
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE COPYRIGHT HOLDER HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 *
 * Google Author(s): Behdad Esfahbod
 */

#ifndef RB_VECTOR_HH
#define RB_VECTOR_HH

#include "hb.hh"
#include "hb-array.hh"
#include "hb-null.hh"

template <typename Type> struct rb_vector_t
{
    typedef Type item_t;
    static constexpr unsigned item_size = rb_static_size(Type);

    rb_vector_t()
    {
        init();
    }
    rb_vector_t(const rb_vector_t &o)
    {
        init();
        alloc(o.length);
        rb_copy(o, *this);
    }
    rb_vector_t(rb_vector_t &&o)
    {
        allocated = o.allocated;
        length = o.length;
        arrayZ = o.arrayZ;
        o.init();
    }
    ~rb_vector_t()
    {
        fini();
    }

private:
    int allocated; /* == -1 means allocation failed. */
public:
    unsigned int length;

public:
    Type *arrayZ;

    void init()
    {
        allocated = length = 0;
        arrayZ = nullptr;
    }

    void fini()
    {
        free(arrayZ);
        init();
    }
    void fini_deep()
    {
        unsigned int count = length;
        for (unsigned int i = 0; i < count; i++)
            arrayZ[i].fini();
        fini();
    }

    void reset()
    {
        resize(0);
    }

    rb_vector_t &operator=(const rb_vector_t &o)
    {
        reset();
        alloc(o.length);
        rb_copy(o, *this);
        return *this;
    }
    rb_vector_t &operator=(rb_vector_t &&o)
    {
        fini();
        allocated = o.allocated;
        length = o.length;
        arrayZ = o.arrayZ;
        o.init();
        return *this;
    }

    bool operator==(const rb_vector_t &o) const
    {
        return as_array() == o.as_array();
    }
    bool operator!=(const rb_vector_t &o) const
    {
        return !(*this == o);
    }
    uint32_t hash() const
    {
        return as_array().hash();
    }

    Type &operator[](int i_)
    {
        unsigned int i = (unsigned int)i_;
        if (unlikely(i >= length))
            return Crap(Type);
        return arrayZ[i];
    }
    const Type &operator[](int i_) const
    {
        unsigned int i = (unsigned int)i_;
        if (unlikely(i >= length))
            return Null(Type);
        return arrayZ[i];
    }

    Type &tail()
    {
        return (*this)[length - 1];
    }
    const Type &tail() const
    {
        return (*this)[length - 1];
    }

    explicit operator bool() const
    {
        return length;
    }
    unsigned get_size() const
    {
        return length * item_size;
    }

    /* Sink interface. */
    template <typename T> rb_vector_t &operator<<(T &&v)
    {
        push(rb_forward<T>(v));
        return *this;
    }

    rb_array_t<Type> as_array()
    {
        return rb_array(arrayZ, length);
    }
    rb_array_t<const Type> as_array() const
    {
        return rb_array(arrayZ, length);
    }

    /* Iterator. */
    typedef rb_array_t<const Type> iter_t;
    typedef rb_array_t<Type> writer_t;
    iter_t iter() const
    {
        return as_array();
    }
    writer_t writer()
    {
        return as_array();
    }
    operator iter_t() const
    {
        return iter();
    }
    operator writer_t()
    {
        return writer();
    }

    rb_array_t<const Type> sub_array(unsigned int start_offset, unsigned int count) const
    {
        return as_array().sub_array(start_offset, count);
    }
    rb_array_t<const Type> sub_array(unsigned int start_offset, unsigned int *count = nullptr /* IN/OUT */) const
    {
        return as_array().sub_array(start_offset, count);
    }
    rb_array_t<Type> sub_array(unsigned int start_offset, unsigned int count)
    {
        return as_array().sub_array(start_offset, count);
    }
    rb_array_t<Type> sub_array(unsigned int start_offset, unsigned int *count = nullptr /* IN/OUT */)
    {
        return as_array().sub_array(start_offset, count);
    }

    rb_sorted_array_t<Type> as_sorted_array()
    {
        return rb_sorted_array(arrayZ, length);
    }
    rb_sorted_array_t<const Type> as_sorted_array() const
    {
        return rb_sorted_array(arrayZ, length);
    }

    template <typename T> explicit operator T *()
    {
        return arrayZ;
    }
    template <typename T> explicit operator const T *() const
    {
        return arrayZ;
    }

    Type *operator+(unsigned int i)
    {
        return arrayZ + i;
    }
    const Type *operator+(unsigned int i) const
    {
        return arrayZ + i;
    }

    Type *push()
    {
        if (unlikely(!resize(length + 1)))
            return &Crap(Type);
        return &arrayZ[length - 1];
    }
    template <typename T> Type *push(T &&v)
    {
        Type *p = push();
        *p = rb_forward<T>(v);
        return p;
    }

    bool in_error() const
    {
        return allocated < 0;
    }

    /* Allocate for size but don't adjust length. */
    bool alloc(unsigned int size)
    {
        if (unlikely(allocated < 0))
            return false;

        if (likely(size <= (unsigned)allocated))
            return true;

        /* Reallocate */

        unsigned int new_allocated = allocated;
        while (size >= new_allocated)
            new_allocated += (new_allocated >> 1) + 8;

        Type *new_array = nullptr;
        bool overflows = (int)new_allocated < 0 || (new_allocated < (unsigned)allocated) ||
                         rb_unsigned_mul_overflows(new_allocated, sizeof(Type));
        if (likely(!overflows))
            new_array = (Type *)realloc(arrayZ, new_allocated * sizeof(Type));

        if (unlikely(!new_array)) {
            allocated = -1;
            return false;
        }

        arrayZ = new_array;
        allocated = new_allocated;

        return true;
    }

    bool resize(int size_)
    {
        unsigned int size = size_ < 0 ? 0u : (unsigned int)size_;
        if (!alloc(size))
            return false;

        if (size > length)
            memset(arrayZ + length, 0, (size - length) * sizeof(*arrayZ));

        length = size;
        return true;
    }

    Type pop()
    {
        if (!length)
            return Null(Type);
        return rb_move(arrayZ[--length]); /* Does this move actually work? */
    }

    void remove(unsigned int i)
    {
        if (unlikely(i >= length))
            return;
        memmove(static_cast<void *>(&arrayZ[i]), static_cast<void *>(&arrayZ[i + 1]), (length - i - 1) * sizeof(Type));
        length--;
    }

    void shrink(int size_)
    {
        unsigned int size = size_ < 0 ? 0u : (unsigned int)size_;
        if (size < length)
            length = size;
    }

    template <typename T> Type *find(T v)
    {
        for (unsigned int i = 0; i < length; i++)
            if (arrayZ[i] == v)
                return &arrayZ[i];
        return nullptr;
    }
    template <typename T> const Type *find(T v) const
    {
        for (unsigned int i = 0; i < length; i++)
            if (arrayZ[i] == v)
                return &arrayZ[i];
        return nullptr;
    }

    void qsort(int (*cmp)(const void *, const void *))
    {
        as_array().qsort(cmp);
    }
    void qsort(unsigned int start = 0, unsigned int end = (unsigned int)-1)
    {
        as_array().qsort(start, end);
    }

    template <typename T> Type *lsearch(const T &x, Type *not_found = nullptr)
    {
        return as_array().lsearch(x, not_found);
    }
    template <typename T> const Type *lsearch(const T &x, const Type *not_found = nullptr) const
    {
        return as_array().lsearch(x, not_found);
    }
};

template <typename Type> struct rb_sorted_vector_t : rb_vector_t<Type>
{
    rb_sorted_array_t<Type> as_array()
    {
        return rb_sorted_array(this->arrayZ, this->length);
    }
    rb_sorted_array_t<const Type> as_array() const
    {
        return rb_sorted_array(this->arrayZ, this->length);
    }

    /* Iterator. */
    typedef rb_sorted_array_t<const Type> const_iter_t;
    typedef rb_sorted_array_t<Type> iter_t;
    const_iter_t iter() const
    {
        return as_array();
    }
    const_iter_t citer() const
    {
        return as_array();
    }
    iter_t iter()
    {
        return as_array();
    }
    operator iter_t()
    {
        return iter();
    }
    operator const_iter_t() const
    {
        return iter();
    }

    template <typename T> Type *bsearch(const T &x, Type *not_found = nullptr)
    {
        return as_array().bsearch(x, not_found);
    }
    template <typename T> const Type *bsearch(const T &x, const Type *not_found = nullptr) const
    {
        return as_array().bsearch(x, not_found);
    }
    template <typename T>
    bool bfind(const T &x,
               unsigned int *i = nullptr,
               rb_bfind_not_found_t not_found = RB_BFIND_NOT_FOUND_DONT_STORE,
               unsigned int to_store = (unsigned int)-1) const
    {
        return as_array().bfind(x, i, not_found, to_store);
    }
};

#endif /* RB_VECTOR_HH */
