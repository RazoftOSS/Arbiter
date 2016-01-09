#ifndef LIB_LIBARBITER_PLAYER_LIST_H_
#define LIB_LIBARBITER_PLAYER_LIST_H_

#include <mutex>
#include <unordered_map>

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
  void Add(const Player& player);
  /** Remove a Player from the PlayerList. */
  void Remove(int id);

  /**
   *  Returns a const pointer to the Player with the given ID.
   *
   *  Returns nullptr if not found.
   */
  const Player* GetPlayer(int id) const;

  /**
   *  Returns a non-const pointer to the Player with the given ID.
   *
   *  Returns nullptr if not found.
   */
  Player* GetMutablePlayer(int id);

  /** Returns the number of Players in the PlayerList. */
  int NumPlayers() const;

 private:
  /** Map of player ID's to players. */
  std::unordered_map<int, Player> players_;

  /** Lock protecting the map of players. */
  std::mutex players_lock_;
};

}  // namespace libarbiter

#endif
