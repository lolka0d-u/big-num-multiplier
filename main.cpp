/*
 * Name: Serhii Nikolaiev
 * Date: 28.10.2024
 */
#include <ranges>
#include <iostream>
#include <algorithm>
#include <string>
#include <deque>
#include <cctype>

const int MAX_INPUT_LENGTH = 30;

bool containsOnlyDigits(const std::string& str) {
    return std::ranges::all_of(str, isdigit);
}

// takes first digit of `b` and multiplies over all digits of `a` and multiplies by 10**n, n is the index of the number
// than takes next digit of `b` and multiplies over all digits of `a` also multiplies by 10**(++n)
std::string multiplyStrings(const std::string& a, const std::string& b) noexcept {
    if (a == "0" || b == "0") return "0";

    const std::size_t len_a = a.length();
    const std::size_t len_b = b.length();

    std::size_t counter = len_a + len_b - 1; // sets to the last item

    std::deque<int> result_digits(len_a + len_b, 0);

    for (std::ptrdiff_t j = len_b - 1; j >= 0; --j) {
        std::size_t pos = counter;
        for (std::ptrdiff_t i = len_a - 1; i >= 0; --i) {
            int digit_a = a[i] - '0';
            int digit_b = b[j] - '0';
            int product = digit_a * digit_b;

            int carry = product + result_digits[pos];

            result_digits[pos - 1] += carry / 10;
            result_digits[pos] = carry % 10;
            --pos;
        }
        --counter;
    }

    std::string c;
    // remove first 0 if exists
    if (result_digits[0] == 0) {
        result_digits.pop_front();
    }
    c.reserve(result_digits.size());

    std::ranges::transform(result_digits, std::back_inserter(c), [](const int digit) {
        return static_cast<char>(digit + '0');
    });

    return c;
}

int main()
{
    std::string num1;
    std::string num2;

    bool continue_input = true;
    while (continue_input) {
        std::cout << "Enter two numbers: ";
        std::cin >> num1 >> num2;

        if (std::ranges::all_of(std::array{num1, num2}, [](const std::string& num) {
            return num.length() <= MAX_INPUT_LENGTH && containsOnlyDigits(num);})) {
            std::cout << "The result of " << num1 << " * " << num2 << " = " << multiplyStrings(num1, num2) << std::endl;
        }
        else {
            std::cout << "Invalid input. Ensure numbers are up to 30 digits and contain only digits." << std::endl;
        }

        std::cout << "Do you want to continue (1/0): ";
        std::cin >> continue_input;
    }
}
