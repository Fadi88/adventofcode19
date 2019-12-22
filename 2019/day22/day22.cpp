#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <chrono>
#include <set>
#include <map>
#include <queue>
#include <numeric>


class timer {
public:
    timer(std::string point) : m_point{ point } {
        m_start_point = std::chrono::high_resolution_clock::now();
    }

    ~timer() {
        auto endclock = std::chrono::high_resolution_clock::now();
        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_start_point).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endclock).time_since_epoch().count();

        auto duration = end - start;
        double ms = duration * 0.001;

        std::cout << "time used by : " << m_point << " was : " << ms << " ms" << std::endl;

    }

private:
    std::string m_point;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_start_point;
};


void task_1(std::vector<std::string> p_ops) {

    std::vector<uint16_t> deck(10007);

    std::iota(deck.begin(), deck.end(), 0);
    for (auto& op : p_ops) {
        if (op.find("new stack") != op.npos) {
            std::reverse(deck.begin(), deck.end());
        }
        else if (op.find("increment") != op.npos) {
            std::stringstream op_stream{ op.substr(op.rfind(' ')) };
            int16_t value;
            op_stream >> value;

            std::vector<uint16_t> tmp_vec(deck.size());
            for (uint16_t idx{}; idx < deck.size(); ++idx) {
                tmp_vec[(idx * value) % tmp_vec.size()] = deck[idx];
            }
            deck = tmp_vec;
        }
        else if (op.find("cut") != op.npos) {
            std::stringstream op_stream{ op.substr(op.rfind(' ')) };
            int16_t value;
            op_stream >> value;

            std::vector<uint16_t> tmp_vec(deck.size());
            if (value > 0) {
                std::copy(deck.begin() + value, deck.end(), tmp_vec.begin());
                std::copy(deck.begin(), deck.begin() + value, tmp_vec.begin() + deck.size() - value);
            }
            else {
                value = std::abs(value);
                std::copy(deck.end() - value, deck.end(), tmp_vec.begin());
                std::copy(deck.begin(), deck.end() - value, tmp_vec.begin() + value);
            }
            deck = tmp_vec;
        }
    }
    std::cout << "task 1 position is : " << std::find(deck.begin(), deck.end(), 2019) - deck.begin() << std::endl;
}

std::pair<int32_t,int32_t> task_1_2(std::vector<std::string> p_ops) {

    int32_t coef{ 1 }, offset{ 0 };
    int16_t deck_size{ 10007 };

    for (auto& op : p_ops) {
        if (op.find("new stack") != op.npos) {
            coef = (deck_size - coef) % deck_size;
            offset = (-offset -1)% deck_size;
        }
        else if (op.find("increment") != op.npos) {
            std::stringstream op_stream{ op.substr(op.rfind(' ')) };
            int16_t value;
            op_stream >> value;

            coef = (coef * value) % deck_size;
            offset = (offset * value) % deck_size;

        }
        else if (op.find("cut") != op.npos) {
            std::stringstream op_stream{ op.substr(op.rfind(' ')) };
            int16_t value;
            op_stream >> value;

            offset = (offset - value + deck_size) % deck_size;
        }
    }

    std::cout << "task 1 improved : " << (2019 * coef + offset) % deck_size << std::endl;
    return { coef , offset };
}

void task_2(std::pair<int32_t, int32_t> p_ops) {

    int64_t len{ 119315717514047 };
    int64_t rep{ 101741582076661 };

    uint16_t pos{ 2020 };


}

int main() {

    std::ifstream input_fd{ "input\\day22_input.txt" };

    std::string tmp;
    std::vector<std::string> ops;
    while (std::getline(input_fd, tmp)) {
        ops.push_back(tmp);
    }

    std::pair<int32_t, int32_t> reduced_op;

    {
        timer t1("task 1");
        task_1(ops);
    }

    {
        timer t1("task 1 improved");
        reduced_op = task_1_2(ops);
    }

    {
        timer t1("task 2");
        task_2(reduced_op);
    }

    return 0;
}
