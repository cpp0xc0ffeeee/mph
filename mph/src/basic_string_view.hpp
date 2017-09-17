/*
 * basicstringview.hpp
 *
 *  Created on: Sep 8, 2017
 *      Author: butters
 */

#ifndef basic_string_view_HPP_HD7CBBBF1_D066_43D7_83BC_8514775A7FA8
#define basic_string_view_HPP_HD7CBBBF1_D066_43D7_83BC_8514775A7FA8

#include <cstddef>
#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>
#include <algorithm>

namespace mph
{

template<class CharT, class Traits=std::char_traits<CharT> >
class basic_string_view
{
public:
    using traits_type = Traits;
    using value_type = CharT;
    using pointer = CharT*;
    using const_pointer = const CharT*;
    using reference = CharT&;
    using const_reference = const CharT&;
    using const_iterator = const CharT*;
    using iterator = const_iterator;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    using reverse_iterator = const_reverse_iterator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

private:
    const_pointer mData;
    size_type mSize;

public:

    static constexpr size_type npos = size_type(-1);




    //constructor and assignment
    constexpr basic_string_view() noexcept
            :mData( nullptr ),
             mSize( 0 )
    {}

    constexpr basic_string_view(const basic_string_view& other) noexcept = default;

    basic_string_view& operator=( const basic_string_view& view ) noexcept
    {
        mData=view.mData;
        mSize=view.mSize;
        return *this;
    }

    constexpr basic_string_view(const CharT* s)
            :mData( s ),
             mSize( Traits::length(s) )
    {}

    constexpr basic_string_view(const CharT* s, size_type count)
            :mData( s ),
             mSize( count )
    {}




    //iterator support
    constexpr const_iterator begin() const noexcept
    {
        return mData;
    }

    constexpr const_iterator end() const noexcept
    {
        return mData+mSize;
    }

    constexpr const_iterator cbegin() const noexcept
    {
        return mData;
    }

    constexpr const_iterator cend() const noexcept
    {
        return mData+mSize;
    }

    constexpr const_reverse_iterator rbegin() const noexcept
    {
        return const_reverse_iterator( mData+mSize );
    }

    constexpr const_reverse_iterator rend() const noexcept
    {
        return const_reverse_iterator( mData );
    }

    constexpr const_reverse_iterator crbegin() const noexcept
    {
        return const_reverse_iterator( mData+mSize );
    }

    constexpr const_reverse_iterator crend() const noexcept
    {
        return const_reverse_iterator( mData );
    }




    //capacity
    constexpr size_type size() const noexcept
    {
        return mSize;
    }

    constexpr size_type length() const noexcept
    {
        return mSize;
    }

    constexpr size_type max_size() const noexcept
    {
        return size_type(-1) / sizeof(CharT);
    }

    constexpr bool empty() const noexcept
    {
        return mSize==0;
    }




    //element access
    constexpr const_reference operator[](size_type pos) const
    {
        return mData[pos];
    }

    constexpr const_reference at(size_type pos) const
    {
        return (pos >= mSize) ? throw std::out_of_range("") : mData[pos] ;
    }

    constexpr const_reference front() const
    {
        return mData[0];
    }

    constexpr const_reference back() const
    {
        return mData[mSize-1];
    }

    constexpr const_pointer data() const noexcept
    {
        return mData;
    }




    //modifier

    //change:  can't use constexpr
    void remove_prefix(size_type n)
    {
        mData+=n;
        mSize-=n;
    }

    //change: can't use constexpr
    void remove_suffix(size_type n)
    {
        mSize-=n;
    }

    void swap(basic_string_view& v)
    {
        std::swap(mData, v.mData);
        std::swap(mSize, v.mSize);
    }




    //string operations
    size_type copy( CharT* dest, size_type count, size_type pos = 0) const
    {
        if(pos>mSize)
            throw std::out_of_range("");
        size_type rcount = std::min(count, mSize-pos);
        std::copy_n(begin() + pos, rcount, dest);
        return rcount;
    }

    constexpr basic_string_view substr(size_type pos = 0, size_type count = npos ) const
    {
        return (pos>mSize) ?
                throw std::out_of_range("") :
                basic_string_view( mData+pos, std::min(count, mSize-pos) );
    }

    //change: removed constexpr
    int compare(basic_string_view v) const
    {
        int compareResult=0;
        compareResult = traits_type::compare( mData, v.mData, std::min(mSize, v.mSize) );
        if( compareResult == 0 )
        {
            if(mSize < v.mSize)
                compareResult = std::numeric_limits<int>::min();
            else if(mSize > v.mSize)
                compareResult = std::numeric_limits<int>::max();
        }
        return compareResult;
    }

    constexpr int compare(size_type pos1, size_type count1, basic_string_view v) const
    {
       return substr(pos1, count1).compare(v);
    }

    constexpr int compare(size_type pos1, size_type count1, basic_string_view v,
                          size_type pos2, size_type count2) const
    {
        return substr(pos1, count1).compare( v.substr(pos2, count2) );
    }

    constexpr int compare(const CharT* s) const
    {
        return compare( basic_string_view(s) );
    }

    constexpr int compare(size_type pos1, size_type count1, const CharT* s) const
    {
        return substr(pos1, count1).compare( basic_string_view(s) );
    }

    constexpr int compare(size_type pos1, size_type count1,
                          const CharT* s, size_type count2) const
    {
        return substr(pos1, count1).compare(basic_string_view(s, count2));
    }




    //searching

    //change: can't use constexpr
    size_type find(basic_string_view str, size_type pos = 0) const noexcept
    {
        if(pos + str.mSize > mSize)
            return npos;

        if(str.mSize==0)
            return pos;

        size_type lastCheck = mSize-str.mSize;
        for( ; pos<=lastCheck; ++pos)
        {
            size_type i=0;
            for( ; i<str.mSize; ++i)
            {
                if( !traits_type::eq(mData[pos+i], str.mData[i] ) )
                    break;
            }
            if(i == str.mSize)
                return pos;
        }
        return npos;
    }

    constexpr size_type find(CharT c, size_type pos = 0) const noexcept
    {
        return find(basic_string_view{&c, 1}, pos);
    }

    constexpr size_type find(const CharT* s, size_type pos, size_type n) const
    {
        return find(basic_string_view{s, n}, pos);
    }

    constexpr size_type find(const CharT* s, size_type pos = 0) const
    {
        return find(basic_string_view{s}, pos);
    }

    //change: can't use constexpr
    size_type rfind(basic_string_view str, size_type pos = npos) const noexcept
    {
        if(pos + str.mSize > mSize)
            return npos;

        if(str.mSize==0)
        {
            return pos==npos ? mSize : pos;
        }

        size_type lastCheck = mSize-str.mSize;
        for( ; lastCheck<pos; --lastCheck)
        {
            size_type i=0;
            for( ; i<str.mSize; ++i)
            {
                if( !traits_type::eq( mData[lastCheck+i], str.mData[i] ) )
                    break;
            }
            if(i == str.mSize)
                return lastCheck;
        }
        return npos;
    }

    constexpr size_type rfind(CharT c, size_type pos = npos) const noexcept
    {
        return rfind(basic_string_view{&c, 1}, pos);
    }

    constexpr size_type rfind(const CharT* s, size_type pos, size_type n) const
    {
        return rfind(basic_string_view{s, n}, pos);
    }

    constexpr size_type rfind(const CharT* s, size_type pos = npos) const
    {
        return rfind(basic_string_view{s}, pos);
    }

    //change: can't use constexpr
    size_type find_first_of(basic_string_view str, size_type pos = 0) const noexcept
    {
        if(pos >= mSize || str.mSize==0)
            return npos;

        for( ; pos<mSize; ++pos)
        {
            for(const_reference ch : str)
            {
                if( traits_type::eq( mData[pos], ch) )
                    return pos;
            }
        }
        return npos;
    }

    constexpr size_type find_first_of(CharT c, size_type pos = 0) const noexcept
    {
        return find_first_of(basic_string_view{&c, 1}, pos);
    }

    constexpr size_type find_first_of(const CharT* s, size_type pos, size_type n) const
    {
        return find_first_of(basic_string_view{s, n}, pos);
    }

    constexpr size_type find_first_of(const CharT* s, size_type pos = 0) const
    {
        return find_first_of(basic_string_view{s}, pos);
    }

    //change: can't use constexpr
    size_type find_last_of(basic_string_view str, size_type pos = npos) const noexcept
    {
        if(pos >= mSize || str.mSize==0)
            return npos;

        size_type i = mSize-1;
        for( ; i>=pos; --i)
        {
            for(const_reference ch : str)
            {
                if( traits_type::eq( mData[i], ch) )
                    return i;
            }
        }
        return npos;
    }

    constexpr size_type find_last_of(CharT c, size_type pos = npos) const noexcept
    {
        return find_last_of(basic_string_view{&c, 1}, pos);
    }

    constexpr size_type find_last_of(const CharT* s, size_type pos, size_type n) const
    {
        return find_last_of(basic_string_view{s, n}, pos);
    }

    constexpr size_type find_last_of(const CharT* s, size_type pos = npos) const
    {
        return find_last_of(basic_string_view{s}, pos);
    }

    //change: can't use constexpr
    size_type find_first_not_of(basic_string_view str, size_type pos = 0) const noexcept
    {
        if(pos >= mSize)
            return npos;
        if(str.mSize==0)
            return pos;

        for( ; pos<mSize; ++pos)
        {
            size_type i=0;
            for(; i<str.mSize; ++i)
            {
                if( traits_type::eq( mData[pos], str.mData[i] ) )
                    break;
            }
            if(i==str.mSize)
                return pos;
        }
        return npos;
    }

    constexpr size_type find_first_not_of(CharT c, size_type pos = 0) const noexcept
    {
        return find_first_not_of(basic_string_view{&c, 1}, pos);
    }

    constexpr size_type find_first_not_of(const CharT* s, size_type pos, size_type n) const
    {
        return find_first_not_of(basic_string_view{s, n}, pos);
    }

    constexpr size_type find_first_not_of(const CharT* s, size_type pos = 0) const
    {
        return find_first_not_of(basic_string_view{s}, pos);
    }

    //change: can't use constexpr
    size_type find_last_not_of(basic_string_view str, size_type pos = npos) const noexcept
    {
        if(pos >= mSize)
            return npos;

        if(str.mSize==0)
            return mSize-1;

        size_type xpos=str.mSize;
        for( ; xpos>=pos; --xpos)
        {
            size_type i=0;
            for(; i<str.mSize; ++i)
            {
                if( traits_type::eq( mData[xpos], str.mData[i] ) )
                    break;
            }
            if(i==str.mSize)
                return xpos;
        }
        return npos;
    }

    constexpr size_type find_last_not_of(CharT c, size_type pos = npos) const noexcept
    {
        return find_last_not_of(basic_string_view{&c, 1}, pos);
    }

    constexpr size_type find_last_not_of(const CharT* s, size_type pos, size_type n) const
    {
        return find_last_not_of(basic_string_view{s, n}, pos);
    }

    constexpr size_type find_last_not_of(const CharT* s, size_type pos = npos) const
    {
        return find_last_not_of(basic_string_view{s}, pos);
    }

};

template< class CharT, class Traits >
constexpr bool operator==( basic_string_view <CharT,Traits> lhs,
                           basic_string_view <CharT,Traits> rhs ) noexcept
{
    return lhs.compare(rhs)==0;
}

template< class CharT, class Traits >
constexpr bool operator!=( basic_string_view <CharT,Traits> lhs,
                           basic_string_view <CharT,Traits> rhs ) noexcept
{
    return lhs.compare(rhs)!=0;
}

template< class CharT, class Traits >
constexpr bool operator< ( basic_string_view <CharT,Traits> lhs,
                           basic_string_view <CharT,Traits> rhs ) noexcept
{
    return lhs.compare(rhs)<0;
}

template< class CharT, class Traits >
constexpr bool operator> ( basic_string_view <CharT,Traits> lhs,
                           basic_string_view <CharT,Traits> rhs ) noexcept
{
    return lhs.compare(rhs)>0;
}

template< class CharT, class Traits >
constexpr bool operator<=( basic_string_view <CharT,Traits> lhs,
                           basic_string_view <CharT,Traits> rhs ) noexcept
{
    return lhs.compare(rhs)<=0;
}

template< class CharT, class Traits >
constexpr bool operator>=( basic_string_view <CharT,Traits> lhs,
                           basic_string_view <CharT,Traits> rhs ) noexcept
{
    return lhs.compare(rhs)>=0;
}

template<class charT, class traits>
std::basic_ostream<charT, traits>&
operator<<(std::basic_ostream<charT, traits>& os, basic_string_view<charT, traits> str)
{
    typedef std::basic_ostream< charT, traits> osType;
    typedef typename osType::ios_base  iosBase;

    typename osType::sentry sentryFlag(os);
    if (sentryFlag)
    {
        const std::streamsize width = os.width();
        if ( width > 0 && static_cast<size_t>(width) > str.size() )
        {
            const bool isLeftStart = ((os.flags() & iosBase::adjustfield) == iosBase::left);
            if (!isLeftStart)
            {
                const charT c=os.fill();
                for( std::size_t i=static_cast<size_t>(width)-str.size(); i>0; --i )
                {
                    const auto put = os.rdbuf()->sputc(c);
                    if( traits::eq_int_type( put, traits::eof() ) )
                    {
                        os.setstate(iosBase::badbit);
                    }
                }
            }
            if (os.good())
            {
                const std::streamsize put = os.rdbuf()->sputn(str.data(), str.size());
                if( static_cast<std::size_t>(put) !=str.size())
                    os.setstate(iosBase::badbit);
            }
            if (isLeftStart && os.good())
            {
                const charT c=os.fill();
                for( std::size_t i=static_cast<size_t>(width)-str.size(); i>0; --i )
                {
                    const auto put = os.rdbuf()->sputc(c);
                    if( traits::eq_int_type( put, traits::eof() ) )
                    {
                        os.setstate(iosBase::badbit);
                    }
                }
            }
        }
        else
        {
            const std::streamsize put = os.rdbuf()->sputn(str.data(), str.size());
            if( static_cast<std::size_t>(put)!=str.size() )
                os.setstate(iosBase::badbit);
        }
        os.width(0);
    }
    return os;
}

using string_view = basic_string_view<char>;
using wstring_view = basic_string_view<wchar_t>;
using u16string_view = basic_string_view<char16_t>;
using u32string_view = basic_string_view<char32_t>;

inline namespace literals
{
inline namespace string_view_literals
{

constexpr string_view operator "" _sv(const char* str, size_t len) noexcept
{
    return string_view(str, len);
}

constexpr u16string_view operator "" _sv(const char16_t* str, size_t len) noexcept
{
    return u16string_view(str, len);
}

constexpr u32string_view operator "" _sv(const char32_t* str, size_t len) noexcept
{
    return u32string_view(str, len);
}

constexpr wstring_view   operator "" _sv(const wchar_t* str, size_t len) noexcept
{
    return wstring_view(str, len);
}

}//inline namespace string_view_literals
}//inline namespace literals

} /* namespace mph */

#endif /* basicstringview_HPP_HD7CBBBF1_D066_43D7_83BC_8514775A7FA8 */
