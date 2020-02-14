/* 
Warren Ball
points2.h

This class allows you to store dynamically allocated arrays.
-the zero parameter constructor just creates an object with a null sequence and a 0 size
-one parameter constructor fills in a 1 coordinate array with the corresponding item coordinates and sets the size to 1
-the destructor deletes the array and sets the size to 0
-the copy constructor allocates spaces and fills it with copies of the array of rhs
-copy assignment creates a dummy copy of rhs, swaps itself with the current Points2, and returns it
-the move constructor just points to rhs's sequence and takes it size, while setting it's sequence to null and it's sie to 0
-the move assignment just swaps rhs's variables with it's own

-ReadPoints takes in a line of input, either from a text file or the user, and takes the first integer as the size
 and fills the array with the rest of the numbers, whether they're ints or doubles

 -size() just returns size_

 -overloaded[] allows you to summon the coordinate in the two []'s you put, for instance a[0][1] will return you the int
 or double in that space

 -overloaded + creates a new Points with a size of the longer Points2 sequence size, fills it with 0's, then adds in
 2 Points2 objects, so it will contain the sum of the two sets of coordinates and will just append the rest of the
 longer sequence_

 -overloaded << prints out the sequence of the given Points2 object in a coordinate fashion, such as (0, 1), (2, 3)
 if size is 0, it'll priint an empty paranthesis and it has adjusted spacing

 date of creation: 2/3/20 - 2/13/20

*/
#ifndef CSCI335_HOMEWORK1_POINTS2_H_
#define CSCI335_HOMEWORK1_POINTS2_H_

#include <array>
#include <iostream>
#include <cstddef>
#include <string>
#include <sstream>

namespace teaching_project {

template<typename Object>
class Points2 {
 public:
 
  // Zero-parameter constructor. 
  // Set size to 0 and sequence to nullptr
  Points2(){
    size_ = 0;
    sequence_ = nullptr;
  }

  // Copy-constructor.
  Points2(const Points2 &rhs): size_{rhs.size_}
  {

    sequence_ = new std::array<Object, 2>[rhs.size_];
    
    int col = 2;
    int row = size_;

    for(int i=0; i<row; i++)
    {
      for(int j = 0; j < col ; j++)
      {
        sequence_[i][j] = rhs.sequence_[i][j];
      }
    }


  }// --end of copy constructor

  // Copy-assignment. 
  Points2& operator=(const Points2 &rhs)
   {
     Points2 copy = rhs; 
     std::swap(*this, copy);
     return *this;
   }

  // Move-constructor. 
  Points2(Points2 &&rhs) : size_{rhs.size_}
  {
    sequence_ = rhs.sequence_;

    
    rhs.sequence_ = nullptr;
    rhs.size_ = 0;
  }

  // Move-assignment.
  // Just use std::swap() for all variables.
  Points2& operator=(Points2 &&rhs)
  {
        std::swap(size_, rhs.size_);

        std::swap(sequence_, rhs.sequence_);

  }

  ~Points2()
  {

      delete [] sequence_;
      sequence_ = nullptr;
      size_ = 0;

  }

  // End of big-five.

  // One parameter constructor.
  Points2(const std::array<Object, 2>& item) 
  {
    size_ = 1;
    sequence_ = new std::array<Object, 2>[1];

    sequence_[0][0] = item[0];
    sequence_[0][1] = item[1];

  }

  // Read a chain from standard input.
  void ReadPoints2() {
    // Part of code included (without error checking).
    std::string input_line;
    std::getline(std::cin, input_line); 
    std::stringstream input_stream(input_line);
    if (input_line.empty()) return;
    // Read size of sequence (an integer).
    int size_of_sequence;
    input_stream >> size_of_sequence;

    size_ = size_of_sequence;
    // Allocate space for sequence.
    sequence_ = new std::array<Object, 2>[size_of_sequence];

    Object token;

    int cur_row = -1;

    for (int i = 0 ;input_stream >> token; ++i) {
      // Read coordinates.
      // Fill sequence_ here.

      if(i % 2 == 0)
      {
        cur_row++;
      
        sequence_[cur_row][0] = token;
      }
      else
      {
        sequence_[cur_row][1] = token;
      }


    }//--end of for loop


   
  }//--end of ReadPoints2


  size_t size() const {
    return size_;
  }

  // @location: an index to a location in the sequence.
  // @returns the point at @location.
  // const version.
  // abort() if out-of-range.
  const std::array<Object, 2>& operator[](size_t location) const { 

    return sequence_[location];

  }

 //  @c1: A sequence.
 //  @c2: A second sequence.
 //  @return their sum. If the sequences are not of the same size, append the
 //    result with the remaining part of the larger sequence.
 friend Points2 operator+(const Points2 &c1, const Points2 &c2) {


  int longer_size = std::max(c1.size_,c2.size_);


  Points2 result;
  result.size_ = longer_size;
  result.sequence_ = new std::array<Object, 2>[longer_size];



  for(int i = 0; i< longer_size; i++)
  { // first, fill the coordinate with zeroes
      result.sequence_[i][0] = 0;
      result.sequence_[i][1] = 0;
    if(i < c1.size_)//then add in any coordinates that are in the same place
    {
      result.sequence_[i][0] += c1.sequence_[i][0];
      result.sequence_[i][1] += c1.sequence_[i][1];

    }

    if(i < c2.size_)
    {
      result.sequence_[i][0] += c2.sequence_[i][0];
      result.sequence_[i][1] += c2.sequence_[i][1];

    }
  }

  return result;
  
 }// --end of overloaded+


 // Overloading the << operator.
friend std::ostream &operator<<(std::ostream &out, const Points2 &some_points2) {
   
  if(some_points2.size_ != 0)
  {
   for(int i=0; i<some_points2.size_; i++)
     {
      if(i != some_points2.size_)//this if statement is purely for spacing
      {
       out<<"("<<some_points2.sequence_[i][0]<<", "<<some_points2.sequence_[i][1]<<") ";
      }
      else
      {
        out<<"("<<some_points2.sequence_[i][0]<<", "<<some_points2.sequence_[i][1]<<")";
      }
      
     }
  }
  else
  {
    out<<"()";
  }

  return out;

 }//--end of overloaded <<
 
 private:
  // Sequence of points. 
  std::array<Object, 2> *sequence_;
  // Size of sequence.
  size_t size_;

};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_POINTS2_H_
