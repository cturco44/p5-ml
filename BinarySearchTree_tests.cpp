// Project UID db1f506d06d84ab787baf250c265e24e

#include "BinarySearchTree.h"
#include "unit_test_framework.h"

using namespace std;

//Compares tree to sorted array;
static bool compare_tree_to_array_int(vector<int> vec, BinarySearchTree<int> *tree) {
    if(vec.size() != tree->size()) {
        return false;
    }
    sort(vec.begin(), vec.end());
    auto itv = vec.begin();
    for(auto i : *tree) {
        if(i != *itv) {
            return false;
        }
        ++itv;
    }
    return true;
}
TEST(test_stub) {
    // Add your tests here
    ASSERT_TRUE(true);
}
TEST(empty_impl) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
    tree.insert(7);
    ASSERT_TRUE(!tree.empty());
}
TEST(insert_impl) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
    tree.insert(5);
    tree.insert(4);
    tree.insert(8);
    tree.insert(6);
    
    ASSERT_TRUE(*tree.min_element() == 4);
    
    vector<int> vec = {5,4,8,6};
    BinarySearchTree<int> *ptr = &tree;
    ASSERT_TRUE(compare_tree_to_array_int(vec, ptr));
}
TEST(insert_empty) {
    BinarySearchTree<string> tree;
    ASSERT_TRUE(tree.empty());
    tree.insert("hello");
    ASSERT_EQUAL(tree.size(), 1);
    
}

TEST(check_sorting_invariant) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(4);
    tree.insert(8);
    tree.insert(6);
    //cout << tree.to_string() << endl;
    
    ASSERT_TRUE(tree.check_sorting_invariant());
    
    *tree.begin() = 7;
    //cout << tree.to_string() << endl;
    ASSERT_TRUE(!tree.check_sorting_invariant());
}
TEST(check_sorting_invariant_string) {
    BinarySearchTree<string> tree;
    tree.insert("apple");
    tree.insert("banana");
    tree.insert("coolbeans");
    ASSERT_TRUE(tree.check_sorting_invariant());
    *tree.begin() = "waffle";
    ASSERT_TRUE(!tree.check_sorting_invariant());
    
}
TEST(check_sorting_invariant_empty) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.check_sorting_invariant());
}
TEST(check_copy_nodes){
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(4);
    tree.insert(8);
    tree.insert(6);
    BinarySearchTree<int> fish(tree);
    //cout<<tree.to_string()<<endl;
    //cout<<fish.to_string();
    ASSERT_EQUAL(tree.to_string(), fish.to_string());
}
TEST(check_copy_nodes_empty) {
    BinarySearchTree<int> tree;
    BinarySearchTree<int> copy(tree);
    
    ASSERT_TRUE(tree.empty());
    ASSERT_TRUE(copy.empty());
}

TEST(check_max_elt){
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(4);
    tree.insert(8);
    tree.insert(6);
    auto i = tree.max_element();
    ASSERT_EQUAL(*i, 8);
}

TEST(max_elt_empty){
    BinarySearchTree<int> tree;
    auto i = tree.max_element();
    ASSERT_EQUAL(i, tree.end());
}

TEST(min_greater_than_impl){
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(4);
    tree.insert(8);
    tree.insert(6);
    tree.insert(1);
    tree.insert(3);
    tree.insert(0);
    tree.insert(9);
    tree.insert(15);
    tree.insert(11);
    tree.insert(7);
    auto i = tree.min_greater_than(7);
    ASSERT_EQUAL(*(i), 8);
}

TEST(min_greater_than_impl_empty){
    BinarySearchTree<int> tree;
    auto i = tree.min_greater_than(7);
    ASSERT_TRUE(i == tree.end());
}

TEST(min_element_impl){
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(4);
    tree.insert(15);
    tree.insert(9);
    tree.insert(8);
    tree.insert(3);
    tree.insert(0);
    tree.insert(1);
    tree.insert(7);
    tree.insert(11);
    tree.insert(6);
    auto i = tree.min_element();
    ASSERT_EQUAL(*(i++), 0);
    ASSERT_EQUAL(*(i++), 1);
    ASSERT_EQUAL(*(i++), 3);
    ASSERT_EQUAL(*(i++), 4);
    ASSERT_EQUAL(*(i++), 5);
    ASSERT_EQUAL(*(i++), 6);
    ASSERT_EQUAL(*(i++), 7);
    ASSERT_EQUAL(*(i++), 8);
    ASSERT_EQUAL(*(i++), 9);
    ASSERT_EQUAL(*(i++), 11);
    ASSERT_EQUAL(*(i++), 15);
}

TEST(min_element_empty){
    BinarySearchTree<int> tree;
    auto i = tree.min_element();
    ASSERT_TRUE(i == tree.end());
}

TEST(max_element_empty){
    BinarySearchTree<int> tree;
    auto i = tree.max_element();
    ASSERT_TRUE(i == tree.end());
}

TEST(check_size_impl){
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(4);
    tree.insert(15);
    tree.insert(9);
    tree.insert(8);
    tree.insert(3);
    tree.insert(0);
    tree.insert(1);
    tree.insert(7);
    tree.insert(11);
    tree.insert(6);
    ASSERT_EQUAL(tree.size(), 11u);
}

TEST(check_size_impl_basic){
    BinarySearchTree<int> tree;
    ASSERT_EQUAL(tree.size(), 0u);
}

TEST(check_find){
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(4);
    tree.insert(15);
    tree.insert(9);
    tree.insert(8);
    tree.insert(3);
    tree.insert(0);
    tree.insert(1);
    tree.insert(7);
    tree.insert(11);
    tree.insert(6);
    BinarySearchTree<int> tree1;
    ASSERT_EQUAL(*(tree.find(6)),6);
    ASSERT_EQUAL(tree.find(2), tree.end());
    ASSERT_EQUAL(tree1.find(1), tree1.end());
}
//ok
TEST(check_find_empty) {
    BinarySearchTree<int> tree;
    ASSERT_EQUAL(tree.find(7), tree.end());
}
TEST(traverse_inorder) {
    stringstream fish;
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(4);
    tree.insert(8);
    tree.insert(6);
    tree.traverse_inorder(fish);
    stringstream checks("4 5 6 8 ");
    ASSERT_EQUAL(fish.str(), checks.str());
}

TEST(traverse_empty) {
    stringstream fish;
    stringstream corn;
    BinarySearchTree<int> tree;
    tree.traverse_inorder(fish);
    tree.traverse_preorder(corn);
    stringstream checks("");
    ASSERT_EQUAL(fish.str(), checks.str());
    ASSERT_EQUAL(corn.str(), checks.str());
}

TEST(traverse_preorder) {
    stringstream fish;
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(4);
    tree.insert(8);
    tree.insert(6);
    tree.traverse_preorder(fish);
    stringstream checks("5 4 8 6 ");
    ASSERT_EQUAL(fish.str(), checks.str());
}

TEST(height) {
    BinarySearchTree<int> tree;
    tree.insert(5);
    tree.insert(4);
    tree.insert(15);
    tree.insert(9);
    tree.insert(8);
    tree.insert(3);
    tree.insert(0);
    tree.insert(1);
    tree.insert(7);
    tree.insert(11);
    tree.insert(6);
    ASSERT_EQUAL(tree.height(), 6u);
}

TEST(height_empty) {
    BinarySearchTree<int> tree;
    ASSERT_EQUAL(tree.height(), 0u);
}

TEST_MAIN()
