#ifndef LIB_LIBARBITER_SWISS_PAIR_TABLE_H_
#define LIB_LIBARBITER_SWISS_PAIR_TABLE_H_

#include <unordered_map>

#include <boost/functional/hash.hpp>
#include <boost/uuid/uuid.hpp>

#include "game.h"
#include "player.h"

namespace libarbiter {
namespace pairing {

class SwissPairTable {
 public:
  typedef std::unordered_map<boost::uuids::uuid, Game,
                             boost::hash<boost::uuids::uuid>>::const_iterator
      const_iterator;

  SwissPairTable() {}

  const_iterator begin() const { return pairs_.cbegin(); }
  const_iterator end() const { return pairs_.cend(); }

 private:
  std::unordered_map<boost::uuids::uuid, Game, boost::hash<boost::uuids::uuid>>
      pairs_;
};

}  // namespace pairing
}  // namespace libarbiter

#endif  // LIB_LIBARBITER_SWISS_PAIR_TABLE_H_
