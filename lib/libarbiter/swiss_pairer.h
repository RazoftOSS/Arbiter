#ifndef LIB_LIBARBITER_SWISS_PAIRER_H_
#define LIB_LIBARBITER_SWISS_PAIRER_H_

#include "player_list.h"
#include "swiss_pair_table.h"

namespace libarbiter {
namespace pairing {

class SwissPairerInterface {
 public:
  /**
   * Generates a SwissPairTable based on a PlayerList.
   */
  virtual SwissPairTable Pair(const PlayerList& players) const = 0;
};

}  // namespace pairing
}  // namespace libarbiter

#endif  // LIB_LIBARBITER_SWISS_PAIRER_H_
