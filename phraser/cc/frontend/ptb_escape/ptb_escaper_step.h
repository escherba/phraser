#ifndef CC_FRONTEND_PTB_ESCAPE_PTB_ESCAPER_H_
#define CC_FRONTEND_PTB_ESCAPE_PTB_ESCAPER_H_

#include <string>
#include <unordered_map>
#include <vector>

#include "cc/frontend/base/token_norm_rewrite_in_place_step.h"

using std::string;
using std::unordered_map;
using std::vector;

class PtbEscaperStep : TokenNormRewriteInPlaceStep {
  public:
    bool Init(string* error);

    bool RewriteInPlace(vector<string>* inout, string* error) const;

  private:
    unordered_map<string, string> s2s_;
};

#endif  // CC_FRONTEND_PTB_ESCAPE_PTB_ESCAPER_H_
