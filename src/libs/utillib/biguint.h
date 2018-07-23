#pragma once
/*-------------------------------------------------------------------------
 * Derived from https://mattmccutchen.net/bigint/index.html
 * From the website under the Legal section: I, Matt McCutchen, the sole author
 * of the original Big Integer Library, waive my copyright to it, placing it
 * in the public domain.  The library comes with absolutely no warranty.
 *------------------------------------------------------------------------*/
#include "basetypes.h"

namespace qblocks {

    //-------------------------------------------------------------------------------
    template <class BaseType>
    class SFBigNumStore {
    public:
        static const unsigned int N;
        unsigned int capacity;
        unsigned int len;
        BaseType *blk;

        SFBigNumStore(void);
        SFBigNumStore(const SFBigNumStore<BaseType>& x);
        SFBigNumStore<BaseType>& operator=(const SFBigNumStore<BaseType>& x);

        explicit SFBigNumStore(unsigned int size);
        SFBigNumStore(const BaseType *b, unsigned int len);
        ~SFBigNumStore();

        void allocate(unsigned int size);
        void allocateAndCopy(unsigned int size);

        bool operator==(const SFBigNumStore<BaseType>& x) const;
        bool operator!=(const SFBigNumStore<BaseType>& x) const { return !operator==(x); }
    };

    //-------------------------------------------------------------------------------
    template <class BaseType>
    const unsigned int SFBigNumStore<BaseType>::N = 8 * sizeof(BaseType);

    //-------------------------------------------------------------------------------
    template <class BaseType>
    inline SFBigNumStore<BaseType>::SFBigNumStore(void) : capacity(0), len(0) {
        blk = 0;
    }

    //-------------------------------------------------------------------------------
    template <class BaseType>
    inline SFBigNumStore<BaseType>::SFBigNumStore(unsigned int c) : capacity(c), len(0) {
        blk = (capacity > 0) ? (new BaseType[capacity]) : 0;
    }

    //-------------------------------------------------------------------------------
    template <class BaseType>
    SFBigNumStore<BaseType>& SFBigNumStore<BaseType>::operator=(const SFBigNumStore<BaseType> &x) {
        if (this == &x)
            return *this;

        len = x.len;
        allocate(len);
        for (unsigned int i = 0; i < len; i++)
            blk[i] = x.blk[i];
        return *this;
    }

    //-------------------------------------------------------------------------------
    template <class BaseType>
    SFBigNumStore<BaseType>::SFBigNumStore(const SFBigNumStore<BaseType> &x) : len(x.len) {
        capacity = len;
        blk = new BaseType[capacity];
        for (unsigned int i = 0; i < len; i++)
            blk[i] = x.blk[i];
    }

    //-------------------------------------------------------------------------------
    template <class BaseType>
    SFBigNumStore<BaseType>::SFBigNumStore(const BaseType *b, unsigned int len) : capacity(len), len(len) {
        blk = new BaseType[capacity];
        for (unsigned int i = 0; i < len; i++)
            blk[i] = b[i];
    }

    //-------------------------------------------------------------------------------
    template <class BaseType>
    inline SFBigNumStore<BaseType>::~SFBigNumStore() {
        if (blk)
            delete [] blk;
    }

    //-------------------------------------------------------------------------------
    template <class BaseType>
    void SFBigNumStore<BaseType>::allocate(unsigned int size) {
        if (size > capacity) {
            if (blk)
                delete [] blk;
            capacity = size;
            blk = new BaseType[capacity];
        }
    }

    //-------------------------------------------------------------------------------
    template <class BaseType>
    void SFBigNumStore<BaseType>::allocateAndCopy(unsigned int size) {
        if (size > capacity) {
            BaseType *oldBlk = blk;
            capacity = size;
            blk = new BaseType[capacity];
            for (unsigned int i = 0; i < len; i++)
                blk[i] = oldBlk[i];
            delete [] oldBlk;
        }
    }

    //-------------------------------------------------------------------------------
    template <class BaseType>
    bool SFBigNumStore<BaseType>::operator==(const SFBigNumStore<BaseType> &x) const {
        if (len != x.len)
            return false;

        for (unsigned int i = 0; i < len; i++)
            if (blk[i] != x.blk[i])
                return false;
        return true;
    }

    //-------------------------------------------------------------------------------
#define thisIsMe(a) (this == &a)

    //----------------------------------------------------------------------
    class SFUintBN : public SFBigNumStore<uint64_t> {
    public:
        SFUintBN(void);
        SFUintBN(const SFUintBN &x);
        SFUintBN& operator=(const SFUintBN &x);

        SFUintBN(int, unsigned int c);
        SFUintBN(const uint64_t *b, unsigned int blen);

        SFUintBN(int64_t x);  // NOLINT
        SFUintBN(int32_t x);  // NOLINT
        SFUintBN(int16_t x);  // NOLINT

        SFUintBN(uint64_t x);  // NOLINT
        SFUintBN(uint32_t x);  // NOLINT
        SFUintBN(uint16_t x);  // NOLINT

        ~SFUintBN();

        int64_t to_long(void) const;
        int32_t to_int(void) const;

        uint64_t to_ulong(void) const;
        uint32_t to_uint(void) const;

        int compareTo(const SFUintBN &x) const;
        bool operator==(const SFUintBN &x) const;
        bool operator!=(const SFUintBN &x) const;
        bool operator<(const SFUintBN &x) const;
        bool operator<=(const SFUintBN &x) const;
        bool operator>=(const SFUintBN &x) const;
        bool operator>(const SFUintBN &x) const;

        SFUintBN operator+(const SFUintBN &x) const;
        SFUintBN operator-(const SFUintBN &x) const;
        SFUintBN operator*(const SFUintBN &x) const;
        SFUintBN operator/(const SFUintBN &x) const;
        SFUintBN operator%(const SFUintBN &x) const;
        SFUintBN operator&(const SFUintBN &x) const;
        SFUintBN operator|(const SFUintBN &x) const;
        SFUintBN operator^(const SFUintBN &x) const;
        SFUintBN operator<<(int b) const;
        SFUintBN operator>>(int b) const;

        void operator+=(const SFUintBN &x);
        void operator-=(const SFUintBN &x);
        void operator*=(const SFUintBN &x);
        void operator/=(const SFUintBN &x);
        void operator%=(const SFUintBN &x);
        void operator&=(const SFUintBN &x);
        void operator|=(const SFUintBN &x);
        void operator^=(const SFUintBN &x);
        void operator<<=(int b);
        void operator>>=(int b);

        void operator++(void);  // prefix
        void operator--(void);

        void operator++(int);  // postfix
        void operator--(int);

        void add(const SFUintBN &a, const SFUintBN &b);
        void subtract(const SFUintBN &a, const SFUintBN &b);
        void multiply(const SFUintBN &a, const SFUintBN &b);
        void divide(const SFUintBN &b, SFUintBN &q);

        unsigned int bitLength(void) const;
        uint64_t getBlock(unsigned int i) const;
        void setBlock(unsigned int i, uint64_t newBlock);
        bool getBit(unsigned int bi) const;
        void setBit(unsigned int bi, bool newBit);
        void trimLeadingZeros(void);

// protected:
        void bitwiseAnd(const SFUintBN &a, const SFUintBN &b);
        void bitwiseOr(const SFUintBN &a, const SFUintBN &b);
        void bitwiseXor(const SFUintBN &a, const SFUintBN &b);

        void shiftLeft(const SFUintBN &a, int b);
        void shiftRight(const SFUintBN &a, int b);

        friend uint64_t getShiftedBlock(const SFUintBN &num, unsigned int x, unsigned int y);

        // template <class X>
        // friend X convertBigUnsignedToPrimitiveAccess(const SFUintBN &a);

        template <class X>
        X convertToSignedPrimitive(void) const;

        template <class X>
        X convertToPrimitive(void) const;
    };

    //----------------------------------------------------------------------
    inline bool SFUintBN::operator==(const SFUintBN &x) const {
        return SFBigNumStore<uint64_t>::operator==(x);
    }

    //----------------------------------------------------------------------
    inline bool SFUintBN::operator!=(const SFUintBN &x) const {
        return SFBigNumStore<uint64_t>::operator!=(x);
    }

    //----------------------------------------------------------------------
    inline bool SFUintBN::operator<(const SFUintBN &x) const {
        return compareTo(x) < 0;
    }

    //----------------------------------------------------------------------
    inline bool SFUintBN::operator<=(const SFUintBN &x) const {
        return compareTo(x) <= 0;
    }

    //----------------------------------------------------------------------
    inline bool SFUintBN::operator>=(const SFUintBN &x) const {
        return compareTo(x) >= 0;
    }

    //----------------------------------------------------------------------
    inline bool SFUintBN::operator>(const SFUintBN &x) const {
        return compareTo(x) > 0;
    }

    //----------------------------------------------------------------------
    inline void SFUintBN::operator+=(const SFUintBN &x) {
        add(*this, x);
    }

    //----------------------------------------------------------------------
    inline void SFUintBN::operator-=(const SFUintBN &x) {
        subtract(*this, x);
    }

    //----------------------------------------------------------------------
    inline void SFUintBN::operator*=(const SFUintBN &x) {
        multiply(*this, x);
    }

    //----------------------------------------------------------------------
    inline void SFUintBN::operator/=(const SFUintBN &x) {
        if (x.len == 0) throw "SFUintBN::operator /=: division by zero";
        SFUintBN q;
        divide(x, q);
        *this = q;
    }

    //----------------------------------------------------------------------
    inline void SFUintBN::operator%=(const SFUintBN &x) {
        if (x.len == 0)
            throw "SFUintBN::operator %=: division by zero";
        SFUintBN q;
        divide(x, q);
    }

    //----------------------------------------------------------------------
    inline void SFUintBN::operator&=(const SFUintBN &x) {
        bitwiseAnd(*this, x);
    }

    //----------------------------------------------------------------------
    inline void SFUintBN::operator|=(const SFUintBN &x) {
        bitwiseOr(*this, x);
    }

    //----------------------------------------------------------------------
    inline void SFUintBN::operator^=(const SFUintBN &x) {
        bitwiseXor(*this, x);
    }

    //----------------------------------------------------------------------
    inline void SFUintBN::operator<<=(int b) {
        shiftLeft(*this, b);
    }

    //----------------------------------------------------------------------
    inline void SFUintBN::operator>>=(int b) {
        shiftRight(*this, b);
    }

    //----------------------------------------------------------------------
    inline SFUintBN SFUintBN::operator+(const SFUintBN &x) const {
        SFUintBN ans;
        ans.add(*this, x);
        return ans;
    }

    //----------------------------------------------------------------------
    inline SFUintBN SFUintBN::operator-(const SFUintBN &x) const {
        SFUintBN ans;
        ans.subtract(*this, x);
        return ans;
    }

    //----------------------------------------------------------------------
    inline SFUintBN SFUintBN::operator*(const SFUintBN &x) const {
        SFUintBN ans;
        ans.multiply(*this, x);
        return ans;
    }

    //----------------------------------------------------------------------
    inline SFUintBN SFUintBN::operator/(const SFUintBN &x) const {
        if (x.len == 0)
            throw "SFUintBN::operator /: division by zero";
        SFUintBN q;
        SFUintBN r = *this;
        r.divide(x, q);
        return q;
    }

    //----------------------------------------------------------------------
    inline SFUintBN SFUintBN::operator%(const SFUintBN &x) const {
        if (x.len == 0)
            throw "SFUintBN::operator %: division by zero";
        SFUintBN q, r;
        r = *this;
        r.divide(x, q);
        return r;
    }

    //----------------------------------------------------------------------
    inline SFUintBN SFUintBN::operator&(const SFUintBN &x) const {
        SFUintBN ans;
        ans.bitwiseAnd(*this, x);
        return ans;
    }

    //----------------------------------------------------------------------
    inline SFUintBN SFUintBN::operator|(const SFUintBN &x) const {
        SFUintBN ans;
        ans.bitwiseOr(*this, x);
        return ans;
    }

    //----------------------------------------------------------------------
    inline SFUintBN SFUintBN::operator^(const SFUintBN &x) const {
        SFUintBN ans;
        ans.bitwiseXor(*this, x);
        return ans;
    }

    //----------------------------------------------------------------------
    inline SFUintBN SFUintBN::operator<<(int b) const {
        SFUintBN ans;
        ans.shiftLeft(*this, b);
        return ans;
    }

    //----------------------------------------------------------------------
    inline SFUintBN SFUintBN::operator>>(int b) const {
        SFUintBN ans;
        ans.shiftRight(*this, b);
        return ans;
    }

    //----------------------------------------------------------------------
    inline void SFUintBN::operator++(int) { operator++(); }  // NOLINT
    inline void SFUintBN::operator++(void) {
        unsigned int i;
        bool carry = true;
        for (i = 0 ; i < len&&carry ; i++) {
            blk[i]++;
            carry =(blk[i] == 0);
        }

        if (carry) {
            // Allocate and then increase length, as in divide
            allocateAndCopy(len + 1);
            len++;
            blk[i] = 1;
        }
    }

    //----------------------------------------------------------------------
    inline void SFUintBN::operator--(int) { operator--(); }  // NOLINT
    inline void SFUintBN::operator--(void) {
        if (len == 0)
            throw "SFUintBN::operator--(): Cannot decrement an unsigned zero";
        unsigned int i;
        bool borrow = true;
        for (i = 0; borrow; i++) {
            borrow =(blk[i] == 0);
            blk[i]--;
        }
        trimLeadingZeros();
    }

    //----------------------------------------------------------------------
    inline uint64_t SFUintBN::getBlock(unsigned int i) const {
        return i >= len ? 0 : blk[i];
    }

    //----------------------------------------------------------------------
    inline bool SFUintBN::getBit(unsigned int bi) const {
        return (getBlock(bi / N) & (((uint64_t)(1)) << (bi % N))) != 0;
    }

    //----------------------------------------------------------------------
    class BigUnsignedInABase : public SFBigNumStore<unsigned short> {  // NOLINT
    public:
        unsigned short base;  // NOLINT

        // Creates a BigUnsignedInABase with a capacity; for internal use.
        BigUnsignedInABase(int, unsigned int c) : SFBigNumStore<unsigned short>(0, c) {}  // NOLINT

        // Decreases len to eliminate any leading zero igits.
        void trimLeadingZeros(void) {
            while (len > 0 && blk[len - 1] == 0)
                len--;
        }

        // Constructs zero in base 2.
        BigUnsignedInABase() : SFBigNumStore<unsigned short>(), base(2) {}  // NOLINT

        // Copy constructor
        BigUnsignedInABase(const BigUnsignedInABase &x) : SFBigNumStore<unsigned short>(x), base(x.base) {}  // NOLINT

        // Assignment operator
        void operator =(const BigUnsignedInABase &x) {
            SFBigNumStore<unsigned short>::operator =(x);  // NOLINT
            base = x.base;
        }

        // Constructor that copies from a given array of igits.
        BigUnsignedInABase(const unsigned short *d, unsigned int l, unsigned short base);  // NOLINT

        // Destructor.  SFBigNumStore does the delete for us.
        ~BigUnsignedInABase() {}

        // LINKS TO BIGUNSIGNED
        BigUnsignedInABase(const SFUintBN &x, unsigned short base);  // NOLINT
        operator SFUintBN() const;

        operator string() const;
        BigUnsignedInABase(const string &s, unsigned short base);  // NOLINT

        /*
         * Equality test.  For the purposes of this test, two BigUnsignedInABase
         * values must have the same base to be equal.
         */
        bool operator ==(const BigUnsignedInABase &x) const {
            return base == x.base && SFBigNumStore<unsigned short>::operator==(x);  // NOLINT
        }
        bool operator !=(const BigUnsignedInABase &x) const { return !operator==(x); }

    };

}  // namespace qblocks
