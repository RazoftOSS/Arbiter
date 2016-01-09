#ifndef LIB_LIBARBITER_PLAYER_LIST_H_
#define LIB_LIBARBITER_PLAYER_LIST_H_

#include <memory>
#include <mutex>
#include <unordered_map>

#include <boost/uuid/uuid.hpp>
#include <boost/functional/hash.hpp>

#include "player.h"

namespace libarbiter {

/**
 *  Table of tournament participants.
 */
class PlayerList {
 public:
  PlayerList() {}
  PlayerList(const PlayerList&) = delete;
  PlayerList& operator=(const PlayerList&) = delete;

  /** Add a Player to the PlayerList. */
  void Add(Player* player);
  /** Remove a Player from the PlayerList. */
  void Remove(boost::uuids::uuid id);

  /**
   *  Returns a const pointer to the Player with the given ID.
   *
   *  Returns nullptr if not found.
   */
  const Player* GetPlayer(boost::uuids::uuid id) const;

  /**
   *  Returns a non-const pointer to the Player with the given ID.
   *
   *  Returns nullptr if not found.
   */
  Player* GetMutablePlayer(boost::uuids::uuid id);

  /** Returns the number of Players in the PlayerList. */
  int NumPlayers() const;

 private:
  /** Map of player ID's to players. */
  std::unordered_map<boost::uuids::uuid, std::unique_ptr<Player>,
                     boost::hash<boost::uuids::uuid>> players_;

  /** Lock protecting the map of players. */
  std::mutex players_lock_;
};

}  // namespace libarbiter

#endif  // LIB_LIBARBITER_PLAYER_LIST_H_
