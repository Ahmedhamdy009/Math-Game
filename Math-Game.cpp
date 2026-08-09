/*
===============================================================================
Project      : Math Game
Version      : 1.0
Language     : C++
Author       : Ahmed Hamdy
Created      : 9 August 2026

Description:
A console-based Math Game implemented in C++.
The project generates random math questions based on the selected
question level and operation type, checks the player's answers,
and displays the final game result.

Key Concepts:
- Functions
- Structs
- Enums
- Arrays
- Loops
- Random Number Generation
- Pass by Reference
- Basic Problem Solving

===============================================================================
*/

#include <string>
#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

enum enQuestionsLevel { Easy = 1, Med = 2, Hard = 3, Mix = 4 };

enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOp = 5 };

// Constants
const short MaxQuestions = 10;

struct stQuestion
{
    int Number1;
    int Number2;
    enQuestionsLevel QuestionLevel;
    enOperationType OperationType;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult = false;
};

struct stQuiz
{
    stQuestion QuestionList[MaxQuestions];
    short NumberOfQuestion;
    enQuestionsLevel QuestionLevel;
    enOperationType OperationType;
    short NumberOfRightAnswer = 0;
    short NumberOfWrongAnswer = 0;
    bool isPass = false;
};

// Input Functions
short ReadHowManyQuestions()
{
    short Number = 0;

    do
    {
        cout << "How Many Questions do you want to answer ? ";
        cin >> Number;
    } while (Number < 1 || Number > MaxQuestions);

    return Number;
}

enQuestionsLevel ReadQuestionsLevel()
{
    short Choice;

    do
    {
        cout << "Enter Questions Level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 4);

    return (enQuestionsLevel)Choice;
}

enOperationType ReadOperationType()
{
    short Choice;

    do
    {
        cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5] MixOp ? ";
        cin >> Choice;
    } while (Choice < 1 || Choice > 5);

    return (enOperationType)Choice;
}

// Random Functions
int RandomNumbers(int From, int To)
{
    int RandomNumbers = From + rand() % (To - From + 1);
    return RandomNumbers;
}

enOperationType GetRandomOperationType()
{
    return (enOperationType)RandomNumbers(1, 4);
}

// Display Helper Functions
string GetOpTypeSymbol(enOperationType OpType)
{
    string arrOpTypeSymbol[5] = { "+", "-", "*", "/", "Mix" };
    return arrOpTypeSymbol[OpType - 1];
}

string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
{
    string arrQuestionLevelText[4] = { "Easy", "Medium", "Hard", "Mixed" };
    return arrQuestionLevelText[QuestionLevel - 1];
}

void ChangeScreenColor(bool Right)
{
    if (Right)
        system("color 2F");
    else
        system("color 4F");
}

void ResetScreen()
{
    system("color 0F");
    system("cls");
}

// Calculation
int SimpleCalculator(int Number1, int Number2, enOperationType OperationType)
{
    switch (OperationType)
    {
    case enOperationType::Add:
        return Number1 + Number2;

    case enOperationType::Sub:
        return Number1 - Number2;

    case enOperationType::Mul:
        return Number1 * Number2;

    case enOperationType::Div:
        return (Number2 != 0) ? (Number1 / Number2) : 0;

    default:
        return Number1 + Number2;
    }
}

// Question Generation
stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OperationType)
{
    stQuestion Question;

    if (QuestionLevel == enQuestionsLevel::Mix)
    {
        QuestionLevel = (enQuestionsLevel)RandomNumbers(1, 3);
    }

    if (OperationType == enOperationType::MixOp)
    {
        OperationType = GetRandomOperationType();
    }

    Question.OperationType = OperationType;
    Question.QuestionLevel = QuestionLevel;

    switch (QuestionLevel)
    {
    case enQuestionsLevel::Easy:
        Question.Number1 = RandomNumbers(1, 10);
        Question.Number2 = RandomNumbers(1, 10);
        break;

    case enQuestionsLevel::Med:
        Question.Number1 = RandomNumbers(10, 50);
        Question.Number2 = RandomNumbers(10, 50);
        break;

    case enQuestionsLevel::Hard:
        Question.Number1 = RandomNumbers(50, 100);
        Question.Number2 = RandomNumbers(50, 100);
        break;

    default:
        Question.Number1 = RandomNumbers(1, 10);
        Question.Number2 = RandomNumbers(1, 10);
        break;
    }

    // Make division questions produce exact integer answers.
    if (Question.OperationType == Div)
    {
        Question.Number1 *= Question.Number2;
    }

    Question.CorrectAnswer = SimpleCalculator(
        Question.Number1,
        Question.Number2,
        Question.OperationType
    );

    return Question;
}

void GenerateQuizQuestion(stQuiz& Quiz)
{
    for (short Question = 0; Question < Quiz.NumberOfQuestion; Question++)
    {
        Quiz.QuestionList[Question] = GenerateQuestion(
            Quiz.QuestionLevel,
            Quiz.OperationType
        );
    }
}

// Question Handling
int ReadPlayerAnswer()
{
    int Answer;

    cout << "Your Answer: ";
    cin >> Answer;

    return Answer;
}

void PrintTheQuestion(stQuiz& Quiz, short QuestionNumber)
{
    cout << endl;
    cout << "Question[" << QuestionNumber + 1 << "/" << Quiz.NumberOfQuestion << "]" << endl;
    cout << Quiz.QuestionList[QuestionNumber].Number1 << endl;
    cout << GetOpTypeSymbol(Quiz.QuestionList[QuestionNumber].OperationType) << endl;
    cout << Quiz.QuestionList[QuestionNumber].Number2 << endl;
    cout << "----------------\n";
}

void CorrectTheQuestionAnswer(stQuiz& Quiz, short QuestionNumber)
{
    if (Quiz.QuestionList[QuestionNumber].PlayerAnswer == Quiz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        Quiz.QuestionList[QuestionNumber].AnswerResult = true;
        Quiz.NumberOfRightAnswer++;
        cout << "Right Answer :) ";
    }
    else
    {
        Quiz.QuestionList[QuestionNumber].AnswerResult = false;
        Quiz.NumberOfWrongAnswer++;
        cout << "Wrong Answer :( ";
        cout << "The Right Answer is : ";
        cout << Quiz.QuestionList[QuestionNumber].CorrectAnswer << endl;
    }

    cout << endl;
    ChangeScreenColor(Quiz.QuestionList[QuestionNumber].AnswerResult);
}

// Results
string GetFinalResult(bool Pass)
{
    return Pass ? "Pass :)" : "Fail :(";
}

void PrintFinalResults(stQuiz Quiz)
{
    cout << "\n=================================\n";
    cout << "Final Results is " << GetFinalResult(Quiz.isPass) << endl;
    cout << "=================================\n";

    cout << "Number of Questions : " << Quiz.NumberOfQuestion << endl;
    cout << "Question Level      : " << GetQuestionLevelText(Quiz.QuestionLevel) << endl;
    cout << "Operation Type      : " << GetOpTypeSymbol(Quiz.OperationType) << endl;
    cout << "Right Answers       : " << Quiz.NumberOfRightAnswer << endl;
    cout << "Wrong Answers       : " << Quiz.NumberOfWrongAnswer << endl;
    cout << "=========================================================\n";
}

// Game Control
void AskAndCorrectQuestionListAnswers(stQuiz& Quiz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quiz.NumberOfQuestion; QuestionNumber++)
    {
        PrintTheQuestion(Quiz, QuestionNumber);
        Quiz.QuestionList[QuestionNumber].PlayerAnswer = ReadPlayerAnswer();
        CorrectTheQuestionAnswer(Quiz, QuestionNumber);
    }

    Quiz.isPass = (Quiz.NumberOfRightAnswer >= Quiz.NumberOfWrongAnswer);
}

void PlayGame()
{
    stQuiz Quiz;

    Quiz.NumberOfQuestion = ReadHowManyQuestions();
    Quiz.QuestionLevel = ReadQuestionsLevel();
    Quiz.OperationType = ReadOperationType();

    GenerateQuizQuestion(Quiz);
    AskAndCorrectQuestionListAnswers(Quiz);
    PrintFinalResults(Quiz);
}

void StartGame()
{
    char PlayAgain = 'Y';

    do
    {
        ResetScreen();
        PlayGame();

        cout << "\nDo you want to play again? [Y/N] ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));
    StartGame();

    return 0;
}