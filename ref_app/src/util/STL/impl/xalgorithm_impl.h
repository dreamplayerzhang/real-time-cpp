///////////////////////////////////////////////////////////////////////////////
//  Copyright Christopher Kormanyos 2007 - 2013.
//  Distributed under the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt
//  or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef _XALGORITHM_IMPL_2010_02_23_H_
  #define _XALGORITHM_IMPL_2010_02_23_H_

  #include "xiterator_impl.h"
  #include "cstddef_impl.h"

  // Implement helper functions for <algorithm>.

  namespace xalgorithm
  {
    template<typename compare_type>
    const compare_type& xmin(const compare_type& a, const compare_type& b)
    {
      return ((a < b) ? a : b);
    }

    template<typename compare_type, typename binary_predicate>
    const compare_type& xmin(const compare_type& a, const compare_type& b, binary_predicate comp)
    {
      return (*comp)(a, b);
    }

    template<typename compare_type>
    const compare_type& xmax(const compare_type& a, const compare_type& b)
    {
      return ((a > b) ? a : b);
    }

    template<typename compare_type, typename binary_predicate>
    const compare_type& xmax(const compare_type& a, const compare_type& b, binary_predicate comp)
    {
      return (*comp)(a, b);
    }

    template<typename input_iterator, typename output_iterator>
    output_iterator xcopy(input_iterator first, input_iterator last, output_iterator result)
    {
      for( ; first != last; ++result, ++first)
      {
        *result = *first;
      }

      return result;
    }

    template<typename forward_iterator, typename value_type>
    void xfill(forward_iterator first, forward_iterator last, const value_type& value)
    {
      const value_type tmp = value;

      for( ; first != last; ++first)
      {
        *first = tmp;
      }
    }

    template<typename output_iterator, typename difference_type, typename value_type>
    output_iterator xfill_n(output_iterator first, difference_type count, const value_type& value)
    {
      const output_iterator last = first + count;

      xfill(first, last, value);

      return last;
    }

    template<typename input_iterator,
             typename output_iterator,
             typename unary_operation>
    output_iterator xtransform(input_iterator first, input_iterator last, output_iterator result, unary_operation unary_op)
    {
      for(; first != last; ++first, ++result)
      {
        *result = unary_op(*first);
      }

      return result;
    }

    template<typename input_iterator1,
             typename input_iterator2,
             typename output_iterator,
             typename binary_operation>
    output_iterator xtransform(input_iterator1 first1, input_iterator1 last1, input_iterator2 first2, output_iterator result, binary_operation binary_op)
    {
      for(; first1 != last1; ++first1, ++first2, ++result)
      {
        *result = binary_op(*first1, *first2);
      }

      return result;
    }

    template<class input_iterator1, class input_iterator2>
    bool xequal(input_iterator1 first1, input_iterator1 last1, input_iterator2 first2)
    {
      while(first1 != last1)
      {
        if(!(*first1 == *first2))
        {
          return false;
        }

        ++first1;
        ++first2;
      }

      return true;
    }

    template<typename iterator_type, typename function_type>
    bool xall_of(iterator_type first, iterator_type last, function_type function)
    {
      while((first != last) && function(*first))
      {
        ++first;
      }

      return (first == last);
    }

    template<typename iterator_type, typename function_type>
    bool xany_of(iterator_type first, iterator_type last, function_type function)
    {
      while((first != last) && (!function(*first)))
      {
        ++first;
      }

      return (first != last);
    }

    template<typename iterator_type, typename function_type>
    bool xnone_of(iterator_type first, iterator_type last, function_type function)
    {
      while((first != last) && (!function(*first)))
      {
        ++first;
      }

      return (first == last);
    }

    template<typename iterator_type, typename function_type>
    function_type xfor_each(iterator_type first, iterator_type last, function_type function)
    {
      for( ; first != last; ++first)
      {
        function(*first);
      }

      return function;
    }

    // Find the first element that satisfies the predicate.
    template<typename input_iterator, typename predicate_type>
    input_iterator xfind_if(input_iterator first, input_iterator last, predicate_type predicate)
    {
      while((first != last) && (!predicate(*first)))
      {
        ++first;
      }

      return first;
    }

    // Find the first element that does not satisfy the predicate.
    template<typename input_iterator, typename predicate_type>
    input_iterator xfind_if_not(input_iterator first, input_iterator last, predicate_type predicate)
    {
      while((first != last) && predicate(*first))
      {
        ++first;
      }

      return first;
    }

    template<typename input_iterator, typename T>
    typename xiterator::xiterator_traits<input_iterator>::difference_type xcount(input_iterator first, input_iterator last, const T& value)
    {
      typename xiterator::xiterator_traits<input_iterator>::difference_type cnt(0U);

      while(first != last)
      {
        if(value == *first) { ++cnt; }
        ++first;
      }

      return cnt;
    }

    template<class input_iterator, class predicate_type>
    typename xiterator::xiterator_traits<input_iterator>::difference_type xcount_if(input_iterator first, input_iterator last, predicate_type predicate)
    {
      typename xiterator::xiterator_traits<input_iterator>::difference_type cnt(0U);

      while(first != last)
      {
        if(predicate(*first)) { ++cnt; }
        ++first;
      }

      return cnt;
    }

    template<typename forward_iterator1,
              typename difference2,
              typename value_type>
    forward_iterator1 xsearch_n(forward_iterator1 first1,
                                forward_iterator1 last1,
                                difference2 count_value,
                                const value_type& search_value)
    {
      // Find the first count_value * search_value match.
      // Use random-access iterators.

      if(count_value <= 0)
      {
        return (first1);
      }

      forward_iterator1 old_first1 = first1;

      for(difference2 inc = 0; count_value <= last1 - old_first1; )
      {
        // There is enough room. Look for a match
        first1 = old_first1 + inc;

        if (*first1 == search_value)
        {
          // Found part of a possible match. Test for a match.
          difference2 count1 = count_value;
          forward_iterator1 mid1 = first1;

          for( ; (old_first1 != first1) && (first1[-1] == search_value); --first1)
          {
            // Back up over any skipped prefix.
            --count1;
          }

          if(count1 <= last1 - mid1)
          {
            // There is enough left. Test the suffix.
            for (;;)
            {
              if(--count1 == 0)
              {
                // Found the rest of match. Report it.
                return (first1);
              }
              else if(!(*++mid1 == search_value))
              {
                // Short match not at end.
                break;
              }
            }
          }

          // Failed to match. Take a small jump.
          old_first1 = ++mid1;
          inc = 0;
        }
        else
        {
          // No match. Take a big jump and back up as needed.
          old_first1 = first1 + 1;
          inc = count_value - 1;
        }
      }

      return (last1);
    }

    template<typename forward_iterator1,
             typename difference2,
             typename value_type,
             typename predicate_type>
    forward_iterator1 xsearch_n(forward_iterator1 first1,
                                forward_iterator1 last1,
                                difference2 count_value,
                                const value_type& search_value,
                                predicate_type predicate)
    {
      // Find the first count_value * search_value that satisfies the predicate.
      // Use random-access iterators.

      if (count_value <= 0)
      {
        return (first1);
      }

      forward_iterator1 old_first1 = first1;

      for( ; count_value <= (last1 - old_first1); )
      {
        // There is enough room. Look for a match
        // enough room, look for a match
        if(predicate(*first1, search_value))
        {
          // Found part of a possible match. Test for a match.
          difference2 count1 = count_value;
          forward_iterator1 mid1 = first1;

          for( ; (old_first1 != first1) && predicate(first1[-1], search_value); --first1)
          {
            // Back up over any skipped prefix.
            --count1;
          }

          if(count1 <= last1 - mid1)
          {
            // There is enough left. Test the suffix.
            for(;;)
            {
              if(--count1 == 0)
              {
                // Found the rest of match. Report it.
                return (first1);
              }
              else if(!predicate(*++mid1, search_value))
              {
                // Short match not at end.
                break;
              }
            }
          }

          // Failed to match. Take a small jump.
          old_first1 = ++mid1;
          first1 = old_first1;
        }
        else
        {
          // No match. Take a big jump and back up as needed.
          old_first1 = first1 + 1;
          first1 += count_value;
        }
      }

      return (last1);
    }

    template<typename swap_type>
    void xswap(swap_type left, swap_type right)
    {
      // Exchange the values stored at left and right if they are different.
      if(&left != &right)
      {
        const swap_type tmp = left;

        left = right;
        right = tmp;
      }
    }

    template<typename swap_type, std::size_t N>
    void xswap(swap_type(&left)[N], swap_type(&right)[N])
    {
      for(std::size_t i = static_cast<std::size_t>(0U); i < N; ++i)
      {
        xswap(left[i], right[i]);
      }
    }

    template<typename input_iterator1, typename input_iterator2>
    void xiter_swap(input_iterator1 left, input_iterator2 right)
    {
      xalgorithm::xswap(*left, *right);
    }

    template<typename input_iterator1, typename input_iterator2>
    input_iterator2 xswap_ranges(input_iterator1 first1, input_iterator1 last1, input_iterator2 first2)
    {
      for(; first1 != last1; ++first1, ++first2)
      {
        xalgorithm::xiter_swap(first1, first2);
      }

      return first2;
    }
  }

#endif // _XALGORITHM_IMPL_2010_02_23_H_
