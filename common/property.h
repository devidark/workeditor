/*!
 *  \brief  .
 *
 *  \author Alex Medveschek
 *  \date   2011-11-01
 */

#pragma once

#include <string>
#include <boost/intrusive/unordered_set.hpp>
#include <boost/shared_ptr.hpp>

namespace NVis {

/*!
 *  \todo   Допилить.
 */
class Property
    : public boost::intrusive::unordered_set_base_hook<>
{
    public:
        Property(unsigned id)
            : id_(id)
        {}

        Property& operator[](unsigned id)
        {
            PropertySet::iterator i = prop_set_->find(id);
            if (i == prop_set_->end()) {
                i = prop_set_->insert(Property(id));
            }
            return *i;
        }

        template <typename T>
        T Get();

        template <bool>
        bool Get()
        {
            return bool_;
        }

        template <int>
        int Get()
        {
            return int_;
        }

        template <unsigned>
        unsigned Get()
        {
            return unsigned_;
        }

        double Get()
        {
            return double_;
        }

        template <std::string>
        const std::string& Get()
        {
            return string_;
        }

        template <typename T>
        void Set(T value);

    private:
        typedef boost::intrusive::unordered_set<Property> PropertySet;
        typedef boost::shared_ptr<PropertySet>  PPropertySet;
        PPropertySet prop_set_;

        unsigned id_;

        bool operator==(const Property& rhs)
        {
            return id_ == rhs.id_;
        }

        bool        bool_;
        int         int_;
        unsigned    unsigned_;
        double      double_;
        std::string string_;
};

}   // NVis
