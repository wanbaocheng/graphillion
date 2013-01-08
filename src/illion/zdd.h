#ifndef ILLION_ZDD_H_
#define ILLION_ZDD_H_

#include <iostream>
#include <set>
#include <unordered_set>
#include <utility>
#include <vector>

#ifdef HAVE_LIBGMPXX
#include <gmpxx.h>
#endif

#include "illion/type.h"

namespace illion {

#ifdef HAVE_LIBGMPXX
typedef mpz_class intx_t;
#else
typedef double intx_t;
#endif

void init(elem_t num_elems);
void new_elems(elem_t max_elem);
elem_t num_elems();

zdd_t single(elem_t e);
inline zdd_t null() { return zdd_t(-1); }
inline zdd_t bot() { return zdd_t(0); }
inline zdd_t top() { return zdd_t(1); }
inline zdd_t lo(zdd_t f) { return f.OffSet(f.Top()); }
inline zdd_t hi(zdd_t f) { return f.OnSet0(f.Top()); }
inline bool is_bot(zdd_t f) { return f == bot(); }
inline bool is_top(zdd_t f) { return f == top(); }
inline bool is_term(zdd_t f) { return f.Top() == 0; }
inline word_t id(zdd_t f) { return f.GetID(); }
inline elem_t elem(zdd_t f) {
  return is_term(f) ? BDD_MaxVar + 1 : f.Top();
}

zdd_t operator|(const zdd_t& f, const zdd_t& g);

zdd_t _not(zdd_t f);
zdd_t minimal(zdd_t f);
zdd_t maximal(zdd_t f);
zdd_t hitting(zdd_t f);
zdd_t nonsubsets(zdd_t f, zdd_t g);
zdd_t nonsupersets(zdd_t f, zdd_t g);
zdd_t choose_random(zdd_t f, std::vector<elem_t>* stack, int* idum);
zdd_t choose_best(zdd_t f, const std::vector<int>& weights,
                  std::set<elem_t>* s);
void save(zdd_t f, std::ostream& out = std::cout);
zdd_t load(std::istream& in = std::cin);
void dump(zdd_t f, std::ostream& out = std::cout);
void dump(zdd_t f, std::ostream& out, std::vector<elem_t>* stack, bool* dumped);
void algo_b(zdd_t f, const std::vector<int>& w, std::vector<bool>* x);
intx_t algo_c(zdd_t f);
zdd_t zuniq(elem_t v, zdd_t l, zdd_t h);
double ran3(int* idum);
void sort_zdd(zdd_t f, std::vector<std::vector<zdd_t> >* stacks,
              std::unordered_set<word_t>* visited,
              elem_t* max_elem = nullptr);
inline std::pair<word_t, word_t> make_key(zdd_t f, zdd_t g) {
  return std::make_pair(id(f), id(g));
}

}  // namespace illion

#endif  // ILLION_ZDD_H_
