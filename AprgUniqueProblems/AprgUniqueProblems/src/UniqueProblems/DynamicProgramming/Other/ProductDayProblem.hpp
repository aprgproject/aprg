#pragma once

#include <Common/Math/Matrix/AlbaMatrix.hpp>

#include <limits>
#include <vector>

namespace alba {

class ProductDayProblem {
public:
    using Price = int;
    using Product = int;
    using Day = int;
    using ProductBits = int;
    using PriceMatrix = matrix::AlbaMatrix<Price>;
    using ProductAndDayPair = std::pair<Product, Day>;
    using ProductAndDayPairs = std::vector<ProductAndDayPair>;
    explicit ProductDayProblem(PriceMatrix const& pricesInDayByProduct);
    explicit ProductDayProblem(PriceMatrix&& pricesInDayByProduct);
    static constexpr Price INVALID_PRICE = std::numeric_limits<Price>::max();
    [[nodiscard]] Price getMinimumPriceUsingMemoizationDP() const;
    [[nodiscard]] Price getMinimumPriceUsingIterativeDP() const;
    static constexpr Price UNUSED_PRICE = INVALID_PRICE - 1;

private:
    [[nodiscard]] Day getNumberOfDays() const;
    [[nodiscard]] Product getNumberOfProducts() const;
    [[nodiscard]] ProductBits getNumberOfProductsSubsets() const;
    [[nodiscard]] ProductBits getProductBitsWithAllProducts() const;
    Price getMinimumPriceUsingMemoizationDP(
        PriceMatrix& minimumPrices, Day const day, ProductBits const productBits) const;
    [[nodiscard]] static bool isProductIncluded(ProductBits const productBits, Product const product);
    static ProductBits getProductBits(Product const product);
    static ProductBits addProduct(ProductBits const productBits, Product const product);
    static ProductBits removeProduct(ProductBits const productBits, Product const product);
    PriceMatrix m_pricesInDayByProduct;
};

}  // namespace alba

// We are given the prices of k products over n days, and we want to buy each product exactly once.
// However, we are allowed to buy at most one product in a day. What is the minimum total price?
// Recursive formulation:
// -> Let price[x][d] denote the price of product x on day d.
// -> Then, let total(S,d) denote the minimum total price for buying a subset S of products by day d.
// ---> total(nullset,d) = 0, because it does not cost anything to buy an empty set,
// ---> and total({x},0) = price[x][0], because there is one way to buy one product on the first day.
// -> Using this function, the solution to the problem is total({0...k-1},n-1).
// -> total(S,d) = min(total(S,d-1), min of (total(S\product,d-1)+price[product][d]) all products)
