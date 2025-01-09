#ifndef _ARGS_TYPE_TRAITS_HPP_
#define _ARGS_TYPE_TRAITS_HPP_

#include <string>
#include <type_traits>

namespace args
{
    namespace details
    {
        template <typename T, typename _ = void>
        struct is_push_backable : std::false_type
        {};

        template <typename T, typename _ = void>
        struct is_pushable : std::false_type
        {};

        template <typename T, typename _ = void>
        struct is_insertable : std::false_type
        {};

        template <typename... Ts>
        struct is_container_helper
        {};

        template <typename T>
        struct is_push_backable<
            T,
            std::conditional_t<
                false,
                is_container_helper<
                    typename T::value_type,
                    decltype(std::declval<T>().push_back(typename T::value_type()))>,
                void>> : public std::true_type
        {};

        template <typename T>
        struct is_pushable<
            T,
            std::conditional_t<
                false,
                is_container_helper<
                    typename T::value_type,
                    decltype(std::declval<T>().push(typename T::value_type()))>,
                void>> : public std::true_type
        {};

        template <typename T>
        struct is_insertable<
            T,
            std::conditional_t<
                false,
                is_container_helper<
                    typename T::value_type,
                    decltype(std::declval<T>().insert(typename T::value_type()))>,
                void>> : public std::true_type
        {};

        template <typename T>
        using is_allowed_type = std::conditional_t<std::is_same_v<T, int> ||
                                                   std::is_same_v<T, long> ||
                                                   std::is_same_v<T, unsigned int> ||
                                                   std::is_same_v<T, unsigned long> ||
                                                   std::is_same_v<T, double> ||
                                                   std::is_same_v<T, float> ||
                                                   std::is_same_v<T, bool> ||
                                                   std::is_same_v<T, std::string>,
                                                   std::true_type,
                                                   std::false_type>;

        template <typename T>
        inline constexpr bool is_allowed_type_v = is_allowed_type<T>::value;

        template <typename T>
        inline constexpr bool is_push_backable_v = is_push_backable<T>::value;

        template <typename T>
        inline constexpr bool is_pushable_v = is_pushable<T>::value;

        template <typename T>
        inline constexpr bool is_insertable_v = is_insertable<T>::value;
    }
}

#endif
