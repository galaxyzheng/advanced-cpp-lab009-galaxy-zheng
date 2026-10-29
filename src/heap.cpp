#include "project/heap.h"

#include <algorithm>
#include <stdexcept>

MaxHeap::MaxHeap() = default;

MaxHeap::MaxHeap(const std::vector<int>& values) {
    buildHeap(values);
}

bool MaxHeap::empty() const noexcept {
    return data_.empty();
}

std::size_t MaxHeap::size() const noexcept {
    return data_.size();
}

int MaxHeap::top() const {
    if (empty()) {
        throw std::logic_error("Heap is empty");
    }
    return data_.front();
}

bool MaxHeap::contains(int value) const {
    for (int item : data_) {
        if (item == value) return true;
    } return false;
}

void MaxHeap::push(int value) {
    data_.push_back(value);
    if (data_.size() > 1) heapifyUp(data_.size() - 1);
}

int MaxHeap::pop() {
    if (data_.empty()) throw(std::logic_error("Pop on empty"));
    int popped = data_.front();
    data_.front() = data_.back();
    data_.pop_back();
    if (data_.size() > 1) heapifyDown(0);
    return popped;
}

void MaxHeap::buildHeap(const std::vector<int>& values) {
    data_.clear();
    for (int i : values) push(i);
}

std::vector<int> MaxHeap::heapSort() {
    std::vector<int> sorted = data_;
    std::size_t progress = 1; //sorting progress
    while (progress < sorted.size()) { //auto checks if size big enough for sort
        std::size_t index = 0;
        std::swap(sorted.front(), sorted[sorted.size() - progress]);
        progress ++;
        while (leftChildIndex(index) < sorted.size() - progress) { //heapify down with progressive boundary
            int rightG = 0;
            if (rightChildIndex(index) < sorted.size() - progress) {
                rightG = (sorted[leftChildIndex(index)] > sorted[rightChildIndex(index)]) ? 0 : 1;
            } //is right greater
            if (sorted[index] < sorted[leftChildIndex(index)+rightG]) swap(sorted[index], sorted[leftChildIndex(index)+rightG]);
            else break;
            index = leftChildIndex(index)+rightG;
        }
    } return sorted;
}

std::vector<int> MaxHeap::toVector() const {
    return data_;
}

std::size_t MaxHeap::parentIndex(std::size_t index) {
    if (index == 0) {
        return 0;
    }
    return (index - 1) / 2;
}

std::size_t MaxHeap::leftChildIndex(std::size_t index) {
    return (2 * index) + 1;
}

std::size_t MaxHeap::rightChildIndex(std::size_t index) {
    return (2 * index) + 2;
}

void MaxHeap::heapifyUp(std::size_t index) {
    while (index > 0 && data_[index] > data_[parentIndex(index)]){
        swap(data_[index], data_[parentIndex(index)]);
        index = parentIndex(index);
    } return;
}

void MaxHeap::heapifyDown(std::size_t index) {
    while (leftChildIndex(index) < data_.size()) { //try as long as a child exists to compare
        int rightG = 0;
        if (rightChildIndex(index) < data_.size()) { //check if right exists for comparison
            rightG = (data_[leftChildIndex(index)] > data_[rightChildIndex(index)]) ? 0 : 1;
        } //is right greater
        if (data_[index] < data_[leftChildIndex(index)+rightG]) swap(data_[index], data_[leftChildIndex(index)+rightG]);
        else return;
        index = leftChildIndex(index)+rightG;
    } return;
}

void MaxHeap::swap(int& a, int& b) {
    std::swap(a, b);
}

bool MaxHeap::isValidHeap() const {
    for (std::size_t i = 1; i < data_.size(); ++i) {
        if (data_[parentIndex(i)] < data_[i]) {
            return false;
        }
    }
    return true;
}
