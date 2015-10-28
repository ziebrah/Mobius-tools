/**
 * \file mobius.cpp
 * \author Lizzie Kumar
 *
 * \brief Implements the Mobius class
 *
 */

#include "mobius.hpp"
#include <iostream>

using namespace cv;
using namespace std;

Mobius::Mobius() :
    a_(complex<float>(1.0f, 0.0f)), b_(complex<float>(0.0f, 0.0f)),
    c_(complex<float>(0.0f, 0.0f)), d_(complex<float>(1.0f, 0.0f))
{
    // Nothing to do here
}

Mobius::Mobius(complex<float> a, complex<float> b, complex<float> c,
            complex<float>d) :
    a_(a), b_(b), c_(c), d_(d)
{
    // Nothing to do here
}

complex<float> Mobius::apply(complex<float> z)
{
    return ((a_*z) + b_)/((c_*z) + d_);
}

Mobius Mobius::inverse()
{
    return Mobius(d_, -b_, -c_, a_);
}

complex<float> Mobius::apply_inv(complex<float> z)
{
    return inverse().apply(z);
}

Mat Mobius::map_x(Mat src)
{
    Mat map;
    map.create(src.size(), CV_32FC1);

    float re;
    float im;
    complex<float> z;

    float newre;

    float origre = (float)src.cols/2;
    float origim = (float)src.rows/2;

    for(int j = 0; j < src.rows; j++)
    {
        for(int i = 0; i < src.cols; i++)
        {
            re = (float) i - origre;
            im = (float) src.rows - j - origim;

            z = complex<float>(re, im);

            newre = apply_inv(z).real();

            if (abs(newre) < (float) src.cols/2.0f)
            {
                map.at<float>(j,i) = static_cast<int>(origre + newre);
            }

        }
    }

    return map;
}

Mat Mobius::map_y(Mat src)
{
    Mat map;
    map.create(src.size(), CV_32FC1);

    float re;
    float im;
    complex<float> z;

    float newim;

    float origre = (float)src.cols/2;
    float origim = (float)src.rows/2;

    for(int j = 0; j < src.rows; j++)
    {
        for(int i = 0; i < src.cols; i++)
        {
            re = (float) i - origre;
            im = (float) src.rows - j - origim;

            z = complex<float>(re, im);
            newim = apply_inv(z).imag();

            if (abs(newim) < (float) src.rows/2.0f)
            {
                map.at<float>(j,i) = static_cast<int>(origim - newim);
            }

        }
    }

    return map;
}



void Mobius::translate(complex<float> v)
{
    a_ = a_ + (v*c_);
    b_ = b_ + (v*d_);
}

void Mobius::dilate(float r)
{
    a_ = r*a_;
    b_ = r*b_;
}

void Mobius::invert()
{
    complex<float> tempa = a_;
    a_ = c_;
    c_ = tempa;

    complex<float> tempb = b_;
    b_ = d_;
    d_ = tempb;
}
