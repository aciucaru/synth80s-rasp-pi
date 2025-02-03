#include "math-util.h"

namespace synth80s
{
  /* This is a static method, but the keyword 'static' is not allowed here,
  ** because it changes the linkage of the method to 'internal linkage', see more at:
  ** https://stackoverflow.com/questions/8826125/cant-use-static-keyword-on-a-static-method-in-a-c-class-implementation-file
  ** This method returns the sign of a float number */
  int MathUtil::signum(float number)
  {
    if (number < 0.0f)
      return -1;
    else if (number > 0.0f)
      return 1;
    else
      return 0;
  }

  // checks if first number is between the next two limits,
  // where the first number could also be equal with any of the two limits
  bool MathUtil::isBetweenLimits(float comparedNumber, float lowerLimit, float upperLimit)
  {
    const float epsilon = std::numeric_limits<float>::epsilon();

    if ( (lowerLimit - epsilon) < comparedNumber &&
          comparedNumber < (upperLimit + epsilon) )
      return true;
    else
      return false;
  }
  
  // checks if two float numbers are almost equal
  bool MathUtil::isAproxEqual(float a, float b, float epsilon)
  {
	  return fabs(a - b) <= ( (fabs(a) > fabs(b) ? fabs(b) : fabs(a)) * epsilon );
  }
}
