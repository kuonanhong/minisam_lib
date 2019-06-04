#ifndef ORDERING_H
#define ORDERING_H

/**
 * @file    Ordering.h
 * @author
 * @date    Sep 2, 2010
 */

#include "../inference/VariableIndex.h"
//#include "../inference/MetisIndex.h"
//#include "../inference/FactorGraph.h"
#include "../inference/FactorPointerGraph.h"
#include <algorithm>
#include <vector>

class VariableIndex;
//class GaussianFactorGraph;
class Ordering: public std::vector<int>
{
public:
    typedef std::vector<int> Base;

public:

    /// Type of ordering to use
    enum OrderingType
    {
        COLAMD, METIS, NATURAL, CUSTOM
    };

public:
    /// Create an empty ordering
    Ordering()
    {
    }

    /// Create from a container
    //template<typename KEYS>
    Ordering(const std::vector<int> keys) :
        Base(keys.begin(), keys.end())
    {
    }

    /// Create an ordering using iterators over keys
    //template<typename ITERATOR>
    Ordering(std::vector<int>::iterator firstKey, std::vector<int>::iterator lastKey) :
        Base(firstKey, lastKey)
    {
    }

    /// Add new variables to the ordering as ordering += key1, key2, ...  Equivalent to calling
    /// push_back.

    std::vector<int> operator+=(int key)
    {
        push_back(key);
        std::vector<int> newbase(this->begin(),this->end());
        return  newbase;
    }

    Ordering& operator=(const Ordering& rObj)
    {
        std::vector<int>::operator=(rObj);
        return *this;
    }

    std::vector<int> getBase()
    {
        std::vector<int> newbase(this->begin(), this->end());
        return  newbase;
    }

    /// Invert (not reverse) the ordering - returns a map from key to order position
    //FastMap<Key, size_t> invert() const;
    std::map<int,int> invert() const;

    /// @name Fill-reducing Orderings @{

    /// Compute a fill-reducing ordering using COLAMD from a factor graph (see details for note on
    /// performance). This internally builds a VariableIndex so if you already have a VariableIndex,
    /// it is faster to use COLAMD(const VariableIndex&)
    /*template<class TPFactor>
    Ordering Colamd(const FactorGraph<TPFactor>& graph)
    {
        if (graph.empty())
            return Ordering();
        else
            return Colamd(VariableIndex(graph));
    }*/

    template<class TPFactor>
    Ordering Colamd(const FactorPointerGraph<TPFactor>& graph)
    {
        if (graph.empty())
            return Ordering();
        else
            return Colamd(VariableIndex(graph));
    }

    /// Compute a fill-reducing ordering using COLAMD from a VariableIndex.
    Ordering Colamd(const VariableIndex& variableIndex);

    /// Compute a fill-reducing ordering using constrained COLAMD from a factor graph (see details
    /// for note on performance).  This internally builds a VariableIndex so if you already have a
    /// VariableIndex, it is faster to use COLAMD(const VariableIndex&).  This function constrains
    /// the variables in \c constrainLast to the end of the ordering, and orders all other variables
    /// before in a fill-reducing ordering.  If \c forceOrder is true, the variables in \c
    /// constrainLast will be ordered in the same order specified in the vector<Key> \c
    /// constrainLast.   If \c forceOrder is false, the variables in \c constrainLast will be
    /// ordered after all the others, but will be rearranged by CCOLAMD to reduce fill-in as well.
    /*template<class TPFactor>
    Ordering ColamdConstrainedLast(const FactorGraph<TPFactor>& graph,
                                   const std::vector<int>& constrainLast, bool forceOrder = false)
    {
        if (graph.empty())
            return Ordering();
        else
            return ColamdConstrainedLast(VariableIndex(graph), constrainLast, forceOrder);
    }*/

    template<class TPFactor>
    Ordering ColamdConstrainedLast(const FactorPointerGraph<TPFactor>& graph,
                                   const std::vector<int>& constrainLast, bool forceOrder = false)
    {
        if (graph.empty())
            return Ordering();
        else
            return ColamdConstrainedLast(VariableIndex(graph), constrainLast, forceOrder);
    }

    /// Compute a fill-reducing ordering using constrained COLAMD from a VariableIndex.  This
    /// function constrains the variables in \c constrainLast to the end of the ordering, and orders
    /// all other variables before in a fill-reducing ordering.  If \c forceOrder is true, the
    /// variables in \c constrainLast will be ordered in the same order specified in the vector<Key>
    /// \c constrainLast.   If \c forceOrder is false, the variables in \c constrainLast will be
    /// ordered after all the others, but will be rearranged by CCOLAMD to reduce fill-in as well.
    Ordering ColamdConstrainedLast(
        const VariableIndex& variableIndex, const std::vector<int>& constrainLast,
        bool forceOrder = false);

    /// Compute a fill-reducing ordering using constrained COLAMD from a factor graph (see details
    /// for note on performance).  This internally builds a VariableIndex so if you already have a
    /// VariableIndex, it is faster to use COLAMD(const VariableIndex&).  This function constrains
    /// the variables in \c constrainLast to the end of the ordering, and orders all other variables
    /// before in a fill-reducing ordering.  If \c forceOrder is true, the variables in \c
    /// constrainFirst will be ordered in the same order specified in the vector<Key> \c
    /// constrainFirst.   If \c forceOrder is false, the variables in \c constrainFirst will be
    /// ordered before all the others, but will be rearranged by CCOLAMD to reduce fill-in as well.
    /*template<class TPFactor>
    Ordering ColamdConstrainedFirst(const FactorGraph<TPFactor>& graph,
                                    const std::vector<int>& constrainFirst, bool forceOrder = false)
    {
        if (graph.empty())
            return Ordering();
        else
            return ColamdConstrainedFirst(VariableIndex(graph), constrainFirst, forceOrder);
    }
    */
    template<class TPFactor>
    Ordering ColamdConstrainedFirst(const FactorPointerGraph<TPFactor>& graph,
                                    const std::vector<int>& constrainFirst, bool forceOrder = false)
    {
        if (graph.empty())
            return Ordering();
        else
            return ColamdConstrainedFirst(VariableIndex(graph), constrainFirst, forceOrder);
    }

    /*Ordering ColamdConstrainedFirst(const GaussianFactorGraph& graph,
       const std::vector<int>& constrainFirst, bool forceOrder = false)
    {
     if (graph.size()==0)
       return Ordering();
     else
       return ColamdConstrainedFirst(VariableIndex(graph), constrainFirst, forceOrder);
    }*/

    /// Compute a fill-reducing ordering using constrained COLAMD from a VariableIndex.  This
    /// function constrains the variables in \c constrainFirst to the front of the ordering, and
    /// orders all other variables after in a fill-reducing ordering.  If \c forceOrder is true, the
    /// variables in \c constrainFirst will be ordered in the same order specified in the
    /// vector<Key> \c constrainFirst.   If \c forceOrder is false, the variables in \c
    /// constrainFirst will be ordered before all the others, but will be rearranged by CCOLAMD to
    /// reduce fill-in as well.
    Ordering ColamdConstrainedFirst(
        const VariableIndex& variableIndex,
        const std::vector<int>& constrainFirst, bool forceOrder = false);

    /// Compute a fill-reducing ordering using constrained COLAMD from a factor graph (see details
    /// for note on performance).  This internally builds a VariableIndex so if you already have a
    /// VariableIndex, it is faster to use COLAMD(const VariableIndex&).  In this function, a group
    /// for each variable should be specified in \c groups, and each group of variables will appear
    /// in the ordering in group index order.  \c groups should be a map from Key to group index.
    /// The group indices used should be consecutive starting at 0, but may appear in \c groups in
    /// arbitrary order.  Any variables not present in \c groups will be assigned to group 0.  This
    /// function simply fills the \c cmember argument to CCOLAMD with the supplied indices, see the
    /// CCOLAMD documentation for more information.
    /*template<class TPFactor>
    Ordering ColamdConstrained(const FactorGraph<TPFactor>& graph,
                               const std::map<int, int>& groups)
    {
        if (graph.empty())
            return Ordering();
        else
            return ColamdConstrained(VariableIndex(graph), groups);
    }
    */

    template<class TPFactor>
    Ordering ColamdConstrained(const FactorPointerGraph<TPFactor>& graph,
                               const std::map<int, int>& groups)
    {
        if (graph.empty())
            return Ordering();
        else
            return ColamdConstrained(VariableIndex(graph), groups);
    }

    /// Compute a fill-reducing ordering using constrained COLAMD from a VariableIndex.  In this
    /// function, a group for each variable should be specified in \c groups, and each group of
    /// variables will appear in the ordering in group index order.  \c groups should be a map from
    /// Key to group index. The group indices used should be consecutive starting at 0, but may
    /// appear in \c groups in arbitrary order.  Any variables not present in \c groups will be
    /// assigned to group 0.  This function simply fills the \c cmember argument to CCOLAMD with the
    /// supplied indices, see the CCOLAMD documentation for more information.
    Ordering ColamdConstrained(
        const VariableIndex& variableIndex, const std::map<int, int>& groups);

    /// Return a natural Ordering. Typically used by iterative solvers
    /*template<class TPFactor>
    Ordering Natural(const FactorGraph<TPFactor> &fg)
    {
        std::set<int> src = fg.keys();
        std::vector<int> keys(src.begin(), src.end());
        std::stable_sort(keys.begin(), keys.end());
        return Ordering(keys);
    }*/

    template<class TPFactor>
    Ordering Natural(const FactorPointerGraph<TPFactor> &fg)
    {
        std::set<int> src = fg.keys();
        std::vector<int> keys(src.begin(), src.end());
        std::stable_sort(keys.begin(), keys.end());
        return Ordering(keys);
    }

    /// METIS Formatting function
   // template<class TPFactor>
   // static  void CSRFormat(std::vector<int>& xadj,
   //                        std::vector<int>& adj, const FactorGraph<TPFactor>& graph);

    /// Compute an ordering determined by METIS from a VariableIndex
    //static  Ordering Metis(const MetisIndex& met);

// template<class FACTOR>
// static Ordering Metis(const FactorGraph<FACTOR>& graph) {
//   return Metis(MetisIndex(graph));
    //}

    /// @}

    /// @name Named Constructors @{
/*
    template<class TPFactor>
    Ordering Create(OrderingType orderingType,
                    const FactorGraph<TPFactor>& graph)
    {
        if (graph.empty())
            return Ordering();

        switch (orderingType)
        {
        case COLAMD:
            return Colamd(graph);
        //case METIS:
        //  return Metis(graph);
        case NATURAL:
            return Natural(graph);
        case CUSTOM:
            throw std::runtime_error(
                "Ordering::Create error: called with CUSTOM ordering type.");
        default:
            throw std::runtime_error(
                "Ordering::Create error: called with unknown ordering type.");
        }
    }*/

    template<class TPFactor>
    Ordering Create(OrderingType orderingType,
                    const FactorPointerGraph<TPFactor>& graph)
    {
        if (graph.empty())
            return Ordering();

        switch (orderingType)
        {
        case COLAMD:
            return Colamd(graph);
        //case METIS:
        //  return Metis(graph);
        case NATURAL:
            return Natural(graph);
        case CUSTOM:
            throw std::runtime_error(
                "Ordering::Create error: called with CUSTOM ordering type.");
        default:
            throw std::runtime_error(
                "Ordering::Create error: called with unknown ordering type.");
        }
    }


    /// @}


private:
    /// Internal COLAMD function
    Ordering ColamdConstrained(
        const VariableIndex& variableIndex, std::vector<int>& cmember);
};

Eigen::VectorXd VectorValuesgetvectorOrdering(const std::map<int,Eigen::VectorXd>& VectorValues,const Ordering& keys);
#endif // ORDERING_H
