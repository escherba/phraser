#ifndef CC_SEQUENCES_VECTOR_MEMBERSHIP_SEQUENCE_DETECTOR_H_
#define CC_SEQUENCES_VECTOR_MEMBERSHIP_SEQUENCE_DETECTOR_H_

#include <vector>

#include "cc/sequence/sequence_detector.h"

using std::vector; 

template <typename Atom>
class VectorMembershipAtomTokenComparer {
  public:
    static size_t NumAtoms(const vector<Atom>& token);
    static const Atom* FirstAtom(const vector<Atom>& token);
    static const Atom* LastAtom(const vector<Atom>& token);
    static bool IsMatch(const vector<Atom>& token_have, const Atom& atom_need);
};

template <typename Atom>
using VectorMembershipSequenceDetector = SequenceDetector<
        Atom, vector<Atom>, VectorMembershipAtomTokenComparer<Atom>>;

#include "vector_membership_sequence_detector_impl.h"

#endif  // CC_SEQUENCES_VECTOR_MEMBERSHIP_SEQUENCE_DETECTOR_H_
