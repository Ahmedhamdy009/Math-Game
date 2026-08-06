#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

enum enQuestionLevel
{
    Easy = 1,
    Medium = 2,
    Hard = 3,
    MixLevel = 4
};

enum enOperationType
{
    Add = 1,
    Sub = 2,
    Mul = 3,
    Div = 4,
    MixOperation = 5
};

struct stQuestion
{
    int Num1 = 0;
    int Num2 = 0;
    enQuestionLevel Level = Easy;
    enOperationType Operation = Add;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool IsCorrect = false;
};

struct stGame
{
    stQuestion Questions[100];
    short NumberOfQuestions = 0;
    enQuestionLevel Level = Easy;
    enOperationType Operation = Add;
    short RightAnswers = 0;
    short WrongAnswers = 0;
    bool Pass = false;
};

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

short ReadNumberOfQuestions()
{
    short Number;
    do
    {
        cout << "How many questions do you want to answer? ";
        cin >> Number;
    } while (Number < 1 || Number > 100);
    return Number;
}

enQuestionLevel ReadQuestionLevel()
{
    short Choice;
    do
    {
        cout << "Enter Question Level [1]Easy, [2]Medium, [3]Hard, [4]Mix: ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 4);
    return (enQuestionLevel)Choice;
}

enOperationType ReadOperationType()
{
    short Choice;
    do
    {
        cout << "Enter Operation Type [1]Add, [2]Sub, [3]Mul, [4]Div, [5]Mix: ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 5);
    return (enOperationType)Choice;
}

string LevelName(enQuestionLevel Level)
{
    switch (Level)
    {
    case Easy: return "Easy";
    case Medium: return "Medium";
    case Hard: return "Hard";
    default: return "Mix";
    }
}

string OperationSymbol(enOperationType Operation)
{
    switch (Operation)
    {
    case Add: return "+";
    case Sub: return "-";
    case Mul: return "*";
    case Div: return "/";
    default: return "Mix";
    }
}

enOperationType RandomOperation()
{
    return (enOperationType)RandomNumber(1, 4);
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

int CalculateAnswer(int Num1, int Num2, enOperationType Operation)
{
    switch (Operation)
    {
    case Add: return Num1 + Num2;
    case Sub: return Num1 - Num2;
    case Mul: return Num1 * Num2;
    case Div: return Num1 / Num2;
    default: return 0;
    }
}

stQuestion GenerateQuestion(enQuestionLevel Level, enOperationType Operation)
{
    stQuestion Question;

    if (Level == MixLevel)
        Level = (enQuestionLevel)RandomNumber(1, 3);

    if (Operation == MixOperation)
        Operation = RandomOperation();

    Question.Level = Level;
    Question.Operation = Operation;

    switch (Level)
    {
    case Easy:
        Question.Num1 = RandomNumber(1, 10);
        Question.Num2 = RandomNumber(1, 10);
        break;
    case Medium:
        Question.Num1 = RandomNumber(10, 50);
        Question.Num2 = RandomNumber(10, 50);
        break;
    case Hard:
        Question.Num1 = RandomNumber(50, 100);
        Question.Num2 = RandomNumber(50, 100);
        break;
    }

    if (Operation == Div)
    {
        Question.Num2 = RandomNumber(1, 10);
        int Answer = RandomNumber(1, 10);
        Question.Num1 = Question.Num2 * Answer;
    }

    Question.CorrectAnswer = CalculateAnswer(Question.Num1, Question.Num2, Question.Operation);
    return Question;
}

void GenerateQuestions(stGame& Game)
{
    for (int i = 0; i < Game.NumberOfQuestions; i++)
        Game.Questions[i] = GenerateQuestion(Game.Level, Game.Operation);
}

void SetScreenColor(bool IsCorrect)
{
    if (IsCorrect)
        system("color 2F");
    else
    {
        system("color 4F");
        cout << "\a";
    }
}

void PrintQuestion(const stQuestion& Question, short QuestionNumber, short TotalQuestions)
{
    cout << "\nQuestion [" << QuestionNumber << "/" << TotalQuestions << "]\n\n";
    cout << Question.Num1 << endl;
    cout << Question.Num2 << " " << OperationSymbol(Question.Operation) << endl;
    cout << "------------------------\n";
}

int ReadAnswer()
{
    int Answer;
    cin >> Answer;
    return Answer;
}

void CheckAnswer(stGame& Game, short Index)
{
    Game.Questions[Index].PlayerAnswer = ReadAnswer();

    if (Game.Questions[Index].PlayerAnswer == Game.Questions[Index].CorrectAnswer)
    {
        Game.Questions[Index].IsCorrect = true;
        Game.RightAnswers++;
        cout << "\nRight Answer :-)\n";
        SetScreenColor(true);
    }
    else
    {
        Game.Questions[Index].IsCorrect = false;
        Game.WrongAnswers++;
        cout << "\nWrong Answer :-(\n";
        cout << "The Right Answer is : " << Game.Questions[Index].CorrectAnswer << endl;
        SetScreenColor(false);
    }
}

void PlayGame(stGame& Game)
{
    GenerateQuestions(Game);

    for (short i = 0; i < Game.NumberOfQuestions; i++)
    {
        PrintQuestion(Game.Questions[i], i + 1, Game.NumberOfQuestions);
        Game.Questions[i].PlayerAnswer = ReadAnswer();
        CheckAnswer(Game, i);
    }

    Game.Pass = (Game.RightAnswers >= Game.WrongAnswers);
}

string GetFinalResult(bool Pass)
{
    return Pass ? "PASS :-)" : "FAIL :(";
}

void PrintGameResult(const stGame& Game)
{
    cout << "\n\n=========================================\n";
    cout << "             FINAL RESULT\n";
    cout << "=========================================\n";
    cout << "Result            : " << GetFinalResult(Game.Pass) << endl;
    cout << "Questions         : " << Game.NumberOfQuestions << endl;
    cout << "Level             : " << LevelName(Game.Level) << endl;
    cout << "Operation         : " << OperationSymbol(Game.Operation) << endl;
    cout << "Right Answers     : " << Game.RightAnswers << endl;
    cout << "Wrong Answers     : " << Game.WrongAnswers << endl;
    cout << "=========================================\n";
}

void StartOneGame()
{
    stGame Game;
    Game.NumberOfQuestions = ReadNumberOfQuestions();
    Game.Level = ReadQuestionLevel();
    Game.Operation = ReadOperationType();
    PlayGame(Game);
    PrintGameResult(Game);
}

void StartGame()
{
    char PlayAgain = 'Y';
    do
    {
        ResetScreen();
        StartOneGame();
        cout << "\nPlay Again? (Y/N): ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}