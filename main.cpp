#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
using namespace std;

class InputData
{
  public:
    int dat; //stores the data
    int OGVect; //stores which vector it was originally in
    //overloads the comparison operators because it wasn't working otherwise 
    bool operator <(const InputData &right)const {return dat < right.dat;};
    bool operator >(const InputData &right)const {return dat > right.dat;};
};

int partition(vector<int>& list, int first, int last) {
  // The pivot should be the median of the
  // first, middle, and last elements.

  int smallIndex = first;

  // partition procedure

  //creates the pivot and middle element locations
  int pivot = first;
  int mid = ((last-first)/2) + first;

  //finds the median
  if(list.at(first) > list.at(last) && list.at(first) < list.at(mid))
    pivot = first;
  else if(list.at(first) < list.at(last) && list.at(first) > list.at(mid))
    pivot = first;
  else if(list.at(last) > list.at(first) && list.at(last) < list.at(mid))
    pivot = last;
  else if(list.at(last) < list.at(first) && list.at(last) > list.at(mid))
    pivot = last;
  else if(list.at(mid) > list.at(first) && list.at(mid) < list.at(last))
    pivot = mid;
  else if(list.at(mid) < list.at(first) && list.at(mid) > list.at(last))
    pivot = mid;

  //puts pivot at the front of the section
  swap(list.at(first), list.at(pivot));

  //swaps the smallest inputs to the front
  for(int pos = first+1; pos <= last; pos++)
  {
    if(list.at(pos) < list.at(first))
    {
      smallIndex++;
      swap(list.at(smallIndex), list.at(pos));
    }
  }

  //swaps the small index and the first element
  swap(list.at(first), list.at(smallIndex));

  return smallIndex;  
}

void quicksort(vector<int>& list, int first, int last)
{
  //base case to end recursion
  if(first == last || first > last)
    return;
  //recursively calls quicksort and partition to sort the array
  if(first < last)
  {
    int mid = partition(list, first, last);
    quicksort(list, first, mid-1);
    quicksort(list, mid+1, last);
  }
}

void multiway_merge(vector<vector<int>>& input_lists, vector<int>& output_list) 
{
  //creates the priority queue
  priority_queue<InputData, vector<InputData>, greater<InputData>> pq;

  //loads all the data from input_lists into the priority queue
  int InSize = input_lists.size();
  for(int pos = 0; pos < InSize; pos++)
  {
    InputData temp;
    temp.dat = input_lists.at(pos).at(0);
    temp.OGVect = pos;
    pq.push(temp);
  }

  //takes the data from the priority queue, sorts it, and puts it into output_list
  for(int pos = 0; pq.empty() == false; pos++)
  {
    //creates a temporary object with the data from the priority queue and removes the top of the priority queue
    InputData temp;
    temp = pq.top();
    output_list.at(pos) = temp.dat;
    pq.pop();

    //erases the data at the beginning of the input_list's vectors
    input_lists.at(temp.OGVect).erase(input_lists.at(temp.OGVect).begin());

    //makes sure the input_list's vectors are not empty after deletion
    if(input_lists.at(temp.OGVect).empty() == false)
    {
      //pushes the next item in input_list's vector onto the priority queue
      InputData temporary;
      temporary.dat = input_lists.at(temp.OGVect).at(0);
      temporary.OGVect = temp.OGVect;
      pq.push(temporary);
    }
  }
} 


int main(int argc, char** argv) {
  int n, m;
  cin >> n >> m;

  vector<vector<int> > input_lists(n, vector<int>(m));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> input_lists[i][j];
    }
  }

  // Quicksort k sublists
  for (int i = 0; i < input_lists.size(); ++i)
    quicksort(input_lists[i], 0, m-1);

  // Merge n input sublists into one sorted list
  vector<int> output_list(n * m);
  multiway_merge(input_lists, output_list);

  for (int i = 0; i < output_list.size(); ++i)
    cout << output_list[i] << " ";
  cout << endl;

  return 1;
}
