#include <iostream>
#include <cassert>
#include <utility>
#include "mydeque.hpp"

int main() {
    MyDeque<int> dq(4);

    assert(dq.empty());
    assert(!dq.full());
    assert(dq.size() == 0);
    assert(dq.max_size() == 4);

    dq.push_back(11);
    dq.push_back(22);
    dq.push_front(33);
    dq.push_front(44);

    assert(dq.full());
    assert(dq.size() == 4);
    assert(dq.front() == 44);
    assert(dq.back() == 22);
    assert(dq[0] == 44 && dq[1] == 33 && dq[2] == 11 && dq[3] == 22);
    assert(dq.index(11) == 2);
    assert(dq.index(99) == -1);

    dq.pop_front();
    assert(dq.front() == 33);
    assert(dq.size() == 3);

    dq.pop_back();
    assert(dq.back() == 11);
    assert(dq.size() == 2);

    dq.insert(1, 55);
    assert(dq.size() == 3);
    assert(dq[0] == 33 && dq[1] == 55 && dq[2] == 11);

    dq.erase(1);
    assert(dq.size() == 2);
    assert(dq[0] == 33 && dq[1] == 11);

    MyDeque<int> dq_copy(dq);
    assert(dq_copy.size() == 2);
    assert(dq_copy[0] == 33 && dq_copy[1] == 11);

    MyDeque<int> dq_assigned(2);
    dq_assigned = dq_copy;
    assert(dq_assigned.size() == 2);
    assert(dq_assigned[0] == 33 && dq_assigned[1] == 11);

    MyDeque<int> dq_moved(std::move(dq_copy));
    assert(dq_moved.size() == 2);
    assert(dq_moved[0] == 33 && dq_moved[1] == 11);
    assert(dq_copy.empty());
    assert(dq_copy.max_size() == 0);

    MyDeque<int> dq_move_assigned(2);
    dq_move_assigned = std::move(dq_moved);
    assert(dq_move_assigned.size() == 2);
    assert(dq_move_assigned[0] == 33 && dq_move_assigned[1] == 11);
    assert(dq_moved.empty());
    assert(dq_moved.max_size() == 0);

    dq.clear();
    assert(dq.empty());
    assert(dq.size() == 0);

    return 0;
}
