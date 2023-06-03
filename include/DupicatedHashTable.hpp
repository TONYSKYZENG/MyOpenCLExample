//
// Created by Xianzhi Zeng 07/02/2022
// This is a pure STL header, so the corresponding *.cpp is empty
//
#pragma once
#ifndef _DUPLICATEDHASHTABLE_HPP_
#define _DUPLICATEDHASHTABLE_HPP_
using namespace std;
#include <vector>
#include <stdint.h>
#include <iostream>
#include <memory>
#include <unordered_map>
namespace std{

/*class:DupicatedHashTable
description: integrted an unsorted_map, and can deal with duplicated key
note: almost all part of this class is similar to the original unsorted_map,
However, the find(key) will return the vector of the duplicated keys.
You can use the find(key)[index] to get the index-th value in the vector
date:20220207
*/
 template<typename _Key, typename _Tp,
	   typename _Hash = hash<_Key>
	   /*typename _Pred = equal_to<_Key>,
	   typename _Alloc = allocator<std::pair<const _Key, _Tp>>*/>
class DupicatedHashTable
{
private:
    /* data */
    unordered_map<_Key,std::vector<_Tp>,_Hash/*,_Pred,_Alloc*/ > map;
public:
    DupicatedHashTable(/* args */)
    {
      map=unordered_map<_Key,std::vector<_Tp> >();
    }
    ~DupicatedHashTable()
    {

    }
  //the empty()
  bool empty() const noexcept
  { return map.empty(); }
  //the emplace, return the key duplication index of emplaced item
  size_t emplace(_Key key,_Tp value)
  {
    if(map.find(key)==map.end())
    {
     std::vector<_Tp> vecKey=std::vector<_Tp>();
      vecKey.push_back(value);
     map.emplace(key,vecKey);
      return  0;
    }
    else
    {

     map.find(key)->second.push_back(value);
     return  map.find(key)->second.size()-1;
    }

  }
  auto find(_Key key)
  {
    return map.find(key);
  }
  auto begin()
  {
    return  map.begin();
  }
  auto end()
  {
    return  map.end();
  }
  auto size()
  {
    return  map.size();
  }
  //everything in this key will be erased
  auto erase(_Key key)
  {
    return  map.erase(key);
  }
  //only try to erase the specific duplicated item (if it exists)
  bool erase(_Key key,size_t duplication)
  { auto k=map.find(key);
      if(k==map.end())
      {
        return false;
      }
      if(k->second.size()<duplication+1)
      {
        return false;
      }
    k->second.erase(k->second.begin()+duplication);

    return true;
  }
  //only try to erase the specific duplicated item from start to end (if they exist)
  bool erase(_Key key,size_t duplicationS,size_t duplicationE)
  { auto k=map.find(key);
    if(duplicationS>duplicationE)
    {
      return false;
    }
    if(k==map.end())
    {
      return false;
    }
    if(k->second.size()<duplicationE+1)
    {
      return false;
    }
    k->second.erase(k->second.begin()+duplicationS,k->second.begin()+duplicationE+1);
    // if nothing left, clear this entry
    if(k->second.size()==0)
    {
      map.erase(key);
    }
    return true;
  }

};


}



#endif