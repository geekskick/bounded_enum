//
//  bounded_enum.hpp
//  bounded_enum
//

#include <type_traits>

template<class ULType>
class bounded_iterator{
public:
    bounded_iterator() = delete;
    explicit bounded_iterator(ULType val): m_parent_idx{ std::move(val) }{}
    ULType operator*() {
        return m_parent_idx;
    }
    
    bool operator==(const bounded_iterator& other) const {
        return m_parent_idx == other.m_parent_idx;
    }
    bool operator!=(const bounded_iterator& other) const {
        return m_parent_idx != other.m_parent_idx;
    }
    
    bounded_iterator& operator++(){
        m_parent_idx++;
        return *this;
    }
    
private:
    ULType m_parent_idx;
};

template<typename EnumT, EnumT TMin, EnumT TMax>
class bounded_enum{
public:
    static_assert(TMin <= TMax, "TMin must be <= TMax");
    using type = EnumT;
    using ULtype = typename std::underlying_type<EnumT>::type;
    using IterType = bounded_iterator<ULtype>;
    
    //====== Rule of 7 ======
    // 1. dtor
    ~bounded_enum() = default;
    
    // 2. ctor
    bounded_enum() = default;
    explicit bounded_enum(ULtype val): m_val { static_cast<EnumT>(val) }{}
    explicit bounded_enum(EnumT val): m_val { std::move(val) }{}
    
    // 3. Copy ctor
    
    
    // 4. Copy Assign
    
    // 5. Move Ctor
    
    // 6. Move assign
    

    //=======================
    ULtype underlying() const { return static_cast<ULtype>(m_val); }
    constexpr static ULtype count { static_cast<ULtype>(TMax) + 1 };
    constexpr static ULtype max_underlying { static_cast<ULtype>(TMax) };
    constexpr static ULtype min_underlying { static_cast<ULtype>(TMin) };
    constexpr static EnumT max_enum { TMax };
    constexpr static EnumT min_enum { TMin };
    
    constexpr EnumT& operator*() { return m_val; }
    constexpr const EnumT* operator*() const { return m_val; }
    
    friend std::ostream& operator<<(std::ostream& os, const bounded_enum& other){
        os << other.underlying();
        return os;
    }
    
    //=======================
    bounded_enum operator + (const bounded_enum& rhs) const {
        return bounded_enum(underlying() + rhs.underlying());
    }
    
    bounded_enum operator - (const bounded_enum& rhs) const {
        return bounded_enum(underlying() - rhs.underlying());
    }

    //====== Iterators ======
    constexpr static IterType begin() { return IterType(min_underlying); }
    constexpr static IterType end(){ return IterType(count); }
    
private:
    EnumT m_val { TMin };
};

