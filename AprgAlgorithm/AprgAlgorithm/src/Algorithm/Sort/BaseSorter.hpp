#pragma once

namespace alba::algorithm {

template <typename Values>
class BaseSorter {
public:
    BaseSorter() = default;
    // virtual destructor because of virtual functions (vtable exists)
    virtual ~BaseSorter() = default;
    BaseSorter(BaseSorter const &) = default;
    BaseSorter(BaseSorter &&) noexcept = default;
    BaseSorter &operator=(BaseSorter const &) = default;
    BaseSorter &operator=(BaseSorter &&) noexcept = default;
    virtual void sort(Values &valuesToSort) const = 0;
};

}  // namespace alba::algorithm

// Applications
// Obvious:
// -> Sort a list of names
// -> Organize an MP3 library
// -> Display Google Page Rank Results
// -> List RSS feed in reverse chronological order
// Problems that becomes easy once items are sorted:
// -> Find the median
// -> Binary Search
// -> Check for statistical outliers
// -> Find duplicates in a mailing list
// Non-obvious applications:
// -> Data compression
// -> Computer graphics
// -> Computational biology
// -> Load balancing on a parallel computer
// There are a hundreds of algorithms on sorting.
// Attributes in sorting:
// -> Stability?
// -> Parallel?
// -> Deterministic?
// -> Keys all distinct?
// -> Multiple key types?
// -> linked list or arrays?
// -> Large or small items?
// -> Initially random ordered?
// -> Need a performance guarantee?
// No sorting algorithm out there that covers all attributes. Usually system sort is good enough.
