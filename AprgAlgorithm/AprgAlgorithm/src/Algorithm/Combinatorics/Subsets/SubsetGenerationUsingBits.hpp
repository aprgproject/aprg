#pragma once

#include <Common/Bit/AlbaBitValueUtilities.hpp>

#include <bitset>
#include <vector>

namespace alba
{

namespace algorithm
{

template <typename Objects, typename BitDataType>
class SubsetGenerationUsingBits
{
public:
    using Object = typename Objects::value_type;
    using Subset = Objects;
    using Subsets = std::vector<Objects>;

    // rule of five or six
    SubsetGenerationUsingBits() = delete;
    ~SubsetGenerationUsingBits() = delete;
    SubsetGenerationUsingBits(SubsetGenerationUsingBits const&) = delete;
    SubsetGenerationUsingBits & operator= (SubsetGenerationUsingBits const&) = delete;
    SubsetGenerationUsingBits(SubsetGenerationUsingBits &&) = delete;
    SubsetGenerationUsingBits & operator= (SubsetGenerationUsingBits &&) = delete;

    static Subsets generateSubsetsUsingBits(Objects const& objects)
    {
        Subsets result;
        BitDataType finalValue = 1 << objects.size();
        for(BitDataType iteration=0; iteration<finalValue; iteration++)
        {
            Subset currentSubset;
            std::bitset<AlbaBitValueUtilities<BitDataType>::getNumberOfBits()> iterationBits(iteration);
            for(unsigned int index=0; index<objects.size(); index++)
            {
                if(iterationBits[index])
                {
                    currentSubset.emplace_back(objects.at(index));
                }
            }
            result.emplace_back(currentSubset);
        }
        return result;
    }
};

}

}
