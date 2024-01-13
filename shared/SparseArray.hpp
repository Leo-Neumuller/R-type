/*
** EPITECH PROJECT, 2023
** bs_rtype
** File description:
** SparseArray.hpp
*/

#ifndef BS_RTYPE_SPARSEARRAY_HPP
#define BS_RTYPE_SPARSEARRAY_HPP

#include <iostream>
#include <vector>
#include <optional>

/*
 * SparseArray
 * Class of the sparse array
 */
template <typename Component>
class SparseArray {
    public:
        using value_type = std::optional<Component>;
        using reference_type = std::optional<Component>&;
        using const_reference_type = const std::optional<Component>&;
        using container_t = std::vector<value_type>;
        using size_type = typename container_t::size_type;
        using iterator = typename container_t::iterator;
        using const_iterator = typename container_t::const_iterator;

        SparseArray() = default;
        SparseArray(SparseArray const &) = default;
        SparseArray(SparseArray &&) noexcept = default;
        ~SparseArray() = default;

        SparseArray &operator=(SparseArray const &) = default;
        SparseArray &operator=(SparseArray &&) noexcept = default;

        /*
         * operator[]
         * Operator for []
         * @param index: the index
         * @return: the value
         */
        reference_type operator[](size_type index)
        {
            return _data[index];
        }

        /*
         * operator[]
         * const Operator for []
         * @param index: the index
         * @return: the value
         */
        const_reference_type operator[](size_type index) const
        {
            if (index >= _data.size())
                return std::nullopt;

            return _data[index];
        }

        /*
         * begin
         * Begin of the array
         * @return: the iterator
         */
        iterator begin()
        {
            return _data.begin();
        }

        /*
         * begin
         * const Begin of the array
         * @return: the iterator
         */
        const_iterator begin() const
        {
            return _data.begin();
        }

        /*
         * cbegin
         * const Begin of the array
         * @return: the iterator
         */
        const_iterator cbegin() const
        {
            return _data.cbegin();
        }

        /*
         * end
         * End of the array
         * @return: the iterator
         */
        iterator end()
        {
            return _data.end();
        }

        /*
         * end
         * const End of the array
         * @return: the iterator
         */
        const_iterator end() const
        {
            return _data.end();
        }

        /*
         * cend
         * const End of the array
         * @return: the iterator
         */
        const_iterator cend() const
        {
            return _data.cend();
        }

        /*
         * size
         * Get the size of the array
         * @return: the size
         */
        size_type size() const
        {
            return _data.size();
        }

        /*
         * insert_at
         * Insert a value at a position
         * @param pos: the position
         * @param value: the component
         * @return: the value
         */
        reference_type insert_at(size_type pos, Component &value)
        {
            std::optional<Component> opt(value);

            if (pos >= _data.size())
            {
                _data.resize(pos + 1);
            }
            _data[pos] = opt;
            return _data[pos];
        }

        /*
         * insert_at
         * Insert a value at a position
         * @param pos: the position
         * @param value: the component
         * @return: the value
         */
        reference_type insert_at(size_type pos, Component &&value)
        {
            std::optional<Component> opt(std::move(value));

            if (pos >= _data.size())
            {
                _data.resize(pos + 1);
            }
            _data[pos] = opt;
            return _data[pos];
        }

        /*
         * insert_at
         * Insert a value at a position
         * @param pos: the position
         * @param params: the params
         * @return: the value
         */
        reference_type insert_at(size_type pos, value_type &value)
        {
            if (pos >= _data.size())
            {
                _data.resize(pos + 1);
            }
            _data[pos] = value;
            return _data[pos];
        }

        /*
         * insert_at
         * Insert a value at a position
         * @param pos: the position
         * @param params: the params
         * @return: the value
         */
        reference_type insert_at(size_type pos, value_type &&value)
        {
            if (pos >= _data.size())
            {
                _data.resize(pos + 1);
            }
            _data[pos] = std::move(value);
            return _data[pos];
        }

        /*
         * emplace_at
         * Emplace a value at a position
         * @param pos: the position
         * @param params: the params
         * @return: the value
         */
        template<class... Params>
        reference_type emplace_at(size_type pos, Params &&... params)
        {
            if (pos >= _data.size())
            {
                _data.resize(pos + 1);
            }
            _data[pos] = value_type(std::forward<Params>(params)...);
            return _data[pos];
        }

        /*
         * erase
         * Erase a value at a position
         * @param pos: the position
         */
        void erase(size_type pos)
        {
            if (pos >= _data.size())
                throw std::runtime_error("Index out of range");
            _data[pos] = std::nullopt;
        }

        /*
         * get_index
         * Get the index of a value
         * @param value: the value
         * @return: the index
         */
        size_type get_index(value_type const &value) const
        {
            for (size_type i = 0; i < _data.size(); i++) {
                if (std::addressof(_data[i]) == std::addressof(value))
                    return i;
            }
            return _data.size();
        }

        /*
         * has_index
         * Check if the index exists
         * @param index: the index
         * @return: true if exists, false otherwise
         */
        bool has_index(size_type index) const
        {
            if (index >= _data.size())
                return false;
            return _data[index].has_value();
        }

        /*
         * push_back
         * Push a value at the end of the array
         * @param value: the value
         */
        void push_back(value_type &&value) {
            _data.push_back(value);
        }

    protected:

    private:
        container_t _data;
};


#endif //BS_RTYPE_SPARSEARRAY_HPP
