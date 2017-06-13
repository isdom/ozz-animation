//----------------------------------------------------------------------------//
//                                                                            //
// ozz-animation is hosted at http://github.com/guillaumeblanc/ozz-animation  //
// and distributed under the MIT License (MIT).                               //
//                                                                            //
// Copyright (c) 2015 Guillaume Blanc                                         //
//                                                                            //
// Permission is hereby granted, free of charge, to any person obtaining a    //
// copy of this software and associated documentation files (the "Software"), //
// to deal in the Software without restriction, including without limitation  //
// the rights to use, copy, modify, merge, publish, distribute, sublicense,   //
// and/or sell copies of the Software, and to permit persons to whom the      //
// Software is furnished to do so, subject to the following conditions:       //
//                                                                            //
// The above copyright notice and this permission notice shall be included in //
// all copies or substantial portions of the Software.                        //
//                                                                            //
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR //
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   //
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    //
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER //
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING    //
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER        //
// DEALINGS IN THE SOFTWARE.                                                  //
//                                                                            //
//----------------------------------------------------------------------------//

#include "ozz/animation/offline/raw_track.h"

#include <limits>

#include "ozz/base/io/archive.h"
#include "ozz/base/maths/math_archive.h"

#include "ozz/base/containers/vector_archive.h"

namespace ozz {
namespace animation {
namespace offline {
namespace internal {

template <typename _ValueType>
RawTrack<_ValueType>::RawTrack() {}

template <typename _ValueType>
RawTrack<_ValueType>::~RawTrack() {}

template <typename _ValueType>
bool RawTrack<_ValueType>::Validate() const {
  float previous_time = -1.f;
  for (size_t k = 0; k < keyframes.size(); ++k) {
    const float frame_time = keyframes[k].time;
    // Tests frame's time is in range [0:1].
    if (frame_time < 0.f || frame_time > 1.f) {
      return false;
    }
    // Tests that frames are sorted.
    if (frame_time - previous_time <= std::numeric_limits<float>::epsilon()) {
      return false;
    }
    previous_time = frame_time;
  }
  return true;  // Validated.
}

template <typename _ValueType>
void RawTrack<_ValueType>::Save(io::OArchive& _archive) const {
  _archive << keyframes;
}

template <typename _ValueType>
void RawTrack<_ValueType>::Load(io::IArchive& _archive,
                                uint32_t _version) {
  (void)_version;
  assert(_version == 1);
  _archive >> keyframes;
}

// Explicitly instantiate supported raw tracks.
template struct RawTrack<float>;
template struct RawTrack<math::Float2>;
template struct RawTrack<math::Float3>;
template struct RawTrack<math::Quaternion>;
}  // namespace internal
}  // namespace offline
}  // namespace animation

namespace io {

// Can be declared locally has only been reference in this file.
OZZ_IO_TYPE_VERSION_T1(1, typename _ValueType,
                       animation::offline::RawTrackKeyframe<_ValueType>)

template <typename _ValueType>
void Save(OArchive& _archive,
          const animation::offline::RawTrackKeyframe<_ValueType>* _keyframes,
          size_t _count) {
  for (size_t i = 0; i < _count; ++i) {
    const animation::offline::RawTrackKeyframe<_ValueType>& keyframe =
        _keyframes[i];
    const uint8_t interp = static_cast<uint8_t>(keyframe.interpolation);
    _archive << interp;
    _archive << keyframe.time;
    _archive << keyframe.value;
  }
}

template <typename _ValueType>
void Load(IArchive& _archive,
          animation::offline::RawTrackKeyframe<_ValueType>* _keyframes,
          size_t _count, uint32_t _version) {
  (void)_version;
  for (size_t i = 0; i < _count; ++i) {
    animation::offline::RawTrackKeyframe<_ValueType>& keyframe = _keyframes[i];
    uint8_t interp;
    _archive >> interp;
    keyframe.interpolation =
        static_cast<animation::offline::RawTrackInterpolation::Value>(interp);
    _archive >> keyframe.time;
    _archive >> keyframe.value;
  }
}
}  // namespace io
}  // namespace ozz