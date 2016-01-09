#ifndef LIB_LIBARBITER_PLAYER_H_
#define LIB_LIBARBITER_PLAYER_H_

#include <string>

namespace libarbiter {

namespace {

int current_player_id = 0;

}  // namespace

/**
 *  A single tournament participant.
 */
class Player {
 public:
  Player(std::string name, int elo)
      : id_(current_player_id++), name_(name), elo_(elo) {}

  int id() const { return id_; }
  std::string name() const { return name_; }
  int elo() const { return elo_; }

  int wins() const { return wins_white_ + wins_black_; }
  int draws() const { return draws_white_ + draws_black_; }
  int losses() const { return losses_white_ + losses_black_; }

 private:
  int id_;
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

#endif
