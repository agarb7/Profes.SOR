#ifndef MPTYPES_H
#define MPTYPES_H

#include <boost/mpl/vector.hpp>
#include <boost/mpl/map.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/pop_front.hpp>

#include <type_traits>

template <class T, T t>
using Ic = std::integral_constant<T, t>;

template <class ...T>
using MplVector = boost::mpl::vector<T...>;

template <class ...T>
using MplMap = boost::mpl::map<T...>;

template <class S>
using MplSize = boost::mpl::size<S>;

template <class S, class I>
using MplAt = typename boost::mpl::at<S, I>::type;

template <class S>
using MplBack = typename boost::mpl::back<S>::type;

template <class S>
using MplFront = typename boost::mpl::front<S>::type;

template <class S>
using MplPopFront = typename boost::mpl::pop_front<S>::type;

template <class T, class U>
using MplPair = boost::mpl::pair<T, U>;

#endif // MPTYPES_H
