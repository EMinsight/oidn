// Copyright 2009-2022 Intel Corporation
// SPDX-License-Identifier: Apache-2.0

#pragma once

#include "common/math.h"

namespace oidn {

  template<typename T>
  struct vec2
  {
    T x, y;

    OIDN_HOST_DEVICE_INLINE vec2() {}
    OIDN_HOST_DEVICE_INLINE vec2(const T& x) : x(x), y(x) {}
    OIDN_HOST_DEVICE_INLINE vec2(const T& x, const T& y) : x(x), y(y) {}

    template<typename U>
    OIDN_HOST_DEVICE_INLINE vec2(const vec2<U>& v) : x(v.x), y(v.y) {}
  };

  template<typename T>
  struct vec3
  {
    T x, y, z;

    OIDN_HOST_DEVICE_INLINE vec3() {}
    OIDN_HOST_DEVICE_INLINE vec3(const T& x) : x(x), y(x), z(x) {}
    OIDN_HOST_DEVICE_INLINE vec3(const T& x, const T& y, const T& z) : x(x), y(y), z(z) {}

    template<typename U>
    OIDN_HOST_DEVICE_INLINE vec3(const vec3<U>& v) : x(v.x), y(v.y), z(v.z) {}
  };

  using vec2i = vec2<int>;
  using vec2f = vec2<float>;

  using vec3i = vec3<int>;
  using vec3f = vec3<float>;

  #define define_vec_binary_op(name, op)                                       \
    template<typename T>                                                       \
    OIDN_HOST_DEVICE_INLINE vec2<T> name(const vec2<T>& a, const vec2<T>& b) { \
      return vec2<T>(a.x op b.x, a.y op b.y);                                  \
    }                                                                          \
    template<typename T>                                                       \
    OIDN_HOST_DEVICE_INLINE vec2<T> name(const vec2<T>& a, const T& b) {       \
      return vec2<T>(a.x op b, a.y op b);                                      \
    }                                                                          \
    template<typename T>                                                       \
    OIDN_HOST_DEVICE_INLINE vec2<T> name(const T& a, const vec2<T>& b) {       \
      return vec2<T>(a op b.x, a op b.y);                                      \
    }                                                                          \
    template<typename T>                                                       \
    OIDN_HOST_DEVICE_INLINE vec3<T> name(const vec3<T>& a, const vec3<T>& b) { \
      return vec3<T>(a.x op b.x, a.y op b.y, a.z op b.z);                      \
    }                                                                          \
    template<typename T>                                                       \
    OIDN_HOST_DEVICE_INLINE vec3<T> name(const vec3<T>& a, const T& b) {       \
      return vec3<T>(a.x op b, a.y op b, a.z op b);                            \
    }                                                                          \
    template<typename T>                                                       \
    OIDN_HOST_DEVICE_INLINE vec3<T> name(const T& a, const vec3<T>& b) {       \
      return vec3<T>(a op b.x, a op b.y, a op b.z);                            \
    }

  define_vec_binary_op(operator+, +)
  define_vec_binary_op(operator-, -)
  define_vec_binary_op(operator*, *)
  define_vec_binary_op(operator/, /)

  #undef define_vec_binary_op

  #define define_vec_unary_func(f)                        \
    template<typename T>                                  \
    OIDN_HOST_DEVICE_INLINE vec2<T> f(const vec2<T>& v) { \
      return vec2<T>(f(v.x), f(v.y));                     \
    }                                                     \
    template<typename T>                                  \
    OIDN_HOST_DEVICE_INLINE vec3<T> f(const vec3<T>& v) { \
      return vec3<T>(f(v.x), f(v.y), f(v.z));             \
    }

  define_vec_unary_func(pow)
  define_vec_unary_func(powr)
  define_vec_unary_func(log)
  define_vec_unary_func(exp)
  define_vec_unary_func(nan_to_zero)

  #undef define_vec_unary_func

  #define define_vec_binary_func(f)                                         \
    template<typename T>                                                    \
    OIDN_HOST_DEVICE_INLINE vec2<T> f(const vec2<T>& a, const vec2<T>& b) { \
      return vec2<T>(f(a.x, b.x), f(a.y, b.y));                             \
    }                                                                       \
    template<typename T>                                                    \
    OIDN_HOST_DEVICE_INLINE vec2<T> f(const vec2<T>& a, const T& b) {       \
      return vec2<T>(f(a.x, b), f(a.y, b));                                 \
    }                                                                       \
    template<typename T>                                                    \
    OIDN_HOST_DEVICE_INLINE vec2<T> f(const T& a, const vec2<T>& b) {       \
      return vec2<T>(f(a, b.x), f(a, b.y));                                 \
    }                                                                       \
    template<typename T>                                                    \
    OIDN_HOST_DEVICE_INLINE vec3<T> f(const vec3<T>& a, const vec3<T>& b) { \
      return vec3<T>(f(a.x, b.x), f(a.y, b.y), f(a.z, b.z));                \
    }                                                                       \
    template<typename T>                                                    \
    OIDN_HOST_DEVICE_INLINE vec3<T> f(const vec3<T>& a, const T& b) {       \
      return vec3<T>(f(a.x, b), f(a.y, b), f(a.z, b));                      \
    }                                                                       \
    template<typename T>                                                    \
    OIDN_HOST_DEVICE_INLINE vec3<T> f(const T& a, const vec3<T>& b) {       \
      return vec3<T>(f(a, b.x), f(a, b.y), f(a, b.z));                      \
    }

  define_vec_binary_func(min)
  define_vec_binary_func(max)

  #undef define_vec_binary_func

  #define define_vec_reduce(f)                               \
    template<typename T>                                     \
    OIDN_HOST_DEVICE_INLINE T reduce_##f(const vec2<T>& v) { \
      return f(v.x, v.y);                                    \
    }                                                        \
    template<typename T>                                     \
    OIDN_HOST_DEVICE_INLINE T reduce_##f(const vec3<T>& v) { \
      return f(f(v.x, v.y), v.z);                            \
    }

  define_vec_reduce(min)
  define_vec_reduce(max)

  #undef define_vec_reduce

  template<typename T>
  OIDN_HOST_DEVICE_INLINE vec2<T> clamp(const vec2<T>& v, const T& minVal, const T& maxVal)
  {
    return vec2<T>(clamp(v.x, minVal, maxVal), clamp(v.y, minVal, maxVal));
  }

  template<typename T>
  OIDN_HOST_DEVICE_INLINE vec3<T> clamp(const vec3<T>& v, const T& minVal, const T& maxVal)
  {
    return vec3<T>(clamp(v.x, minVal, maxVal), clamp(v.y, minVal, maxVal), clamp(v.z, minVal, maxVal));
  }

} // namespace oidn