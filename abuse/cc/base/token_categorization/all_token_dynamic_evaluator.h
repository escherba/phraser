#ifndef CC_BASE_TOKEN_CATEGORIZATION_ALL_TOKEN_DYNAMIC_EVALUATOR_H_
#define CC_BASE_TOKEN_CATEGORIZATION_ALL_TOKEN_DYNAMIC_EVALUATOR_H_

#include <string>
#include <vector>

#include "cc/base/token_categorization/expression.h"

using std::string;
using std::vector;

template <typename TokenDescription>
class AllTokenDynamicEvaluator {
  public:
    virtual ~AllTokenDynamicEvaluator() = 0;

    // Is the expression possible?
    //
    // Reasons for false:
    // * Its type does not match my type
    // * It has a filter dimension I have never heard of
    virtual bool IsExpressionPossible(const Expression& expr) const = 0;

    // Tokens -> list of corresponding opaque objects (eg. tags, maps of
    // features, etc.).
    virtual void DescribeTokens(
        const vector<string>& tokens,
        vector<TokenDescription>* descs) const = 0;

    // Does the expression accept the token given the additional info?
    virtual bool IsMatch(
        const Expression& expr, const string& token,
        const TokenDescription& desc) = 0;
};

#endif  // CC_BASE_TOKEN_CATEGORIZATION_ALL_TOKEN_DYNAMIC_EVALUATOR_H_
