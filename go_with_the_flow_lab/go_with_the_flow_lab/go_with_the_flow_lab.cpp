#include <iostream>
#include <vector>
#include <iomanip>
#include <map>


class HeatFlow {
private:
    std::vector<double> temperatures; // Current temperatures 
    double K;
    int length; // Number of sections in the rod

public:
    // Constructor
    HeatFlow(double initialTemp, int sections, double constantK, const std::map<int, float>& sources) : K(constantK), length(sections) {
        temperatures.resize(sections, initialTemp);
        // Set the heat sources/sinks
        for (const auto& source : sources) {
            int pos = source.first;   // Get the position from the map
            float temp = source.second; // Get the temperature from the map
            if (pos >= 0 && pos < length) {
                temperatures[pos] = temp; // Set to the specified temperature 
            }
        }
    }

    // Method to compute the next time step
    void tick() {
        std::vector<double> newTemperatures = temperatures; // Copy current temperatures

        
        for (int i = 0; i < length; ++i) {
            if (i == 0) {
                // First section, heat source or initial temperature remains the same
                newTemperatures[i] = temperatures[i];
            }
            else {
                double left = (i > 0) ? temperatures[i - 1] : 0; 
                double right = (i < length - 1) ? temperatures[i + 1] : 0; 
                newTemperatures[i] = temperatures[i] + K * (left - 2 * temperatures[i] + right);
            }
        }

        temperatures = newTemperatures; 
    }

    // Method to print the temperatures in a formatted way
    void pretty_print() const {
        // Printing top border
        std::cout << "+";
        for (int i = 0; i < length; ++i) {
            std::cout << std::string(6, '---') << "-+";
        }
        std::cout << std::endl;

        // Printing temperatures centered
        std::cout << "|";
        for (int i = 0; i < length; ++i) {
            // Using a width of 7 to ensure proper spacing and alignment
            std::cout << std::setw(6) << std::setprecision(1) << std::fixed << std::right << temperatures[i] << " |";
        }
        std::cout << std::endl;

        // Printing bottom border
        std::cout << "+";
        for (int i = 0; i < length; ++i) {
            std::cout << std::string(6, '---') << "-+";
        }
        std::cout << std::endl;
    }
};

int main() {
    std::map<int, float> sources_and_sinks;
    sources_and_sinks[0] = 100.0; // Heat source at the first section

    double initial_temperature = 10.0;
    int number_of_sections = 6; // Adjusting to fit the required output
    double K = 0.1;

    HeatFlow h(initial_temperature, number_of_sections, K, sources_and_sinks);

    h.pretty_print(); // Initial state

    h.tick();
    h.pretty_print(); // After first tick

    h.tick();
    h.pretty_print(); // After second tick

    return 0;
}
