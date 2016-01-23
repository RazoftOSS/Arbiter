#ifndef LIB_LIBARBITER_GAME_H_
#define LIB_LIBARBITER_GAME_H_

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "player.h"

namespace libarbiter {

class Game {
 public:
  enum Status { UNFINISHED, DRAW, WHITE_WIN, BLACK_WIN };

  Game(Player* white, Player* black)
      : id_(boost::uuids::random_generator()()), white_(white), black_(black) {}

  boost::uuids::uuid id() const { return id_; }
  Player* white() const { return white_; }
  Player* black() const { return black_; }
  Status status() const { return status_; }

 private:
  boost::uuids::uuid id_;
  Player* white_;
  Player* black_;
  Status status_ = UNFINISHED;
};

}  // namespace libarbiter

#endif  // LIB_LIBARBITER_GAME_H_
