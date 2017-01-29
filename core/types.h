#ifndef TYPES_H
#define TYPES_H

#include <boost/signals2.hpp>
#include <boost/endian/arithmetic.hpp>

#include <string>
#include <array>
#include <utility>

#include <cstddef>
#include <cstdint>

namespace Core {

template <class T>
using Signal = boost::signals2::signal<T>;

using SizeType = std::size_t;

using LeInt16 = boost::endian::little_int16_t;
using LeUInt16 = boost::endian::little_uint16_t;

using LeInt32 = boost::endian::little_int32_t;
using LeUInt32 = boost::endian::little_uint32_t;

using String = std::string;

template <SizeType Size>
using FixedString = std::array<char, Size>;

using LeUInt16Vector = std::vector<LeUInt16>;

template <class T, class U>
using Pair = std::pair<T,U>;

} // namespace Core

#endif // TYPES_H
