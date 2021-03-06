#ifndef CC_ANALYSIS_ANALYSIS_RESULT_H_
#define CC_ANALYSIS_ANALYSIS_RESULT_H_

#include <string>
#include <unordered_map>
#include <vector>

#include "cc/base/json.h"
#include "cc/base/unicode/unicode.h"
#include "cc/phrase_detection/phrase_detection_result.h"
#include "cc/tokenization/span.h"

using std::string;
using std::unordered_map;
using std::vector;

#define TEXT_MAX_LEN (1ul << 16)

struct AnalysisResult {
    void Clear();

    // Output.
    json::Object* ToJSON() const;
    void Dump() const;
    void ToHTML(string* s) const;
    void AppendAsLine(const vector<string>& comment_tags, string* s) const;

    // Input:
    // * The original text.
    ustring original_text;

    // Preprocessing results:
    // * Text after preprocessing.
    // * Index in 'clean_text' -> index in 'original_text'.
    // * Code point -> number of times it was dropped by destuttering.
    ustring clean_text;
    vector<uint16_t> clean2original;
    unordered_map<ucode, size_t> chr2drop;

    // Tokenization results:
    // * The fully processed tokens.
    // * Token index -> span in 'clean_text' that the token is from.
    vector<string> tokens;
    vector<Span> token2clean;

    // Phrase detection results:
    vector<PhraseDetectionResult> phrase_results;
};

#endif  // CC_ANALYSIS_ANALYSIS_RESULT_H_
