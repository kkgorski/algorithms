// ******************** REVERSE ITERATOR ********************
//https://stackoverflow.com/questions/8542591/c11-reverse-range-based-for-loop
template <typename T>
struct reversion_wrapper{
  T& iterable;
};

template <typename T>
auto begin (reversion_wrapper<T> w){
  return std::rbegin(w.iterable);
}

template <typename T>
auto end (reversion_wrapper<T> w){
  return std::rend(w.iterable);
}

template <typename T>
reversion_wrapper<T> reverse_wrap (T&& iterable){
  return { iterable };
}
// ******************** REVERSE ITERATOR ********************

