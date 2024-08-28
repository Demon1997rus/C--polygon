#include "date.h"

#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/qi.hpp>

Date parse_date_time1(const std::string &s)
{
    using boost::phoenix::ref;
    using boost::spirit::qi::_1;
    using boost::spirit::qi::char_;
    using boost::spirit::qi::ushort_;
    Date res;
    const char *first = s.data();
    const char *const end = first + s.size();
    const bool success = boost::spirit::qi::parse(
        first, end,
        //	Реализация	правила	«date-fullyear»	из	грамматики	РБНФ.
        ushort_[ref(res.year) = _1] >> char_('-') >> ushort_[ref(res.month) = _1] >>
            char_('-') >> ushort_[ref(res.day) = _1]);
    if (!success || first != end) {
        throw std::logic_error("Parsing failed");
    }
    return res;
}

Date parse_date_time2(const std::string &s)
{
    using boost::phoenix::ref;
    using boost::spirit::qi::_1;
    using boost::spirit::qi::char_;
    using boost::spirit::qi::uint_parser;

    Date res;

    // Используем	unsigned short в качестве выходного	типа; требуется	система
    // счисления по основанию 10 и от 2 до 2 цифр (то есть ровно 2 цифры).
    uint_parser<unsigned short, 10, 2, 2> u2_;

    //	Используем	unsigned	short	в	качестве	выходного	типа;	требуется
    // десятичная 	система	счисления	и	от	4	до	4	цифр	(то	есть	ровно	4
    // цифры).
    uint_parser<unsigned short, 10, 4, 4> u4_;

    const char *first = s.data();
    const char *const end = first + s.size();
    const bool success = boost::spirit::qi::parse(first, end,
                                                  u4_[ref(res.year) = _1] >> char_('-') >>
                                                      u2_[ref(res.month) = _1] >> char_('-') >>
                                                      u2_[ref(res.day) = _1]);
    if (success == false || first != end) {
        throw std::logic_error("Parsing failed");
    }
    return res;
}

void set_zone_offset(DateTime &dt, char sign, unsigned short hours, unsigned short minutes)
{
    dt.setZoneOffsetType(sign == '+' ? DateTime::OFFSET_UTC_PLUS : DateTime::OFFSET_UTC_MINUS);
    dt.setZoneOffsetInMin(hours * 60 + minutes);
}

DateTime parse_datetime(const std::string &s)
{
    //    using boost::phoenix::bind;
    using boost::phoenix::ref;
    using boost::spirit::qi::_1;
    using boost::spirit::qi::_2;
    using boost::spirit::qi::_3;
    using boost::spirit::qi::char_;
    using boost::spirit::qi::uint_parser;
    DateTime res;

    //	Используем	unsigned	short	в	качестве	выходного	типа;	требуется
    //	десятичная	система	счисления	и	от	2	до	2	цифр	(то	есть	ровно	2
    //цифры).
    uint_parser<unsigned short, 10, 2, 2> u2_;

    //	Используем	unsigned	short	в	качестве	выходного	типа;	требуется
    //	десятичная	система	счисления	и	от	4	до	4	цифр	(то	есть	ровно	4
    //цифры).
    uint_parser<unsigned short, 10, 4, 4> u4_;

    //    boost::spirit::qi::rule<const char *, void()> timezone_parser =
    //        -(char_('Z')[bind(&DateTime::set)]);

    return res;
}
