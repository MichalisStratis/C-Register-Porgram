#include "Course.h"
#include <iostream>

std::string Course::m_courses[7] = { "Mathematics", "Computer Science", "Music", "Accounting and Finance","Business Management", "Psychology", "Sports Science" };

Course::Course( int courseId, long startDate, long endDate, int levelId ) :
    m_id( courseId ),
    m_start( startDate ),
    m_end( endDate ),
    m_level( levelId )
{

}

int Course::SelectCourse()
{
    int num;
    std::cout << "  1. Mathematics\n";
    std::cout << "  2. Computer Science\n";
    std::cout << "  3. Music\n";
    std::cout << "  4. Accounting and Finance\n";
    std::cout << "  5. Business Management\n";
    std::cout << "  6. Psychology\n";
    std::cout << "  7. Sports Science\n";
   

    do
    {
        std::cout << "  Select item number:";
        std::cin >> num;
        if ( num < 1 || num > m_ncourses )
            std::cout << "  ERROR: Incorrect number. Try again.\n";
    }
    while ( num < 1 || num > m_ncourses );

    return num - 1;
}

int Course::SelectLevel()
{
    int num;
    char level;

    do
    {
        std::cout << "  ( C, I or H ): ";
        std::cin >> level;
        switch ( level )
        {
        case 'c': case 'C': num = Level::LevelId::C; break;
        case 'h': case 'H': num = Level::LevelId::H; break;
        case 'i': case 'I': num = Level::LevelId::I; break;
        default: num = Level::LevelId::EMPTY;
        }
    }
    while ( num == Level::LevelId::EMPTY );

    return num;
}

void Course::Fill()
{
    for ( int i = 0; i <= m_level; i++ )
    {
        m_levels[i].SetLevel( i );
        std::size_t n1, n2, n3, n4;
        std::cout << "\n-------------------- LEVEL " << Level::DecodeLevel( i ) << " --------------------\n";
        std::cout << "Number of asessments for Coursework for Subcourse 1 in Level " << Level::DecodeLevel( i ) << ": ";
        std::cin >> n1;
        std::cout << "Number of asessments for Portfolio for Subcourse 1 in Level " << Level::DecodeLevel( i ) << ": ";
        std::cin >> n2;
        std::cout << "Number of asessments for Coursework for Subcourse 2 in Level " << Level::DecodeLevel( i ) << ": ";
        std::cin >> n3;
        std::cout << "Number of asessments for Portfolio for Subcourse 2 in Level " << Level::DecodeLevel( i ) << ": ";
        std::cin >> n4;
        std::cout << "  ----- SubCourse 1 -----\n";
        m_levels[i].FillSubcourseData( 0, n1, n2 );
        std::cout << "  ----- SubCourse 2 -----\n";
        m_levels[i].FillSubcourseData( 1, n3, n4 );

        std::cout << "\n  The level " << Level::DecodeLevel( i ) << " overal is " << m_levels[i].Calculate() << " or " << EvaluateMark( m_levels[i].Calculate() ) << "\n";
    }
    m_mark = Calculate();
}

double Course::Calculate()
{
    if ( m_levels[0].GetMark() != -1 && m_levels[1].GetMark() != -1 && m_levels[2].GetMark() != -1 )
        m_mark = m_levels[0].GetMark() * 0.1 + m_levels[1].GetMark() * 0.3 + m_levels[2].GetMark() * 0.6;
    else
        m_mark = -1;
    return m_mark;
}

std::string Course::GetMarks() const
{
    std::string s = "";
    for ( int i = 0; i <= m_level; i++ )
    {
        s += MarkToString( m_levels[i].GetMark() ) + " \t";
    }
    for ( int i = m_level + 1; i < 3; i++ )
    {
        s += "N/A";
        s += " \t";
    }
    if ( m_level != 2 )
    {
        s += "N/A";
    }
    else
    {
        s += MarkToString( m_mark );
    }
    return s;
}

std::string Course::InfoMarks(int level) const
{
    std::string s = "";
    s += "=== Level " + Level::DecodeLevel( level ) + " ===\n";
    s += "Subcourses: 1 - " + MarkToString( m_levels[level].GetSubCourseMark(0) ) + ";\t2 - " + MarkToString( m_levels[level].GetSubCourseMark(1) ) + "\n";
    s += "Overall: " + MarkToString( m_levels[level].GetMark() ) + " \n";

    return s;
}


std::string Course::toString() const
{
    std::string s = "";

    s += std::to_string( m_id ) + "|" + std::to_string( m_start ) + "|" + std::to_string( m_end );
    for ( int i = 0; i < 3; i++ )
    {
        s += "|" + std::to_string( m_levels[i].GetMark() ) + "|" + std::to_string( m_levels[i].GetSubCourseMark(0) ) + "|" + std::to_string( m_levels[i].GetSubCourseMark(0) );
    }
    s += "|" + std::to_string( m_mark );

    return s;
}

void Course::SetMarks( double l1, double l2, double l3, double tot )
{
    m_mark = tot;
    
    m_levels[0].SetMark( l1 );
    m_levels[0].SetLevel( 0 );
    m_levels[1].SetMark( l2 );
    m_levels[1].SetLevel( 1 );
    m_levels[2].SetMark( l3 );
    m_levels[2].SetLevel( 2 );

    if ( l2 == -1 )
        m_level = 0;
    else if ( l3 == -1 )
        m_level = 1;
    m_level = 2;

}

void Course::SetSubcourseMarks( int level, double sb1, double sb2 )
{
    m_levels[level].SetSubcourseMarks( sb1, sb2 );
}