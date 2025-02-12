/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <fb303/ThreadLocalStats.h>

#include <gflags/gflags.h>

DEFINE_bool(
    fb303_tcData_dont_update_on_read,
    false,
    "If set, timeseries owned by thread-local timeseries classes will never be updated "
    "in between aggregation. It fixes a bug that is causing "
    "rapid false oscillations in all timeseries (most noticeable "
    "with aggregation intervals <= 10s");

namespace facebook {
namespace fb303 {

/*
 * Explicitly instantiate the commonly-used instantations of ThreadLocalStatsT.
 */

// Explicitly instantiate ThreadLocalStatsT and related classes
// when used with TLStatsNoLocking.
template class ThreadLocalStatsT<TLStatsNoLocking>;
template class TLStatT<TLStatsNoLocking>;
template class TLTimeseriesT<TLStatsNoLocking>;
template class TLHistogramT<TLStatsNoLocking>;
template class TLCounterT<TLStatsNoLocking>;

// Explicitly instantiate ThreadLocalStatsT and related classes
// when used with TLStatsThreadSafe.
template class ThreadLocalStatsT<TLStatsThreadSafe>;
template class TLStatT<TLStatsThreadSafe>;
template class TLTimeseriesT<TLStatsThreadSafe>;
template class TLHistogramT<TLStatsThreadSafe>;
template class TLCounterT<TLStatsThreadSafe>;

namespace detail {

bool shouldUpdateGlobalStatOnRead() {
  return !FLAGS_fb303_tcData_dont_update_on_read;
}

} // namespace detail

} // namespace fb303
} // namespace facebook
