#pragma once

#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>





class vec3 {
public:
    vec3();
    vec3(double e0, double e1, double e2);

    double x() const;
    double y() const;
    double z() const;

    //-V
    vec3 operator-() const;
    // V[i]
    double operator[](int i) const;
    // &V[i] ? TODO try this
    double& operator[](int i);

    // V1 += V2
    vec3& operator+=(const vec3& v);
    // V1 *= t
    vec3& operator*=(const double t);
    // V1 /= t
    vec3& operator/=(const double t);

    double length() const;
    double length_squared() const;
public:
    double e[3];

    vec3 cross(const vec3& u, const vec3& v);
    double dot(const vec3 & u, const vec3 & v);
    vec3 unit_vector(vec3 v);

    // inline friend std::ostream& operator<<(std::ostream& out, const vec3& v);
    // inline friend vec3 operator+(const vec3& u, const vec3& v);



};
    // utilities and vector operations

           inline std::ostream& operator<<(std::ostream& out, const vec3& v)
        {
            // TODO: insert return statement here
           return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
        }

inline vec3 operator+(const vec3& u, const vec3& v)
{
    return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}



inline vec3 operator-(const vec3& u, const vec3& v) {
    return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
    return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

inline vec3 operator*(double t, const vec3 &v) {
    return vec3(t*v.e[0], t*v.e[1], t*v.e[2]);
}

inline vec3 operator*(const vec3 &v, double t) {
    return t * v;
}
    inline vec3 operator/(vec3 v, double t) {
    return (1/t) * v;
}

// U.V cartesien
inline double dot(const vec3 &u, const vec3 &v) {
    return u.e[0] * v.e[0]
         + u.e[1] * v.e[1]
         + u.e[2] * v.e[2];
}

// U x V vectoriel
inline vec3 cross(const vec3 &u, const vec3 &v) {
    return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
                u.e[2] * v.e[0] - u.e[0] * v.e[2],
                u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}
//     // inline std::ostream& operator<<(std::ostream& out, const vec3& v);

//     inline vec3 operator-(const vec3& u, const vec3& v);
//     inline vec3 operator*(const vec3& u, const vec3& v);
//     inline vec3 operator*(double t, const vec3& v);
//     inline vec3 operator*(const vec3& v, double t);

//  inline vec3 operator/(vec3 v, double t);

//     // U.V cartesien
//     inline double dot(const vec3& u, const vec3& v);
//     // U x V vectoriel
//     inline vec3 cross(const vec3& u, const vec3& v);
//     inline vec3 unit_vector(vec3 v);

        //juste pour visibilité
        // point coordinates and color vectors are type vec3
        using point3 = vec3;   // 3D point
        using color = vec3;    // RGB color


#endif
