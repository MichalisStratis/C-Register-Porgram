#include "Student.h"

#include <iostream>


void Student::FillCourse()
{
    m_course.Fill();

    if ( m_course.GetLevel() == 2 )
    {
        double k = m_course.Calculate();
        std::cout << "\n\nTHE OVERAL MARK OF THE STUDENT IN ALL THREE YEARS IS  " << k << " OR " << EvaluateMark( k ) << "\n";

        if ( k < 42 )
        {
            if ( k >= 25 )
                std::cout << "Overall aggregate for the course is 25 or higher, further assessment needed, reassessment granted.\n";
            else
                std::cout << "Overall aggregate for the course is 24 or lower, first attempt at the course, retake with full attendance granted.\n";
        }
    }
    else
    {
        std::cout << "\n\nNOT ALL LEVELS ARE COMPLETED. THE MARK IS N/A.\n";
    }
    std::cout << "\n\n";
}

void Student::SetMarks( double l1, double l2, double l3, double tot )
{
    m_course.SetMarks(l1,l2,l3,tot);
}

void Student::SetLevelSubCourseMarks( double sb1, double sb2, double sb3, double sb4, double sb5, double sb6 )
{
    m_course.SetSubcourseMarks( 0, sb1, sb2 );
    m_course.SetSubcourseMarks( 1, sb3, sb4 );
    m_course.SetSubcourseMarks( 2, sb5, sb6 );
}

std::string Student::toString() const
{
    std::string s = "";

    s += std::to_string( m_id ) + "|" + m_name + "|" + m_course.toString() + "\n";

    return s;
}

std::string Student::Info() const
{
    std::string s = "";
    s += std::to_string( m_id ) + " \t" + m_name + " \t" + m_course.GetName() + " \t";
    s += m_course.GetStrStart() + " \t" + m_course.GetStrEnd() + " \t";
    s += m_course.GetMarks() + "\n";

    return s;
}

Student Student::fromString( std::string& s )
{
    std::string name;
    std::size_t pos1 = 0, pos2 = 0;
    long startDate = 0L;
    long endDate = 0L;
    int courseId = 0;
    long stId = -1;
    double m1 = -1, m2 = -1, m3 = -1, tot = -1;
    int level = 0;
    double sb1 = -1, sb2 = -1, sb3 = -1, sb4 = -1, sb5 = -1, sb6 = -1;

    pos2 = s.find( "|" );
    stId = std::stol(s.substr( 0, pos2 ));
    
    pos1 = pos2 + 1;
    pos2 = s.find( "|", pos1 );
    name = s.substr( pos1, pos2 - pos1);
    
    pos1 = pos2 + 1;
    pos2 = s.find( "|", pos1 );
    courseId = std::stoi(s.substr( pos1, pos2 - pos1 ));

    pos1 = pos2 + 1;
    pos2 = s.find( "|", pos1 );
    startDate = std::stol( s.substr( pos1, pos2 - pos1 ));

    pos1 = pos2 + 1;
    pos2 = s.find( "|", pos1 );
    endDate = std::stol( s.substr( pos1, pos2 - pos1 ));

    pos1 = pos2 + 1;
    pos2 = s.find( "|", pos1 );
    m1 = std::stod(s.substr( pos1, pos2 - pos1 ));

    pos1 = pos2 + 1;
    pos2 = s.find( "|", pos1 );
    sb1 = std::stod( s.substr( pos1, pos2 - pos1 ) );

    pos1 = pos2 + 1;
    pos2 = s.find( "|", pos1 );
    sb2 = std::stod( s.substr( pos1, pos2 - pos1 ) );

    pos1 = pos2 + 1;
    pos2 = s.find( "|", pos1 );
    m2 = std::stod( s.substr( pos1, pos2 - pos1 ));

    pos1 = pos2 + 1;
    pos2 = s.find( "|", pos1 );
    sb3 = std::stod( s.substr( pos1, pos2 - pos1 ) );

    pos1 = pos2 + 1;
    pos2 = s.find( "|", pos1 );
    sb4 = std::stod( s.substr( pos1, pos2 - pos1 ) );

    pos1 = pos2 + 1;
    pos2 = s.find( "|", pos1 );
    m3 = std::stod( s.substr( pos1, pos2 - pos1 ));

    pos1 = pos2 + 1;
    pos2 = s.find( "|", pos1 );
    sb5 = std::stod( s.substr( pos1, pos2 - pos1 ) );

    pos1 = pos2 + 1;
    pos2 = s.find( "|", pos1 );
    sb6 = std::stod( s.substr( pos1, pos2 - pos1 ) );

    pos1 = pos2 + 1;
    pos2 = s.find( "|", pos1 );
    tot = std::stod( s.substr( pos1, pos2 - pos1 ));

    Student st(name, stId, courseId, startDate, endDate, level);
    st.SetMarks( m1, m2, m3, tot );
    st.SetLevelSubCourseMarks( sb1, sb2, sb3, sb4, sb5, sb6 );
    return st;
}

static long DtToLong( std::string dt )
{
    std::size_t day_offset = dt.find( "/" );
    int day = std::stoi( dt.substr( 0, day_offset ) );

    std::size_t month_offset = dt.rfind( "/" );
    int month = std::stoi( dt.substr( day_offset + 1, month_offset - day_offset - 1 ) );

    int year = std::stoi( dt.substr( month_offset + 1 ) );

    return year * 10000 + month * 100 + day;
}

Student Student::FromInfo( std::string& s )
{
    std::string name;
    std::size_t pos1 = 0, pos2 = 0;
    long startDate = 0L;
    long endDate = 0L;
    std::string courseName;
    int courseId = 0;
    long stId = -1;
    double m1 = -1, m2 = -1, m3 = -1, tot = -1;
    int level = 0;

    pos2 = s.find( "|" );
    stId = std::stol( s.substr( 0, pos2 ) );

    pos1 = pos2 + 1;
    pos2 = s.find( "|", pos1 );
    name = s.substr( pos1, pos2 - pos1 );

    pos1 = pos2 + 1;
    pos2 = s.find( "|", pos1 );
    courseName = s.substr( pos1, pos2 - pos1 );

    courseId = Course::IdByName( courseName );

    pos1 = pos2 + 1;
    pos2 = s.find( "|", pos1 );
    std::string stDt = s.substr( pos1, pos2 - pos1 );
    startDate = DtToLong( stDt );

    pos1 = pos2 + 1;
    pos2 = s.find( "|", pos1 );
    std::string eDt = s.substr( pos1, pos2 - pos1 );
    endDate = DtToLong( eDt );

    pos1 = pos2 + 1;
    pos2 = s.find( "|", pos1 );
    m1 = std::stod( s.substr( pos1, pos2 - pos1 ) );

    pos1 = pos2 + 1;
    pos2 = s.find( "|", pos1 );
    m2 = std::stod( s.substr( pos1, pos2 - pos1 ) );

    pos1 = pos2 + 1;
    pos2 = s.find( "|", pos1 );
    m3 = std::stod( s.substr( pos1, pos2 - pos1 ) );

    pos1 = pos2 + 1;
    pos2 = s.find( "|", pos1 );
    tot = std::stod( s.substr( pos1, pos2 - pos1 ) );

    Student st( name, stId, courseId, startDate, endDate, level );
    st.SetMarks( m1, m2, m3, tot );
    return st;
}