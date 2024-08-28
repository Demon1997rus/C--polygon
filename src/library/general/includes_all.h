#ifndef INCLUDES_ALL_H
#define INCLUDES_ALL_H

// standard
#include <queue>

#include <algorithm>
#include <cassert>
#include <exception>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// boost algorithm
#include <boost/algorithm/string.hpp>

// boost format
#include <boost/format.hpp>

// boost utility
#include <boost/utility/string_view.hpp>

// boost interprocess
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>

// boost property
#include <boost/property_tree/json_parser.hpp>

// boost regex
#include <boost/regex.hpp>

// boost mpl
#include <boost/mpl/at.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/vector.hpp>

// boost type
#include <boost/static_assert.hpp>
#include <boost/type_index.hpp>
#include <boost/type_traits.hpp>

// boost containers
#include <boost/bimap.hpp>
#include <boost/bimap/multiset_of.hpp>
#include <boost/container/flat_set.hpp>
#include <boost/container/slist.hpp>
#include <boost/container/small_vector.hpp>
#include <boost/container/static_vector.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/identity.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/pool/pool_alloc.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>

// Сбор информации о платформе и компиляторе
#include <boost/predef/compiler.h>
#include <boost/predef/os.h>

// Работа с системой
#include <boost/filesystem/operations.hpp>

// boost atomic
#include <boost/atomic.hpp>

// boost coroutine
#include <boost/coroutine2/coroutine.hpp>

// boost random
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>

// my includes
#include "../containers/queue_process.h"
#include "../general/functions.h"
#include "../time/timemeter.h"

#endif // INCLUDES_ALL_H
