
#include <iostream>
#include <boost/numeric/odeint.hpp>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;
using namespace boost::numeric::odeint;

// Define the constants
double K = 1.0;
double alpha = 1.0;
double gamma1 = 1.0;
double gamma2 = 1.0;
double b = 1.0;
double gamma3 = 1.0;

// Define the state type (4 variables)
typedef std::vector<double> state_type;

// The system of ODEs
void ode_system(const state_type &y, state_type &dydt, double t)
{
    // y[0] = y1, y[1] = y2, y[2] = y3, y[3] = y4 (algebraic variable)
    dydt[0] = K - alpha * y[0] * y[1] - gamma1 * y[0];
    dydt[1] = K - alpha * y[0] * y[1] - gamma2 * y[1];
    dydt[2] = b * y[0] - y[2] * gamma3;
    dydt[3] = 0; // Algebraic equation
}

// The observer function
struct push_back_state_and_time
{
    std::vector<state_type> &m_states;
    std::vector<double> &m_times;

    push_back_state_and_time(std::vector<state_type> &states, std::vector<double> &times)
            : m_states(states), m_times(times) {}

    void operator()(const state_type &x, double t)
    {
        m_states.push_back(x);
        m_times.push_back(t);
    }
};

int main()
{
    // Initial conditions
    state_type y(4);
    y[0] = 1.0; // Initial y1
    y[1] = 1.0; // Initial y2
    y[2] = 1.0; // Initial y3
    y[3] = 1.0; // Initial y4, algebraic variable

    // Integration time
    double t0 = 0.0;
    double t_f = 100.0;

    // Vectors to store the solution
    std::vector<state_type> x_vec;
    std::vector<double> times;

    // Integrate the system
    size_t steps = integrate(ode_system, y, t0, t_f, 0.1, push_back_state_and_time(x_vec, times));

    // Save the results to a file
    std::ofstream file("ode_results.csv");
    file << "time,y1,y2,y3,y4\n";
    for (size_t i = 0; i <= steps; ++i)
    {
        file << times[i] << "," << x_vec[i][0] << "," << x_vec[i][1] << "," << x_vec[i][2] << "," << x_vec[i][3] << "\n";
    }
    file.close();

    return 0;
}
