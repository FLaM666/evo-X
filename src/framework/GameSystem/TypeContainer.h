/*
 * Copyright (C) 2005-2009 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef MANGOS_TYPECONTAINER_H
#define MANGOS_TYPECONTAINER_H

/*
 * Here, you'll find a series of containers that allow you to hold multiple
 * types of object at the same time.
 */

#include <map>
#include <vector>
#include "Platform/Define.h"
#include "Utilities/TypeList.h"
#include "Utilities/UnorderedMap.h"
#include "GameSystem/GridRefManager.h"

template<class OBJECT, class KEY_TYPE> struct ContainerUnorderedMap
{
    UNORDERED_MAP<KEY_TYPE, OBJECT*> _element;
};
template<class KEY_TYPE> struct ContainerUnorderedMap<TypeNull, KEY_TYPE>
{
};
template<class H, class T, class KEY_TYPE> struct ContainerUnorderedMap< TypeList<H, T>, KEY_TYPE >
{
    ContainerUnorderedMap<H, KEY_TYPE> _elements;
    ContainerUnorderedMap<T, KEY_TYPE> _TailElements;
};

template<class OBJECT_TYPES, class KEY_TYPE = OBJECT_HANDLE>
class TypeUnorderedMapContainer
{
    public:
        template<class SPECIFIC_TYPE> bool insert(KEY_TYPE handle, SPECIFIC_TYPE* obj)
        {
            return TypeUnorderedMapContainer::insert(i_elements, handle, obj);
        }
        template<class SPECIFIC_TYPE> bool erase(KEY_TYPE handle, SPECIFIC_TYPE* /*obj*/)
        {
            return TypeUnorderedMapContainer::erase(i_elements, handle, (SPECIFIC_TYPE*)NULL);
        }
        template<class SPECIFIC_TYPE> SPECIFIC_TYPE* find(KEY_TYPE hdl, SPECIFIC_TYPE* /*obj*/)
        {
            return TypeUnorderedMapContainer::find(i_elements, hdl, (SPECIFIC_TYPE*)NULL);
        }
    private:
        ContainerUnorderedMap<OBJECT_TYPES, KEY_TYPE> i_elements;

        // Helpers
        // Insert helpers
        template<class SPECIFIC_TYPE> static bool insert(ContainerUnorderedMap<SPECIFIC_TYPE, KEY_TYPE>& elements, KEY_TYPE handle, SPECIFIC_TYPE* obj)
        {
            typename UNORDERED_MAP<OBJECT_HANDLE, SPECIFIC_TYPE*>::iterator i = elements._element.find(handle);
            if (i == elements._element.end())
            {
                elements._element[handle] = obj;
                return true;
            }
            else
            {
                assert (i->second == obj && "Object with certain key already in but objects are different!");
                return false;
            }
        }
        template<class SPECIFIC_TYPE> static bool insert(ContainerUnorderedMap<TypeNull, KEY_TYPE>& /*elements*/, KEY_TYPE /*handle*/, SPECIFIC_TYPE* /*obj*/)
        {
            return false;
        }
        template<class SPECIFIC_TYPE, class T> static bool insert(ContainerUnorderedMap<T, KEY_TYPE>& /*elements*/, KEY_TYPE /*handle*/, SPECIFIC_TYPE* /*obj*/)
        {
            return false;
        }
        template<class SPECIFIC_TYPE, class H, class T> static bool insert(ContainerUnorderedMap< TypeList<H, T>, KEY_TYPE >& elements, KEY_TYPE handle, SPECIFIC_TYPE* obj)
        {
            bool ret = TypeUnorderedMapContainer::insert(elements._elements, handle, obj);
            return ret ? ret : TypeUnorderedMapContainer::insert(elements._TailElements, handle, obj);
        }
        // Find helpers
        template<class SPECIFIC_TYPE> static SPECIFIC_TYPE* find(ContainerUnorderedMap<SPECIFIC_TYPE, KEY_TYPE>& elements, KEY_TYPE hdl, SPECIFIC_TYPE* /*obj*/)
        {
            typename UNORDERED_MAP<OBJECT_HANDLE, SPECIFIC_TYPE*>::iterator i = elements._element.find(hdl);
            if (i == elements._element.end())
                return NULL;
            else
                return i->second;
        }
        template<class SPECIFIC_TYPE> static SPECIFIC_TYPE* find(ContainerUnorderedMap<TypeNull, KEY_TYPE>& /*elements*/, KEY_TYPE /*hdl*/, SPECIFIC_TYPE* /*obj*/)
        {
            return NULL;
        }
        template<class SPECIFIC_TYPE, class T> static SPECIFIC_TYPE* find(ContainerUnorderedMap<T, KEY_TYPE>& /*elements*/, KEY_TYPE /*hdl*/, SPECIFIC_TYPE* /*obj*/)
        {
            return NULL;
        }
        template<class SPECIFIC_TYPE, class H, class T> static SPECIFIC_TYPE* find(ContainerUnorderedMap< TypeList<H, T>, KEY_TYPE >& elements, KEY_TYPE hdl, SPECIFIC_TYPE* /*obj*/)
        {
            SPECIFIC_TYPE* ret = TypeUnorderedMapContainer::find(elements._elements, hdl, (SPECIFIC_TYPE*)NULL);
            return ret ? ret : TypeUnorderedMapContainer::find(elements._TailElements, hdl, (SPECIFIC_TYPE*)NULL);
        }
        // Erase helpers
        template<class SPECIFIC_TYPE> static bool erase(ContainerUnorderedMap<SPECIFIC_TYPE, KEY_TYPE>& elements, KEY_TYPE handle, SPECIFIC_TYPE* /*obj*/)
        {
            elements._element.erase(handle);

            return true;
        }
        template<class SPECIFIC_TYPE> static bool erase(ContainerUnorderedMap<TypeNull, KEY_TYPE>& /*elements*/, KEY_TYPE /*handle*/, SPECIFIC_TYPE* /*obj*/)
        {
            return false;
        }
        template<class SPECIFIC_TYPE, class T> static bool erase(ContainerUnorderedMap<T, KEY_TYPE>& /*elements*/, KEY_TYPE /*handle*/, SPECIFIC_TYPE* /*obj*/)
        {
            return false;
        }
        template<class SPECIFIC_TYPE, class H, class T> static bool erase(ContainerUnorderedMap< TypeList<H, T>, KEY_TYPE >& elements, KEY_TYPE handle, SPECIFIC_TYPE* /*obj*/)
        {
            bool ret = TypeUnorderedMapContainer::erase(elements._elements, handle, (SPECIFIC_TYPE*)NULL);
            return ret ? ret : TypeUnorderedMapContainer::erase(elements._TailElements, handle, (SPECIFIC_TYPE*)NULL);
        }
};

/*
 * @class ContainerMapList is a mulit-type container for map elements
 * By itself its meaningless but collaborate along with TypeContainers,
 * it become the most powerfully container in the whole system.
 */
template<class OBJECT> struct ContainerMapList
{
    //std::map<OBJECT_HANDLE, OBJECT *> _element;
    GridRefManager<OBJECT> _element;
};

template<> struct ContainerMapList<TypeNull>                /* nothing is in type null */
{
};
template<class H, class T> struct ContainerMapList<TypeList<H, T> >
{
    ContainerMapList<H> _elements;
    ContainerMapList<T> _TailElements;
};

/*
 * @class ContaierArrayList is a multi-type container for
 * array of elements.
 */
template<class OBJECT> struct ContainerArrayList
{
    std::vector<OBJECT> _element;
};

// termination condition
template<> struct ContainerArrayList<TypeNull> {};
// recursion
template<class H, class T> struct ContainerArrayList<TypeList<H, T> >
{
    ContainerArrayList<H> _elements;
    ContainerArrayList<T> _TailElements;
};

/*
 * @class ContainerList is a simple list of different types of elements
 *
 */
template<class OBJECT> struct ContainerList
{
    OBJECT _element;
};

/* TypeNull is underfined */
template<> struct ContainerList<TypeNull> {};
template<class H, class T> struct ContainerList<TypeList<H, T> >
{
    ContainerList<H> _elements;
    ContainerMapList<T> _TailElements;
};

#include "TypeContainerFunctions.h"

/*
 * @class TypeMapContainer contains a fixed number of types and is
 * determined at compile time.  This is probably the most complicated
 * class and do its simplest thing, that is, holds objects
 * of different types.
 */

template<class OBJECT_TYPES>
class MANGOS_DLL_DECL TypeMapContainer
{
    public:
        template<class SPECIFIC_TYPE> size_t Count() const { return MaNGOS::Count(i_elements, (SPECIFIC_TYPE*)NULL); }

        template<class SPECIFIC_TYPE> SPECIFIC_TYPE* find(OBJECT_HANDLE hdl, SPECIFIC_TYPE *fake) { return MaNGOS::Find(i_elements, hdl,fake); }

        /// find a specific type of object in the container
        template<class SPECIFIC_TYPE> const SPECIFIC_TYPE* find(OBJECT_HANDLE hdl, SPECIFIC_TYPE *fake) const { return MaNGOS::Find(i_elements, hdl,fake); }

        /// inserts a specific object into the container
        template<class SPECIFIC_TYPE> bool insert(OBJECT_HANDLE hdl, SPECIFIC_TYPE *obj)
        {
            SPECIFIC_TYPE* t = MaNGOS::Insert(i_elements, obj, hdl);
            return (t != NULL);
        }

        ///  Removes the object from the container, and returns the removed object
        template<class SPECIFIC_TYPE> bool remove(SPECIFIC_TYPE* obj, OBJECT_HANDLE hdl)
        {
            SPECIFIC_TYPE* t = MaNGOS::Remove(i_elements, obj, hdl);
            return (t != NULL);
        }

        ContainerMapList<OBJECT_TYPES> & GetElements(void) { return i_elements; }
        const ContainerMapList<OBJECT_TYPES> & GetElements(void) const { return i_elements;}

    private:
        ContainerMapList<OBJECT_TYPES> i_elements;
};
#endif
