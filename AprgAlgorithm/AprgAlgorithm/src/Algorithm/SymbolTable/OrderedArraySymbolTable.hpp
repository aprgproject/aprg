#pragma once

#include <Algorithm/SetAndSymbolTable/Common/Array/BaseOrderedArray.hpp>
#include <Algorithm/SymbolTable/BaseSymbolTable.hpp>

namespace alba
{
namespace algorithm
{

template <typename Key, typename Value>
class OrderedArraySymbolTable : public BaseOrderedArray<Key, BaseSymbolTable<Key, Value>>
{
public:
    using BaseClass = BaseOrderedArray<Key, BaseSymbolTable<Key, Value>>;
    using Keys = typename BaseClass::Keys;
    using Values = std::vector<Value>;

    OrderedArraySymbolTable()
        : BaseClass()
        , b_size(BaseClass::m_size)
        , b_keys(BaseClass::m_keys)
    {}

    Value get(Key const& key) const override
    {
        Value result{};
        if(!this->isEmpty())
        {
            unsigned int rank(this->getRank(key));
            if(rank < b_size && b_keys.at(rank) == key)
            {
                result = m_values.at(rank);
            }        }
        return result;
    }

    void put(Key const& key, Value const& value) override
    {
        bool isKeyFound(false);
        unsigned int rank(this->getRank(key));
        if(rank < b_size && b_keys.at(rank) == key)
        {
            m_values[rank] = value;
            isKeyFound = true;        }
        if(!isKeyFound)
        {
            b_keys.emplace_back();
            m_values.emplace_back();
            for(unsigned int i=b_size; i>rank; i--)
            {
                b_keys[i] = b_keys.at(i-1);
                m_values[i] = m_values.at(i-1);
            }
            b_keys[rank] = key;
            m_values[rank] = value;
            b_size++;
        }
    }

    void deleteBasedOnKey(Key const& key) override
    {
        unsigned int rank(this->getRank(key));
        if(rank < b_size && b_keys.at(rank) == key)
        {
            if(b_size >= 2)
            {
                for(unsigned int i=rank; i<b_size-1; i++)
                {
                    b_keys[i] = b_keys.at(i+1);
                    m_values[i] = m_values.at(i+1);
                }
            }
            b_keys.pop_back();
            m_values.pop_back();
            b_size--;
        }
    }

    void deleteMinimum() override
    {
        for(unsigned int i=0; i<b_size-1; i++)
        {
            b_keys[i] = b_keys.at(i+1);
            m_values[i] = m_values.at(i+1);
        }
        b_keys.pop_back();
        m_values.pop_back();
        b_size--;
    }

    void deleteMaximum() override
    {
        b_keys.pop_back();
        m_values.pop_back();
        b_size--;
    }


private:
    unsigned int & b_size;
    Keys & b_keys;
    Values m_values;
};

}
}
