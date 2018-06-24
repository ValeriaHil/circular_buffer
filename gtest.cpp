#include "gtest/gtest.h"
# include <bits/stdc++.h>
# include "circular_buffer.h"
#include "counted.h"

using container = circ_buff<counted>;

template<typename C, typename T>
void mass_push_back(C &c, std::initializer_list<T> elems) {
    for (T const &e : elems)
        c.push_back(e);
}

template<typename C, typename T>
void mass_push_front(C &c, std::initializer_list<T> elems) {
    for (T const &e : elems)
        c.push_front(e);
}

template<typename It, typename T>
void expect_eq(It i1, It e1, std::initializer_list<T> elems) {
    auto i2 = elems.begin(), e2 = elems.end();

    for (;;) {
        if (i1 == e1 || i2 == e2) {
            EXPECT_TRUE(i1 == e1 && i2 == e2);
            break;
        }

        EXPECT_EQ(*i2, *i1);
        ++i1;
        ++i2;
    }
}

template<typename C, typename T>
void expect_eq(C const &c, std::initializer_list<T> elems) {
    expect_eq(c.begin(), c.end(), elems);
}

template<typename C, typename T>
void expect_reverse_eq(C const &c, std::initializer_list<T> elems) {
    expect_eq(c.rbegin(), c.rend(), elems);
}

TEST(correctness, default_ctor) {
    counted::no_new_instances_guard g;

    container c;
    g.expect_no_instances();
}

TEST(correctness, end_iterator) {
    counted::no_new_instances_guard g;

    container c;
    container::iterator i = c.end();

    EXPECT_EQ(c.begin(), i);
}


TEST(correctness, back_front) {
    counted::no_new_instances_guard g;

    container c;
//    mass_push_back(c, {1, 2});
    c.push_back(1);
    c.push_back(2);
    auto x = c.front();
    EXPECT_EQ(1, c.front());
    //EXPECT_EQ(1, std::as_const(c).front());
    //EXPECT_EQ(2, c.back());
    //EXPECT_EQ(2, std::as_const(c).back());
}

TEST(correctness, back_front_ref) {
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4, 5});
    c.front() = 6;
    c.back() = 7;
    expect_eq(c, {6, 2, 3, 4, 7});
}

TEST(correctness, back_front_cref) {
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4, 5});
    EXPECT_TRUE(&c.front() == &std::as_const(c).front());
    EXPECT_TRUE(&c.back() == &std::as_const(c).back());
}

void magic(counted &c) {
    c = 42;
}

void magic(counted const &c) {}

TEST(correctness, back_front_ncref) {
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4, 5});
    magic(std::as_const(c).front());
    magic(std::as_const(c).back());

    expect_eq(c, {1, 2, 3, 4, 5});
}

TEST(correctness, push_back) {
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4});
    expect_eq(c, {1, 2, 3, 4});
}

TEST(correctness, copy_ctor) {
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4});
    container c2 = c;
    expect_eq(c2, {1, 2, 3, 4});
}

TEST(correctness, copy_ctor_empty) {
    counted::no_new_instances_guard g;

    container c;
    container c2 = c;
    EXPECT_TRUE(c2.empty());
}

TEST(correctness, assignment_operator) {
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4});
    container c2;
    mass_push_back(c2, {5, 6, 7, 8});
    c2 = c;
    expect_eq(c2, {1, 2, 3, 4});
}

TEST(correctness, self_assignment) {
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4});
    c = c;
    expect_eq(c, {1, 2, 3, 4});
}

TEST(correctness, pop_back) {
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4});
    c.pop_back();
    expect_eq(c, {1, 2, 3});
    c.pop_back();
    expect_eq(c, {1, 2});
    c.pop_back();
    expect_eq(c, {1});
    c.pop_back();
    EXPECT_TRUE(c.empty());
}

TEST(correctness, push_front) {
    counted::no_new_instances_guard g;

    container c;
    mass_push_front(c, {1, 2, 3, 4});
    expect_eq(c, {4, 3, 2, 1});
}

TEST(correctness, empty) {
    counted::no_new_instances_guard g;

    container c;
    EXPECT_EQ(c.begin(), c.end());
    EXPECT_TRUE(c.empty());
    c.push_back(1);
    EXPECT_NE(c.begin(), c.end());
    EXPECT_FALSE(c.empty());
    c.pop_front();
    EXPECT_EQ(c.begin(), c.end());
    EXPECT_TRUE(c.empty());
}

TEST(correctness, reverse_iterators) {
    counted::no_new_instances_guard g;

    container c;
    mass_push_front(c, {1, 2, 3, 4});
    expect_reverse_eq(c, {1, 2, 3, 4});

    EXPECT_EQ(1, *c.rbegin());
    EXPECT_EQ(2, *std::next(c.rbegin()));
    EXPECT_EQ(4, *std::prev(c.rend()));
}

TEST(correctness, iterator_conversions) {
    counted::no_new_instances_guard g;

    container c;
    container::const_iterator i1 = c.begin();
    container::iterator i2 = c.end();
    EXPECT_TRUE(i1 == i1);
    EXPECT_TRUE(i1 == i2);
    EXPECT_TRUE(i2 == i1);
    EXPECT_TRUE(i2 == i2);
    EXPECT_FALSE(i1 != i1);
    EXPECT_FALSE(i1 != i2);
    EXPECT_FALSE(i2 != i1);
    EXPECT_FALSE(i2 != i2);

    EXPECT_TRUE(std::as_const(i1) == i1);
    EXPECT_TRUE(std::as_const(i1) == i2);
    EXPECT_TRUE(std::as_const(i2) == i1);
    EXPECT_TRUE(std::as_const(i2) == i2);
    EXPECT_FALSE(std::as_const(i1) != i1);
    EXPECT_FALSE(std::as_const(i1) != i2);
    EXPECT_FALSE(std::as_const(i2) != i1);
    EXPECT_FALSE(std::as_const(i2) != i2);

    EXPECT_TRUE(i1 == std::as_const(i1));
    EXPECT_TRUE(i1 == std::as_const(i2));
    EXPECT_TRUE(i2 == std::as_const(i1));
    EXPECT_TRUE(i2 == std::as_const(i2));
    EXPECT_FALSE(i1 != std::as_const(i1));
    EXPECT_FALSE(i1 != std::as_const(i2));
    EXPECT_FALSE(i2 != std::as_const(i1));
    EXPECT_FALSE(i2 != std::as_const(i2));

    EXPECT_TRUE(std::as_const(i1) == std::as_const(i1));
    EXPECT_TRUE(std::as_const(i1) == std::as_const(i2));
    EXPECT_TRUE(std::as_const(i2) == std::as_const(i1));
    EXPECT_TRUE(std::as_const(i2) == std::as_const(i2));
    EXPECT_FALSE(std::as_const(i1) != std::as_const(i1));
    EXPECT_FALSE(std::as_const(i1) != std::as_const(i2));
    EXPECT_FALSE(std::as_const(i2) != std::as_const(i1));
    EXPECT_FALSE(std::as_const(i2) != std::as_const(i2));
}

TEST(correctness, iterators_postfix) {
    counted::no_new_instances_guard g;

    container s;
    mass_push_back(s, {1, 2, 3});
    container::iterator i = s.begin();
    EXPECT_EQ(1, *i);
    container::iterator j = i++;
    EXPECT_EQ(2, *i);
    EXPECT_EQ(1, *j);
    j = i++;
    EXPECT_EQ(3, *i);
    EXPECT_EQ(2, *j);
    j = i++;
    EXPECT_EQ(s.end(), i);
    EXPECT_EQ(3, *j);
    j = i--;
    EXPECT_EQ(3, *i);
    EXPECT_EQ(s.end(), j);
}

TEST(correctness, const_iterators_postfix) {
    counted::no_new_instances_guard g;

    container s;
    mass_push_back(s, {1, 2, 3});
    container::const_iterator i = s.begin();
    EXPECT_EQ(1, *i);
    container::const_iterator j = i++;
    EXPECT_EQ(2, *i);
    EXPECT_EQ(1, *j);
    j = i++;
    EXPECT_EQ(3, *i);
    EXPECT_EQ(2, *j);
    j = i++;
    EXPECT_TRUE(i == s.end());
    EXPECT_EQ(3, *j);
    j = i--;
    EXPECT_EQ(3, *i);
    EXPECT_TRUE(j == s.end());
}

TEST(correctness, insert_begin) {
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4});
    c.insert(c.begin(), 0);
    expect_eq(c, {0, 1, 2, 3, 4});
}

TEST(correctness, insert_middle) {
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4});
    c.insert(std::next(c.begin(), 2), 5);
    expect_eq(c, {1, 2, 5, 3, 4});
}

TEST(correctness, insert_end) {
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4});
    c.insert(c.end(), 5);
    expect_eq(c, {1, 2, 3, 4, 5});
}

TEST(correctness, insert_return_value) {
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4});

    container::iterator i = c.insert(std::next(c.begin(), 2), 5);
    EXPECT_EQ(5, *i);
    EXPECT_EQ(2, *std::prev(i));
    EXPECT_EQ(3, *std::next(i));
}

TEST(correctness, erase_begin) {
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4});
    c.erase(c.begin());
    expect_eq(c, {2, 3, 4});
}

TEST(correctness, erase_middle) {
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4});
    c.erase(std::next(c.begin(), 2));
    expect_eq(c, {1, 2, 4});
}

TEST(correctness, erase_end) {
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4});
    c.erase(std::prev(c.end()));
    expect_eq(c, {1, 2, 3});
}

TEST(correctness, erase_return_value) {
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4});
    container::iterator i = c.erase(std::next(c.begin()));
    EXPECT_EQ(3, *i);
    i = c.erase(i);
    EXPECT_EQ(4, *i);
}

TEST(correctness, swap) {
    counted::no_new_instances_guard g;

    container c1, c2;
    mass_push_back(c1, {1, 2, 3, 4});
    mass_push_back(c2, {5, 6, 7, 8});
    swap(c1, c2);
    expect_eq(c1, {5, 6, 7, 8});
    expect_eq(c2, {1, 2, 3, 4});
}

TEST(correctness, swap_self) {
    counted::no_new_instances_guard g;

    container c1;
    mass_push_back(c1, {1, 2, 3, 4});
    swap(c1, c1);
}

TEST(correctness, swap_empty) {
    counted::no_new_instances_guard g;

    container c1, c2;
    mass_push_back(c1, {1, 2, 3, 4});
    swap(c1, c2);
    EXPECT_TRUE(c1.empty());
    expect_eq(c2, {1, 2, 3, 4});
    swap(c1, c2);
    expect_eq(c1, {1, 2, 3, 4});
    EXPECT_TRUE(c2.empty());
}

TEST(correctness, swap_empty_empty) {
    counted::no_new_instances_guard g;

    container c1, c2;
    swap(c1, c2);
}

TEST(correctness, swap_empty_self) {
    counted::no_new_instances_guard g;

    container c1;
    swap(c1, c1);
}

TEST(correctness, clear_empty) {
    counted::no_new_instances_guard g;

    container c;
    c.clear();
    EXPECT_TRUE(c.empty());
    c.clear();
    EXPECT_TRUE(c.empty());
    c.clear();
    EXPECT_TRUE(c.empty());
}

TEST(correctness, clear) {
    counted::no_new_instances_guard g;

    container c;
    mass_push_back(c, {1, 2, 3, 4});
    c.clear();
    EXPECT_TRUE(c.empty());
    EXPECT_EQ(c.begin(), c.end());
    mass_push_back(c, {5, 6, 7, 8});
    expect_eq(c, {5, 6, 7, 8});
}












//TEST(correctness, test1_easy) {
//    circ_buff<int> a;
//    for (int i = 0; i < 100; i++) {
//        a.push_back(i);
//    }
//
//    bool wr = true;
//    for (int i = 0; i < 100; i++) {
//        if (a.front() != i) {
//            wr = false;
//            break;
//        }
//        a.pop_front();
//    }
//    EXPECT_TRUE(wr);
//}
//
//TEST(correctness, test1_hard) {
//    circ_buff<int> a;
//    for (int i = 0; i < 100000; i++) {
//        a.push_back(i);
//    }
//
//    bool wr = true;
//    for (int i = 0; i < 100000; i++) {
//        if (a.front() != i) {
//            wr = false;
//            break;
//        }
//        a.pop_front();
//    }
//    EXPECT_TRUE(wr);
//}
//
//TEST(correctness, test2_easy) {
//    circ_buff<int> a;
//    for (int i = 0; i < 100; i++) {
//        a.push_back(i);
//    }
//
//    bool wr = true;
//    for (int i = 99; i >= 0; i--) {
//        if (a.back() != i) {
//            wr = false;
//            break;
//        }
//        a.pop_back();
//    }
//    EXPECT_TRUE(wr);
//}
//
//TEST(correctness, test2_hard) {
//    circ_buff<int> a;
//    for (int i = 0; i < 100000; i++) {
//        a.push_back(i);
//    }
//
//    bool wr = true;
//    for (int i = 99999; i >= 0; i--) {
//        if (a.back() != i) {
//            wr = false;
//            break;
//        }
//        a.pop_back();
//    }
//    EXPECT_TRUE(wr);
//}
//
//TEST(correctness, test3_easy) {
//    circ_buff<int> a;
//    for (int i = 0; i < 100; i++) {
//        a.push_back(i);
//        a.push_front(i);
//    }
//
//    bool wr = true;
//    for (int i = 99; i >= 0; i--) {
//        if (a.back() != i) {
//            wr = false;
//            break;
//        }
//        a.pop_back();
//        if (a.front() != i) {
//            wr = false;
//            break;
//        }
//        a.pop_front();
//    }
//    EXPECT_TRUE(wr);
//}
//
//TEST(correctness, test3_hard) {
//    circ_buff<int> a;
//    for (int i = 0; i < 100000; i++) {
//        a.push_back(i);
//        a.push_front(i);
//    }
//
//    bool wr = true;
//    for (int i = 99999; i >= 0; i--) {
//        if (a.back() != i) {
//            wr = false;
//            break;
//        }
//        a.pop_back();
//        if (a.front() != i) {
//            wr = false;
//            break;
//        }
//        a.pop_front();
//    }
//    EXPECT_TRUE(wr);
//}
//
//TEST(correctness, erase_easy) {
//    circ_buff<int> a;
//    for (int i = 0; i < 100; i++) {
//        a.push_back(i);
//    }
//
//    bool wr = true;
//    circ_buff<int>::const_iterator it = a.begin();
//    it += 50;
//    for (int i = 50; i < 60; i++) {
//        a.erase(it);
//    }
//    for (int i = 0; i < 50; i++) {
//        if (a.front() != i) {
//            wr = false;
//            break;
//        }
//        a.pop_front();
//    }
//    for (int i = 60; i < 100; i++) {
//        if (a.front() != i) {
//            wr = false;
//            break;
//        }
//        a.pop_front();
//    }
//    EXPECT_TRUE(wr);
//}
//
//TEST(correctness, erase_hard) {
//    circ_buff<int> a;
//    for (int i = 0; i < 10000; i++) {
//        a.push_back(i);
//    }
//
//    bool wr = true;
//    circ_buff<int>::const_iterator it = a.begin();
//    it += 5000;
//    for (int i = 5000; i < 6000; i++) {
//        a.erase(it);
//    }
//    for (int i = 0; i < 5000; i++) {
//        if (a.front() != i) {
//            wr = false;
//            break;
//        }
//        a.pop_front();
//    }
//    for (int i = 6000; i < 10000; i++) {
//        if (a.front() != i) {
//            wr = false;
//            break;
//        }
//        a.pop_front();
//    }
//    EXPECT_TRUE(wr);
//}
//
//TEST(correctness, insert_easy) {
//    circ_buff<int> a;
//    bool wr = true;
//    for (int i = 0; i < 100; i++) {
//        a.push_back(i);
//    }
//
//    circ_buff<int>::const_iterator it = a.begin();
//    for (int i = 0; i < 100; i++) {
//        it = a.begin();
//        it += i * 2;
//        a.insert(it, i);
//
//    }
//    for (int i = 0; i < 200; i++) {
//        if (i / 2 != a.front()) {
//            wr = false;
//        }
//        a.pop_front();
//    }
//    EXPECT_TRUE(wr);
//}

//TEST(correctness, insert_hard) {
//    circ_buff<int> a;
//    bool wr = true;
//    for (int i = 0; i < 10000; i++) {
//        a.push_back(i);
//    }
//
//    circ_buff<int>::iterator it = a.begin();
//    for (int i = 0; i < 10000; i++) {
//        it = a.begin();
//        it += i * 2;
//
//        a.insert(circ_buff<int>::const_iterator(it), i);
//
//    }
//    for (int i = 0; i < 20000; i++) {
//        if (i / 2 != a.front()) {
//            wr = false;
//        }
//        a.pop_front();
//    }
//    EXPECT_TRUE(wr);
//}