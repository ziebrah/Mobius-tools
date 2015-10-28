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
 * \brief Defines unique Mobius transformations
 *
 * \details
 * Stores four complex numbers that define the Mobius transformation
 *
 */

class Mobius {
public:
    /**
     * \brief Default constructor is the identity transformation.
     */
    Mobius();

    Mobius(complex<float> a, complex<float> b, complex<float> c,
            complex<float>d);

    complex<float> apply(complex<float> z);

    Mobius inverse();

    complex<float> apply_inv(complex<float> z);

    Mat map_x(Mat src);

    Mat map_y(Mat src);

    void translate(complex<float> v);

    void dilate(float r);

    void invert();

//    void invert(complex<float> center, float radius);

private:
    complex<float> a_;
    complex<float> b_;
    complex<float> c_;
    complex<float> d_;

};

#endif // ifndef MOBIUS_HPP_INCLUDED
