/** mobius.hpp
   =========

   Interface definition for the Mobius Transformation class, which defines a
   composition of rotations, dilations, and reflections.

 */
#ifndef MOBIUS_HPP_INCLUDED
#define MOBIUS_HPP_INCLUDED = 1;

#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

/**
 * \class Mobius
 * \brief Each member of the class Mobius defines a Mobius transformation
 * unique up to complex scaling of its coefficients.
 * 
 * \details
 * Stores four complex numbers that define the Mobius transformation
 * (az+b)/(cz+d)
 */

class Mobius {
public:
    /**
     * \brief Default constructor is the identity transformation
     */
    Mobius();

    /**
     * \brief Construct with the four coefficients as parameters
     */
    Mobius(complex<float> a, complex<float> b, complex<float> c,
            complex<float>d);

    /**
     * \brief Apply the transformation to a complex number
     */
    complex<float> apply(complex<float> z);

    Mobius inverse();
    
    complex<float> apply_inv(complex<float> z);

    /**
     * \brief Return a map for x vals to be used by opencv's remapping fn
     */
    Mat map_x(Mat src);
    
    /**
     * \brief Return a map for y vals to be used by opencv's remapping fn
     */
    Mat map_y(Mat src);

    void translate(complex<float> v);

    void dilate(float r);

    void invert();

private:
    complex<float> a_;
    complex<float> b_;
    complex<float> c_;
    complex<float> d_;

};

#endif // ifndef MOBIUS_HPP_INCLUDED
