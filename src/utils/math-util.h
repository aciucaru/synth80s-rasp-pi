#ifndef SYNTH80S_SRC_UTILS_MATH_UTIL_H

#define SYNTH80S_SRC_UTILS_MATH_UTIL_H

#include <cmath>
#include <limits>

namespace synth80s
{
  class MathUtil
  {
  private:
      // utility class, so constructor is private (it's not meant to be instantiated)
      MathUtil();

    public:
      // returns the sign of a number (-1, 0 or 1)
      static int signum(float number);

      // checks if first number is between the next two limits,
      // where the first number could also be equal with any of the two limits
      static bool isBetweenLimits(float comparedNumber, float lowerLimit, float upperLimit);
      
      static bool isAproxEqual(float a, float b, float epsilon);
  };
}

#endif

