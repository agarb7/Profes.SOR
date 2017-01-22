#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <boost/signals2.hpp>
#include <boost/endian/arithmetic.hpp>
#include <boost/optional.hpp>

#include <string>
#include <array>
#include <utility>

#include <cstddef>
#include <cstdint>

template<class T>
using Signal = boost::signals2::signal<T>;

using SizeType = std::size_t;

using LittleInt16 = boost::endian::little_int16_t;
using LittleUInt16 = boost::endian::little_uint16_t;

using LittleInt32 = boost::endian::little_int32_t;
using LittleUInt32 = boost::endian::little_uint32_t;

using String = std::string;

template <SizeType Size>
using FixedString = std::array<char, Size>;

using LittleUInt16Vector = std::vector<LittleUInt16>;

template<class T, class U>
using Pair = std::pair<T,U>;

#endif // DEFINITIONS_H
