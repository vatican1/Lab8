#include <iostream>

double alpha = 0.1, beta = 0.1, delta = 0.01, gamma_ = 0.01;

double x_(double x, double y)
{
    return alpha * x + beta * x * y;
}

double y_(double x, double y)
{
    return delta * x * y - gamma_ * y;
}

std::pair<double, double> f(const double t, const double dt = 0.1)
{
    double x_0 = 20, y_0 = 5;
    double x_curr = x_0, y_curr = y_0;
    double x_next, y_next;
    double t_now = 0;
    while(t_now < t)
    {
        // x_next = x_curr + x_(x_curr + dt / 2 * x_(x_curr, y_curr), y_curr + dt / 2 * y_(x_curr, y_curr));
        // y_next = y_next + y_(x_curr + dt / 2 * x_(x_curr, y_curr), y_curr + dt / 2 * y_(x_curr, y_curr));
        x_next = x_curr + dt * x_(x_curr, y_curr);
        y_next = y_curr + dt * y_(x_curr, y_curr);
        x_curr = x_next;
        y_curr = y_next;
        if(abs(x_curr) > 10000 || abs(y_curr) > 10000)
        {
            std::cout << "Разошелся на: " << t_now << "/" << t << std::endl;
            return std::make_pair(0.0, 0.0);
        }
        t_now += dt;
    }
    return std::make_pair(x_curr, y_curr);
}

int main()
{
    std::pair<double, double> res;
    double dt = 0.0001;
    do
    {
        res = f(1, dt);
        dt *= 2;
        // std::cout << res.first << " " << res.second << std::endl;
    } while(res != std::make_pair(0.0, 0.0));
    std::cout << "dt чтобы разошёлся: " << dt << std::endl; 
    return 0;
}