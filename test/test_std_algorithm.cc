#include <algorithm>
#include <array>
#include <iostream>
#include <memory>
#include <random>
#include <thread>
#include "gtest/gtest.h"
 
// std::all_of [Test condition on all elements in range](cpp 11)
TEST(Algorithm, all_of) {
  std::array<int, 4> test_arr{1, 3, 5, 7};
  if (std::all_of(test_arr.begin(), test_arr.end(), [](int i){ return i%2; })) {
    std::cout << "all are odd number" << std::endl;
  }
}

// std::any_of [Test if any element in range fulfills condition](cpp 11)
TEST(Algorithm, any_of) {
  std::array<int, 4> test_arr{2, 4, 6, 8};
  if (!std::any_of(test_arr.begin(), test_arr.end(), [](int i){ return i%2; })) {
    std::cout << "all are even number" << std::endl;
  }

  test_arr[2] = 1;
  if (std::any_of(test_arr.begin(), test_arr.end(), [](int i){ return i%2; })) {
    std::cout << "odd number is existed" << std::endl;
  }
}

// std::none_of [Test if no elements fulfill condition](cpp 11)
TEST(Algorithm, none_of) {
  std::array<int, 4> test_arr{2, 4, 6, 8};
  if (std::none_of(test_arr.begin(), test_arr.end(), [](int i){ return i%2; })) {
    std::cout << "all are even number" << std::endl;
  }

  test_arr[2] = 1;
  if (!std::none_of(test_arr.begin(), test_arr.end(), [](int i){ return i%2; })) {
    std::cout << "odd number is existed" << std::endl;
  }
}

// std::for_each [Apply function to range]
TEST(Algorithm, for_each) {
  std::vector<int> test_vec{1, 2, 3, 4};
  std::cout << "test_vec's elements: " << std::endl;
  std::for_each(test_vec.begin(), test_vec.end(), [](int& i){ std::cout<< i << ", "; });
  std::cout << std::endl;
}

// std::find [Find value in range]
TEST(Algorithm, find) {
  std::default_random_engine e;
  std::uniform_int_distribution<unsigned> distrib(1, 20);
  std::vector<int> test_vec;
  for(auto i = 0 ;i != 30; i++){
    test_vec.push_back(distrib(e));
  }
  auto iter = std::find(test_vec.begin(), test_vec.end(), test_vec[20]);
  std::cout << "find *iter : " << *iter << std::endl;
  ASSERT_EQ(*iter, test_vec[iter - test_vec.begin()]);
  iter = std::find(test_vec.begin(), test_vec.end(), 21);
  ASSERT_EQ(iter, test_vec.end());
  std::cout << "can't find unexisted number" << std::endl;
}

// std::find_if [Find element in range]
TEST(Algorithm, find_if) {
  std::default_random_engine e;
  std::uniform_int_distribution<unsigned> distrib(0, 100);
  std::vector<int> test_vec;
  for(auto i = 0; i != 100; i++) {
    test_vec.push_back(distrib(e));
  }
  e.seed(300);
  auto iter = std::find_if(test_vec.begin(), test_vec.end(), [](int i){ return i%2; });
  if(iter != test_vec.end()){
    std::cout << "find num : " << *iter << std::endl;
    ASSERT_EQ(*iter % 2, 1);
  }
}

// std::find_if_not [Find element in range (negative condition)](cpp 11)
TEST(Algorithm, find_if_not) {
  std::default_random_engine e;
  std::uniform_int_distribution<unsigned> distrib(0, 100);
  std::vector<int> test_vec;
  for(auto i = 0; i != 100; i++) {
    test_vec.push_back(distrib(e));
  }
  e.seed(300);
  auto iter = std::find_if_not(test_vec.begin(), test_vec.end(), [](int i){ return i%2; });
  if(iter != test_vec.end()){
    std::cout << "find num : " << *iter << std::endl;
    ASSERT_EQ(*iter % 2, 0);
  }
}

// std::find_end [Find last subsequence in range]
TEST(Algorithm, find_end) {
  std::vector src_vec{1, 2, 3, 6, 1, 2, 3, 2, 3, 4};
  std::array<int, 3> comp_array{1, 2, 3};
  auto iter = std::find_end(src_vec.begin(), src_vec.end(), comp_array.begin(), comp_array.end());
  ASSERT_EQ(iter - src_vec.begin(), 4);
  iter = std::find_end(src_vec.begin(), src_vec.end(), comp_array.begin(), comp_array.end(), [](int i, int j){ return --i == j; }); 
  ASSERT_EQ(iter - src_vec.begin(), 7);
}

// std::find_first_of [Find element from set in range]
// [!] find the iter of src_vec that iter's value equal to compare_array's first value
TEST(Algorithm, find_first_of) {
  std::vector src_vec{1, 2, 4, 6, 1, 2, 3, 2, 3, 4};
  std::array<int, 3> comp_array{1, 2, 3};
  auto iter = std::find_first_of(src_vec.begin(), src_vec.end(), comp_array.begin(), comp_array.end());
  ASSERT_EQ(iter - src_vec.begin(), 0);
  iter = std::find_first_of(src_vec.begin(), src_vec.end(), comp_array.begin(), comp_array.end(), [](int i, int j){ return --i == j; }); 
  ASSERT_EQ(iter - src_vec.begin(), 1);
}

// std::adjacent_find [Find equal adjacent elements in range]
TEST(Algorithm, adjacent_find) {
  std::vector test_vec{1, 2, 3, 4, 4, 7, 9};
  auto iter = std::adjacent_find(test_vec.begin(), test_vec.end());
  ASSERT_EQ(iter - test_vec.begin(), 3);
  iter = std::adjacent_find(test_vec.begin(), test_vec.end(), [](int i, int j){ return i == j - 3; });
  ASSERT_EQ(iter - test_vec.begin(), 4);
}

// std::count [Count appearances of value in range] && std::count_if [Return number of elements in range satisfying condition]
TEST(Algorithm, count_and_count_if) {
  std::vector test_vec{1, 1, 1, 2, 3, 3, 4, 5, 6};
  auto count = std::count(test_vec.begin(), test_vec.end(), 1);
  ASSERT_EQ(count, 3);
  count = std::count_if(test_vec.begin(), test_vec.end(), [](int i){ return i%2; });
  ASSERT_EQ(count, 6);
}

// std::mismatch's return: pair [Return first position where two ranges differ] std::equal [Test whether the elements in two ranges are equal]
TEST(Algorithm, mismatch_and_equal) { 
  std::vector<int> src {1, 2, 3, 4};
  std::vector<int> ref {1, 2, 4, 6};
  auto iter = std::mismatch(src.begin(), src.end(), ref.begin());
  ASSERT_EQ(iter.first - src.begin(), 2);
  ASSERT_EQ(iter.second - ref.begin(), 2);

  ASSERT_FALSE(std::equal(src.begin(), src.end(), ref.begin()));
  ASSERT_TRUE(std::equal(src.begin(), src.end(), ref.begin(), [](int i, int j){ return j - i <= 2; }));
}

// std::is_permutation [compare if the two containers' element are all same even they are in different order](cpp 11)
TEST(Algorithm, is_permutation) {
  std::array<int, 4> src{1, 2, 3, 4};
  std::array<int, 4> ref{2, 1, 3, 4};
  ASSERT_TRUE(std::is_permutation(src.begin(), src.end(), ref.begin()));
  ASSERT_FALSE(std::is_permutation(src.begin(), src.end(), ref.begin(), [](int i, int j){ return i - j > 3; }));
}

// std::serach [Search range for subsequence]
TEST(Algorithm, serach) {
  std::array<int, 8> src{1, 2, 3, 4, 5, 6, 7, 8};
  std::array<int, 4> ref{3, 4, 5, 6};
  auto iter = std::search(src.begin(), src.end(), ref.begin(), ref.end());
  ASSERT_EQ(iter - src.begin(), 2);
  iter = std::search(src.begin(), src.end(), ref.begin(), ref.end(), [](int i, int j){ return j - i <= 2; }); 
  ASSERT_EQ(iter, src.begin());
}

// std::serach_n [Search range for elements]
TEST(Algorithm, serach_n) {
  std::array<int, 8> src{1, 2, 3, 4, 4, 6, 7, 8};
  auto iter = std::search_n(src.begin(), src.end(), 2, 4);
  ASSERT_EQ(iter - src.begin(), 3);
  iter = std::search_n(src.begin(), src.end(), 2, 4, [](int i, int j){ return j - i <= 3; });
  ASSERT_EQ(iter, src.begin());
}

// std::copy && std::copy_n [Copy range of elements]copy_n(cpp 11)
TEST(Algorithm, copy_and_copy_n) {
  std::array<int, 4> src{1,2,3,4};
  std::vector<int> dst(4); // vector must be assigned enough size
  auto iter = std::copy(src.begin(), src.end(), dst.begin());
  for(auto i = 0; i != src.size(); i++) {
    ASSERT_EQ(src.at(i), dst.at(i));
  } 
  ASSERT_EQ(*(iter - 1), 4);
  iter = std::copy_n(src.begin(), 2, dst.begin());
  for(auto i = 0; i != 2; i++) {
    ASSERT_EQ(src.at(i), dst.at(i));
  }
  ASSERT_EQ(*(iter - 1), 2);
}

// std::copy_if [Copy certain elements of range](cpp 11)
TEST(Algorithm, copy_if) {
  std::array<int, 4> src{1,2,3,4};
  std::vector<int> dst(2); // vector must be assigned enough size
  auto iter = std::copy_if(src.begin(), src.end(), dst.begin(), [](int i){ return i%2; });
  for(auto& i : dst){
    ASSERT_EQ(i % 2 , 1);
  }
  ASSERT_EQ(iter, dst.end());
}

// std::copy_backward [Copy range of elements backward]
TEST(Algorithm, copy_backward) {
  std::array<int, 4> src{1,2,3,4};
  std::vector<int> dst(4); // vector must be assigned enough size
  auto iter = std::copy_backward(src.begin(), src.end(), dst.end());
  for(auto i = 0; i != src.size(); i++){
    ASSERT_EQ(src.at(i), dst.at(i));
  }
  ASSERT_EQ(iter, dst.begin());
}

// std::move [Move range of elements](cpp 11)
TEST(Algorithm, move) {
  std::vector<int> src{1, 2, 3, 4};
  std::array<int, 4> dst;
  auto iter = std::move(src.begin(), src.end(), dst.begin());
  for(auto i = 1; i != 4; i++) {
    ASSERT_EQ(i, dst.at(i - 1));
  }
  ASSERT_EQ(iter, dst.end());
  ASSERT_EQ(src.size(), dst.size());
  for(auto i = 1; i != 4; i++) {
    ASSERT_EQ(i, dst.at(i - 1));
  }
  std::cout << "after `std::move`, src is an unspecified but valid state" << std::endl;
}

// std::move_backward [Move range of elements backward](cpp 11)
TEST(Algorithm, move_backward) {
  std::vector<int> src{1, 2, 3, 4};
  std::array<int, 4> dst;
  auto iter = std::move_backward(src.begin(), src.end(), dst.end());
  for(auto i = 1; i != 4; i++) {
    ASSERT_EQ(i, dst.at(i - 1));
  }
  ASSERT_EQ(iter, dst.begin());
  ASSERT_EQ(src.size(), dst.size());
  for(auto i = 1; i != 4; i++) {
    ASSERT_EQ(i, dst.at(i - 1));
  }
  std::cout << "after `std::move`, src is an unspecified but valid state" << std::endl;
}

// std::swap_ranges [Exchange values of two ranges]
TEST(Algorithm, swap_ranges) {
  std::array<int, 4> src{1, 2, 3, 4};
  auto tmp_src = src;
  std::vector<int> dst(4);
  std::swap_ranges(src.begin(), src.end(), dst.begin());
  for(auto i : src) {
    ASSERT_EQ(i, 0);
  }
  for(auto i = 0; i != 4; i++) {
    ASSERT_EQ(tmp_src.at(i), dst.at(i));
  }
}

// std::iter_swap [Exchange values of objects pointed to by two iterators]
TEST(Algorithm, iter_swap) {
  std::array<int, 4> src{1, 2, 3, 4};
  std::array<int, 4> src_cmp{3, 4, 1, 2};
  std::iter_swap(src.begin(), src.begin() + 2);
  std::iter_swap(src.begin() + 1, src.begin() + 3);
  ASSERT_EQ(src, src_cmp);
}

// std::transform [Transform range]
TEST(Algorithm, transform) {  
  std::array<int, 4> src{1, 2, 3, 4};
  std::vector<int> dst(4);
  //unary op
  auto iter = std::transform(src.begin(), src.end(), dst.begin(), [](int i){ return i * 2; });
  ASSERT_EQ(iter, dst.end());
  for(auto i = 0; i != 4; i++) {
    ASSERT_EQ(dst.at(i), src.at(i) * 2);
  }
  //binary op
  std::vector<int> dst_binary(4);
  iter = std::transform(src.begin(), src.end(), dst.begin(), dst_binary.begin(), std::plus<int>());
  ASSERT_EQ(iter, dst_binary.end());
  for(auto i = 0; i != 4; i++) {
    ASSERT_EQ(dst_binary.at(i), src.at(i) * 3);
  }
}

// std::replace && std::replace_if [Replace value in range]
TEST(Algorithm, replace_and_replace_if) {
  std::array<int, 4> src{256, 512, 1024, 1024};
  std::replace(src.begin(), src.end() - 1, 1024, 2048);
  ASSERT_EQ(src.at(2), 2048);
  ASSERT_EQ(src.at(3), 1024);

  std::replace_if(src.begin(), src.end(), [](int i){ return i != 1024; }, 1024);
  for(auto i : src) {
    ASSERT_EQ(i, 1024);
  }
}

// std::replace_copy && std::replace_copy_if [Copy range replacing value]
TEST(Algorithm, repalce_copy_and_replace_copy_if) {
  std::array<int, 4> src{256, 512, 1024, 2048};
  std::array<int, 4> src_tmp = src;
  std::vector<int> dst(4);
  std::replace_copy(src.begin(), src.end(), dst.begin(), 256, 512);
  ASSERT_EQ(dst.at(0), 512);
  ASSERT_EQ(src, src_tmp);

  std::replace_copy_if(src.begin(), src.end(), dst.begin(), [](int i){ return i != 1024; }, 1024);
  for(auto i : dst) {
    ASSERT_EQ(i, 1024);  
  }
  ASSERT_EQ(src, src_tmp);
}

// std::fill && std::fill_n [Fill range with value]
TEST(Algorithm, fill_and_fill_n) {
  std::array<int, 4> arr;
  std::fill(arr.begin(), arr.end(), 3);
  for(auto i : arr) {
    ASSERT_EQ(i, 3);
  }
  std::fill_n(arr.begin(), 2, 1); 
  ASSERT_EQ(arr.at(0), 1);
  ASSERT_EQ(arr.at(3), 3);
}

// std::generate && std::generate_n [Generate values for range with function]
TEST(Algorithm, generate_and_generate_n) {
  std::array<int, 4> arr;
  std::generate(arr.begin(), arr.end(), [](){ return std::rand(); });
  std::cout << "std::generated: ";
  for(auto i : arr) {
    std::cout << i <<", ";
  }  
  std::cout << std::endl;
  std::generate_n(arr.begin(), 2, [](){ return std::rand(); });
}

// std::remove && std::remove_if [Remove value from range]
TEST(Algorithm, remove) {
  std::vector<int> arr{1, 1, 2, 3, 4};
  auto removed_value = 1;
  auto left_num = std::count_if(arr.begin(), arr.end(), [&removed_value](const int& i){ return i != removed_value; });
  auto iter = std::remove(arr.begin(), arr.end(), removed_value); // this function has a nodiscard property
  // now arr:[2, 3, 4, 3, 4], real format is [left1, left2, ..leftn, ?, ?, ..?], only the left values make sense 
  ASSERT_EQ(iter, arr.begin() + left_num); 
  // the container's size doesn't change
  ASSERT_EQ(arr.size(), 5);

  removed_value = 3;
  iter = std::remove_if(arr.begin(), arr.end(), [&removed_value](const int& i){ return i == removed_value; });
  // now arr:[2, 4, 4, 3, 4], [o, o, o, x, x]
  ASSERT_EQ(iter, arr.begin() + 3);
}

// std::remove_copy && std::remove_copy_if [Copy range removing value]
TEST(Algorithm, remove_copy_and_remove_copy_if) {
  std::array<int, 5> src{7, 2, 7, 2, 2};
  std::vector<int> dst(src.size());
  auto left_num  = std::count_if(src.begin(), src.end(), [](int& i){ return i != 7;});
  auto iter = std::remove_copy(src.begin(), src.end(), dst.begin(), 7);
  ASSERT_EQ(iter, dst.begin() + left_num);
  for(auto i = 0; i != left_num; i++) {
    ASSERT_EQ(dst.at(i), 2);
  }

  dst.clear();
  dst.resize(src.size());
  iter = std::remove_copy_if(src.begin(), src.end(), dst.begin(), [](int& i){ return i == 7; });
  ASSERT_EQ(iter, dst.begin() + left_num);
  for(auto i = 0; i != left_num; i++) {
    ASSERT_EQ(dst.at(i), 2);
  }
}

// std::unique && std::unique_copy [Remove `consecutive` duplicates in range]
TEST(Algorithm, unique_and_unqiue_copy) {
  std::array<int,4> arr{1, 2, 1, 3};
  auto arry_tmp = arr;
  auto iter = std::unique(arr.begin(), arr.end());
  ASSERT_EQ(iter, arr.end());
  ASSERT_EQ(arr, arry_tmp);
  arr.swap(std::array<int,4>{1, 1, 1, 3});
  iter = std::unique(arr.begin(), arr.end()); // arr:[1, 3, 1, 3] nodiscard
  ASSERT_EQ(iter, arr.begin() + 2);

  std::array<int, 6> arr2{1, 1, 1, 2, 1, 3};
  std::vector<int> result(4);
  auto iter2 = std::unique_copy(arr2.begin(), arr2.end(), result.begin()); // result: [1, 2, 1, 3]
  ASSERT_EQ(iter2, result.end());
}

// std::reverse && std::reverse_copy [Reverse range]
TEST(Algorithm, reverse_and_reverse_copy) {
  std::array<int,6> arr{1, 2, 3, 4, 5, 6};
  auto arr_tmp = arr;
  std::reverse(arr.begin(), arr.end());
  for(auto i = 0; i != arr.size() / 2; i++) {
    ASSERT_EQ(arr_tmp[i], arr[arr.size() - i - 1]);
  }
  
  std::array<int, 6> dst{};
  auto iter = std::reverse_copy(arr.begin(), arr.end(), dst.begin());
  ASSERT_EQ(iter, dst.end());
  ASSERT_EQ(arr_tmp, dst);
}

// std::rotate && std::rotate_copy [Rotate left the elements in range]
TEST(Algorithm, rotate_and_rotate_copy) {
  std::array<int, 8> arr{1, 2, 3, 4, 5, 6, 7, 8};
  auto tmp_arr = arr;
  auto iter = std::rotate(arr.begin(), arr.begin() + 3, arr.end());
  ASSERT_EQ(iter, arr.begin() + 5);

  std::array<int, 8> dst{};
  iter = std::rotate_copy(arr.begin(), arr.begin() + 3, arr.end(), dst.begin());
  ASSERT_EQ(iter, dst.end());
}

// std::random_shuffle(cpp98) && std::shuffle [Randomly rearrange elements in range(using generator)](cpp11)
TEST(Algorithm, shuffle) {
  std::array<int, 6> arr{1, 2, 3, 4, 5, 6};
  auto tmp_arr = arr;
  std::shuffle(arr.begin(), arr.end(), std::default_random_engine(100));
  ASSERT_TRUE(std::is_permutation(arr.begin(), arr.end(), tmp_arr.begin()));
}