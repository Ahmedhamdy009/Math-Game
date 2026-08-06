#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

enum enOperationType
{
    Add = 1,
    Sub = 2,
    Mul = 3,
    Div = 4,
    MixOp = 5
};

enum enQuestionLevel
{
    Easy = 1,
    Mid = 2,
    Hard = 3,
    Mix = 4
};

int GetRandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

string GetOpTypeSymbol(enOperationType OperationType)
{
    switch (OperationType)
    {
    case Add: return "+";
    case Sub: return "-";
    case Mul: return "*";
    case Div: return "/";
    default: return "Mix";
    }
}

string GetQuestionLevelText(enQuestionLevel QuestionLevel)
{
    string arrQuestionLevel[4] = { "Easy", "Mid", "Hard", "Mix" };
    return arrQuestionLevel[QuestionLevel - 1];
}

void SetScreenColor(bool Right)
{
    if (Right)
        system("color 2F");
    else
    {
        system("color 4F");
        cout << "\a";
    }
}

short ReadHowManyQuestions()
{
    short NumberOfQuestions;
    do
    {
        cout << "How Many Questions do you want to answer ? ";
        cin >> NumberOfQuestions;
    } while (NumberOfQuestions < 1 || NumberOfQuestions > 10);
    return NumberOfQuestions;
}

enQuestionLevel ReadQuestionLevel()
{
    short QuestionLevel;
    do
    {
        cout << "Enter Question Level [1]Easy, [2]Med, [3]Hard, [4]Mix ? ";
        cin >> QuestionLevel;
    } while (QuestionLevel < 1 || QuestionLevel > 4);
    return (enQuestionLevel)QuestionLevel;
}

enOperationType ReadOperationType()
{
    short OperationType;
    do
    {
        cout << "Enter Operation Type [1]Add, [2]Sub, [3]Mul, [4]Div, [5]Mix ? ";
        cin >> OperationType;
    } while (OperationType < 1 || OperationType > 5);
    return (enOperationType)OperationType;
}

struct stQuestion
{
    int Number1;
    int Number2;
    enOperationType OperationType;
    enQuestionLevel QuestionLevel;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};

struct stQuizz
{
    stQuestion QuestionList[100];
    short NumberOfQuestion;
    enQuestionLevel QuestionLevel;
    enOperationType OperationType;
    short NumberOfRightAnswer = 0;
    short NumberOfWrongAnswer = 0;
    bool isPass = false;
};

int SimpleCalculation(int Number1, int Number2, enOperationType OpType)
{
    switch (OpType)
    {
    case Add:
        return Number1 + Number2;
    case Sub:
        return Number1 - Number2;
    case Mul:
        return Number1 * Number2;
    case Div:
        return Number1 / Number2;
    default:
        return Number1 + Number2;
    }
}

enOperationType GetRandomOperationType()
{
    return (enOperationType)GetRandomNumber(1, 4);
}

stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OperationType)
{
    stQuestion Question;

    if (QuestionLevel == Mix)
        QuestionLevel = (enQuestionLevel)GetRandomNumber(1, 3);

    if (OperationType == MixOp)
        OperationType = GetRandomOperationType();

    Question.OperationType = OperationType;
    Question.QuestionLevel = QuestionLevel;

    if (OperationType == Div)
    {
        int Answer = 0;

        switch (QuestionLevel)
        {
        case Easy:
            Answer = GetRandomNumber(1, 10);
            Question.Number2 = GetRandomNumber(1, 10);
            break;
        case Mid:
            Answer = GetRandomNumber(10, 30);
            Question.Number2 = GetRandomNumber(2, 10);
            break;
        case Hard:
            Answer = GetRandomNumber(10, 50);
            Question.Number2 = GetRandomNumber(2, 20);
            break;
        }

        Question.Number1 = Question.Number2 * Answer;
    }
    else
    {
        switch (QuestionLevel)
        {
        case Easy:
            Question.Number1 = GetRandomNumber(1, 10);
            Question.Number2 = GetRandomNumber(1, 10);
            break;
        case Mid:
            Question.Number1 = GetRandomNumber(10, 50);
            Question.Number2 = GetRandomNumber(10, 50);
            break;
        case Hard:
            Question.Number1 = GetRandomNumber(50, 100);
            Question.Number2 = GetRandomNumber(50, 100);
            break;
        }
    }

    Question.CorrectAnswer = SimpleCalculation(Question.Number1, Question.Number2, Question.OperationType);
    return Question;
}

void GenerateQuizzQuestion(stQuizz& Quizz)
{
    for (short Question = 0; Question < Quizz.NumberOfQuestion; Question++)
        Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionLevel, Quizz.OperationType);
}

int ReadQuestionAnswer()
{
    int Answer = 0;
    cin >> Answer;
    return Answer;
}

void PrintTheQuestion(const stQuizz& Quizz, short QuestionNumber)
{
    cout << "\n";
    cout << "Question[" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestion << "]" << endl;
    cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
    cout << Quizz.QuestionList[QuestionNumber].Number2 << " " << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType) << endl;
    cout << "----------------\n";
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
    if (Quizz.QuestionList[QuestionNumber].PlayerAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnswer++;
        cout << "Wrong Answer :(" << endl;
        cout << "The Right Answer is : " << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
    }
    else
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfRightAnswer++;
        cout << "Right Answer :)" << endl;
    }

    cout << endl;
    SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestion; QuestionNumber++)
    {
        PrintTheQuestion(Quizz, QuestionNumber);
        Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
        CorrectTheQuestionAnswer(Quizz, QuestionNumber);
    }

    Quizz.isPass = (Quizz.NumberOfRightAnswer >= Quizz.NumberOfWrongAnswer);
}

string GetFinalResult(bool Pass)
{
    return Pass ? "Pass :)" : "Fail :(";
}

void PrintQuizzResults(const stQuizz& Quizz)
{
    cout << "\n";
    cout << "----------------------------------------------------------------\n\n";
    cout << "Final Result is " << GetFinalResult(Quizz.isPass) << endl;
    cout << "----------------------------------------------------------------\n\n";
    cout << "Number Of Question : " << Quizz.NumberOfQuestion << endl;
    cout << "Question Level : " << GetQuestionLevelText(Quizz.QuestionLevel) << endl;
    cout << "Operation Type : " << GetOpTypeSymbol(Quizz.OperationType) << endl;
    cout << "Number of Right Answer : " << Quizz.NumberOfRightAnswer << endl;
    cout << "Number of Wrong Answer : " << Quizz.NumberOfWrongAnswer << endl;
    cout << "----------------------------------------------------------------\n\n";
}

void PlayMathGame()
{
    stQuizz Quizz;
    Quizz.NumberOfQuestion = ReadHowManyQuestions();
    Quizz.QuestionLevel = ReadQuestionLevel();
    Quizz.OperationType = ReadOperationType();

    GenerateQuizzQuestion(Quizz);
    AskAndCorrectQuestionListAnswers(Quizz);
    PrintQuizzResults(Quizz);
}

void ResetScreen()
{
    system("cls");
    system("color 0F");
}

void StartGame()
{
    char PlayAgain = 'Y';
    do
    {
        ResetScreen();
        PlayMathGame();
        cout << endl << "Do you want to play again? Y/N? ";
        cin >> PlayAgain;
    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}
