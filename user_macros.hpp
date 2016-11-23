#ifndef BOOST_PROTO17_USER_MACROS_HPP_INCLUDED
#define BOOST_PROTO17_USER_MACROS_HPP_INCLUDED


#define BOOST_PROTO17_USER_UNARY_OPERATOR_MEMBER(op, op_name, this_type, expr_template) \
    auto operator op const &                                            \
    {                                                                   \
        using lhs_type = ::boost::proto17::expression_ref<this_type const &>; \
        using tuple_type = ::boost::hana::tuple<lhs_type>;              \
        return expr_template< ::boost::proto17::expr_kind::op_name, tuple_type>{ \
            tuple_type{lhs_type{*this}}                                 \
        };                                                              \
    }                                                                   \
    auto operator op &                                                  \
    {                                                                   \
        using lhs_type = ::boost::proto17::expression_ref<this_type &>; \
        using tuple_type = ::boost::hana::tuple<lhs_type>;              \
        return expr_template< ::boost::proto17::expr_kind::op_name, tuple_type>{ \
            tuple_type{lhs_type{*this}}                                 \
        };                                                              \
    }                                                                   \
    auto operator op &&                                                 \
    {                                                                   \
        using tuple_type = ::boost::hana::tuple<this_type>;             \
        return expr_template< ::boost::proto17::expr_kind::op_name, tuple_type>{ \
            tuple_type{std::move(*this)}                                \
        };                                                              \
    }

#define BOOST_PROTO17_USER_BINARY_OPERATOR_MEMBER(op, op_name, this_type, expr_template) \
    template <typename Expr>                                            \
    auto operator op (Expr && rhs) const &                              \
    {                                                                   \
        using lhs_type = ::boost::proto17::expression_ref<this_type const &>; \
        using rhs_type = ::boost::proto17::detail::operand_type_t<Expr>; \
        using tuple_type = ::boost::hana::tuple<lhs_type, rhs_type>;    \
        return expr_template< ::boost::proto17::expr_kind::op_name, tuple_type>{ \
            tuple_type{lhs_type{*this}, static_cast<Expr &&>(rhs)}      \
        };                                                              \
    }                                                                   \
    template <typename Expr>                                            \
    auto operator op (Expr && rhs) &                                    \
    {                                                                   \
        using lhs_type = ::boost::proto17::expression_ref<this_type &>; \
        using rhs_type = ::boost::proto17::detail::operand_type_t<Expr>; \
        using tuple_type = ::boost::hana::tuple<lhs_type, rhs_type>;    \
        return expr_template< ::boost::proto17::expr_kind::op_name, tuple_type>{ \
            tuple_type{lhs_type{*this}, static_cast<Expr &&>(rhs)}      \
        };                                                              \
    }                                                                   \
    template <typename Expr>                                            \
    auto operator op (Expr && rhs) &&                                   \
    {                                                                   \
        using rhs_type = ::boost::proto17::detail::operand_type_t<Expr>; \
        using tuple_type = ::boost::hana::tuple<this_type, rhs_type>;   \
        return expr_template< ::boost::proto17::expr_kind::op_name, tuple_type>{ \
            tuple_type{std::move(*this), static_cast<Expr &&>(rhs)}     \
        };                                                              \
    }

#define BOOST_PROTO17_USER_NON_MEMBER_BINARY_OPERATOR(op, op_name, expr_template) \
    template <typename T, typename Expr>                                \
    auto operator op (T && lhs, Expr const & rhs)                       \
        -> ::boost::proto17::detail::binary_op_result_t<                \
            ::boost::proto17::expr_kind::op_name,                       \
            T,                                                          \
            Expr const &,                                               \
            expr_template                                               \
        >                                                               \
    {                                                                   \
        using result_types = ::boost::proto17::detail::binary_op_result< \
            ::boost::proto17::expr_kind::op_name,                       \
            T,                                                          \
            Expr const &,                                               \
            expr_template                                               \
        >;                                                              \
        using lhs_type = typename result_types::lhs_type;               \
        using rhs_type = typename result_types::rhs_type;               \
        using tuple_type = ::boost::hana::tuple<lhs_type, rhs_type>;    \
        return {                                                        \
            tuple_type{static_cast<T &&>(lhs), rhs_type{rhs}}           \
        };                                                              \
    }                                                                   \
    template <typename T, typename Expr>                                \
    auto operator op (T && lhs, Expr & rhs)                             \
        -> ::boost::proto17::detail::binary_op_result_t<                \
            ::boost::proto17::expr_kind::op_name,                       \
            T,                                                          \
            Expr &,                                                     \
            expr_template                                               \
        >                                                               \
    {                                                                   \
        using result_types = ::boost::proto17::detail::binary_op_result< \
            ::boost::proto17::expr_kind::op_name,                       \
            T,                                                          \
            Expr &,                                                     \
            expr_template                                               \
        >;                                                              \
        using lhs_type = typename result_types::lhs_type;               \
        using rhs_type = typename result_types::rhs_type;               \
        using tuple_type = ::boost::hana::tuple<lhs_type, rhs_type>;    \
        return {                                                        \
            tuple_type{static_cast<T &&>(lhs), rhs_type{rhs}}           \
        };                                                              \
    }                                                                   \
    template <typename T, typename Expr>                                \
    auto operator op (T && lhs, ::boost::proto17::detail::remove_cv_ref_t<Expr> && rhs) \
        -> ::boost::proto17::detail::binary_op_result_t<                \
            ::boost::proto17::expr_kind::op_name,                       \
            T,                                                          \
            ::boost::proto17::detail::remove_cv_ref_t<Expr>,            \
            expr_template                                               \
        >                                                               \
    {                                                                   \
        using result_types = ::boost::proto17::detail::binary_op_result< \
            ::boost::proto17::expr_kind::op_name,                       \
            T,                                                          \
            ::boost::proto17::detail::remove_cv_ref_t<Expr>,            \
            expr_template                                               \
        >;                                                              \
        using lhs_type = typename result_types::lhs_type;               \
        using rhs_type = typename result_types::rhs_type;               \
        using tuple_type = ::boost::hana::tuple<lhs_type, rhs_type>;    \
        return {                                                        \
            tuple_type{static_cast<T &&>(lhs), std::move(rhs)}          \
        };                                                              \
    }

#endif
