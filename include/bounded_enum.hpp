//
//  bounded_enum.hpp
//  bounded_enum
//

#include <exception>
#include <sstream>
#include <type_traits>

template<class ULType>
class bounded_iterator {
  public:
    bounded_iterator() = delete;
    explicit bounded_iterator(ULType val)
      : m_parent_idx{ std::move(val) } {}

    ULType operator*() { return m_parent_idx; }
    bool operator==(const bounded_iterator& other) const { return m_parent_idx == other.m_parent_idx; }
    bool operator!=(const bounded_iterator& other) const { return m_parent_idx != other.m_parent_idx; }

    bounded_iterator& operator++() {
        m_parent_idx++;
        return *this;
    }

  private:
    ULType m_parent_idx;
};

template<typename EnumT, EnumT TMin, EnumT TMax>
class bounded_enum {
  public:
    static_assert(TMin <= TMax, "TMin must be <= TMax");
    using type = EnumT;
    using ULType = typename std::underlying_type<EnumT>::type;
    using IterType = bounded_iterator<ULType>;

    //====== Rule of 7 ======
    // 1. dtor
    ~bounded_enum() = default;

    // 2. ctor
    bounded_enum() = default;

    explicit bounded_enum(ULType val) {
        if (val > to_underlying(TMax) || val < to_underlying(TMin)) {
            std::stringstream ss;
            ss << "Restriction is that " << to_underlying(TMin) << " < " << val << " < " << to_underlying(TMax) << ".";
            throw std::runtime_error(ss.str());
        }
        m_val = from_underlying(val);
    }

    explicit bounded_enum(EnumT val)
      : m_val{ std::move(val) } {}

    // 3. Copy ctor
    bounded_enum(const bounded_enum& other) = default;

    // 4. Copy Assign
    bounded_enum& operator=(const bounded_enum& other) = default;

    // 5. Move Ctor
    bounded_enum(bounded_enum&& other) {
        if (this != &other) {
            m_val = other.m_val;
            other.m_val = other.min_enum;
        }
    }

    // 6. Move assign
    bounded_enum& operator=(bounded_enum&& other) {
        if (this != &other) {
            m_val = other.m_val;
            other.m_val = other.min_enum;
        }
        return *this;
    }

    // 7. Swap not done yet

    //=======================
    ULType underlying() const { return static_cast<ULType>(m_val); }
    constexpr static ULType count{ static_cast<ULType>(TMax) + 1 };
    constexpr static ULType max_underlying{ static_cast<ULType>(TMax) };
    constexpr static ULType min_underlying{ static_cast<ULType>(TMin) };
    constexpr static EnumT max_enum{ TMax };
    constexpr static EnumT min_enum{ TMin };

    constexpr EnumT& operator*() { return m_val; }
    constexpr const EnumT* operator*() const { return m_val; }
    constexpr const EnumT& get() const { return m_val; }
    constexpr EnumT& get() { return m_val; }
    constexpr static ULType to_underlying(const EnumT& e) { return static_cast<ULType>(e); }

    constexpr static EnumT from_underlying(const ULType& u) { return static_cast<EnumT>(u); }

    friend std::ostream& operator<<(std::ostream& os, const bounded_enum& other) {
        os << other.underlying();
        return os;
    }

    //=======================
    bool operator==(const bounded_enum& rhs) const { return m_val == rhs.m_val; }
    bool operator==(const EnumT& rhs) const { return m_val == rhs; }
    bool operator!=(const bounded_enum& rhs) const { return m_val != rhs.m_val; }
    bool operator!=(const EnumT& rhs) const { return m_val != rhs; }

    bounded_enum& operator++() {
        if (m_val == TMax) {
            std::stringstream ss;
            ss << "Trying to increment " << to_underlying(m_val) << " past it's max.";
            throw std::runtime_error(ss.str());
        }
        m_val = from_underlying(to_underlying(m_val) + 1);
        return *this;
    }

    bounded_enum operator++(int) {
        bounded_enum t = *this;
        ++*this;
        return t;
    }

    bounded_enum& operator--() {
        if (m_val == TMin) {
            std::stringstream ss;
            ss << "Trying to decrement " << to_underlying(m_val) << " past it's min.";
            throw std::runtime_error(ss.str());
        }
        m_val = from_underlying(to_underlying(m_val) - 1);
        return *this;
    }

    bounded_enum operator--(int) {
        bounded_enum t = *this;
        --*this;
        return t;
    }

    //====== Iterators ======
    constexpr static IterType begin() { return IterType(min_underlying); }
    constexpr static IterType end() { return IterType(count); }

  private:
    EnumT m_val{ TMin };
};