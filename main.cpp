#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Student.h"

enum OPTION
{
    ADD = 1, EDIT, READ, VIEW, EXIT
};

std::vector<Student> ReadData()
{
    std::vector<Student> vec;

    std::string line;
    std::ifstream studentsBase( "database.txt" );
    if ( studentsBase.is_open() )
    {
        while ( std::getline( studentsBase, line ) )
        {
            if ( line.size() )
                vec.emplace_back( Student::fromString( line ) );
        }
        studentsBase.close();
    }
    else
    {
        std::cout << "Unable to open file with students\n";
    }

    return std::move( vec );
}

void UpdateData( std::vector<Student>& vec )
{
    std::ofstream studentsBase;
    studentsBase.open( "database.txt" );
    for ( const auto& st : vec )
    {
        studentsBase << st.toString();
    }
    studentsBase.close();
}

int checkDate( int day, int month, int year )
{
    if ( day < 1 || day > 31 )
        return false;
    else if ( month < 1 || month > 12 )
        return false;
    else if ( year < 1900 || year > 2022 )
        return false;

    if ( ( month == 4 || month == 6 || month == 9 || month == 11 ) && day == 31 )
        return false;
    else if ( ( month == 2 ) && ( year % 4 == 0 ) && day > 29 )
        return false;
    else if ( ( month == 2 ) && ( year % 4 != 0 ) && day > 28 )
        return false;

    return true;
}

long InputDate()
{
    std::string dt;
    int day, month, year;

    do
    {
        std::cin >> dt;

        std::size_t day_offset = dt.find( "/" );
        day = std::stoi( dt.substr( 0, day_offset ) );

        std::size_t month_offset = dt.rfind( "/" );
        month = std::stoi( dt.substr( day_offset + 1, month_offset - day_offset - 1 ) );

        year = std::stoi( dt.substr( month_offset + 1 ) );

        if ( !checkDate( day, month, year ) )
        {
            std::cout << "  ERROR: Incorect date. Try again.\n";
            std::cout << "  Enter date: ";
        }
    }
    while ( !checkDate( day, month, year ) );

    return year * 10000 + month * 100 + day;
}


void AddStudent( std::vector<Student>& vec)
{
    std::cout << "=== REGISTER STUDENT ===\n";

    std::string studentName;
    std::cout << "(register) Input student name: " ;
    std::getline( std::cin >> std::ws, studentName );

    long studentId;
    std::cout << "(register) Input student id number: ";
    std::cin >> studentId;

    for ( const auto& st : vec )
    {
        if ( studentId == st.GetId() )
        {
            std::cout << "ERROR: The record already exists!\n";
            return;
        }
    }
    

    
    std::cout << "(register) Select course:\n";
    int courseId = Course::SelectCourse();
    
    long startDate, endDate;
    do
    {
        std::cout << "(register) Input course start date in format dd/mm/yyyy: ";
        startDate = InputDate();
        std::cout << "(register) Input course end date in format dd/mm/yyyy: ";
        endDate = InputDate();

        if ( startDate > endDate )
            std::cout << "ERROR: End date is before start date.\n";

    }
    while ( startDate > endDate );

    std::cout << "(register) Enter the level:\n";
    int levelId = Course::SelectLevel();

    Student st( studentName, studentId, courseId, startDate, endDate, levelId );

    st.FillCourse();

    int ans = 0;
    do
    {
        std::cout << "\nSAVE ? (1 - yes, 0 - no): ";
        std::cin >> ans;
    }
    while ( ans != 0 and ans != 1 );

    if ( ans == 1 )
        vec.emplace_back( std::move( st ) );
}


static double EnterGrade()
{
    double n = 0;
    do
    {
        std::cout << "Enter the grade: ";
        std::cin >> n;
        if ( n < 0 || n > 100 )
            std::cout << "ERROR: incorrect mark. Try again.\n";
    }
    while ( n < 0 || n > 100 );
 
    return n;
}

void EditMarks( std::vector<Student>& vec, std::size_t ind )
{
    std::cout << "(edit) Enter the level:\n";
    int levelId = Course::SelectLevel();

    std::cout << vec[ind].GetLevelInfo( levelId );

    std::cout << "1. Edit subcourse 1 mark\n";
    std::cout << "2. Edit subcourse 2 mark\n";
    std::cout << "3. Edit Overall mark\n";

    int choice = 0;

    do
    {
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if ( choice < 1 || choice > 3 )
        {
            std::cout << "ERROR: Incorrect choice.\n";
            choice = 0;
        }
    }
    while ( !choice );

    double grade;
    std::cout << "Enter new grade: ";
    grade = EnterGrade();
    switch ( choice )
    {
    case 1:
        vec[ind].SetLevelSubMark( levelId, 0, grade );
        break;
    case 2:
        vec[ind].SetLevelSubMark( levelId, 0, grade );
        break;
    default:
        vec[ind].SetLevelMark( levelId, grade );
        break;
    }

    std::cout << "New info:\n";
    std::cout << vec[ind].GetLevelInfo( levelId );

}

void EditStudent( std::vector<Student>& vec)
{
    long id = 1;
    std::cout << "=== EDIT STUDENT ===\n";
    std::cout << "(edit) Enter students ID: ";

    std::cin >> id;
    bool bFound = false;
    std::size_t ind = 0;
    for ( std::size_t i = 0; i < vec.size(); i++ )
    {
        if ( id == vec[i].GetId() )
        {
            bFound = true;
            ind = i;
            break;
        }
    }
    if ( !bFound )
    {
        std::cout << "ERROR: Student id " << id << " not found.\n";
        return;
    }

    std::cout << vec[ind].Info() << "\n";
    std::cout << "(edit) Choose the item to edit\n";
    std::cout << "1. ID\n";
    std::cout << "2. Name\n";
    std::cout << "3. Course name\n";
    std::cout << "4. Course start date\n";
    std::cout << "5. Course end date\n";
    std::cout << "6. Marks\n";
    int choice = 0;
    do
    {
        std::cin >> choice;
        if ( choice < 1 || choice > 6 )
        {
            std::cout << "ERROR: Incorrect choice\n";
            choice = 0;
        }
    }
    while ( !choice );

    switch ( choice )
    {
    case 1:
        long id_new;
        std::cout << "(edit) Input student ID: ";
        std::cin >> id_new;
        for ( const auto& st : vec )
        {
            if ( st.GetId() == id_new )
            {
                std::cout << "Such id already exists.\n";
                return;
            }
        }
        vec[ind].SetId( id_new );
        break;
    case 2:
    {
        std::string studentName;
        std::cout << "(edit) Input student name: ";
        std::getline( std::cin >> std::ws, studentName );
        vec[ind].SetName( studentName );
        break;
    }
    case 3:
        int courseId;
        std::cout << "(edit) Select course:\n";
        courseId = Course::SelectCourse();
        vec[ind].SetCourseId( courseId );
        break;
    case 4:
    {
        std::cout << "(edit) Input course start date in format dd/mm/yyyy: ";
        long startDate = InputDate();

        if ( startDate > vec[ind].GetEndDate() )
        {
            std::cout << "ERROR: Start date cannot be later than end date. Enter end date first.\n";
            return;
        }
        vec[ind].SetStartDate( startDate );
        break;
    }
    case 5:
    {
        std::cout << "(edit) Input course end date in format dd/mm/yyyy: ";
        long endDate = InputDate();
        if ( endDate < vec[ind].GetStartDate() )
        {
            std::cout << "ERROR: End date cannot be earlier than start date. Enter end date first.\n";
            return;
        }
        vec[ind].SetEndDate( endDate );
        break;
    }
    default:
        EditMarks( vec, ind );

    }
    std::cout << "(edit) Changes saved.\n";
}

void ReadFile(std::vector<Student>& vec)
{
    std::cout << "=== READ FROM FILE ===\n";

    std::string filename;
    std::cout << "(read file) Enter the filename: ";

    std::getline( std::cin >> std::ws, filename );

    std::string line;
    std::ifstream studentsFile( filename );

    int studentsAdded = 0;
    if ( studentsFile.is_open() )
    {
        while ( std::getline( studentsFile, line ) )
        {
            Student st = Student::FromInfo( line );
            bool bExist = false;
            for ( const auto& s : vec )
            {
                if ( s.GetId() == st.GetId() )
                {
                    bExist = true;
                    break;
                }
            }
            if ( !bExist )
            {
                vec.emplace_back( st );
                studentsAdded++;
            }
        }
        studentsFile.close();
    }
    else
    {
        std::cout << "Unable to open file with students\n";
    }

    std::cout << "\n  STUDENTS ADDED: " << studentsAdded << "\n\n";

}

void ViewTranscript( std::vector<Student>& vec)
{
    std::cout << "=== VIEW TRANSCRIPT ===\n";
    for ( const auto& st : vec )
    {
        std::cout << st.Info() << "\n";
    }
    std::cout << "\n\n";
}

void ShowMainMenu()
{
	std::cout << "Created By the Little Einsteins\n\n\n";
    std::cout << "1. ADD A NEW RECORD\n";
    std::cout << "2. EDIT AN EXISTING RECORD\n";
    std::cout << "3. READ FILE\n";
    std::cout << "4. VIEW STUDENT TRANSCRIPT\n";
    std::cout << "5. EXIT\n";
}

std::size_t EnterOption()
{
    std::size_t option = 0;

    do
    {
        std::cout << "\n   Enter option: ";
        std::cin >> option;

        if ( option < ADD || option > EXIT )
        {
            option = 0;
            std::cout << "ERROR: Incorrect option. Try again.\n";
        }
    }
    while ( !option );

    return option;
}

int main()
{
    std::size_t option;
    std::cout << "\n\nWELCOME TO STUDENT ENROLLMENT\n";

    std::vector<Student> vec = ReadData();

    do
    {
        ShowMainMenu();
        option = EnterOption();

        switch ( option )
        {
        case ADD:
            AddStudent( vec );
            break;
        case EDIT:
            EditStudent(vec);
            break;
        case READ:
            ReadFile(vec);
            break;
        case VIEW:
            ViewTranscript(vec);
            break;
        default: break;
        }
    }
    while ( option != EXIT );

    UpdateData( vec );


    return 0;
}
