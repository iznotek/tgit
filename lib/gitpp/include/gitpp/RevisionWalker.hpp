#ifndef GITPP_REVISIONWALKER_HPP
#define GITPP_REVISIONWALKER_HPP

#include <iterator>
#include <memory>

#include <gitpp/ObjectId.hpp>

struct git_revwalk;

namespace gitpp {

class Commit;
class Repository;

class RevisionWalkIterator;

class RevisionWalker {
public:
  enum Sorting : unsigned int { None = 0, TopologicalSort = 0b001, DateSort = 0b010, Reverse = 0b100 };

  RevisionWalker(RevisionWalker&&) noexcept = default;
  ~RevisionWalker();
  RevisionWalker& operator=(RevisionWalker&&) noexcept = default;

  explicit RevisionWalker(Repository& repo, unsigned int) noexcept;

  void pushHead();

  Commit current() const;
  bool next() noexcept;

  RevisionWalkIterator begin() noexcept;
  RevisionWalkIterator end() noexcept;

private:
  RevisionWalker(git_revwalk*) noexcept;

  struct deleter {
    void operator()(git_revwalk*) const noexcept;
  };
  std::unique_ptr<git_revwalk, deleter> Handle;
  ObjectId Current;
};

struct RevisionWalkIterator {
  using value_type = Commit;
  using reference = Commit;
  using pointer = void;

  RevisionWalkIterator() noexcept = default;
  explicit RevisionWalkIterator(RevisionWalker&) noexcept;
  RevisionWalkIterator(const RevisionWalkIterator& other) noexcept = default;

  RevisionWalkIterator& operator=(const RevisionWalkIterator& other) noexcept = default;

  bool operator==(const RevisionWalkIterator& other) const;
  bool operator!=(const RevisionWalkIterator& other) const;

  reference operator*() noexcept;

  RevisionWalkIterator& operator++() noexcept;

private:
  RevisionWalker* Walker = nullptr;
};

inline auto begin(RevisionWalker& rw) {
  return rw.begin();
}

inline auto end(RevisionWalker& rw) {
  return rw.end();
}

} // namespace gitpp

namespace std {

template <>
struct iterator_traits<gitpp::RevisionWalkIterator> {
  using IteratorT = gitpp::RevisionWalkIterator;

  using difference_type = std::ptrdiff_t;
  using iterator_category = std::input_iterator_tag;
  using value_type = IteratorT::value_type;
  using reference = IteratorT::reference;
  using pointer = IteratorT::pointer;
};

} // namespace std

#endif
