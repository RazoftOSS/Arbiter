#ifndef LIB_LIBARBITER_PLAYER_H_
#define LIB_LIBARBITER_PLAYER_H_

#include <string>

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

namespace libarbiter {

enum PlayerStringType {
  JSON,
  CSV,
};

/**
 *  A single tournament participant.
 */
class Player {
 public:
  Player(std::string name, int elo)
      : id_(boost::uuids::random_generator()()), name_(name), elo_(elo) {}

  boost::uuids::uuid id() const { return id_; }
  std::string name() const { return name_; }
  int elo() const { return elo_; }

  int wins() const { return wins_white_ + wins_black_; }
  int draws() const { return draws_white_ + draws_black_; }
  int losses() const { return losses_white_ + losses_black_; }

  /**
   *  Generates a Player from a single line of JSON or CSV.
   *
   *  JSON example:
   *  \code
   *    { "name": "foo", "elo": 2000 }
   *  \endcode
   *
   *  CSV example:
   *  \code
   *    foo,2000
   *  \endcode
   */
  static Player* NewPlayer(std::string player_string, PlayerStringType type);

 private:
  boost::uuids::uuid id_;
  std::string name_;
  int elo_;

  int wins_white_ = 0;
  int wins_black_ = 0;
  int draws_white_ = 0;
  int draws_black_ = 0;
  int losses_white_ = 0;
  int losses_black_ = 0;
};

}  // namespace libarbiter

#endif  // LIB_LIBARBITER_PLAYER_H_
