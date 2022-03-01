#include "SubCourse.h"

#include <iostream>
#include <string>

std::string MarkToString( double mark )
{
    if ( mark < 0 )
        return ( "N/A" );
    std::string s = std::to_string( mark ) + " or " + EvaluateMark( mark ) + " " + IsGoodMark( mark );
    return s;
}

std::string IsGoodMark( double mark )
{
    if ( mark >= 42 )
        return "Passed";
    else return "Failed";
}

std::string EvaluateMark( double mark )
{
    if ( mark >= 92 )
        return "A++";
    else if ( mark >= 84 )
        return "A +";
    else if ( mark >= 76 )
        return "A";
    else if ( mark >= 70 )
        return "A -";
    else if ( mark >= 68 )
        return "B +";
    else if ( mark >= 64 )
        return "B";
    else if ( mark >= 60 )
        return "B -";
    else if ( mark >= 58 )
        return "C +";
    else if ( mark >= 54 )
        return "C";
    else if ( mark >= 50 )
        return "C -";
    else if ( mark >= 48 )
        return "D";
    else if ( mark >= 42 )
        return "E";
    else if ( mark >= 38 )
        return "F +";
    else if ( mark >= 32 )
        return "F";
    else if ( mark >= 22 )
        return "F -";
    else if ( mark >= 12 )
        return "WF";
    else
        return "U";
}

static void AskQuestion()
{
    std::cout << "Select the reason.\n";
    std::cout << "1. Unexplained Non Submission, or absence from exam/test, etc\n";
    std::cout << "2. Assessment deferred due to valid Mitigating circumstances\n";
    std::cout << "3. Plagiarism or other academic misconduct\n";
    std::cout << "4. Mark reduced to 0 due to Late submission\n";
    std::cout << "5. Undertaking block/module on Attendance Only\n";
    std::cout << "6. Not yet submitted/attended – extension given\n";
    
    int res = 0;
    do
    {
        std::cout << "Your choice: ";
        std::cin >> res;
        if ( res < 1 || res > 6 )
            std::cout << "ERROR: Incorrect code.\n";
    }
    while ( res < 1 || res > 6 );
}

static int EnterGrade( std::string a, int nGrade )
{
    int n = 0;
    do
    {
        std::cout << "Enter the grade for the " << a << " assesment #" << nGrade + 1 << ": ";
        std::cin >> n;
        if ( n < 0 || n > 100 )
            std::cout << "ERROR: incorrect mark. Try again.\n";
        else if ( n == 0 )
        {
            AskQuestion();
        }
    }
    while ( n < 0 || n > 100 );
    return n;
}

void SubCourse::Fill(int level, int n)
{
    double resCW = 0;
    double resP = 0;
    double resE = 0;
    for ( int i = 0; i < m_acourse; i++ )
    {
        resCW += EnterGrade( "coursework", i );
    }
    if ( m_acourse > 0 )
    {
        resCW /= m_acourse;
    }

    for ( int i = 0; i < m_aportfolio; i++ )
    {
        resP += EnterGrade( "portfolio", i );
    }
    if ( m_aportfolio > 0 )
        resP /= m_aportfolio;

    resE = EnterGrade( "exam", 0 );

    if ( level == 2 && n == 1)
        EnterGrade( "Project", 0 );

    switch ( level )
    {
    case 0:
        m_coursemark = 0.34 * resCW + 0.33 * resP + 0.33 * resE;
        break;
    case 1:
        m_coursemark = 0.5 * resCW + 0.25 * resP + 0.25 * resE;
        break;
    case 2:
        m_coursemark = 0.67 * resCW + 0.33 * resE;
        break;
    }
}