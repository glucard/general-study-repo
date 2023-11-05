#include "BezierCurve.hpp"

int factorial(int x) {
    int y = 1;
    for(int i = 2; i <= x; i++)
        y *= i;
    return y;
}

void bzc::BezierCurve::add_point(int x, int y) {
    rtz::Point p(x, y);
    points.push_back(p);
}

void bzc::BezierCurve::parametric(int max_steps, arr::Array2d frame_buffer){
    int n, n_factorial;
    float binomial, B;
    
    // grau
    n = points.size() - 1;

    // check if have at least grau 1, since its n - 1 
    if (n < 1) {
        std::string error = "Error: parametric bezier curve must have at least 2 points.";
        std::cout << error;
        throw std::invalid_argument(error);
    }

    // do n factorial just one time
    n_factorial = factorial(n);
    std::cout << "(x, y) : ";

    
    float x_sum, y_sum;
    float t;
    for(int step = 0; step < max_steps; step++) {
        t = step / (float)max_steps;

        x_sum = 0;
        y_sum = 0;
        
        for(int i = 0; i <= n; i++) {
            binomial = n_factorial / (float)(factorial(i)*factorial(n-i));
            B = binomial * pow(t, i) * pow(1-t, n-i);
            x_sum += B * points[i].x;
            y_sum += B * points[i].y;
        }
        frame_buffer.data[(int)y_sum][(int)x_sum] = 1;
        std::cout << "(" << x_sum << ", " << y_sum << ") ";
    }


    return;
}